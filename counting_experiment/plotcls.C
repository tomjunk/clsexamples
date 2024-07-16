
// ROOT macro for plotting limits

{
  TLatex *tl1 = (TLatex*) new TLatex;
  TCanvas *mycanvas = (TCanvas*) new TCanvas("c1","c1",800,400);
  mycanvas->Divide(2,1);
  mycanvas->cd(1);
  TTree *t90 = (TTree*) new TTree("cls","cls");
  t90->ReadFile("celim_90percent.output","cl/F:n/I:b/F:slim/F");
  t90->Draw("slim:b");
  tl1->DrawLatex(7,10,"90% CL CLs Limits");
  
  mycanvas->cd(2);
  TTree *t95 = (TTree*) new TTree("cls","cls");
  t95->ReadFile("celim_95percent.output","cl/F:n/I:b/F:slim/F");
  t95->Draw("slim:b");
  tl1->DrawLatex(7,12,"95% CL CLs Limits");

  mycanvas->Print("clslimits9095.png");
}
