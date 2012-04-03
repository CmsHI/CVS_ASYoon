


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


//double pthatbins[] = {0.,5.,10.,20.,30.,50.,80.,120.,170.,230.,300.,380.,1000.};
double pthatbins[] = {0.,5.,10.,20.,30.,50.,80.,120.,170.,230.,300.,380.,470.,570.,670.,800.,930.,1000.,1100.,1200.,1400.};

const int npthat = sizeof(pthatbins)/sizeof(double);

Int_t color[13]={kViolet+2,kBlue,kAzure+6,kGreen-3,kOrange-5,kOrange-3,kOrange+4,kRed-3,kRed,kRed+2,kMagenta+1,kRed+1,kGreen+3};


void divideHistByFunc(TH1D *hist, TF1* fit, double xmin, double xmax);
void divideByWidth(TH1D *hist);
void setErrorY(TH1D *hist);

void PlotPythiaGENSpectra(){

  // Variables
  float msize = 0.8;

  //TFile *f1 = new TFile("/Users/andreyoon/Research/ana/jetquenching/root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v2.root");
  //TFile *f1 = new TFile("/Users/andreyoon/Research/ana/jetquenching/root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v2_VariedN.root");
  TFile *f1 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN_noJetEtaCut.root");

  if(f1==0) return;

  TH1F *hdnevtminpthat = (TH1F*) f1->Get("dNevtMinPtHat");
  TH1F *hpthat = (TH1F*) f1->Get("dPtHat");
  TH2F *hdnjetdetdpthat = (TH2F*) f1->Get("dNJetdEtdPtHat");
  TH2F *hdnjetdetdpthat_ff = (TH2F*) f1->Get("dNJetdEtdPtHat_FF");

  TH2F *hddtrkdptdpthat = (TH2F*) f1->Get("dNTrkdPtdPtHat");
  TH2F *hddalltrkdptdpthat = (TH2F*) f1->Get("dNAllTrkdPtdPtHat");

  TH3F *hddtrkdptdpthatdjetet = (TH3F*) f1->Get("dNTrkdPtdPtHatdJetEt");

  double small = 1e-3;
  double tot_evt_minpthat = hdnevtminpthat->GetEntries();

  cout<<"Number of min_pt_hat event sample = "<<tot_evt_minpthat<<endl;

  if(tot_evt_minpthat<1E-22){
    cout<<"This sample doesn't include the minimum pt hat bin sample!"<<endl;
    return; 
  }

  
  // -----------------------------------------------------------------
  // tot_evt_minpthat is the numbe of processed events 
  // in the min pt_hat sample. It is needed to obtain (dSigma/dpT) !
  // -----------------------------------------------------------------
  hdnjetdetdpthat->Scale(1./tot_evt_minpthat);
  hdnjetdetdpthat_ff->Scale(1./tot_evt_minpthat);
  hddtrkdptdpthat->Scale(1./tot_evt_minpthat);
  hddalltrkdptdpthat->Scale(1./tot_evt_minpthat);
  hddtrkdptdpthatdjetet->Scale(1./tot_evt_minpthat);
  

  TCanvas *c1 =new TCanvas("c1","",500,500);
  c1->SetLogy();

  TH1D *hdum = new TH1D("hdum","",200,0.0,1400);
  hdum->SetStats(0);
  hdum->SetAxisRange(1E-22,1E4,"Y");
  hdum->GetXaxis()->SetTitle("E_{T} (GeV)");
  hdum->GetXaxis()->CenterTitle();
  hdum->GetYaxis()->SetTitle("d#sigma/dE_{T} (mb/GeV) (|#eta|<2.0)");
  hdum->GetYaxis()->CenterTitle();
  hdum->Draw("");

  
  for(int i=0;i<npthat-1;i++){
    
    int binlow = hdnjetdetdpthat->GetYaxis()->FindBin(pthatbins[i]);
    int binhig = hdnjetdetdpthat->GetYaxis()->FindBin(pthatbins[i+1]-small);

    cout<<"PtHat Bin: "<<pthatbins[i]<<" to "<<pthatbins[i+1]
	<<" Hist Bin = "<<binlow<<" to "<<binhig
	<<" Bin (Low,High) = "<<hdnjetdetdpthat->GetYaxis()->GetBinLowEdge(binlow)
	<<" to "<<hdnjetdetdpthat->GetYaxis()->GetBinUpEdge(binhig)<<endl;
    
    cout<<"Last bin number = "<<hdnjetdetdpthat->GetYaxis()->GetLast()<<endl;

    
    TH1D *hdnjetdet = (TH1D*) hdnjetdetdpthat->ProjectionX("",binlow,binhig,"e");
    hdnjetdet->SetName(Form("hdnjetdet_pthat%1.0fto%1.0f",pthatbins[i],pthatbins[i+1]));
    divideByWidth(hdnjetdet);

    hdnjetdet->SetMarkerSize(msize);
    hdnjetdet->SetMarkerColor(color[i%13]);
    hdnjetdet->SetLineColor(color[i%13]);
    hdnjetdet->Draw("pzsame");


    TH1D *hddtrkdpt = (TH1D*) hddtrkdptdpthat->ProjectionX("",binlow,binhig,"e");
    hddtrkdpt->SetName(Form("hddtrkdpt_pthat%1.0fto%1.0f",pthatbins[i],pthatbins[i+1]));
    divideByWidth(hddtrkdpt);

    TH1D *hddalltrkdpt = (TH1D*) hddalltrkdptdpthat->ProjectionX("",binlow,binhig,"e");
    hddalltrkdpt->SetName(Form("hddalltrkdpt_pthat%1.0fto%1.0f",pthatbins[i],pthatbins[i+1]));
    divideByWidth(hddalltrkdpt);

  }

  // + Projection (First,Last) = (0,-1)
  TH1D *hdnjetdet_full = (TH1D*) hdnjetdetdpthat->ProjectionX("",0,-1,"e");
  hdnjetdet_full->SetName("hdnjetdet_full");
  divideByWidth(hdnjetdet_full);  // dN/dET
  hdnjetdet_full->SetMarkerSize(msize);
  hdnjetdet_full->SetMarkerStyle(24);
  hdnjetdet_full->SetMarkerColor(kBlack);
  hdnjetdet_full->Draw("pzsame");

  TH1D *hddtrkdpt_full = (TH1D*) hddtrkdptdpthat->ProjectionX("",0,-1,"e");
  hddtrkdpt_full->SetName("hddtrkdpt_full");
  divideByWidth(hddtrkdpt_full);

  TH1D *hddalltrkdpt_full = (TH1D*) hddalltrkdptdpthat->ProjectionX("",0,-1,"e");
  hddalltrkdpt_full->SetName("hddalltrkdpt_full");
  divideByWidth(hddalltrkdpt_full);



  // Fit the distribution (Ratio inset) 
  TCanvas *c2 =new TCanvas("c2","Fit to the cross-section",500,500);
  c2->SetLogy();
  hdum->Draw("");

  float rebinf = 1.0;

  TH1D *hdnjetdet_full_cln = (TH1D*) hdnjetdet_full->Clone("hdnjetdet_full_cln");
  hdnjetdet_full_cln->Rebin(rebinf);
  hdnjetdet_full_cln->Draw("pzsame");

  double par1[5];
  double fitmin = 4.5;
  double fitmax = 1100;
  TF1 *fit1 = new TF1("fit1","[0]*pow((1+x/[1]),[2])*pow((1-x/[3]),[4])",fitmin,fitmax);

  par1[0] = 1E9*hdnjetdet_full_cln->GetBinContent(1); // cross section at pT->0
  par1[1] = 3.0;  // soft and hard scattering transition 
  par1[2] = -10.0; // characterizes power-law
  par1[3] = 1380;   // max parton energy  (fixed)
  par1[4] = 5.0; // characterizes end of phase

  fit1->SetParameters(par1);
  fit1->SetParLimits(3,0.8*par1[3],1.2*par1[3]);

  hdnjetdet_full_cln->Fit(fit1,"RN"); // I option is more cpu intensive
  fit1->SetLineColor(kRed);
  fit1->Draw("same");

  TPad *tpad = new TPad("tpad", "", 0.40, 0.58, 0.95, 0.92);
  //gStyle->SetPadColor(0);tpad->SetFillColor(0);//tpad->Modified();//tpad->Update();
  tpad->Draw();
  tpad->cd();
  gPad->SetLogx();  
  gPad->SetBottomMargin(0.24);
  gPad->SetLeftMargin(0.20);
  

  TH1D *hdnjetdet_full_cln2 = (TH1D*) hdnjetdet_full_cln->Clone("hdnjetdet_full_cln2");
  divideHistByFunc(hdnjetdet_full_cln2,fit1,fitmin,fitmax);

  int bin_low = hdnjetdet_full_cln2->GetXaxis()->FindBin(fitmin);
  double fitmin_low = hdnjetdet_full_cln2->GetBinLowEdge(bin_low);
  
  hdnjetdet_full_cln2->SetStats(0);
  hdnjetdet_full_cln2->SetMarkerSize(0.4);

  hdnjetdet_full_cln2->GetYaxis()->SetNdivisions(505);
  hdnjetdet_full_cln2->GetYaxis()->SetLabelFont(43);
  hdnjetdet_full_cln2->GetYaxis()->SetTitleFont(43);
  hdnjetdet_full_cln2->GetYaxis()->SetLabelSize(16);
  hdnjetdet_full_cln2->GetYaxis()->SetTitleSize(16);
  hdnjetdet_full_cln2->GetYaxis()->SetTitleOffset(2.6);

  hdnjetdet_full_cln2->SetAxisRange(fitmin_low,fitmax,"X");
  hdnjetdet_full_cln2->GetXaxis()->SetNdivisions(504);
  hdnjetdet_full_cln2->GetXaxis()->SetLabelFont(43);
  hdnjetdet_full_cln2->GetXaxis()->SetTitleFont(43);
  hdnjetdet_full_cln2->GetXaxis()->SetLabelSize(16);
  hdnjetdet_full_cln2->GetXaxis()->SetTitleSize(15);
  hdnjetdet_full_cln2->GetXaxis()->SetTitleOffset(3.5);

  hdnjetdet_full_cln2->SetAxisRange(0.1,5.0,"Y");
  hdnjetdet_full_cln2->GetXaxis()->SetTitle("E_{T} (GeV)");
  hdnjetdet_full_cln2->GetXaxis()->CenterTitle();
  hdnjetdet_full_cln2->GetYaxis()->SetTitle("Dist / Fit");
  hdnjetdet_full_cln2->GetYaxis()->CenterTitle();
  hdnjetdet_full_cln2->Draw("pz");

  TLine *line = new TLine(fitmin_low,1,fitmax,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->SetLineColor(kRed);
  line->Draw();


  // Fit function + variation!
  TCanvas *c2_1 =new TCanvas("c2_1","",500,500);
  c2_1->SetLogy();
  TH1D* hdum2 = (TH1D*) hdum->Clone("hdum2");
  hdum2->SetAxisRange(fitmin,fitmax,"X");
  hdum2->Draw("");
  fit1->Draw("same");

  
  // Making Fragmentation functions

  // check first dN/dET
  TCanvas *c2_2 =new TCanvas("c2_2","dsigma/dE_{T} (mb/GeV) used for FF",500,500);
  c2_2->SetLogy();
  
  //TH1D *hdjetet_ff = (TH1D*) hddtrkdptdpthatdjetet->ProjectionZ("",0,-1,0,-1,"e");
  //TH1D *hdjetet_ff = (TH1D*) hddtrkdptdpthatdjetet->Project3D("ze");
  TH1D *hdjetet_ff = (TH1D*) hdnjetdetdpthat_ff->ProjectionX("",0,-1,"e");
  hdjetet_ff->SetName("hdjetet_ff");

  divideByWidth(hdjetet_ff); // this step is crucial (dN/dET!)

  hdum->Draw("");
  hdjetet_ff->SetLineColor(kRed);
  hdjetet_ff->Draw("histsame");
  //hdnjetdet_full->Rebin(10);
  //hdnjetdet_full->Scale(1./10.);
  hdnjetdet_full->Draw("pzsame");

  // plot ff in each jet ET bins
  TCanvas *c2_3 =new TCanvas("c2_3","",500,500);
  c2_3->SetLogy();
  
  TH1D* hdum3 = (TH1D*) hdum->Clone("hdum2");
  hdum3->SetAxisRange(0.1,1400,"X");
  hdum3->SetAxisRange(1E-7,1E2,"Y");
  hdum3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hdum3->GetYaxis()->SetTitle("FF");
  hdum3->Draw("");


  cout<<"Total number of FFs = "<<hddtrkdptdpthatdjetet->GetNbinsZ()<<endl;
  
  for(int j=0;j<hddtrkdptdpthatdjetet->GetNbinsZ();j++){

    //double etcent = hddtrkdptdpthatdjetet->GetZaxis()->GetBinCenter(j+1);
    //double dsigma = hdnjetdet_full_cln->GetBinContent(hdnjetdet_full_cln->GetXaxis()->FindBin(etcent));    

    double dsigma = hdjetet_ff->GetBinContent(j+1);
    if(dsigma<1E-22) continue; // no jet ET bins

    double etmin = hddtrkdptdpthatdjetet->GetZaxis()->GetBinLowEdge(j+1);
    double etmax = hddtrkdptdpthatdjetet->GetZaxis()->GetBinUpEdge(j+1);

    cout<<"ET bins = "<<etmin<<" to "<<etmax<<" Sigma = "<<dsigma<<endl;

    // Fragmentation Function (Be carefull not [j+1,j+2])
    TH1D *hddtrkdpt_ff = (TH1D*) hddtrkdptdpthatdjetet->ProjectionX("",0,-1,j+1,j+1,"e");  
    hddtrkdpt_ff->SetName(Form("hddtrkdpt_ff_et%1.0fto%1.0f",etmin,etmax));

    // --> dN/dpT
    divideByWidth(hddtrkdpt_ff);

    // --> dN/dpT / sigma
    hddtrkdpt_ff->Scale(1./dsigma);

    hddtrkdpt_ff->SetMarkerSize(1.0);
    hddtrkdpt_ff->SetMarkerColor(color[j%13]);
    hddtrkdpt_ff->SetLineColor(color[j%13]);
    hddtrkdpt_ff->Draw("pzsame");

  }



  // Charged Particle Spectra ------------------------------------------

  /*

  1 . dN/dpT from all tracks

  2 . dN/dpT from all fragmented 

  3 . dN/dpT from convoluted
  3'. dN/dpT from convoluted with para
  
  * 1 vs 2 ==> deficit in the low pt tracks
  * 2 vs 3(3') ==> binning effect 

  4. EdN^3/dp^3 comparison with the measurement

  */

  // From All
  TCanvas *c1_1 =new TCanvas("c1_1","",500,500);
  c1_1->SetLogy();

  TH1D *hdum_1 = new TH1D("hdum_1","",200,0.0,1400);
  hdum_1->SetStats(0);
  hdum_1->SetAxisRange(1E-20,1E4,"Y");
  hdum_1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hdum_1->GetXaxis()->CenterTitle();
  hdum_1->GetYaxis()->SetTitle("dN/dp_{T} (|#eta|<1.0)");
  hdum_1->GetYaxis()->CenterTitle();
  hdum_1->Draw("");


  for(int i=0;i<npthat-1;i++){

    TH1D *hddalltrkdpt_obt = (TH1D*) gDirectory->Get(Form("hddalltrkdpt_pthat%1.0fto%1.0f",pthatbins[i],pthatbins[i+1]));

    hddalltrkdpt_obt->SetMarkerSize(1.0);
    hddalltrkdpt_obt->SetMarkerColor(color[i%13]);
    hddalltrkdpt_obt->SetLineColor(color[i%13]);
    hddalltrkdpt_obt->Draw("pzsame");
  }

  hddalltrkdpt_full->SetMarkerStyle(24);
  hddalltrkdpt_full->SetMarkerColor(kBlack);
  hddalltrkdpt_full->SetMarkerSize(1.0);
  hddalltrkdpt_full->Draw("pzsame");

  // From Fragmented
  TCanvas *c1_2 =new TCanvas("c1_2","",500,500);
  c1_2->SetLogy();

  hdum_1->Draw("");

  for(int i=0;i<npthat-1;i++){

    TH1D *hddtrkdpt_obt = (TH1D*) gDirectory->Get(Form("hddtrkdpt_pthat%1.0fto%1.0f",pthatbins[i],pthatbins[i+1]));

    hddtrkdpt_obt->SetMarkerSize(1.0);
    hddtrkdpt_obt->SetMarkerColor(color[i%13]);
    hddtrkdpt_obt->SetLineColor(color[i%13]);
    hddtrkdpt_obt->Draw("pzsame");
  }

  hddtrkdpt_full->SetMarkerStyle(24);
  hddtrkdpt_full->SetMarkerColor(kBlack);
  hddtrkdpt_full->SetMarkerSize(1.0);
  hddtrkdpt_full->Draw("pzsame");


  // From CONVOLUTED !!
  TH1D *hddtrkdpt_ff2_convol = (TH1D*) hddtrkdpt_full->Clone("hddtrkdpt_ff2_convol");
  hddtrkdpt_ff2_convol->Reset();

  for(int k=0;k<hddtrkdptdpthatdjetet->GetNbinsZ();k++){

    double etcent = hddtrkdptdpthatdjetet->GetZaxis()->GetBinCenter(k+1);
    double etmin2 = hddtrkdptdpthatdjetet->GetZaxis()->GetBinLowEdge(k+1);
    double etmax2 = hddtrkdptdpthatdjetet->GetZaxis()->GetBinUpEdge(k+1);
    
    TH1D *hddtrkdpt_ff2 = (TH1D*) gDirectory->Get(Form("hddtrkdpt_ff_et%1.0fto%1.0f",etmin2,etmax2));
    if(hddtrkdpt_ff2==0) continue;  // don't use empty histograms

    TH1D *hddtrkdpt_ff2_cln = (TH1D*) hddtrkdpt_ff2->Clone("hddtrkdpt_ff2_cln");
    
    
    double dsigma2 = hdjetet_ff->GetBinContent(k+1);    
    //double dsigma2 = hdnjetdet_full_cln->GetBinContent(hdnjetdet_full_cln->GetXaxis()->FindBin(etcent));

    //TH1D *hdnjetdet_full_mean = (TH1D*) hdnjetdet_full->Clone("hdnjetdet_full_mean");
    //double dsigma2 = hdnjetdet_full_mean->GetBinContent(k+1);        
    
    //double etmin2_full = hdnjetdet_full_mean->GetXaxis()->FindBin(etmin2);
    //double etmax2_full = hdnjetdet_full_mean->GetXaxis()->FindBin(etmax2);
    //hdnjetdet_full_mean->GetXaxis()->SetRange(etmin2_full,etmax2_full);
    //double etmean2 = hdnjetdet_full_mean->GetXaxis()->FindBin(hdnjetdet_full_mean->GetMean());
    //double dsigma2 = hdnjetdet_full_mean->GetBinContent(etmean2);


    //double dsigma2 = fit1->Eval(hdnjetdet_full_mean->GetMean());
    
    hddtrkdpt_ff2_cln->Scale(dsigma2);

    hddtrkdpt_ff2_convol->Add(hddtrkdpt_ff2_cln);
  }

  TCanvas *c1_3_1 =new TCanvas("c1_3_1","",500,500);
  c1_3_1->SetLogy();
  hdum_1->Draw("");
  hddtrkdpt_ff2_convol->SetMarkerStyle(24);
  hddtrkdpt_ff2_convol->SetMarkerSize(1.0);
  hddtrkdpt_ff2_convol->Draw("pzsame");


  // Division Fragmented / Full
  TCanvas *c1_3 =new TCanvas("c1_3","All Fragmented / All Hadrons",500,500);
  //c1_3->SetLogy();
  c1_3->SetLogx();

  TH1D *hddalltrkdpt_full_cln = (TH1D*) hddalltrkdpt_full->Clone("hddalltrkdpt_full_cln");
  TH1D *hddtrkdpt_full_cln = (TH1D*) hddtrkdpt_full->Clone("hddtrkdpt_full_cln");

  //hddalltrkdpt_full_cln->Divide(hddtrkdpt_full_cln);
  hddtrkdpt_full_cln->Divide(hddalltrkdpt_full_cln);

  setErrorY(hddtrkdpt_full_cln);

  hddtrkdpt_full_cln->SetStats(0);
  hddtrkdpt_full_cln->SetAxisRange(2E-3,2,"Y");
  hddtrkdpt_full_cln->SetAxisRange(1E-1,1E3,"X");

  hddtrkdpt_full_cln->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hddtrkdpt_full_cln->GetXaxis()->CenterTitle();
  hddtrkdpt_full_cln->GetYaxis()->SetTitle("Ratio (All Fragmented / All)");
  hddtrkdpt_full_cln->GetYaxis()->CenterTitle();

  hddtrkdpt_full_cln->Draw("pz");
  
  TLine *line2 = new TLine(1E-1,1,1E3,1);
  line2->SetLineStyle(2);
  line2->SetLineWidth(2);
  line2->SetLineColor(kRed);
  line2->Draw();


  // Division FF Convoluted / Fragmented
  TCanvas *c1_4 =new TCanvas("c1_4","",500,500);
  //c1_4->SetLogy();
  c1_4->SetLogx();

  TH1D *hddtrkdpt_full_cln2 = (TH1D*) hddtrkdpt_full->Clone("hddtrkdpt_full_cln2");
  TH1D *hddtrkdpt_ff2_convol_cln = (TH1D*) hddtrkdpt_ff2_convol->Clone("hddtrkdpt_ff2_convol_cln");

  hddtrkdpt_ff2_convol_cln->Divide(hddtrkdpt_full_cln2);
  

  hddtrkdpt_ff2_convol_cln->SetStats(0);
  hddtrkdpt_ff2_convol_cln->SetAxisRange(1E-1,1E3,"X");
  hddtrkdpt_ff2_convol_cln->SetAxisRange(0.0,2.0,"Y");

  hddtrkdpt_ff2_convol_cln->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hddtrkdpt_ff2_convol_cln->GetXaxis()->CenterTitle();
  hddtrkdpt_ff2_convol_cln->GetYaxis()->SetTitle("Ratio (FF Convoluted / All Fragmented)");
  hddtrkdpt_ff2_convol_cln->GetYaxis()->CenterTitle();

  setErrorY(hddtrkdpt_ff2_convol_cln);

  hddtrkdpt_ff2_convol_cln->Draw("pz");
  line2->Draw();


  // Division FF Convulted / Full
  TCanvas *c1_5 =new TCanvas("c1_5","",500,500);
  c1_5->SetLogx();

  TH1D *hddalltrkdpt_full_cln2 = (TH1D*) hddalltrkdpt_full->Clone("hddalltrkdpt_full_cln");
  TH1D *hddtrkdpt_ff2_convol_cln2 = (TH1D*) hddtrkdpt_ff2_convol->Clone("hddtrkdpt_ff2_convol_cln2");

  hddtrkdpt_ff2_convol_cln2->Divide(hddalltrkdpt_full_cln2);

  hddtrkdpt_ff2_convol_cln2->SetStats(0);
  hddtrkdpt_ff2_convol_cln2->SetAxisRange(1E-1,1E3,"X");
  hddtrkdpt_ff2_convol_cln2->SetAxisRange(0.0,2.0,"Y");

  hddtrkdpt_ff2_convol_cln2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hddtrkdpt_ff2_convol_cln2->GetXaxis()->CenterTitle();
  hddtrkdpt_ff2_convol_cln2->GetYaxis()->SetTitle("Ratio (FF Convoluted / All)");
  hddtrkdpt_ff2_convol_cln2->GetYaxis()->CenterTitle();

  setErrorY(hddtrkdpt_ff2_convol_cln2);

  hddtrkdpt_ff2_convol_cln2->Draw("pz");
  line2->Draw();



}

void divideHistByFunc(TH1D *hist, TF1* fit, double xmin, double xmax){
  
  for(int j=0;j<hist->GetNbinsX();j++){
    double pt = hist->GetBinCenter(j+1);
    double yield = hist->GetBinContent(j+1);
    double error = hist->GetBinError(j+1);

    if(pt>xmin && pt<xmax){
      hist->SetBinContent(j+1,yield/fit->Eval(pt));
      hist->SetBinError(j+1,error/fit->Eval(pt));
    }else{
      hist->SetBinContent(j+1,1E10);
      hist->SetBinError(j+1,1E-10);
    }
  }
}

void divideByWidth(TH1D *hist){

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
