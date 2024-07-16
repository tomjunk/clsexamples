// standalone C++ program for computing CLs limits on possible signal
// in the presence of background.  Scan over nobs and b and make text output
// standalone software -- needs only C++ standard libraries

// to compile:   g++ -O -o celim celim.C
//     or use clang

#include <iostream>
#include <cmath>

double cls(int n, double b, double s);
double slimit(int n, double b, double cl);
double factorial(int n);
double ppoiss(int n, double r);

#define DEBUG 0

int main(int, char **)
{
  double blow = 0.0;
  double bhigh = 20;
  double db = 0.01;
  double cl = 0.95;
  int nlow=0;
  int nhigh=10;

  int nbsamples = (bhigh - blow)/db;
  for (int ibsample=0; ibsample<nbsamples; ++ibsample)
    {
      double b = blow + ibsample * db;
      for (int n=nlow; n<=nhigh; ++n)
	{
	  double slim = slimit(n,b,cl);
	  std::cout << cl << " " << n << " " << b << " " << slim << std::endl;
	}
    }
}

double ppoiss(int n, double r)
{
  if (r < 0)
    {
      std::cout << "Poisson probability of negative number requested: " << r << std::endl;
      exit(1);
    }
  double p = std::pow(r,n)*std::exp(-r)/factorial(n);
  return p;
}

double factorial(int n)
{
  if (n<0)
    {
      std::cout << "problem taking fatorial of: " << n << std::endl;
      exit(1);
    }
  double f = 1.0;
  for (int i=2; i<=n; ++i)
    {
      f *= i;
    }
  return f;
}

// cls calculator for a single counting experiment

double cls(int n, double b, double s)
{
  double clsb = 0;
  double clb = 0;    // clb is 1-p0, the null hypothesis p-value, though it includes the 

  for (int i=0; i<=n; ++i)
    {
      clsb += ppoiss(i,s+b);
      clb += ppoiss(i,b);
    }
  double clsret = clsb/clb;

  if (DEBUG)
    {
      std::cout << "In CLs calc: " << s << " " << b << " " << n << " " << clsb << " " << clb << " " << clsret << std::endl;
    }
  return clsret;
}

// find the signal s such that cls(n, b) = 1-cl.
// do a binary search at the moment -- improve to do Newton's method later if necessary

double slimit(int n, double b, double cl)
{
  double slow = 0;
  double shigh = 1.0;
  double desiredprecision = 1E-8;

  
  double clsslow = cls(n,b,slow);
  double clsshigh = cls(n,b,shigh);
  
  do
    {
      if (DEBUG)
	{
	  std::cout << "in limit loop: " << slow << " " << shigh << " " << n << " " << b << " " << clsslow << " " << clsshigh << std::endl;
	}
      if (clsshigh > 1.0-cl)
	{
	  shigh *= 2.0;
	  clsshigh = cls(n,b,shigh);
	  if (shigh > 1000)
	    {
	      std::cout << "slimit -- exploring a very large signal: " << n << " " << b << " " << shigh << std::endl;
	      exit(1);
	    }
	}
      else
	{
	  double smid = (slow + shigh)/2.0;
	  double clsmid = cls(n,b,smid);
	  if (clsmid < 1.0-cl)
	    {
	      shigh = smid;
	      clsshigh = clsmid;
	    }
	  else
	    {
	      slow = smid;
	      clsslow = clsmid;
	    }
	}
    }
  while (shigh - slow > desiredprecision);
  
  double savg = (shigh + slow)/2.0;
  return savg;
}
