//--------------------------------------------------------------------------------------
// August 3 2010    Andre S. Yoon
// 
// This macros reads the two output files of CorrectTypeOneNSave.C and get a correction
// factor (in the form of a functional form) as a function of pT for the spectra not
// included in track (~4) event selection (multiplicity of 1,2,3).
//
// One output file should contain the spectra for multiplicity of 1~inf
// The other output file should contain the spectra for multiplicity of 1~3 
// (hTrkPtEtaJetEtMult0to3_vbin)
// 
// The correction factor obtained here is applied in the CorrectTypeOneNSave.C
// ** the correction factor is obtained in the corrected dn/dpt level (not in the inva
// yield level) so it should be applied in the type one, not in type two!
//-------------------------------------------------------------------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include <utility>
#include <iostream>

#include "utilities.h"
#include "commonStyle.h"

#include <TROOT.h>
#include <TStyle.h>
#include "TError.h"

#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "TMath.h"

#include "TDirectory.h"
#include "TDirectoryFile.h"

#include "TChain.h"
#include "TGraph.h"

#include "TLine.h"

#include "TKey.h"
#include "TString.h"

using namespace std;

#endif

char inFile1[300], inFile2[300];
TFile *spectraF1=0, *spectraF2=0;

TH1D *hdndpt_1toinf=0, *hdndpt_1to3=0;
TH1D *hdndpt_1toinfR=0, *hdndpt_1to3R=0;
TH1D *hdndpt_diff=0, *hdndpt_corr=0;

TF1 *fitF=0;

TCanvas *can1=0, *can2=0, *can3=0, *can4=0, *can5=0, *can6=0, *can7=0;
TH1D *dum1=0, *dum2=0, *dum3=0, *dum4=0, *dum5=0, *dum6=0, *dum7=0;


void GetCorFact1to3Spectra(const char *cFile1="CORR_TEST1_trkhists_r132440_v2_eta_0.0to1.0_jet_0.0to2000.0_looseTrackAna_STD_GEN0_varBin1_otthist0",
			   const char *cFile2="CORR_TEST1_trkhists_r132440_v2_eta_0.0to1.0_jet_0.0to2000.0_looseTrackAna_STD_GEN0_varBin1_otthist1",
			   const char *dir_ana="loosetrackAna_STD",
			   float ieta=0, float feta=1.0, int rebinF=4
			   )

{

  gStyle->SetOptTitle(1);
  gStyle->SetPadTopMargin(0.1);

  cout<<"\n"<<"\n"<<endl;
  cout<<"Rebinning factor = "<<rebinF<<endl;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH3::SetDefaultSumw2();

  sprintf(inFile1,"./rootOutput/%s.root",cFile1);
  cout<<"First input file for spectra (1~inf bin)  will be "<<inFile1<<endl;
  
  sprintf(inFile2,"./rootOutput/%s.root",cFile2);
  cout<<"Second input file for spectra (1~3 bin) will be "<<inFile2<<endl;

  spectraF1 = (TFile*) loadFile(spectraF1,inFile1);
  spectraF2 = (TFile*) loadFile(spectraF2,inFile2);

  char histStr1[100], histStr2[100];
  sprintf(histStr1,"corrTypeOne/hdndpt_full");
  sprintf(histStr2,"corrTypeOne/hdndpt_full");

  cout<<"\n"<<endl;
  cout<<"1st spectra hist to be looked at = "<<histStr1<<endl;
  cout<<"2nd spectra hist to be looked at = "<<histStr2<<endl;
  cout<<"eta range from 0 to "<<feta<<endl;

  hdndpt_1toinf = (TH1D*) spectraF1->Get(histStr1);
  hdndpt_1to3 = (TH1D*) spectraF2->Get(histStr2);

  if(hdndpt_1toinf==0||hdndpt_1to3==0) {
    Error("[HistLoading]","could not get histogram");
    return;
  }


  //hdndpt_1toinf->Rebin(2,"hdndpt_1toinf"), hdndpt_1toinf->Scale(1/2);
  //hdndpt_1to3->Rebin(2,"hdndpt_1to3"), hdndpt_1to3->Scale(1/2);

  hdndpt_1toinfR = (TH1D*) hdndpt_1toinf->Rebin(rebinF,"hdndpt_1toinfR"), hdndpt_1toinfR->Scale((double)(1./rebinF));
  hdndpt_1to3R = (TH1D*) hdndpt_1to3->Rebin(rebinF,"hdndpt_1to3R"), hdndpt_1to3R->Scale((double)(1./rebinF));

  can1 = new TCanvas("can1","can1",550,410);
  can1->cd(), can1->SetLogy();

  dum1 = GetDummyHist(0.1,100,(2E-6),(1E+2),"p_{T}","dN/dp_{T}",true);
  dum1->SetTitle("raw dn/dpt"), dum1->SetName("dum1");
  dum1->Draw();

  hdndpt_1toinfR->SetMarkerColor(1), hdndpt_1toinfR->SetMarkerSize(1);
  hdndpt_1toinfR->Draw("pzsame");

  hdndpt_1to3R->SetMarkerColor(2), hdndpt_1to3R->SetMarkerSize(1);
  hdndpt_1to3R->Draw("pzsame");


  hdndpt_diff = (TH1D*) hdndpt_1toinfR->Clone("hdndpt_diff");
  hdndpt_diff->Add(hdndpt_1to3R,-1.0);
  hdndpt_diff->Sumw2();

  hdndpt_corr = (TH1D*) hdndpt_1toinfR->Clone("hdndpt_corr");
  hdndpt_corr->Sumw2();
  hdndpt_corr->Divide(hdndpt_diff);
  
  can2 = new TCanvas("can2","can2",550,410);
  can2->cd();

  dum2 = GetDummyHist(0.1,10,0.98,1.05,"p_{T}","Ratio Spect(1~inf) / Spect(4~inf)",true);
  dum2->SetTitle("correction factor"), dum2->SetName("dum2");
  dum2->Draw();
  
  hdndpt_corr->SetMarkerColor(2), hdndpt_corr->SetMarkerSize(1);
  hdndpt_corr->Draw("pzsame");

  TLine *line = new TLine(0,1,10,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  /*
  fitF = new TF1("fitFunction","[0]+[1]*pow(x,[2])+[3]*pow(x,[4])",0.2,3.5);
  fitF->SetParameters(1,6,-0.005,1,1);
  */

  fitF = new TF1("fitFunction","pol4(0)",0.4,4.0);
  fitF->SetParameters(1,1.5,-3,1,-2);

  //fitF = new TF1("fitFunction","pol3(0)",0.4,4.0);
  //fitF->SetParameters(1,1.5,-3,1);


  hdndpt_corr->Fit(fitF,"NLR");
  fitF->Draw("same");
}
