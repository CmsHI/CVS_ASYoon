#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TError.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TF1.h"
#include "TMath.h"

#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "/Users/andreyoon/Research/ana/common/utilities_2012.h"

void divideByWidth(TH1 *hist);
void setErrorY(TH1D *hist);

void PlotRAAForJetAndTrack(){


  // Variables

  // JetQuenching Mode
  // 1 = constQ
  // 2 = fractQ
  // 3 = energy dependent fractQ
  int jetqMode = 2;

  float msize = 0.8;
  float lwidth = 2;

  float rebinf = 4;

  float raamin_x = 8;
  float raamax_x = 1500;

  float raamin_x2 = 1.0;
  float raamax_x2 = 1500;

  // Read RAA data
  TString inf_raa_cbin1 = "../data_tables/raa/raa_0005_ptmean_sumerr.txt";
  TGraphErrors *gpraa_cbin1 = new TGraphErrors(inf_raa_cbin1.Data(),"%lg %lg %lg");
  
  if (!gpraa_cbin1 || gpraa_cbin1->IsZombie()){
    Error("<Data Point Reading>","RAA data points reading");
    return 0;
  }

  
  // Read root files
  TFile *f1 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN.root");
  //TFile *f1 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN.root");
  TFile *f2=0, *f3=0, *f4=0;

  if(jetqMode==1){
    f2 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_const10.00.root");
    f3 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_const20.00.root");
    f4 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_const30.00.root");
  }else if(jetqMode==2){
    f2 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fract0.10.root");
    f3 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fract0.20.root");
    f4 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fract0.30.root");
    /*
    f2 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN_jetQ_fract0.1.root");
    f3 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN_jetQ_fract0.2.root");
    f4 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN_jetQ_fract0.3.root");
    */
  }else if(jetqMode==3){
    f2 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.00.root");
    f3 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.00.root");
    f4 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog3.00.root");
  }

  
  if(!f1 || !f2 || !f3 || !f4){
    cout<<"File loading failure"<<endl;
    return;
  }


  TH1F *hdnevtminpthat = (TH1F*) f1->Get("dNevtMinPtHat");
  
  TH1F *hjetspecv0 = (TH1F*) f1->Get("dNJetdEt");
  TH1F *hjetspec_fracv1 = (TH1F*) f2->Get("dNJetdEt");
  TH1F *hjetspec_fracv2 = (TH1F*) f3->Get("dNJetdEt");
  TH1F *hjetspec_fracv3 = (TH1F*) f4->Get("dNJetdEt");

  TH2F *hdntrkdptdpthat = (TH2F*) f1->Get("dNTrkdPtdPtHat");
  TH3F *hdntrkdptdpthatdjetet = (TH3F*) f1->Get("dNTrkdPtdPtHatdJetEt");

  
  double small = 1e-3;
  double tot_evt_minpthat = hdnevtminpthat->GetEntries();

  cout<<"Number of min_pt_hat event sample = "<<tot_evt_minpthat<<endl;

  if(tot_evt_minpthat<1E-22){
    cout<<"This sample doesn't include the minimum pt hat bin sample!"<<endl;
    return; 
  }

  // Overall Normalization
  hjetspecv0->Scale(1./tot_evt_minpthat);
  hjetspec_fracv1->Scale(1./tot_evt_minpthat);
  hjetspec_fracv2->Scale(1./tot_evt_minpthat);
  hjetspec_fracv3->Scale(1./tot_evt_minpthat);
  hdntrkdptdpthatdjetet->Scale(1./tot_evt_minpthat);
  hdntrkdptdpthat->Scale(1./tot_evt_minpthat);


  // Parton/Jet Spectra and RAA -------------------------------------

  TCanvas *c1 =new TCanvas("c1","Parton/Jet Spectra and R_{AA}",1000,500);
  c1->Divide(2,1);
  
  TH1D *hdum = new TH1D("hdum","",200,0.0,1400);
  hdum->SetStats(0);
  hdum->SetAxisRange(1E-23,1E4,"Y");
  hdum->GetXaxis()->SetTitle("E_{T} (GeV)");
  hdum->GetXaxis()->CenterTitle();
  hdum->GetYaxis()->SetTitle("d#sigma/dE_{T} (mb/GeV) (|#eta|<2.0)");
  hdum->GetYaxis()->CenterTitle();
  hdum->GetXaxis()->SetMoreLogLabels();

  TH1D *hdum2 = (TH1D*) hdum->Clone("hdum2");
  hdum2->SetAxisRange(0.0,1.5,"Y");
  hdum2->SetAxisRange(raamin_x,raamax_x,"X");
  hdum2->GetYaxis()->SetTitle("Jet R_{AA}");
  hdum2->GetXaxis()->SetMoreLogLabels();

  c1->cd(1);
  gPad->SetLogy();
  hdum->Draw("");

  divideByWidth(hjetspecv0);
  divideByWidth(hjetspec_fracv1);
  divideByWidth(hjetspec_fracv2);
  divideByWidth(hjetspec_fracv3);

  TGraphErrors *tg_jetspecv0 = (TGraphErrors*) TgraphIt(hjetspecv0);
  TGraphErrors *tg_jetspec_fracv1 = (TGraphErrors*) TgraphIt(hjetspec_fracv1);
  TGraphErrors *tg_jetspec_fracv2 = (TGraphErrors*) TgraphIt(hjetspec_fracv2);
  TGraphErrors *tg_jetspec_fracv3 = (TGraphErrors*) TgraphIt(hjetspec_fracv3);


  hjetspecv0->SetMarkerSize(msize);
  hjetspecv0->SetMarkerStyle(24);
  hjetspecv0->SetMarkerColor(kBlack);
  hjetspecv0->SetLineColor(kBlack);
  //hjetspecv0->Draw("pzsame");

  tg_jetspecv0->SetLineWidth(lwidth);
  tg_jetspecv0->SetLineColor(kBlack);
  tg_jetspecv0->Draw("lsame");

  hjetspec_fracv1->SetMarkerSize(msize);
  hjetspec_fracv1->SetMarkerStyle(24);
  hjetspec_fracv1->SetMarkerColor(kRed);
  hjetspec_fracv1->SetLineColor(kRed);
  //hjetspec_fracv1->Draw("pzsame");

  tg_jetspec_fracv1->SetLineWidth(lwidth);
  tg_jetspec_fracv1->SetLineColor(kRed);
  tg_jetspec_fracv1->Draw("lsame");

  hjetspec_fracv2->SetMarkerSize(msize);
  hjetspec_fracv2->SetMarkerStyle(24);
  hjetspec_fracv2->SetMarkerColor(kBlue);
  hjetspec_fracv2->SetLineColor(kBlue);
  //hjetspec_fracv2->Draw("pzsame");

  tg_jetspec_fracv2->SetLineWidth(lwidth);
  tg_jetspec_fracv2->SetLineColor(kBlue);
  tg_jetspec_fracv2->Draw("lsame");

  hjetspec_fracv3->SetMarkerSize(msize);
  hjetspec_fracv3->SetMarkerStyle(24);
  hjetspec_fracv3->SetMarkerColor(kGreen+2);
  hjetspec_fracv3->SetLineColor(kGreen+2);
  //hjetspec_fracv3->Draw("pzsame");
  
  tg_jetspec_fracv3->SetLineWidth(lwidth);
  tg_jetspec_fracv3->SetLineColor(kGreen+2);
  tg_jetspec_fracv3->Draw("lsame");


  TH1D *hjetspecv0_cln = (TH1D*) hjetspecv0->Clone("hjetspecv0_cln");
  TH1D *hjetspec_fracv1_cln = (TH1D*) hjetspec_fracv1->Clone("hjetspec_fracv1_cln");
  TH1D *hjetspec_fracv2_cln = (TH1D*) hjetspec_fracv2->Clone("hjetspec_fracv2_cln");
  TH1D *hjetspec_fracv3_cln = (TH1D*) hjetspec_fracv3->Clone("hjetspec_fracv3_cln");

  c1->cd(2);
  gPad->SetLogx();
  hdum2->Draw("");

  hjetspecv0_cln->Rebin(rebinf);
  hjetspec_fracv1_cln->Rebin(rebinf);
  hjetspec_fracv2_cln->Rebin(rebinf);
  hjetspec_fracv3_cln->Rebin(rebinf);

  hjetspec_fracv1_cln->Divide(hjetspecv0_cln);
  hjetspec_fracv2_cln->Divide(hjetspecv0_cln);
  hjetspec_fracv3_cln->Divide(hjetspecv0_cln);

  setErrorY(hjetspec_fracv1_cln);  // remove y-error bar
  setErrorY(hjetspec_fracv2_cln);
  setErrorY(hjetspec_fracv3_cln);

  TGraphErrors *tg_jetspecv0_cln = (TGraphErrors*) TgraphIt(hjetspecv0_cln);
  TGraphErrors *tg_jetspec_fracv1_cln = (TGraphErrors*) TgraphIt(hjetspec_fracv1_cln);
  TGraphErrors *tg_jetspec_fracv2_cln = (TGraphErrors*) TgraphIt(hjetspec_fracv2_cln);
  TGraphErrors *tg_jetspec_fracv3_cln = (TGraphErrors*) TgraphIt(hjetspec_fracv3_cln);

  tg_jetspecv0_cln->SetLineWidth(lwidth);
  tg_jetspecv0_cln->SetLineColor(kBlack);
  
  tg_jetspec_fracv1_cln->SetLineWidth(lwidth);
  tg_jetspec_fracv1_cln->SetLineColor(kRed);

  tg_jetspec_fracv2_cln->SetLineWidth(lwidth);
  tg_jetspec_fracv2_cln->SetLineColor(kBlue);

  tg_jetspec_fracv3_cln->SetLineWidth(lwidth);
  tg_jetspec_fracv3_cln->SetLineColor(kGreen+2);


  hjetspec_fracv1_cln->Draw("pzsame");
  hjetspec_fracv2_cln->Draw("pzsame");
  hjetspec_fracv3_cln->Draw("pzsame");


  int bin_raamin_x = hdum2->GetXaxis()->FindBin(raamin_x);
  int bin_raamax_x = hdum2->GetXaxis()->FindBin(400);

  TLine *line = new TLine(hdum2->GetXaxis()->GetBinLowEdge(bin_raamin_x),1,
			  hdum2->GetXaxis()->GetBinUpEdge(bin_raamax_x),1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  

  // Charged Particle Spectra and RAA ------------------------------------- 
  TCanvas *c2 =new TCanvas("c2","Charged Particle Spectra and R_{AA}",1000,500);
  c2->Divide(2,1);


  // 1. Obtain FF ---------------------------------------------------
  //TH1D *hdjetet_ff = (TH1D*) hdnjetdetdpthat_ff->ProjectionX("",0,-1,"e");
  //hdjetet_ff->SetName("hdjetet_ff");
  //divideByWidth(hdjetet_ff); // this step is crucial (dN/dET!)
  
  for(int j=0;j<hdntrkdptdpthatdjetet->GetNbinsZ();j++){

    //double dsigma = hdjetet_ff->GetBinContent(j+1);
    double dsigma = hjetspecv0->GetBinContent(j+1);

    if(dsigma<1E-22) continue; // no jet ET bins

    double etmin = hdntrkdptdpthatdjetet->GetZaxis()->GetBinLowEdge(j+1);
    double etmax = hdntrkdptdpthatdjetet->GetZaxis()->GetBinUpEdge(j+1);

    // Fragmentation Function (Be carefull not [j+1,j+2])
    TH1D *hdntrkdpt_ff = (TH1D*) hdntrkdptdpthatdjetet->ProjectionX("",0,-1,j+1,j+1,"e");  
    hdntrkdpt_ff->SetName(Form("hdntrkdpt_ff_et%1.0fto%1.0f",etmin,etmax));

    // --> dN/dpT
    divideByWidth(hdntrkdpt_ff);

    // --> dN/dpT / sigma
    hdntrkdpt_ff->Scale(1./dsigma);
  }
  // ----------------------------------------------------------------

  
  // 2. Convolution -------------------------------------------------
  TH1D *hdntrkdpt = (TH1D*) hdntrkdptdpthat->ProjectionX("",0,-1,"e");
  hdntrkdpt->SetName("hdntrkdpt");
  hdntrkdpt->Reset();

  TH1D *hdntrkdpt_fracv1 = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_fracv1");
  TH1D *hdntrkdpt_fracv2 = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_fracv2");
  TH1D *hdntrkdpt_fracv3 = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_fracv3");

  for(int k=0;k<hdntrkdptdpthatdjetet->GetNbinsZ();k++){

    double etcent = hdntrkdptdpthatdjetet->GetZaxis()->GetBinCenter(k+1);
    double etmin2 = hdntrkdptdpthatdjetet->GetZaxis()->GetBinLowEdge(k+1);
    double etmax2 = hdntrkdptdpthatdjetet->GetZaxis()->GetBinUpEdge(k+1);
    
    TH1D *hdntrkdpt_ff = (TH1D*) gDirectory->Get(Form("hdntrkdpt_ff_et%1.0fto%1.0f",etmin2,etmax2));
    if(hdntrkdpt_ff==0) continue;  // don't use empty histograms

    TH1D *hdntrkdpt_ff_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_cln");
    TH1D *hdntrkdpt_ff_fracv1_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_fracv1_cln");
    TH1D *hdntrkdpt_ff_fracv2_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_fracv2_cln");
    TH1D *hdntrkdpt_ff_fracv3_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_fracv3_cln");

    double dsigma_v0 = hjetspecv0->GetBinContent(k+1);    
    double dsigma_fracv1 = hjetspec_fracv1->GetBinContent(k+1);
    double dsigma_fracv2 = hjetspec_fracv2->GetBinContent(k+1);
    double dsigma_fracv3 = hjetspec_fracv3->GetBinContent(k+1);

    hdntrkdpt_ff_cln->Scale(dsigma_v0);
    hdntrkdpt_ff_fracv1_cln->Scale(dsigma_fracv1);
    hdntrkdpt_ff_fracv2_cln->Scale(dsigma_fracv2);
    hdntrkdpt_ff_fracv3_cln->Scale(dsigma_fracv3);

    hdntrkdpt->Add(hdntrkdpt_ff_cln);
    hdntrkdpt_fracv1->Add(hdntrkdpt_ff_fracv1_cln);
    hdntrkdpt_fracv2->Add(hdntrkdpt_ff_fracv2_cln);
    hdntrkdpt_fracv3->Add(hdntrkdpt_ff_fracv3_cln);

  }
  // ---------------------------------------------------------------



  c2->cd(1);
  gPad->SetLogy();

  TH1D *hdum_1 = new TH1D("hdum_1","",1400,0.0,1400);
  hdum_1->SetStats(0);
  hdum_1->SetAxisRange(1E-22,1E3,"Y");
  hdum_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hdum_1->GetXaxis()->CenterTitle();
  hdum_1->GetYaxis()->SetTitle("d#sigma/dp_{T} (mb/GeV/c) (|#eta|<1.0)");
  hdum_1->GetYaxis()->CenterTitle();
  hdum_1->Draw("");

  TGraphErrors *tg_dntrkdpt = (TGraphErrors*) TgraphIt(hdntrkdpt);
  TGraphErrors *tg_dntrkdpt_fracv1 = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv1);
  TGraphErrors *tg_dntrkdpt_fracv2 = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv2);
  TGraphErrors *tg_dntrkdpt_fracv3 = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv3);

  tg_dntrkdpt->SetLineWidth(lwidth);
  tg_dntrkdpt->SetLineColor(kBlack);

  tg_dntrkdpt_fracv1->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv1->SetLineColor(kRed);

  tg_dntrkdpt_fracv2->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv2->SetLineColor(kBlue);

  tg_dntrkdpt_fracv3->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv3->SetLineColor(kGreen+2);

  hdntrkdpt->SetMarkerSize(msize);
  hdntrkdpt->SetMarkerStyle(24);
  hdntrkdpt->SetMarkerColor(kBlack);
  hdntrkdpt->SetLineColor(kBlack);
  hdntrkdpt->Draw("pzsame");

  hdntrkdpt_fracv1->SetMarkerSize(msize);
  hdntrkdpt_fracv1->SetMarkerStyle(24);
  hdntrkdpt_fracv1->SetMarkerColor(kRed);
  hdntrkdpt_fracv1->SetLineColor(kRed);
  hdntrkdpt_fracv1->Draw("pzsame");

  hdntrkdpt_fracv2->SetMarkerSize(msize);
  hdntrkdpt_fracv2->SetMarkerStyle(24);
  hdntrkdpt_fracv2->SetMarkerColor(kBlue);
  hdntrkdpt_fracv2->SetLineColor(kBlue);
  hdntrkdpt_fracv2->Draw("pzsame");

  hdntrkdpt_fracv3->SetMarkerSize(msize);
  hdntrkdpt_fracv3->SetMarkerStyle(24);
  hdntrkdpt_fracv3->SetMarkerColor(kGreen+2);
  hdntrkdpt_fracv3->SetLineColor(kGreen+2);
  hdntrkdpt_fracv3->Draw("pzsame");
  

  c2->cd(2);
  gPad->SetLogx();

  TH1D *hdum2_1 = (TH1D*) hdum_1->Clone("hdum2_1");
  hdum2_1->SetAxisRange(0.0,1.5,"Y");
  hdum2_1->SetAxisRange(raamin_x2,raamax_x2,"X");
  hdum2_1->GetYaxis()->SetTitle("Charged Particle R_{AA}");
  hdum2_1->Draw("");

  TH1D *hdntrkdpt_cln = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_cln");
  TH1D *hdntrkdpt_fracv1_cln = (TH1D*) hdntrkdpt_fracv1->Clone("hdntrkdpt_fracv1_cln");
  TH1D *hdntrkdpt_fracv2_cln = (TH1D*) hdntrkdpt_fracv2->Clone("hdntrkdpt_fracv2_cln");
  TH1D *hdntrkdpt_fracv3_cln = (TH1D*) hdntrkdpt_fracv3->Clone("hdntrkdpt_fracv3_cln");


  hdntrkdpt_cln->Rebin(4);
  hdntrkdpt_fracv1_cln->Rebin(4);
  hdntrkdpt_fracv2_cln->Rebin(4);
  hdntrkdpt_fracv3_cln->Rebin(4);

  hdntrkdpt_fracv1_cln->Divide(hdntrkdpt_cln);
  hdntrkdpt_fracv2_cln->Divide(hdntrkdpt_cln);
  hdntrkdpt_fracv3_cln->Divide(hdntrkdpt_cln);

  setErrorY(hdntrkdpt_fracv1_cln);
  setErrorY(hdntrkdpt_fracv2_cln);
  setErrorY(hdntrkdpt_fracv3_cln);

  TGraphErrors *tg_dntrkdpt_fracv1_cln = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv1_cln);
  TGraphErrors *tg_dntrkdpt_fracv2_cln = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv2_cln);
  TGraphErrors *tg_dntrkdpt_fracv3_cln = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv3_cln);


  tg_dntrkdpt_fracv1_cln->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv1_cln->SetLineColor(kRed);

  tg_dntrkdpt_fracv2_cln->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv2_cln->SetLineColor(kBlue);

  tg_dntrkdpt_fracv3_cln->SetLineWidth(lwidth);
  tg_dntrkdpt_fracv3_cln->SetLineColor(kGreen+2);

  hdntrkdpt_fracv1_cln->Draw("pzsame");
  hdntrkdpt_fracv2_cln->Draw("pzsame");
  hdntrkdpt_fracv3_cln->Draw("pzsame");

  
  int bin_raamin_x2 = hdum2_1->GetXaxis()->FindBin(raamin_x2);
  int bin_raamax_x2 = hdum2_1->GetXaxis()->FindBin(130);

  TLine *line2 = new TLine(hdum2_1->GetXaxis()->GetBinLowEdge(bin_raamin_x2),1,
			   hdum2_1->GetXaxis()->GetBinUpEdge(bin_raamax_x2),1);
  line2->SetLineStyle(2);
  line2->SetLineWidth(2);
  line2->Draw();

  
  // Replot Jet Spectra and RAA
  TLegend *legd = new TLegend(0.45,0.56,0.90,0.92);
  legd->SetMargin(0.2);
  legd->SetBorderSize(0);
  legd->SetFillColor(kWhite);
  legd->SetFillStyle(0);
  legd->SetTextSize(0.035);
  legd->SetMargin(0.25);
  if(jetqMode==1) {
    legd->SetHeader("   Constant E-loss");
    legd->AddEntry(tg_jetspec_fracv1_cln,"#Delta E = 10 GeV","l");
    legd->AddEntry(tg_jetspec_fracv2_cln,"#Delta E = 20 GeV","l");
    legd->AddEntry(tg_jetspec_fracv3_cln,"#Delta E = 30 GeV","l");
  }else if(jetqMode==2) {
    legd->SetHeader("   Fractional E-loss");
    legd->AddEntry(tg_jetspec_fracv1_cln,"c = 0.1","l");
    legd->AddEntry(tg_jetspec_fracv2_cln,"c = 0.2","l");
    legd->AddEntry(tg_jetspec_fracv3_cln,"c = 0.3","l");
  }else if(jetqMode==3) {
    legd->SetHeader(" E-depndent fractional E-loss");
    legd->AddEntry(tg_jetspec_fracv1_cln,"c = 1","l");
    legd->AddEntry(tg_jetspec_fracv2_cln,"c = 2","l");
    legd->AddEntry(tg_jetspec_fracv3_cln,"c = 3","l");
  }

  float xmin_local = 10.0;;

  TCanvas *c3 =new TCanvas("c3","Jet Spectra and R_{AA}",1000,500);
  c3->Divide(2,1);

  TH1D *hdum_re = (TH1D*) hdum->Clone("hdum_re");
  TH1D *hdum_1_re = (TH1D*) hdum_1->Clone("hdum_1_re");

  TH1D *hdum2_re = (TH1D*) hdum2->Clone("hdum2_re");
  TH1D *hdum2_1_re = (TH1D*) hdum2_1->Clone("hdum2_1_re");

  
  c3->cd(1);
  gPad->SetLogy();
  hdum_re->SetAxisRange(xmin_local,400,"X");   
  hdum_re->SetAxisRange(1E-11,20,"Y");
  hdum_re->Draw("");
  
  tg_jetspecv0->Draw("lsame");
  tg_jetspec_fracv1->Draw("lsame");
  tg_jetspec_fracv2->Draw("lsame");
  tg_jetspec_fracv3->Draw("lsame");
  legd->Draw("");
  
  c3->cd(2);
  //gPad->SetLogx();
  hdum2_re->SetAxisRange(0.0,1.1,"Y");
  hdum2_re->SetAxisRange(xmin_local,400,"X");
  hdum2_re->Draw("");

  tg_jetspec_fracv1_cln->Draw("lsame");
  tg_jetspec_fracv2_cln->Draw("lsame");
  tg_jetspec_fracv3_cln->Draw("lsame");

  line->Draw("");

  // Replot Charged Spectra and RAA
  TCanvas *c4 =new TCanvas("c4","Charged Particle Spectra and R_{AA}",1000,500);
  c4->Divide(2,1);

  c4->cd(1);
  gPad->SetLogy();
  hdum_1_re->SetAxisRange(1.2,130,"X");
  hdum_1_re->SetAxisRange(1E-10,2E2,"Y");
  hdum_1_re->Draw("");

  /*
  hjetspec_fracv1_cln->Draw("pzsame");
  hjetspec_fracv2_cln->Draw("pzsame");
  hjetspec_fracv3_cln->Draw("pzsame");
  */

  tg_dntrkdpt->Draw("lsame");
  tg_dntrkdpt_fracv1->Draw("lsame");
  tg_dntrkdpt_fracv2->Draw("lsame");
  tg_dntrkdpt_fracv3->Draw("lsame");
  legd->Draw("");


  c4->cd(2);
  //gPad->SetLogx();
  hdum2_1_re->SetAxisRange(1.2,130,"X");
  hdum2_1_re->SetAxisRange(0.0,1.1,"Y");
  hdum2_1_re->Draw("");

  gpraa_cbin1->SetMarkerSize(1.1*msize);
  gpraa_cbin1->Draw("pzsame");

  tg_dntrkdpt_fracv1_cln->Draw("lsame");
  tg_dntrkdpt_fracv2_cln->Draw("lsame");
  tg_dntrkdpt_fracv3_cln->Draw("lsame");
  
  line2->Draw("");

  /*
  hdntrkdpt_fracv1_cln->Draw("clzsame");
  hdntrkdpt_fracv2_cln->Draw("pzsame");
  hdntrkdpt_fracv3_cln->Draw("pzsame");
  */


}

void divideByWidth(TH1 *hist){

  for(int j=0;j<hist->GetNbinsX();j++){
    double width = hist->GetBinWidth(j+1);
    double yield = hist->GetBinContent(j+1);
    double error = hist->GetBinError(j+1);

    hist->SetBinContent(j+1,yield/width);
    hist->SetBinError(j+1,error/width);
  }

}


void setErrorY(TH1D *hist){

  for(int j=0;j<hist->GetNbinsX();j++){
    hist->SetBinError(j+1,0.0);
  }

}
