//-----------------------------------------------------------------------------
// Andre S. Yoon, Nov 22 2010
//
// Simple macro that plots gen and sim level spectra 
// 
//-----------------------------------------------------------------------------

void plotGenSimSpectra(){

  //TFile *f = new TFile("../root_files/mc/AMPT_37X_1K.root");
  //TString name = "AMPT_37X_1K";

  //TFile *f = new TFile("../root_files/mc/AMPT_391_1K_list.root");
  //TString name = "AMPT_391_1K_list";

  TFile *f = new TFile("../root_files/mc/HYDJET_391_1K_list.root");
  TString name = "HYDJET_391_1K_list";


  TNtuple *hTreeGEN = (TNtuple*) f->Get("gensimSpectraValidator/nt_gen");
  TNtuple *hTreeSIM = (TNtuple*) f->Get("gensimSpectraValidator/nt_sim");

  float numEvt = 1000;

  // gen
  TH1F *hdndpt_gen_all = new TH1F("hdndpt_gen_all","hdndpt_gen_all",200,0,10);
  TH1F *hdndpt_gen_pi = new TH1F("hdndpt_gen_pi","hdndpt_gen_pi",200,0,10);
  TH1F *hdndpt_gen_ka = new TH1F("hdndpt_gen_ka","hdndpt_gen_ka",200,0,10);
  TH1F *hdndpt_gen_p = new TH1F("hdndpt_gen_p","hdndpt_gen_p",200,0,10);
  TH1F *hdndpt_gen_sig = new TH1F("hdndpt_gen_sig","hdndpt_gen_sig",200,0,10);
  TH1F *hdndpt_gen_omg = new TH1F("hdndpt_gen_omg","hdndpt_gen_omg",200,0,10);
  TH1F *hdndpt_gen_xi = new TH1F("hdndpt_gen_xi","hdndpt_gen_xi",200,0,10);
  

  // sim
  TH1F *hdndpt_sim_all = new TH1F("hdndpt_sim_all","hdndpt_sim_all",200,0,10);
  TH1F *hdndpt_sim_pi = new TH1F("hdndpt_sim_pi","hdndpt_sim_pi",200,0,10);
  TH1F *hdndpt_sim_ka = new TH1F("hdndpt_sim_ka","hdndpt_sim_ka",200,0,10);
  TH1F *hdndpt_sim_p = new TH1F("hdndpt_sim_p","hdndpt_sim_p",200,0,10);
  TH1F *hdndpt_sim_sig = new TH1F("hdndpt_sim_sig","hdndpt_sim_sig",200,0,10);
  TH1F *hdndpt_sim_omg = new TH1F("hdndpt_sim_omg","hdndpt_sim_omg",200,0,10);
  TH1F *hdndpt_sim_xi = new TH1F("hdndpt_sim_xi","hdndpt_sim_xi",200,0,10);

  // GEN fill from ntuple 
  hTreeGEN->Draw("gpt>>hdndpt_gen_all","","goff"); hdndpt_gen_all->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_pi","abs(gpdgid)==211","goff"); hdndpt_gen_pi->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_ka","abs(gpdgid)==321","goff"); hdndpt_gen_ka->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_p","abs(gpdgid)==2212","goff"); hdndpt_gen_p->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_sig","abs(gpdgid)==3112","goff"); hdndpt_gen_sig->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_omg","abs(gpdgid)==3334","goff"); hdndpt_gen_omg->Sumw2();
  hTreeGEN->Draw("gpt>>hdndpt_gen_xi","abs(gpdgid)==3312","goff"); hdndpt_gen_xi->Sumw2();

  hdndpt_gen_all->Scale(1./numEvt);
  hdndpt_gen_pi->Scale(1./numEvt);
  hdndpt_gen_ka->Scale(1./numEvt);
  hdndpt_gen_p->Scale(1./numEvt);
  hdndpt_gen_sig->Scale(1./numEvt);
  hdndpt_gen_omg->Scale(1./numEvt);
  hdndpt_gen_xi->Scale(1./numEvt);

  // SIM fill from ntuple
  hTreeSIM->Draw("spt>>hdndpt_sim_all","","goff"); hdndpt_sim_all->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_pi","abs(spdgid)==211","goff"); hdndpt_sim_pi->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_ka","abs(spdgid)==321","goff"); hdndpt_sim_ka->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_p","abs(spdgid)==2212","goff"); hdndpt_sim_p->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_sig","abs(spdgid)==3112","goff"); hdndpt_sim_sig->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_omg","abs(spdgid)==3334","goff"); hdndpt_sim_omg->Sumw2();
  hTreeSIM->Draw("spt>>hdndpt_sim_xi","abs(spdgid)==3312","goff"); hdndpt_sim_xi->Sumw2();

  hdndpt_sim_all->Scale(1./numEvt);
  hdndpt_sim_pi->Scale(1./numEvt);
  hdndpt_sim_ka->Scale(1./numEvt);
  hdndpt_sim_p->Scale(1./numEvt);
  hdndpt_sim_sig->Scale(1./numEvt);
  hdndpt_sim_omg->Scale(1./numEvt);
  hdndpt_sim_xi->Scale(1./numEvt);

  


  // dum histogram
  float xnhitsmin = 0; float xnhitsmax = 10;
  TH1D *hDumNhits = new TH1D("hDumNhits","hDumNhits",100,xnhitsmin,xnhitsmax); hDumNhits->SetStats(0);


  // legend
  TLegend *legNhits = new TLegend(0.56,0.61,0.92,0.90);
  legNhits->SetFillColor(0); legNhits->SetBorderSize(0);
  legNhits->SetTextSize(0.04);
  legNhits->AddEntry(hdndpt_gen_pi,"Pion","lp");
  legNhits->AddEntry(hdndpt_gen_ka,"Kaon","lp");
  legNhits->AddEntry(hdndpt_gen_p,"Proton","lp");
  legNhits->AddEntry(hdndpt_gen_sig,"#Sigma","lp");
  legNhits->AddEntry(hdndpt_gen_omg,"#Omega","lp");
  legNhits->AddEntry(hdndpt_gen_xi,"#Xi","lp");


  TCanvas *c1 = new TCanvas("c1","GEN spectra distribution",400,600);
  
  gPad->SetRightMargin(0.05); gPad->SetLogy();
  hDumNhits->SetMinimum(1E-4);  hDumNhits->SetMaximum(5E2);
  hDumNhits->GetXaxis()->SetTitle("p_{T}^{GEN or SIM}"); hDumNhits->GetYaxis()->SetTitle("dN/dp_{T}");
  hDumNhits->GetXaxis()->CenterTitle(); hDumNhits->GetYaxis()->CenterTitle(); 
  hDumNhits->Draw("");

  hdndpt_gen_pi->SetLineColor(kBlack); hdndpt_gen_pi->SetMarkerColor(kBlack); hdndpt_gen_pi->SetMarkerStyle(20); 
  hdndpt_gen_pi->SetMarkerSize(0.8); hdndpt_gen_pi->Draw("samehist");
  
  hdndpt_gen_ka->SetLineColor(kRed); hdndpt_gen_ka->SetMarkerColor(kRed); hdndpt_gen_ka->SetMarkerStyle(20);
  hdndpt_gen_ka->SetMarkerSize(0.8); hdndpt_gen_ka->Draw("samehist");

  hdndpt_gen_p->SetLineColor(kBlue); hdndpt_gen_p->SetMarkerColor(kBlue); hdndpt_gen_p->SetMarkerStyle(20);
  hdndpt_gen_p->SetMarkerSize(0.8); hdndpt_gen_p->Draw("samehist");

  hdndpt_gen_sig->SetLineColor(kYellow-1); hdndpt_gen_sig->SetMarkerColor(kYellow-1); hdndpt_gen_sig->SetMarkerStyle(20);
  hdndpt_gen_sig->SetMarkerSize(0.8); hdndpt_gen_sig->Draw("samehist");

  hdndpt_gen_omg->SetLineColor(kGreen+2); hdndpt_gen_omg->SetMarkerColor(kGreen+2); hdndpt_gen_omg->SetMarkerStyle(20);
  hdndpt_gen_omg->SetMarkerSize(0.8); hdndpt_gen_omg->Draw("samehist");

  hdndpt_gen_xi->SetLineColor(kMagenta); hdndpt_gen_xi->SetMarkerColor(kMagenta); hdndpt_gen_xi->SetMarkerStyle(20);
  hdndpt_gen_xi->SetMarkerSize(0.8); hdndpt_gen_xi->Draw("samehist");

  legNhits->Draw("");

  // SIM 
  TCanvas *c2 = new TCanvas("c2","SIM spectra distribution",400,600);

  gPad->SetRightMargin(0.05); gPad->SetLogy();
  hDumNhits->Draw("");

  hdndpt_sim_pi->SetLineColor(kBlack); hdndpt_sim_pi->SetMarkerColor(kBlack); hdndpt_sim_pi->SetMarkerStyle(20);
  hdndpt_sim_pi->SetMarkerSize(0.8); hdndpt_sim_pi->Draw("pzsame");

  hdndpt_sim_ka->SetLineColor(kRed); hdndpt_sim_ka->SetMarkerColor(kRed); hdndpt_sim_ka->SetMarkerStyle(20);
  hdndpt_sim_ka->SetMarkerSize(0.8); hdndpt_sim_ka->Draw("pzsame");

  hdndpt_sim_p->SetLineColor(kBlue); hdndpt_sim_p->SetMarkerColor(kBlue); hdndpt_sim_p->SetMarkerStyle(20);
  hdndpt_sim_p->SetMarkerSize(0.8); hdndpt_sim_p->Draw("pzsame");

  hdndpt_sim_sig->SetLineColor(kYellow-1); hdndpt_sim_sig->SetMarkerColor(kYellow-1); hdndpt_sim_sig->SetMarkerStyle(20);
  hdndpt_sim_sig->SetMarkerSize(0.8); hdndpt_sim_sig->Draw("pzsame");

  hdndpt_sim_omg->SetLineColor(kGreen+2); hdndpt_sim_omg->SetMarkerColor(kGreen+2); hdndpt_sim_omg->SetMarkerStyle(20);
  hdndpt_sim_omg->SetMarkerSize(0.8); hdndpt_sim_omg->Draw("pzsame");

  hdndpt_sim_xi->SetLineColor(kMagenta); hdndpt_sim_xi->SetMarkerColor(kMagenta); hdndpt_sim_xi->SetMarkerStyle(20);
  hdndpt_sim_xi->SetMarkerSize(0.8); hdndpt_sim_xi->Draw("pzsame");
  legNhits->Draw("");

  
  // GEN SIM together
  TCanvas *c3 = new TCanvas("c3","GEN SIM spectra distribution",400,600);
  gPad->SetRightMargin(0.05); gPad->SetLogy(); gPad->SetLogx();
  hDumNhits->Draw("");

  hdndpt_gen_pi->Draw("samehist"); hdndpt_gen_ka->Draw("samehist"); hdndpt_gen_p->Draw("samehist"); 
  hdndpt_gen_sig->Draw("samehist"); hdndpt_gen_omg->Draw("samehist"); hdndpt_gen_xi->Draw("samehist");

  hdndpt_sim_pi->Draw("pzsame"); hdndpt_sim_ka->Draw("pzsame"); hdndpt_sim_p->Draw("pzsame"); 
  hdndpt_sim_sig->Draw("pzsame"); hdndpt_sim_omg->Draw("pzsame"); hdndpt_sim_xi->Draw("pzsame");

  
  c1->cd(); c1->Print(Form("./fig/%s_gen.gif",name.Data()));
  c2->cd(); c2->Print(Form("./fig/%s_sim.gif",name.Data()));
  c3->cd(); c3->Print(Form("./fig/%s_gen_sim.gif",name.Data()));

}
