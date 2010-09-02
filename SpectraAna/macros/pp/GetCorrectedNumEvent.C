//-------------------------------------------------------------------------------
// July 11 2010 Andre S. Yoon
//
// This macros reads the outputs of TrackSpectraAnalyzer and various stages of 
// EvtSelAnalyzer and VertexAnalyzer and get (various levels of) corrected
// number of events. It outputs numbers in std I/O (and *.out file as well), 
// which later need to be used for event normalization. 
//
//
// CORRECTION LEVEL CONVENTIONS
//   1. raw  - number of events that went into TrackSpectraAnalyzer
//   2. lev1 - number of events corrected with evt selection efficiency 
//   3. lev2 - lev1 + zero bin fraction corrected (MC based)
//   4. lev3 - lev2 + 123 bins fraction corrected (MC based)
//   5. full - lev3 + pile-up corrected (estimated pile-up rate based)
//------------------------------------------------------------------------------- 

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

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TF1.h"

#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

#include "TDirectory.h"
#include "TDirectoryFile.h"

#include "TChain.h"
#include "TGraph.h"

#include "TKey.h"
using namespace std;

#endif

TFile *spectraF=0;
TFile *evtcorF=0;

char cList[100];
char cListEVT[100];

TH1F *hevt_raw=0, *hevt_lev1=0;
TH1F *hrecMultCorr=0;
TH1F *hnsd_genZ=0, *hnsd_genZOTT=0,*hnsd_genOTT=0;

//--------------------------------------------------------------------
double getZeroBinFraction(TH1F* hist);
double getZOTTBinFraction(TH1F* hist);
double getEffWeightedNevt(TH1F* histE);
//-------------------------------------------------------------------- 

void GetCorrectedNumEvent(const char *cDir="../root_files/",
			  const char *cDirOut="./rootOutput/",
			  const char *cFile="TrkHistMC_june09_qcdMB",
			  const char *cFileEVT="TrkHistMC_june09_qcdMB",
			  const char *dir_ana="trackAna_STD",
			  const char *dir_corr="trkEffAnalyzer",
			  double corrF=1,
			  bool isGEN=false, 
			  bool saveFile=false)

{

   cout<<"\n"<<"\n"<<endl;
   sprintf(cList,"%s%s.root",cDir,cFile);   // spectra file
   sprintf(cListEVT,"%s%s.root",cDir,cFileEVT); // output file with evt_sel_ana/vtx_sel_ana

   spectraF = (TFile*) loadFile(spectraF,cList);
   evtcorF = (TFile*) loadFile(evtcorF,cListEVT);

   // get raw, corrected number of events from spectra file ------------------------------------------

   double nevt_raw = 0.0;               // number of entries 
   double nevt_lev1 = 0.0;              // number of entries weithed by evt sel eff 
   double nevt_lev1_mult = 0.0;         // number of entries weighted by eve sel eff (mult dist hist)
   double nevt_lev1_mult1toInf = 0.0;   // number of entries weighted by eve sel eff (mult: 1 ~ inf)
   double nevt_lev1_mult1to3 = 0.0;     // number of entries weighted by eve sel eff (mult: 1 ~ 3)

   double nevt_lev2 = 0.0, nevt_lev2_mult = 0.0;
   double nevt_lev3 = 0.0, nevt_lev3_mult = 0.0;
   double nevt_lev3_mult_data = 0.0;

   char histStr[100], histStr_mult[100];

   sprintf(histStr,"%s/hNevt",dir_ana); 
   sprintf(histStr_mult,"%s/hRecMult_STD_corr",dir_ana);

   cout<<"\n"<<"number of event is from "<<histStr<<endl;
   cout<<"mult distribution hist is from "<<histStr_mult<<endl;

   hevt_raw = (TH1F*) spectraF->Get(histStr);
   hrecMultCorr = (TH1F*) spectraF->Get(histStr_mult);

   if(hevt_raw==0||
      hrecMultCorr==0) {
      Error("[HistLoading]","could not get histogram for hevt_raw or hrecMultCorr");
      return;
   }

   nevt_raw = hevt_raw->GetEntries();
   nevt_lev1 = getEffWeightedNevt(hevt_raw);  
   nevt_lev1_mult = hrecMultCorr->Integral();

   nevt_lev1_mult1toInf = hrecMultCorr->Integral(2,hrecMultCorr->GetXaxis()->GetLast());
   nevt_lev1_mult1to3 = hrecMultCorr->Integral(2,4);

   // why nevt_lev1 =! nevt_lev1_mult ?
   
   cout<<"\n"<<endl;
   cout<<"============================== NUMBER OF EVENTS ==================================="<<endl;
   cout<<"raw number of events is  "<<nevt_raw<<endl;
   cout<<"evt sel eff corrected number of event is "<<nevt_lev1<<endl;
   cout<<"evt sel eff corrected number of event (from multiplicity hist) is "<<nevt_lev1_mult<<endl;
   cout<<"evt sel eff corrected number of event (mult: 1~Inf) is "<<nevt_lev1_mult1toInf<<endl;
   cout<<"evt sel eff corrected number of event (mult: 1~3) is "<<nevt_lev1_mult1to3<<endl;

   // **later two numbers should be equal to the one before and 0 respectively
   // "if tight selection is being looked at!

   // get 0,1,2,3 bin fractions from preTrgAna (before minBiasBscFilter => right after l1)--------------
   double zerobinF=0;
   double zottbinF=0;

   hnsd_genZ = (TH1F*) evtcorF->Get("preTrgAna/hGenRecMultNSD_STD");
   if(hnsd_genZ==0) {
      Error("[HistLoading]","could not get histogram");
      return;
   }

   zerobinF = getZeroBinFraction(hnsd_genZ);
   cout<<"Zero bin fraction = "<<zerobinF<<endl;
   
   hnsd_genZOTT = (TH1F*) evtcorF->Get("preTrgAna/hGenRecMultNSD_STD");
   if(hnsd_genZOTT==0) {
      Error("[HistLoading]","could not get histogram");
      return;
   }
   
   zottbinF = getZOTTBinFraction(hnsd_genZOTT);
   cout<<"0,1,2,3 bin fraction = "<<zottbinF<<endl;

   nevt_lev2 = nevt_lev1/(1-zerobinF);
   nevt_lev3 = nevt_lev1/(1-zottbinF);

   nevt_lev2_mult = nevt_lev1_mult/(1-zerobinF);
   nevt_lev3_mult = nevt_lev1_mult/(1-zottbinF);

   //if(corrF==1) corrF=1;
   //else corrF = nevt_lev1_mult1toInf/(nevt_lev1_mult1toInf-nevt_lev1_mult1to3);

   nevt_lev3_mult_data = nevt_lev2_mult*corrF;

   cout<<"correction factor for mult (used): 1~3 is "<<corrF<<endl;
   //cout<<"correction factor for mult (calculated): 1~3 is "<<nevt_lev1_mult1toInf/(nevt_lev1_mult1toInf-nevt_lev1_mult1to3)<<endl;
   cout<<"number of event (zero bin corrected) is "<<nevt_lev2<<endl;
   cout<<"number of event (0,1,2,3 bin corrected) is "<<nevt_lev3<<endl;
   cout<<"number of event (zero bin corrected) is (from mult dist hist) "<<nevt_lev2_mult<<endl;
   cout<<"number of event (0,1,2,3 bin corrected) is (from mult dist hist) "<<nevt_lev3_mult<<endl;
   cout<<"number of event (0,1,2,3 bin corrected) is (data driven for 1,2,3) "<<nevt_lev3_mult_data<<endl;
   cout<<"============================== NUMBER OF EVENTS ==================================="<<endl;
   cout<<"\n"<<endl;

}

double getEffWeightedNevt(TH1F* histE){

   double nevt = 0;
   for(int i=0;i<histE->GetNbinsX();i++){
      nevt = nevt + (histE->GetBinContent(i+1)/histE->GetBinCenter(i+1));
   }
   return nevt;

}

// fraction is defined as a fraction of event with mult =x out of N_{tot}
// not out of N_{i} (where i = 4,5,6.. (summed implicitly)) 
double getZeroBinFraction(TH1F* histZ){

   double total = histZ->Integral();
   double zerobin = histZ->Integral(1,1);
   double fraction = (zerobin)/total;
   return fraction;
}

double getZOTTBinFraction(TH1F* histZOTT){

   double total = histZOTT->Integral();
   double zerobin = histZOTT->Integral(1,4);
   double fraction = (zerobin)/total;
   return fraction;
}
