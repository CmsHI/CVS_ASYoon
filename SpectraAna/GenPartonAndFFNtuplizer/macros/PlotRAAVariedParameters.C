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

/*
  - Inspect chi^2 of toy-model with respect to the data 
  - for a given "fit" range and find the best one 
  - that describes the measurements in different centrality 
*/

double calResidChi2(TGraphErrors *tg_data, TGraphErrors *tg_model, double minpt);
void divideByWidth(TH1 *hist);
void setErrorY(TH1D *hist);

//Int_t color[15]={kViolet+2,kBlue,kAzure+6,kGreen-3,kOrange-5,kOrange-3,kOrange+4,kRed-3,kRed,kRed+2,kMagenta+1,kRed+1,kGreen+3,kBlue+3,kViolet+4};
Int_t color[15]={kViolet+2,kBlue,kAzure+6,kGreen-3,kOrange-5,kOrange-3,kOrange+4,kRed-3,kRed,kRed+2,kMagenta+1,kRed+1,kRed+2,kPink+4,kPink-6};

void PlotRAAVariedParameters(int centbin=0){


  // Varialbes
  float jraa_xmin = 10.0;
  float jraa_xmax = 400.0;

  float craa_xmin = 1.0;
  float craa_xmax = 130.0;

  float rebinf = 4;

  float msize = 0.8;
  
  TString cbintag;
  TString cbin;
  if(centbin==0){
    cbin = "0010";
    cbintag = "0-10%";
  }else if(centbin==1){
    cbin = "1030";
    cbintag = "10-30%";
  }else if(centbin==2){
    cbin = "3050";
    cbintag = "30-50%";
  }else if(centbin==3){
    cbin = "5070";
    cbintag = "50-70%";
  }else if(centbin==4){
    cbin = "7090";
    cbintag = "70-90%";
  }else if(centbin==5){
    cbin = "0005";
    cbintag = "0-5%";
  }


  // Read RAA data 
  TString inf_raa_cbin1 = Form("../data_tables/raa/raa_%s_ptmean_sumerr.txt",cbin.Data());
  TGraphErrors *gpraa_cbin1 = new TGraphErrors(inf_raa_cbin1.Data(),"%lg %lg %lg");

  
  
  if (!gpraa_cbin1 || gpraa_cbin1->IsZombie()){
    Error("<Data Point Reading>","RAA data points reading");
    return 0;
  }


  TString dir = "../root_files/";

  vector<TFile*> f;
  vector<double> par;

  // First one should be reference (with FF)
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN.root",dir.Data())));         

  // With JetQuenching
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog0.20.root",dir.Data())));
  par.push_back(0.2);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog0.40.root",dir.Data())));
  par.push_back(0.4);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog0.60.root",dir.Data())));
  par.push_back(0.6);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog0.80.root",dir.Data())));
  par.push_back(0.8);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.00.root",dir.Data())));
  par.push_back(1.0);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.20.root",dir.Data())));
  par.push_back(1.2);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.40.root",dir.Data())));
  par.push_back(1.4);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.60.root",dir.Data())));
  par.push_back(1.6);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog1.80.root",dir.Data())));
  par.push_back(1.8);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.00.root",dir.Data())));
  par.push_back(2.0);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.20.root",dir.Data())));
  par.push_back(2.2);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.40.root",dir.Data())));
  par.push_back(2.4);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.60.root",dir.Data())));
  par.push_back(2.6);
  f.push_back(new TFile(Form("%s/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog3.00.root",dir.Data())));
  par.push_back(3.0);

  // Chi^2 graph
  TGraph *tg_chi2 = 0;
  Double_t px[par.size()], py[par.size()];
  

  TCanvas *c1 =new TCanvas("c1","Jet and Charged Particle R_{AA}",1000,500);
  c1->Divide(2,1);


  TH1D *hdum = new TH1D("hdum","",200,0.0,1400);
  hdum->SetStats(0);
  hdum->SetAxisRange(0.0,1.5,"Y");
  hdum->SetAxisRange(jraa_xmin,jraa_xmax,"X");
  hdum->GetXaxis()->CenterTitle();
  hdum->GetYaxis()->CenterTitle();
  hdum->GetYaxis()->SetTitle("Jet R_{AA}");
  hdum->GetXaxis()->SetTitle("E_{T} (GeV)");
  hdum->GetXaxis()->SetMoreLogLabels();

  TH1D *hdum2 = (TH1D*) hdum->Clone("hdum2");
  hdum2->SetAxisRange(0.0,1.5,"Y");
  hdum2->SetAxisRange(craa_xmin,craa_xmax,"X");
  hdum2->GetYaxis()->SetTitle("Charged Particle R_{AA}");
  hdum2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hdum2->GetXaxis()->SetMoreLogLabels();


  c1->cd(1);
  hdum->Draw("");
  
  c1->cd(2);
  hdum2->Draw("");

  gpraa_cbin1->SetMarkerSize(1.1*msize);
  gpraa_cbin1->Draw("pzsame");
  
  double small = 1e-3;

  // First get reference
  TH1F *hdnevtminpthat_ref = (TH1F*) f[0]->Get("dNevtMinPtHat");
  TH1F *hjetspecv0 = (TH1F*) f[0]->Get("dNJetdEt");
  TH2F *hdntrkdptdpthat = (TH2F*) f[0]->Get("dNTrkdPtdPtHat");
  TH3F *hdntrkdptdpthatdjetet = (TH3F*) f[0]->Get("dNTrkdPtdPtHatdJetEt");

  double tot_evt_minpthat_ref = hdnevtminpthat_ref->GetEntries();

  hjetspecv0->Scale(1./tot_evt_minpthat_ref);
  hdntrkdptdpthat->Scale(1./tot_evt_minpthat_ref);
  hdntrkdptdpthatdjetet->Scale(1./tot_evt_minpthat_ref);

  divideByWidth(hjetspecv0);

  TH1D *hjetspecv0_cln = (TH1D*) hjetspecv0->Clone("hjetspecv0_cln");
  hjetspecv0_cln->Rebin(rebinf);

  TH1D *hdntrkdpt = (TH1D*) hdntrkdptdpthat->ProjectionX("",0,-1,"e"); // template                                                                   
  hdntrkdpt->SetName("hdntrkdpt");
  hdntrkdpt->Reset();
  TH1D *hdntrkdpt_cln = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_cln");

  // Obtain Fragmentation functions ---------------------------------------
  for(int j=0;j<hdntrkdptdpthatdjetet->GetNbinsZ();j++){

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

    // Reference spectra
    TH1D *hdntrkdpt_ff_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_cln");
    hdntrkdpt_ff_cln->Scale(dsigma); 
    hdntrkdpt_cln->Add(hdntrkdpt_ff_cln);
  }
  hdntrkdpt_cln->Rebin(rebinf);
  // -------------------------------------------------------------------------

  TLegend *legd = new TLegend(0.20,0.68,0.91,0.92);
  legd->SetNColumns(3);
  legd->SetMargin(0.2);
  legd->SetBorderSize(0);
  legd->SetFillColor(kWhite);
  legd->SetFillStyle(0);
  legd->SetTextSize(0.035);
  legd->SetMargin(0.25);
  //legd->SetHeader(Form("%s",cbintag.Data()));

  for(unsigned i=1; i<f.size(); i++) {

    TH1F *hdnevtminpthat = (TH1F*) f[i]->Get("dNevtMinPtHat");
    double tot_evt_minpthat = hdnevtminpthat->GetEntries();
    cout<<"Number of min_pt_hat event sample = "<<tot_evt_minpthat<<endl;

    TH1F *hjetspec_fracv0 = (TH1F*) f[i]->Get("dNJetdEt");
    
    // Overall Normalization 
    hjetspec_fracv0->Scale(1./tot_evt_minpthat);
    
    divideByWidth(hjetspec_fracv0);
    

    // Jet RAA
    c1->cd(1);

    TH1D *hjetspec_fracv0_cln = (TH1D*) hjetspec_fracv0->Clone("hjetspec_fracv0_cln");
    hjetspec_fracv0_cln->Rebin(rebinf);

    hjetspec_fracv0_cln->Divide(hjetspecv0_cln);
    //tg_jetspec_fracv0_cln->Draw("pzsame");
    setErrorY(hjetspec_fracv0_cln);
    
    TGraphErrors *tg_jetspec_fracv0_cln = (TGraphErrors*) TgraphIt(hjetspec_fracv0_cln);
    tg_jetspec_fracv0_cln->SetLineWidth(2);
    tg_jetspec_fracv0_cln->SetLineColor(color[i%15-1]);
    tg_jetspec_fracv0_cln->Draw("lsame");
    
    // Charged Particle RAA
    c1->cd(2);
    TH1D *hdntrkdpt_fracv0 = (TH1D*) hdntrkdpt->Clone("hdntrkdpt_fracv0");
    
    for(int k=0;k<hdntrkdptdpthatdjetet->GetNbinsZ();k++){

      double etcent = hdntrkdptdpthatdjetet->GetZaxis()->GetBinCenter(k+1);
      double etmin2 = hdntrkdptdpthatdjetet->GetZaxis()->GetBinLowEdge(k+1);
      double etmax2 = hdntrkdptdpthatdjetet->GetZaxis()->GetBinUpEdge(k+1);

      TH1D *hdntrkdpt_ff = (TH1D*) gDirectory->Get(Form("hdntrkdpt_ff_et%1.0fto%1.0f",etmin2,etmax2));
      if(hdntrkdpt_ff==0) continue;  // don't use empty histograms                                                                                     
      TH1D *hdntrkdpt_ff_fracv0_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_fracv0_cln");

      double dsigma_fracv0 = hjetspec_fracv0->GetBinContent(k+1);

      hdntrkdpt_ff_fracv0_cln->Scale(dsigma_fracv0);

      hdntrkdpt_fracv0->Add(hdntrkdpt_ff_fracv0_cln);

    }

    TH1D *hdntrkdpt_fracv0_cln = (TH1D*) hdntrkdpt_fracv0->Clone("hdntrkdpt_fracv0_cln");
    hdntrkdpt_fracv0_cln->Rebin(rebinf);
    hdntrkdpt_fracv0_cln->Divide(hdntrkdpt_cln);
    setErrorY(hdntrkdpt_fracv0_cln);

    TGraphErrors *tg_dntrkdpt_fracv0_cln = (TGraphErrors*) TgraphIt(hdntrkdpt_fracv0_cln);
    tg_dntrkdpt_fracv0_cln->SetLineWidth(2);
    tg_dntrkdpt_fracv0_cln->SetLineColor(color[i%15-1]);
    tg_dntrkdpt_fracv0_cln->Draw("lsame");

    legd->AddEntry(tg_dntrkdpt_fracv0_cln,Form("c = %1.1f",par[i-1]),"l");

    double chi2_residual = calResidChi2(gpraa_cbin1,tg_dntrkdpt_fracv0_cln,5.0);
    cout<<"Parameter = "<<1<<" Chi^2/NDF = "<<chi2_residual<<endl;
    px[i-1] = par[i-1];
    py[i-1] = chi2_residual;
  }


  // draw
  legd->Draw();

  TLatex *tl = new TLatex(0.8,0.2,Form("%s",cbintag.Data()));
  tl->SetTextFont(63);
  tl->SetTextSize(20);
  tl->SetTextColor(kBlack);
  tl->SetLineWidth(1);
  tl->SetNDC();
  tl->Draw("");

  // Draw Chi^2 residual
  TCanvas *c2 =new TCanvas("c2","Chi^2 Residual between data vs model",500,500);
  gPad->SetGridx();
  gPad->SetGridy();

  tg_chi2 = new TGraph(par.size(),px,py);
  tg_chi2->SetLineWidth(2);
  tg_chi2->SetMarkerSize(1.5*msize);
  tg_chi2->SetMarkerColor(kRed);
  tg_chi2->GetYaxis()->CenterTitle();
  tg_chi2->GetXaxis()->CenterTitle();
  tg_chi2->GetYaxis()->SetTitle("Normalized #chi^{2}");
  tg_chi2->GetXaxis()->SetTitle("Parameter"); 
  tg_chi2->Draw("Aplsame");


}





double calResidChi2(TGraphErrors *tg_data, TGraphErrors *tg_model, double minpt){

  int nbins = tg_data->GetN();
  const int nlines = nbins;

  double pt[nlines], xsec[nlines];
  double pterr[nlines], xsecerr[nlines];

  double chi2 = 0.0;

  int npts = 0;

  for(int i = 0; i<nbins; i++ ){

    // data
    tg_data->GetPoint(i,pt[i],xsec[i]);
    pterr[i] = tg_data->GetErrorX(i);
    xsecerr[i] = tg_data->GetErrorY(i);

    if(pt[i]<minpt) continue;

    // model
    
    double diff = (xsec[i] - tg_model->Eval(pt[i]))/xsecerr[i];
    chi2 = chi2 + diff*diff;

    npts++;
  }

  return chi2/npts; 
  
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
