// standalone C++ program for computing Bayesian limits on possible signal
// in the presence of background, assuming a uniform prior for the signal strenght.
// Scan over nobs and b and make text output
// standalone software -- needs only C++ standard libraries

// to compile:   g++ -O -o bayeslim bayeslim.C
//     or use clang

#include <iostream>
#include <cmath>
#include <vector>

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
  double cl = 0.90;
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

// find the signal s such that the integral of the posterior is CL

double slimit(int n, double b, double cl)
{
  double slow = 0;
  double shigh = 50;  // integrate this far to get posterior
  double ds=0.001;
  int ns = (shigh-slow)/ds;

  std::vector<double> post;
  double sum=0.0;
  for (int i=0; i<ns; ++i)
    {
      double s = slow + ds*i;
      post.push_back(ppoiss(n,s+b));
      sum += post.back();
    }
  double psum = 0;
  for (int i=0;i<ns;++i)
    {
      psum += post.at(i)/sum;
      if (psum>cl)
	{
	  return (slow+ds*i);
	}
    }
  return 0;
}
