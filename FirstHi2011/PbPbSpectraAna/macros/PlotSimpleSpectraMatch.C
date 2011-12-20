
// compare dn/dpt (jet65+jet80) vs dn/dpt (jet65)

void drawText(const char *text, float xp, float yp){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(18);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}

void PlotSimpleSpectraMatch(int centmode=1){

  gStyle->SetOptStat(0);
  
  TString dir = "dec192011_sub0_v1_44x";

  TString file1 = "CORRv1_trkhistDATA_proc_nov042011_mb_sub4_eta_0.0to1.0_jet_0.0to1000.0_hitrackAna_jetMode1_GEN0_reb0_MergedJets";
  TString file2 = "CORRv1_HighPtAnaSkimPRv1_dec192011_sub0_jet65_AtoM_v0_eta_0.0to1.0_jet_0.0to1000.0_hitrackAna_GEN0_reb0";

  TString cbin, cbintag;

  if(centmode==1) cbintag = "_cbin0to1", cbin = "0 ~ 5%";
  else if(centmode==2) cbintag = "_cbin2to3", cbin = "5 ~ 10%";
  else if(centmode==3) cbintag = "_cbin4to11", cbin = "10 ~ 30%";
  else if(centmode==4) cbintag = "_cbin12to19", cbin = "30 ~ 50%";
  else if(centmode==5) cbintag = "_cbin20to27", cbin = "50 ~ 70%";
  else if(centmode==6) cbintag = "_cbin28to35", cbin = "70 ~ 90%";

  file1.Append(Form("%s",cbintag.Data()));
  file2.Append(Form("%s",cbintag.Data()));

  TFile *f1 = new TFile(Form("../rootOutput/%s/%s.root",dir.Data(),file1.Data()));
  TFile *f2 = new TFile(Form("../rootOutput/%s/%s.root",dir.Data(),file2.Data()));


  TH1D *hist1 = (TH1D*) f1->Get("corrTypeOne/hdndpt_full");
  TH1D *hist2 = (TH1D*) f2->Get("corrTypeOne/hdndpt_full");


  // dn/dpt =============================================
  TCanvas *c0 = new TCanvas("c0","",500,500);
  //c0->SetGridy();
  c0->SetLogy();
  hist1->GetYaxis()->SetTitle("dn/dp_{T} (1/GeV/c)");
  hist1->SetMarkerSize(1.2);
  hist1->SetAxisRange(0.5,120,"X");
  hist1->SetAxisRange(1E-12,1,"Y");
  hist1->Draw("pz");

  hist2->SetMarkerColor(2);
  hist2->SetMarkerSize(1.2);
  hist2->Draw("pzsame");

  TLegend *legd = new TLegend(0.2,0.65,0.65,0.90);
  legd->SetMargin(0.2);
  legd->SetBorderSize(0);
  legd->SetFillColor(kWhite);
  legd->SetFillStyle(0);
  legd->SetTextSize(0.032);
  legd->SetMargin(0.3);
  legd->AddEntry(hist1,"Jet65 (80 < E_{T} < 100)+ Jet80 (E_{T} > 100 GeV)","pl");
  legd->AddEntry(hist2,"Jet65 (no E_{T} cut)","pl");
  legd->Draw();

  drawText(cbin.Data(),0.22,0.31);

  // ratio =============================================
  TCanvas *c0_1 = new TCanvas("c0_1","",500,500);
  c0_1->SetGridy();
  
  TH1D *hist1_cln = (TH1D*) hist1->Clone("hist1_cln");
  TH1D *hist2_cln = (TH1D*) hist2->Clone("hist2_cln");

  hist1_cln->Divide(hist2_cln);

  hist1_cln->GetYaxis()->SetTitle("Jet65 + Jet80 / Jet65 ");
  hist1_cln->SetMarkerSize(1.2);
  hist1_cln->SetAxisRange(0.5,120,"X");
  hist1_cln->SetAxisRange(0,2,"Y");
  hist1_cln->Draw("pz");


  // Fitting
  TF1 *fit1 = new TF1("fit1","[0]",65,120);
  fit1->SetLineColor(kAzure+6);                                                                                                                           
  fit1->SetLineColor(kRed);
  hist1_cln->Fit(fit1,"R","");
  fit1->Draw("same");
  
  drawText(cbin.Data(),0.22,0.81);


}
