#include "common.h"

void dNdEta_vs_roots_fit() {
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogon.C");


  bool ErrorFlag = false;

  //****************************************************
  Bool_t bw = 1;       // 1: BLACK AND WHITE, 0: COLOR
  Float_t msize = 1.; // MARKER SIZE
  //****************************************************
  
  TCanvas *c = new TCanvas("c","c",550,600);

  //  gStyle->SetTitleYSize(.060);
  gStyle->SetTitleYOffset(1.4);

  c->SetLogx();
  //  c->SetLeftMargin(0.15);

  TH1F *dummy = new TH1F("dummy","dummy",100,9,10000);
  dummy->SetMaximum(7.5);
  dummy->SetMinimum(0);
  dummy->SetXTitle("#sqrt{s} [GeV]");
  dummy->SetYTitle("dN_{ch}/d#eta|_{#eta=0}");
  /*
  dummy->GetYaxis()->SetNdivisions(505);
  dummy->GetXaxis()->SetNdivisions(505);
  dummy->GetXaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetXaxis()->SetTitleSize(0.05);
  dummy->GetYaxis()->SetTitleSize(0.05);
  dummy->GetXaxis()->SetLabelOffset(0.00);
  dummy->GetXaxis()->SetTitleOffset(1.0);
  dummy->GetYaxis()->SetTitleOffset(0.75);
   */
  dummy->GetYaxis()->CenterTitle();
  dummy->GetXaxis()->CenterTitle();
  dummy->Draw();

  Int_t N = 100;
  Int_t ip = 0;

  // ---- UA5 NSD ---
  TGraphErrors *gre = new TGraphErrors(N);
  gre->SetName("Graph");
  gre->SetTitle("Graph");

  gre->SetMarkerStyle(kFullCircle);
  gre->SetMarkerSize(msize);

  gre->SetPoint(ip,51.5,1.982);
  gre->SetPoint(++ip,200,2.474);
  gre->SetPoint(++ip,532,3.047);
  gre->SetPoint(++ip,886,3.478);

  // ---- CDF NSD ----
  gre->SetPoint(++ip,630,3.18);
  gre->SetPoint(++ip,1800,3.95);

  // ---- UA1 NSD ---
  gre->SetPoint(++ip,200,2.65);
  gre->SetPoint(++ip,260,2.71);
  gre->SetPoint(++ip,380,2.94);
  gre->SetPoint(++ip,500,3.05);
  gre->SetPoint(++ip,620,3.15);
  gre->SetPoint(++ip,790,3.41);
  gre->SetPoint(++ip,900,3.48);

  // ---- ALICE NSD ------
  gre->SetPoint(++ip,900,3.51);

  // ---- CMS NSD ---
  gre->SetPoint(++ip,900,3.4984);
  gre->SetPoint(++ip,2360,4.46);

  // ---- STAR NSD ----
  gre->SetPoint(++ip,200,2.98);
  gre->SetPointError(ip,200,0.34);

  gre->Draw("p");

  // fit
   //TF1 *func = new TF1("func","[0]+[1]*log(x^2)+[2]*(log(x^2))^2",18,100000);
   TF1 *func = new TF1("func","[0]+[1]*exp(sqrt(log(x^2)))",18,100000);
   func->SetLineColor(1);
   func->SetLineWidth(1.5);
   //func->SetParameters(2,-0.2,0.02);
   gre->Fit("func","wR","",18,3000);
   func->Draw("same");
   func->Print();
}

