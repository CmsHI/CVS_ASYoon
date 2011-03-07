void plotMultVtxPAS() {

  //gROOT->Macro("/net/hisrv0001/home/edwenger/CMSSW_3_7_0/src/UserCode/ASYoon/dNdEtaPlotMacrosV2/paper/rootlogon.C");

  //TFile *f = new TFile("/net/hibat0003/d00/scratch/frankma/data/MinimumBias/MB-C10-PR9-TRKANASKIM-v3/all/trkhists_histOnly_all.root");
  TFile *f = new TFile("../root_files/trkhists_histOnly_all.root");

  //set_plot_style();

  TH2F *h2 = (TH2F*) f->Get("postTrkVtxSel/hMultVtxZ");
  h2->SetTitle(";z_{PV}^{0} [cm];z_{PV}^{1} [cm]");
  h2->SetStats(0);
  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetRangeUser(-17,17);
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetRangeUser(-17,17);
  h2->SetMinimum(0.9);

  //TCanvas *pas = new TCanvas("pas","pas",520,550);
  //TCanvas *pas = new TCanvas("pas","pas",567,622);
  TCanvas *pas = new TCanvas("pas","pas",480,550); 
  gPad->SetLogz();
  gPad->SetRightMargin(0.14);
  h2->Draw("contz");
  //h2->Draw("colz");

  //TLatex *tex = new TLatex(0.66,0.86,"CMS Preliminary");
  TLatex *tex = new TLatex(0.55,0.90,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  //tex->Draw();

  //TLatex *tex2 = new TLatex(0.68,0.78,"#intLdt = 10.2 nb^{-1}");
  TLatex *tex2 = new TLatex(0.59,0.88,"#intLdt = 10.2 nb^{-1}");
  tex2->SetTextSize(0.033);
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();

  TLatex *tex3 = new TLatex(0.27,0.88,"#sqrt{s} = 7 TeV");
  tex3->SetTextSize(0.033);
  tex3->SetLineWidth(2);
  tex3->SetNDC();
  tex3->Draw();
  
  TLatex * texB;
  texB= new TLatex(0.2,0.88,"(b)");
  texB->SetTextSize(0.04);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();

  pas->Print("./fig/multVtxZ_bothGood.gif");
  pas->Print("./fig/multVtxZ_bothGood.pdf");

}


void plotMultVtx() {

  //gROOT->Macro("/net/hisrv0001/home/edwenger/CMSSW_3_7_0/src/UserCode/ASYoon/dNdEtaPlotMacrosV2/paper/rootlogon.C");
  gStyle->SetOptStat(0);
  //set_plot_style();

  //TFile *f = new TFile("/net/hibat0003/d00/scratch/frankma/data/MinimumBias/MB-C10-PR9-TRKANASKIM-v3/all/trkhists_histOnly_all.root");
  TFile *f = new TFile("../root_files/trkhists_histOnly_all.root");

  TLatex *tex = new TLatex(0.52,0.83,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();

  TH2F *h1 = (TH2F*) f->Get("preVtxSel/hMultVtxZ");
  h1->SetTitle(";z_{PV}^{0} [cm];z_{PV}^{1} [cm]");
  h1->GetXaxis()->CenterTitle();
  h1->GetXaxis()->SetRangeUser(-17,17);
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetRangeUser(-17,17);

  TH2F *h2 = (TH2F*) f->Get("postTrkVtxSel/hMultVtxZ");
  h2->SetTitle(";z_{PV}^{0} [cm];z_{PV}^{1} [cm]");
  h2->GetXaxis()->CenterTitle();
  h2->GetXaxis()->SetRangeUser(-17,17);
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetRangeUser(-17,17);

  TH2F *h3 = (TH2F*) f->Get("preVtxSel/hMultVtxTracks");
  h3->SetTitle(";ntrk_{PV}^{0} [cm];ntrk_{PV}^{1} [cm]");
  h3->GetXaxis()->CenterTitle();
  h3->GetXaxis()->SetRangeUser(0,40);
  h3->GetYaxis()->CenterTitle();
  h3->GetYaxis()->SetRangeUser(0,40);

  TH2F *h4 = (TH2F*) f->Get("postTrkVtxSel/hMultVtxTracks");
  h4->SetTitle(";ntrk_{PV}^{0} [cm];ntrk_{PV}^{1} [cm]");
  h4->GetXaxis()->CenterTitle();
  h4->GetXaxis()->SetRangeUser(0,40);
  h4->GetYaxis()->CenterTitle();
  h4->GetYaxis()->SetRangeUser(0,40);

  TCanvas *c1 = new TCanvas("c1","c1",480,550);
  gPad->SetLogz();
  gPad->SetRightMargin(0.15);
  h1->Draw("colz");
  tex->Draw();

  TCanvas *c2 = new TCanvas("c2","c2",480,550);
  gPad->SetLogz();
  gPad->SetRightMargin(0.15);
  h2->Draw("colz");
  tex->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",480,550);
  gPad->SetLogz();
  gPad->SetRightMargin(0.15);
  h3->Draw("colz");
  tex->Draw();

  TCanvas *c4 = new TCanvas("c4","c4",480,550);
  gPad->SetLogz();
  gPad->SetRightMargin(0.15);
  h4->Draw("colz");
  tex->Draw();

}


void set_plot_style() {

  // nicer colz plots

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  //const Int_t NCont = 100;   

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

}
