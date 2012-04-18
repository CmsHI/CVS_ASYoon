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

double GetMeanV2(TH1D *hist);
void setHist(TH1D *hist);
void divideByWidth(TH1 *hist);
void setErrorY(TH1D *hist);
void Obtain2DFF(TH3F* hist3d, TH1F* hist1d);
void ObtainFF(TH3F* hist3d, TH1F* hist1d);

double FourierDecomp(double *x, double *par){

  double cterm1 = 2*par[1]*cos(x[0]);
  double cterm2 = 2*par[2]*cos(2*x[0]);
  double cterm3 = 2*par[3]*cos(3*x[0]);
  double cterm4 = 2*par[4]*cos(4*x[0]);
  double cterm5 = 2*par[5]*cos(5*x[0]);
  double cterm6 = 2*par[6]*cos(6*x[0]);

  return par[0]*(1 + cterm1 + cterm2 + cterm3 + cterm4 + cterm5 + cterm6);
}



/* 
   Two different methods for extracting v2

   1. Directly extract v2 = <cos2(phi-psi)> over all particles in all events
   2. Fit the distributions with 1 + Sum(2xv_{i}xcos[i(phi-pse)])

   1. Jet V2
   - Fit each dPhi distribution of Jet in Jet ET bin 

   2. Charged Particle V2
   - First convolute Jet with FF assuming no dPhi dendence of FF
   - Fit each dPhi distribution of convoluted particle spectra
*/


void PlotV2ForJetAndTrack(){


  /* Variable */
  double ETMIN = 15;
  
  /* File Loading */
  TFile *f1 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN.root");

  TFile *f2=0, *f3=0, *f4=0;
  f2 = new TFile("../root_files/ANA_spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN_jetQ_fractLog2.00_phidep_a7.00_b10.00.root");

  /* Histogram Loading */
  TH1F *hdnevtminpthat = (TH1F*) f1->Get("dNevtMinPtHat");

  TH1F *hjetspecv0 = (TH1F*) f1->Get("dNJetdEt");

  TH2F *hjetspecdphiv0 = (TH2F*) f1->Get("dNJetdEtdPhi");
  TH2F *hjetspecdphiv0_q1 = (TH2F*) f2->Get("dNJetdEtdPhi");
  TH2F *hjetspecdcos2phiv0_q1 = (TH2F*) f2->Get("dNJetdEtdCos2Phi");

  TH2F *hdntrkdptdpthat = (TH2F*) f1->Get("dNTrkdPtdPtHat");

  TH3F *hdntrkdptdjetetdphi = (TH3F*) f1->Get("dNTrkdPtdJetEtdPhi");
  TH3F *hdntrkdptdpthatdjetet = (TH3F*) f1->Get("dNTrkdPtdPtHatdJetEt");
  

  double small = 1e-3;
  double tot_evt_minpthat = hdnevtminpthat->GetEntries();

  cout<<"Number of min_pt_hat event sample = "<<tot_evt_minpthat<<endl;

  if(tot_evt_minpthat<1E-22){
    cout<<"This sample doesn't include the minimum pt hat bin sample!"<<endl;
    return;
  }

  /* Overall Normalization */
  hjetspecv0->Scale(1./tot_evt_minpthat);
  hjetspecdphiv0->Scale(1./tot_evt_minpthat);
  hjetspecdphiv0_q1->Scale(1./tot_evt_minpthat);
  hdntrkdptdpthat->Scale(1./tot_evt_minpthat);
  hdntrkdptdjetetdphi->Scale(1./tot_evt_minpthat);
  hdntrkdptdpthatdjetet->Scale(1./tot_evt_minpthat);

  /* Dividing By Bin Width */
  divideByWidth(hjetspecv0);


  /* Duplications of Some Histograms */
  TH2F *hjetspecdphiv0_cln = (TH2F*) hjetspecdphiv0->Clone("hjetspecdphiv0_cln");
  TH2F *hjetspecdphiv0_q1_cln = (TH2F*) hjetspecdphiv0_q1->Clone("hjetspecdphiv0_q1_cln");
  TH3F *hdntrkdptdjetetdphi_cln = (TH3F*) hdntrkdptdjetetdphi->Clone("hdntrkdptdjetetdphi_cln");


  /* Dum Histograms */
  TH1D *hdum = new TH1D("hdum","",200,-3.2,3.2);
  hdum->SetStats(0);
  hdum->SetAxisRange(-0.001,0.1,"Y");
  hdum->GetXaxis()->SetTitle("#phi - #psi (rad)");
  hdum->GetXaxis()->CenterTitle();
  hdum->GetYaxis()->SetTitle("A.U");
  hdum->GetYaxis()->CenterTitle();
  hdum->GetXaxis()->SetMoreLogLabels();
  setHist(hdum);

  TH1D *hdum_1 = (TH1D*) hdum->Clone("hdum_1");
  hdum_1->SetAxisRange(0.0,2.0,"X");
  hdum_1->SetAxisRange(-0.001,0.2,"Y");
  hdum_1->GetXaxis()->SetTitle("2cos(#phi - #psi (rad))");
  

  /* ------------ Jet V2 --------------- */

  cout<<"Number of ET bins = "<<hjetspecdphiv0_q1->GetNbinsX()<<endl;

  TCanvas *c0 = new TCanvas("c0","",1250,930);
  makeMultiPanelCanvas(c0,5,4,0.0,0.0,0.2,0.2,0.02);

  TCanvas *c0_1 = new TCanvas("c0_1","",1250,930);
  makeMultiPanelCanvas(c0_1,5,4,0.0,0.0,0.2,0.2,0.02);


  int index = 0;
  hjetspecdphiv0_q1->RebinX(10);  // as original bin is too fine
  hjetspecdcos2phiv0_q1->RebinX(10);

  TH1D *hjetspecdphiv0_q1_projx= (TH1D*) hjetspecdphiv0_q1->ProjectionX("hjetspecdphiv0_q1_projx",0,-1,"e");
  TH1D *hjetspecdcos2phiv0_q1_projx= (TH1D*) hjetspecdcos2phiv0_q1->ProjectionX("hjetspecdcos2phiv0_q1_projx",0,-1,"e");

  for(int i=0;i<hjetspecdphiv0_q1->GetNbinsX();i++){
    
    double etmin = hjetspecdphiv0_q1->GetXaxis()->GetBinLowEdge(i+1);
    double etmax = hjetspecdphiv0_q1->GetXaxis()->GetBinUpEdge(i+1);

    // dPhi distribution of Jet
    TH1D *hjetspec_dphi = (TH1D*) hjetspecdphiv0_q1->ProjectionY("",i+1,i+1,"e");
    hjetspec_dphi->SetName(Form("hjetspec_dphi_et%1.0fto%1.0f",etmin,etmax));     

    // cos(dPhi) distribution of Jet
    TH1D *hjetspec_dcosphi = (TH1D*) hjetspecdcos2phiv0_q1->ProjectionY("",i+1,i+1,"e");
    hjetspec_dcosphi->SetName(Form("hjetspec_dcosphi_et%1.0fto%1.0f",etmin,etmax));

    // --> rebinning
    hjetspec_dphi->Rebin(4);
    hjetspec_dphi->Scale(1./4.);
    
    hjetspec_dcosphi->Rebin(4);
    hjetspec_dcosphi->Scale(1./4.);

    // --> dN/dphi (not necessary, though)
    //divideByWidth(hjetspec_dphi);

    // --> Normalization 
    hjetspec_dphi->Scale(1./hjetspec_dphi->Integral());
    hjetspec_dcosphi->Scale(1./hjetspec_dcosphi->Integral());


    // Draw
    if(etmin<ETMIN) continue;
    if(i%2+1) index++;
    if(index<20) {

      // Fitting methods
      c0->cd(index);
      hdum->Draw("");
      hjetspec_dphi->SetMarkerStyle(20);
      hjetspec_dphi->SetMarkerSize(1.0);
      hjetspec_dphi->Draw("pzsame");

      TLatex *tl_jet = new TLatex(0.5,0.8,Form("%1.1f<E_{T}<%1.1f",etmin,etmax));
      tl_jet->SetTextFont(63);
      tl_jet->SetTextSize(16);
      tl_jet->SetTextColor(kBlack);
      tl_jet->SetLineWidth(1);
      tl_jet->SetNDC();
      tl_jet->Draw("");

      // Fitting
      TF1 *fit1 = new TF1("fit1",FourierDecomp,-3.2,3.2,7);
      //for(int k=0;k<7;k++) fit1->SetParLimits(k,0,10);
      hjetspec_dphi->Fit(fit1,"RNQ");
      
      fit1->SetLineColor(kRed);
      fit1->SetLineWidth(2);
      fit1->Draw("same");

      double par1[7];
      const int binn = sizeof(par1)/sizeof(double) - 1;
      for(int j=0;j<binn;j++) par1[j] = 0.0;
      par1[0] = fit1->GetParameter(0);
      par1[2] = fit1->GetParameter(2);
      //cout<<"par1[2] = "<<par1[2]<<endl;

      TF1 *fit1_v2 = new TF1("fit1_v2",FourierDecomp,-3.2,3.2,7);
      fit1_v2->SetParameters(par1);
      fit1_v2->SetLineColor(kBlue);
      fit1_v2->SetLineWidth(2);
      fit1_v2->Draw("same");
      
      // Extracting methods
      c0_1->cd(index);
      hdum_1->Draw("");
      hjetspec_dcosphi->SetMarkerStyle(20);
      hjetspec_dcosphi->SetMarkerSize(1.0);
      hjetspec_dcosphi->Draw("pzsame");

      cout<<"PAR0 = "<<fit1->GetParameter(0)<<" PAR1 = "<<fit1->GetParameter(1)
	  <<" PAR2 = "<<fit1->GetParameter(2)<<" PAR3 = "<<fit1->GetParameter(3)<<endl;
      //cout<<"fit1->GetParameter(2) = "<<fit1->GetParameter(2)<<endl;
      //cout<<" hjetspec_dcosphi = "<<hjetspec_dcosphi->GetMean()<<endl;
      
      // v2 vs pT
      hjetspecdphiv0_q1_projx->SetBinContent(i+1,fit1->GetParameter(2));
      hjetspecdcos2phiv0_q1_projx->SetBinContent(i+1,GetMeanV2(hjetspec_dcosphi));
      //hjetspecdcos2phiv0_q1_projx->SetBinContent(i+1,hjetspec_dcosphi->Integral()/hjetspec_dcosphi->GetEntries());
      //hjetspecdcos2phiv0_q1_projx->SetBinContent(i+1,hjetspec_dcosphi->GetMean());
    }

    
  }

  // Drawing V2 (pT)
  TCanvas *c1 =new TCanvas("c1","v_{2} as a function of p_{T}",500,500);
  hjetspecdphiv0_q1_projx->SetStats(0);
  //hjetspecdphiv0_q1_projx->SetAxisRange(-0.0001,0.001,"Y");
  hjetspecdphiv0_q1_projx->SetAxisRange(-0.0001,2.0,"Y");    
  hjetspecdphiv0_q1_projx->SetAxisRange(ETMIN,300,"X");
  hjetspecdphiv0_q1_projx->GetYaxis()->SetTitle("Jet v_{2}");
  hjetspecdphiv0_q1_projx->GetXaxis()->SetTitle("Jet E_{T}");
  hjetspecdphiv0_q1_projx->GetXaxis()->CenterTitle();
  hjetspecdphiv0_q1_projx->GetYaxis()->CenterTitle();
  hjetspecdphiv0_q1_projx->GetXaxis()->SetMoreLogLabels();
  hjetspecdphiv0_q1_projx->SetMarkerSize(1.2);
  hjetspecdphiv0_q1_projx->Draw("");
  
  hjetspecdcos2phiv0_q1_projx->SetMarkerColor(kRed);
  hjetspecdcos2phiv0_q1_projx->SetMarkerSize(1.2);
  hjetspecdcos2phiv0_q1_projx->Draw("pzsame");



  /* ---------------- Convoluting Jet Spectra with FF ---------------- */

  // Obtain FF 
  // - 3D of (track pt, pthat, jet et) 
  // - 1D of dN/dET 

  //ObtainFF(hdntrkdptdpthatdjetet, hjetspecv0);
  Obtain2DFF(hdntrkdptdjetetdphi, hjetspecv0);
  
  TH2D *hdntrkdptdphi_cln = (TH2D*) hdntrkdptdjetetdphi_cln->Project3D("zxe");
  hdntrkdptdphi_cln->Reset();

  for(int ij=0;ij<hjetspecdphiv0_cln->GetNbinsX();ij++){

    double etmin = hjetspecdphiv0_cln->GetXaxis()->GetBinLowEdge(ij+1);
    double etmax = hjetspecdphiv0_cln->GetXaxis()->GetBinUpEdge(ij+1);

    // dPhi distribution of Jet
    TH1D *hjetspec_dphi_cln = (TH1D*) hjetspecdphiv0_q1_cln->ProjectionY("",ij+1,ij+1,"e");
    hjetspec_dphi_cln->SetName(Form("hjetspec_dphi_cln_et%1.0fto%1.0f",etmin,etmax));

    // FF (pt,phi) 
    TH2D *hdntrkdpt_2dff_cln2 = (TH2D*) gDirectory->Get(Form("hdntrkdpt_2dff_et%1.0fto%1.0f",etmin,etmax));
    if(hdntrkdpt_2dff_cln2==0) continue;  // don't use empty histograms  

    // Loop over phi in each jet ET bin 
    for(int ijk=0;ijk<hjetspec_dphi_cln->GetNbinsX();ijk++){ 
      
      double phimin = hjetspec_dphi_cln->GetXaxis()->GetBinLowEdge(ijk+1);
      double phimax = hjetspec_dphi_cln->GetXaxis()->GetBinUpEdge(ijk+1);

      //cout<<"phi: "<<phimin<<" to "<<phimax<<endl;

      //TH1D *hdntrkdpt_1dff_cln2 = (TH1D*) hdntrkdpt_2dff_cln2->ProjectionY("",ijk,ijk,"e");
      //hdntrkdpt_1dff_cln2->SetName(Form("hdntrkdpt_1dff_cln2_phi%1.0fto%1.0f",phimin,phimax));

      double dsigma_v0 = hjetspec_dphi_cln->GetBinContent(ijk+1);
      //hdntrkdpt_1dff_cln2->Scale(dsigma_v0);

      // Scale each (pt,phi) 
      for(int m=0;m<hdntrkdpt_2dff_cln2->GetNbinsX();m++){

	double ffval = hdntrkdpt_2dff_cln2->GetBinContent(m,ijk);
	double ffvalerr = hdntrkdpt_2dff_cln2->GetBinError(m,ijk);

	hdntrkdpt_2dff_cln2->SetBinContent(m,ijk,ffval*dsigma_v0);
	hdntrkdpt_2dff_cln2->SetBinError(m,ijk,ffvalerr*dsigma_v0);
      } // end of m

    }// end of ijk

    hdntrkdptdphi_cln->Add(hdntrkdpt_2dff_cln2);

  }// end of convolution

  /* ----------------------- Charged Particle V2 ----------------- */
  TCanvas *c2 =new TCanvas("c2","Track p_{T} vs #phi",500,500);
  hdntrkdptdphi_cln->Draw("COLZ");
  //hdntrkdptdphi_cln->ProjectionX()->Draw("");
  //hdntrkdptdphi_cln->ProjectionY()->Draw("");   
  

  TCanvas *c0_2 = new TCanvas("c0_2","",1250,930);
  makeMultiPanelCanvas(c0_2,5,4,0.0,0.0,0.2,0.2,0.02);


  for(int n=0;n<hdntrkdptdphi_cln->GetNbinsX();n++){
    
    
  }
  



}



double GetMeanV2(TH1D *hist){

  double mean = 0.0;

  for(int i=0;i<hist->GetNbinsX();i++){
    mean = mean + hist->GetBinContent(i+1)*hist->GetBinCenter(i+1);
  }
  
  return mean/hist->Integral();

}

void setHist(TH1D *hist){
  hist->GetYaxis()->SetNdivisions(509);
  hist->GetYaxis()->SetLabelFont(43);
  hist->GetYaxis()->SetTitleFont(43);
  hist->GetYaxis()->SetLabelSize(17);
  hist->GetYaxis()->SetTitleSize(20);
  hist->GetYaxis()->SetTitleOffset(4.2);

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetLabelFont(43);
  hist->GetXaxis()->SetTitleFont(43);
  hist->GetXaxis()->SetLabelSize(18);
  hist->GetXaxis()->SetTitleSize(18);
  hist->GetXaxis()->SetTitleOffset(3.2);

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


void Obtain2DFF(TH3F* hist3d, TH1F* hist1d){

  /*  Obrain 2D Fragmentation Functions (pt,phi)

  - It will create dN/dpT/dSigma for [ET,ET+small] in memory 
  - Which can be later picked up to convolute 

  */

  for(int j=0;j<hist3d->GetNbinsY();j++){ // this y-axis now

    double dsigma = hist1d->GetBinContent(j+1);
    if(dsigma<1E-22) continue; // no jet ET bins 

    double etmin = hist3d->GetYaxis()->GetBinLowEdge(j+1);
    double etmax = hist3d->GetYaxis()->GetBinUpEdge(j+1);

    // Fragmentation Function (Be carefull not [j+1,j+2]) 
    hist3d->GetYaxis()->SetRange(j+1,j+1);
    TH2D *hdntrkdpt_2dff = (TH2D*) hist3d->Project3D("zxe"); // phi -> y axis; pt -> x axis
    hdntrkdpt_2dff->SetName(Form("hdntrkdpt_2dff_et%1.0fto%1.0f",etmin,etmax));

    // --> dN/dpT
    //divideByWidth(hdntrkdpt_ff);

    // --> dN/dpTdphi / sigma
    hdntrkdpt_2dff->Scale(1./dsigma);

    // Reference spectra
    TH2D *hdntrkdpt_2dff_cln = (TH2D*) hdntrkdpt_2dff->Clone("hdntrkdpt_2dff_cln");
    hdntrkdpt_2dff_cln->Scale(dsigma);
  }

}


void ObtainFF(TH3F* hist3d, TH1F* hist1d){

  /*  Obrain Fragmentation Functions    

  - It will create dN/dpT/dSigma for [ET,ET+small] in memory 
  - Which can be later picked up to convolute

  */

  for(int j=0;j<hist3d->GetNbinsZ();j++){

    double dsigma = hist1d->GetBinContent(j+1);
    if(dsigma<1E-22) continue; // no jet ET bins 

    double etmin = hist3d->GetZaxis()->GetBinLowEdge(j+1);
    double etmax = hist3d->GetZaxis()->GetBinUpEdge(j+1);

    // Fragmentation Function (Be carefull not [j+1,j+2]) 
    TH1D *hdntrkdpt_ff = (TH1D*) hist3d->ProjectionX("",0,-1,j+1,j+1,"e");
    hdntrkdpt_ff->SetName(Form("hdntrkdpt_ff_et%1.0fto%1.0f",etmin,etmax));

    // --> dN/dpT 
    divideByWidth(hdntrkdpt_ff);

    // --> dN/dpT / sigma 
    hdntrkdpt_ff->Scale(1./dsigma);

    // Reference spectra
    TH1D *hdntrkdpt_ff_cln = (TH1D*) hdntrkdpt_ff->Clone("hdntrkdpt_ff_cln");
    hdntrkdpt_ff_cln->Scale(dsigma);
  }
  
}
