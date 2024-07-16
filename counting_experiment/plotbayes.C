
// ROOT macro for plotting limits

{
  TLatex *tl1 = (TLatex*) new TLatex;
  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",800,400);
  mycanvas->Divide(2,1);
  mycanvas->cd(1);
  TTree *t90 = (TTree*) new TTree("cls","cls");
  t90->ReadFile("bayeslim90.output","cl/F:n/I:b/F:slim/F");
  t90->Draw("slim:b");
  tl1->DrawLatex(7,10,"90% CL Bayesian Limits");
  
  mycanvas->cd(2);
  TTree *t95 = (TTree*) new TTree("cls","cls");
  t95->ReadFile("bayeslim95.output","cl/F:n/I:b/F:slim/F");
  t95->Draw("slim:b");
  tl1->DrawLatex(7,12,"95% CL Bayesian Limits");

  mycanvas->Print("bayeslimits9095.png");
}
