#include "TLatex.h"

void printFinalCanvases(TCanvas * MyCanvas, char * name)
{
  MyCanvas->cd();

  // add some text labels
  double ndcX = 0.2;
  double ndcY = 0.9;

  TLatex *tex = new TLatex(0.85,ndcY,"CMS");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();

  TLatex *tex2 = new TLatex(0.85-0.132,ndcY-0.045,"#sqrt{s}=900 GeV");
  tex2->SetTextSize(0.04);
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();


  MyCanvas->Print(Form("%s.eps"),name);
  MyCanvas->Print(Form("%s.gif"),name);
  MyCanvas->Print(Form("%s.pdf"),name);

  tex = new TLatex(ndcX,ndcY,"(a)");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();

  MyCanvas->Print(Form("%s_A.eps"),name);
  MyCanvas->Print(Form("%s_A.gif"),name);
  MyCanvas->Print(Form("%s_A.pdf"),name);

  tex->Delete();
  tex = new TLatex(ndcX,ndcY,"(b)");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();

  MyCanvas->Print(Form("%s_B.eps"),name);
  MyCanvas->Print(Form("%s_B.gif"),name);
  MyCanvas->Print(Form("%s_B.pdf"),name);
}
