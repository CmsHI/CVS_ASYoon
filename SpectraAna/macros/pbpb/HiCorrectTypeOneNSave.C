//-------------------------------------------------------------------------------------
// June 30 2010 Andre S. Yoon
//
// This macro reads the output of TrackSpectraAnalyzer and extract dN/dpT for a given
// eta range, and correct for trk inefficiency based on the outputs of TrkEffAnalyzer.
// Various histograms are saved in a seperate root file, which in turn feeds the 
// next type correction, i.e CorrectTypeTwoNSave.C
//
// MC vs DATA
//    MC   -> a) RECO  
//         -> b) GEN (by isGEN flag)
//    DATA -> a) RECO
//
// CORRECTION LEVEL CONVENTION:
//    1. lev1 -> trk
//    2. lev2 -> trk+sec
//    3. full -> trk+sec+mult
//
// * UPDATE NOTE (Sept 21 2010)
//
// A major update is made to improve on tracking efficiency and fake rate corrections
// The idea is, knowing a priori that neither efficieny nor fake has exterem values 
// such as 0 or 1, when there's a such efficieny/fake is returned with small
// number of entries (or even none) due to various reasons (e.g. not enough statistics,
// different fragmetnation properties between the correction sample and the sample that
// is corrected), another correction is applied to the efficincy (or fake) number 
// by averaging near phase space (pt,jet). The search window for the near phase space 
// is determined by input ("clevel" in the member function)
//
// Also, now one more file is used for correction to deal with higher pT reach!
//
// * UPDATE NOTE (Nov 10 2010)
//
// Again it is modified for PbPb sepctra with a new name HiCorrectTypeOneNSave.C
//-------------------------------------------------------------------------------------


#if !defined(__CINT__) || defined(__MAKECINT__)

#include "HiCorrectType.h"

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

TH3F *hdndptdetadet=0;
TH3F *hdndptdetadet_raw=0;
TH3F *hdndptdetadet_lev1=0;
TH3F *hdndptdetadet_lev2=0;
TH3F *hdndptdetadet_full=0;

TH1D *hdndptR_raw_dum=0;

TH1D *hdndpt_raw=0, *hdndptR_raw=0;
TH1D *hdndpt_full=0, *hdndptR_full=0;
TH1D *hdndpt_lev1=0, *hdndptR_lev1=0;
TH1D *hdndpt_lev2=0, *hdndptR_lev2=0;

TH1D *hInv_raw=0, *hInvR_raw=0;
TH1D *hInv_full=0, *hInvR_full=0;
TH1D *hInv_lev1=0, *hInvR_lev1=0;
TH1D *hInv_lev2=0, *hInvR_lev2=0;

TF1 *fCorr=0;

TGraphErrors *tdndpt_raw=0, *tdndptR_raw=0;
TGraphErrors *tdndpt_full=0, *tdndptR_full=0;
TGraphErrors *tdndpt_lev1=0, *tdndptR_lev1=0;
TGraphErrors *tdndpt_lev2=0, *tdndptR_lev2=0;

TGraphErrors *tInv_raw=0, *tInvR_raw=0;
TGraphErrors *tInv_full=0, *tInvR_full=0;
TGraphErrors *tInv_lev1=0, *tInvR_lev1=0;
TGraphErrors *tInv_lev2=0, *tInvR_lev2=0;


TFile *spectraF=0;
TFile *trkcorF1=0, *trkcorF2=0,*trkcorF3=0,*trkcorF4=0,*trkcorF5=0,*trkcorF6=0;

TFile *outputFile=0;
TDirectory *dTypeOne=0;

const int NHIST = 6;
const char *cFileTRKArray[NHIST];

char hist1[100], hist2[100], hist3[100], hist4[100];
TH3F *hPNEff3D[NHIST], *hPDEff3D[NHIST], *hPNFake3D[NHIST], *hPDFake3D[NHIST];
std::pair<TH3F*,TH3F*> h3DEff[NHIST], h3DFake[NHIST];

char histMult1[100], histMult2[100];
TH3F *hPNMult3D[NHIST], *hPDMult3D[NHIST];
std::pair<TH3F*,TH3F*> h3DMult[NHIST];

char histSec1[100], histSec2[100];
TH3F *hPNSec3D[NHIST], *hPDSec3D[NHIST];
std::pair<TH3F*,TH3F*> h3DSec[NHIST];

char xTitle[100],yTitle[100];

TCanvas *call, *callR, *callRR;
TH1D *dum, *dumR, *dumRR;

char cList[100];
char cListTRK1[100], cListTRK2[100], cListTRK3[100];
char cListTRK4[100], cListTRK5[100], cListTRK6[100]; 
char outFile[300];

double jet_1st, jet_2nd, jet_3rd, jet_4th, jet_5th;
double var_1st, var_2nd, var_3rd, var_4th, var_5th; // var can be pt, Et, etc..

float recTracktotal = 0.0; 
int recTracktotalBin = 0;

// for eff
float recTrackNotCorrectedEff = 0.0; 
float recTrackWithNoEff = 0.0;
float recTrackWithHoaxEff = 0.0;
float recTrackWithEffOfOne = 0.0;
float recTrackWithEffOfZero = 0.0;
float recTrackWithHoaxFrag = 0.0;

int recTrackNotCorrectedEffBin = 0;
int recTrackWithNoEffBin = 0;
int recTrackWithHoaxEffBin = 0;
int recTrackWithEffOfOneBin = 0;
int recTrackWithEffOfZeroBin = 0;
int recTrackWithHoaxFragBin = 0;

// for fak
float recTrackNotCorrectedFak = 0.0; 
float recTrackWithNoFak = 0.0;
float recTrackWithHoaxFak = 0.0;
float recTrackWithFakOfOne = 0.0;
float recTrackWithFakOfZero = 0.0;
float recTrackWithHoaxFragFak = 0.0;

int recTrackNotCorrectedFakBin = 0;
int recTrackWithNoFakBin = 0;
int recTrackWithHoaxFakBin = 0;
int recTrackWithFakOfOneBin = 0;
int recTrackWithFakOfZeroBin = 0;
int recTrackWithHoaxFragBinFak = 0;

double pt_thres = 13.0; //  for debugging
double eta_thres = 1.0;

//------------------------------------------------------------------------------
void checkEtaRange(double iEta, double fEta, int EtaMin, int EtaMax);
void checkEtRange(double iJet, double fJet, int EtMin, int EtMax);
void prepareTrkEffCorrection(const char *dirCorr, const char *cTRK1,
                             const char *cTRK2, const char *cTRK3,
                             const char *cTRK4, const char *cTRK5, const char *cTRK6);
std::pair<TH3F*,TH3F*> getEffHists(const char *file, const char *dirC, 
				   const char *histN, const char *histD);
double GetEffFactor(TH3F* num, TH3F* den, double pt, double eta, double jet, int entrycut, bool nonzero);
double GetFakFactor(TH3F* num, TH3F* den, double pt, double eta, double jet, int entrycut, bool nonzero);
double GetEffFactorFromAvgNearPhaseS(int xbin, int ybin, int zbin, int xbinmax, int ybinmax, int zbinmax, double ptorig, 
				     double jetorig, double efforig, double eta, double etacut, bool nonzero, int clevel, int efforfak);
void GetEffFactorDEBUG(TH3F* num, TH3F* den, double pt, double eta, double jet);
TH1D *correctedFor1to3(TH1D *hist);
void drawDebugPlots();
void printDebug();
int findIndexOfTheLeast(std::vector<double> inv);
int findIndexBeforeSort(std::vector<double> sortedv, std::vector<float> unsortedv);
//-----------------------------------------------------------------------------


void HiCorrectTypeOneNSave(const char *cDirData="../root_files/data",
			   const char *cDirCorr="../root_files/mc",
			   const char *cDirOut="./rootOutput/",
			   const char *cFile="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK1="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK2="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK3="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK4="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK5="TrkHistMC_june09_qcdMB",
			   const char *cFileTRK6="TrkHistMC_june09_qcdMB",
			   const char *dir_ana="trackAna_STD",
			   const char *dir_corr="trkEffAnalyzer",
			   bool isGEN=false, bool varBin=false,
			   double ijet=0, double fjet=2000,
			   double ieta=0, double feta=2.4,
			   double scaleF=1,
			   int hiOrdCorrLevEff=0, int hiOrdCorrLevFak=0,
			   bool debug = true, bool onetothree = false,
			   bool correc1to3 = false,
			   bool drawFig =true, bool saveFile=false,
			   int version=0
			   )
{

   cout<<"\n"<<"\n"<<endl;

   cout<<">>>> scale factor = "<<scaleF<<endl;
   
   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();


   sprintf(outFile,"%sCORRv%i_%s_eta_%1.1fto%1.1f_jet_%1.1fto%1.1f_%s_GEN%i_varBin%i_otthist%i_correct1to3i%i_corrLevEff%i_corrLevFak%i.root",
	   cDirOut,version,cFile,ieta,feta,ijet,fjet,dir_ana,isGEN,varBin,onetothree,correc1to3,hiOrdCorrLevEff,hiOrdCorrLevFak);

   cout<<"Output file will be "<<outFile<<endl;
   cout<<"\n"<<endl;

   sprintf(cList,"%s%s.root",cDirData,cFile);
   sprintf(cListTRK1,"%s%s.root",cDirCorr,cFileTRK1);
   sprintf(cListTRK2,"%s%s.root",cDirCorr,cFileTRK2);
   sprintf(cListTRK3,"%s%s.root",cDirCorr,cFileTRK3);
   sprintf(cListTRK4,"%s%s.root",cDirCorr,cFileTRK4);
   sprintf(cListTRK5,"%s%s.root",cDirCorr,cFileTRK5);
   sprintf(cListTRK6,"%s%s.root",cDirCorr,cFileTRK6);

   spectraF = (TFile*) loadFile(spectraF,cList);
   trkcorF1 = (TFile*) loadFile(trkcorF1,cListTRK1);
   trkcorF2 = (TFile*) loadFile(trkcorF2,cListTRK2);
   trkcorF3 = (TFile*) loadFile(trkcorF3,cListTRK3);
   trkcorF4 = (TFile*) loadFile(trkcorF4,cListTRK4);
   trkcorF5 = (TFile*) loadFile(trkcorF5,cListTRK5);
   trkcorF6 = (TFile*) loadFile(trkcorF6,cListTRK6);

   char histName[50];

   if(isGEN) sprintf(histName,"hGenTrkPtEtaJetEt");
   else if(!onetothree) sprintf(histName,"hTrkPtEtaJetEt");
   else sprintf(histName,"hTrkPtEtaJetEtMult0to3");

   if(varBin) strcat(histName,"_vbin");

   char histStr[100];
   sprintf(histStr,"%s/threeDHist/%s",dir_ana,histName);
   cout<<"\n"<<endl;
   cout<<"spectra hist to be looked at = "<<histStr<<endl;

   hdndptdetadet = (TH3F*) spectraF->Get(histStr);
   if(hdndptdetadet==0) {
      Error("[HistLoading]","could not get histogram"); 
      return;
   }


   hdndptdetadet_raw = (TH3F*) hdndptdetadet->Clone("hdndptdetadet_raw");
   hdndptdetadet_raw->Reset();

   hdndptdetadet_lev1 = (TH3F*) hdndptdetadet->Clone("hdndptdetadet_lev1");
   hdndptdetadet_lev1->Reset();

   hdndptdetadet_lev2 = (TH3F*) hdndptdetadet->Clone("hdndptdetadet_lev2");
   hdndptdetadet_lev2->Reset();

   hdndptdetadet_full = (TH3F*) hdndptdetadet->Clone("hdndptdetadet_full");
   hdndptdetadet_full->Reset();

   // First decide eta and jet et range -----------------------------
   double small = 0.01; // when the eta value is at the edge (1.0 and 2.4 is at the edges!)  

   int eta_min_bin = (ieta<=hdndptdetadet->GetXaxis()->GetXmin()) ?
      hdndptdetadet->GetXaxis()->GetFirst() : hdndptdetadet->GetXaxis()->FindBin(-1.0*feta+small);
   int eta_max_bin = (feta>=hdndptdetadet->GetXaxis()->GetXmax()) ?
      hdndptdetadet->GetXaxis()->GetLast() : hdndptdetadet->GetXaxis()->FindBin(feta-small);
   
   checkEtaRange(ieta,feta,eta_min_bin,eta_max_bin);

   int jet_min_bin = (ijet<=hdndptdetadet->GetZaxis()->GetXmin()) ? 
      hdndptdetadet->GetZaxis()->GetFirst() : hdndptdetadet->GetZaxis()->FindBin(ijet+small); 
   int jet_max_bin = (fjet>=hdndptdetadet->GetZaxis()->GetXmax()) ?
      hdndptdetadet->GetZaxis()->GetLast() : hdndptdetadet->GetZaxis()->FindBin(fjet-small);

   checkEtRange(ijet,fjet,jet_min_bin,jet_max_bin);


   // Loop over the 3D histograms and apply correction --------------
   if(!isGEN) prepareTrkEffCorrection(dir_corr, cListTRK1,
				      cListTRK2,cListTRK3,
				      cListTRK4,cListTRK5,cListTRK6); // first prepare relevant histograms for corrections
   
   int  nbinX = hdndptdetadet->GetNbinsX();
   int  nbinY = hdndptdetadet->GetNbinsY();
   int  nbinZ = hdndptdetadet->GetNbinsZ();
   
   cout<<"[Check number of bins] number of bin in x axis = "<<nbinX<<" in y axis = "<<nbinY<<" in z axis = "<<nbinZ<<endl;

   // jet et range for different samples for trk correction
   // make sure jet et range is quantized with min et range of 20 GeV!
   // so the range has to be at n*20, where n = 1,2,3...
   //jet_1st = 1000, jet_2nd = 2000, jet_3rd = 3000, jet_4th = 4000, jet_5th = 5000; 
   jet_1st = 41, jet_2nd = 81, jet_3rd = 121, jet_4th = 251, jet_5th = 351;

   // -------------------------------------------------------------------------
   // Below is for the purpose of debugging, i.e. to find how many tracks are
   // not corrected due to the lack of statistics or different fragmentation in 
   // the correction MC samples!
   // -------------------------------------------------------------------------
   cout<<"\n"<<endl;
   cout<<"[Tracking corrections applied for each entires] ========================================================="<<endl;

   int corrLevEff=0, corrLevFak=0;

   int minEntry1st = 0; // minimum entries requred in obtaining efficiency/fake
   
   for(int j=0;j<(nbinX*nbinY*nbinZ);j++){
      
      int xbin = (j % nbinX);
      int ybin = ((j-xbin)/nbinX) % nbinY;
      int zbin = (j-(xbin+((ybin)*nbinX)))/(nbinX*nbinY);
      
      double  eta = hdndptdetadet->GetXaxis()->GetBinCenter(xbin+1);
      double  pt = hdndptdetadet->GetYaxis()->GetBinCenter(ybin+1);
      double  jet = hdndptdetadet->GetZaxis()->GetBinCenter(zbin+1);

      double  deta = hdndptdetadet->GetXaxis()->GetBinWidth(xbin+1);
      double  dpt = hdndptdetadet->GetYaxis()->GetBinWidth(ybin+1);
      double  djet = hdndptdetadet->GetZaxis()->GetBinWidth(zbin+1);
      
      double  dbin = hdndptdetadet->GetYaxis()->GetBinWidth(ybin+1);
      
      double  dn = hdndptdetadet->GetBinContent(xbin+1,ybin+1,zbin+1);
      double  edn = hdndptdetadet->GetBinError(xbin+1,ybin+1,zbin+1);
      
      double eff=0, fak=0;
      double mlt=0, sec=0;
      
      bool nonzeroentries = false;
      
      double var_for_corr = 0;
      
      var_for_corr = jet;
      var_1st = jet_1st, var_2nd = jet_2nd, var_3rd = jet_3rd, var_4th = jet_4th, var_5th = jet_5th;
      
      // set jet = 0 to be matched with jet et used in efficiency histogram
      //jet = 0;

      if(!isGEN){  // for GEN truth, no correction is needed!
	if(var_for_corr<var_1st){
	  if(dn>0) nonzeroentries = true;
	  eff = GetEffFactor(hPNEff3D[0],hPDEff3D[0],pt,eta,jet,minEntry1st,nonzeroentries);
	  fak = GetFakFactor(hPNFake3D[0],hPDFake3D[0],pt,eta,jet,minEntry1st,nonzeroentries);
	  mlt = GetFakFactor(hPNMult3D[0],hPDMult3D[0],pt,eta,jet,minEntry1st,false);
	  sec = GetFakFactor(hPNSec3D[0],hPDSec3D[0],pt,eta,jet,minEntry1st,false);
	}else if(var_for_corr>=var_1st && var_for_corr<var_2nd){
	  if(dn>0) nonzeroentries = true;
	  eff = GetEffFactor(hPNEff3D[1],hPDEff3D[1],pt,eta,jet,minEntry1st,nonzeroentries);
	  fak = GetFakFactor(hPNFake3D[1],hPDFake3D[1],pt,eta,jet,minEntry1st,nonzeroentries);
	  mlt = GetFakFactor(hPNMult3D[1],hPDMult3D[1],pt,eta,jet,minEntry1st,false);
	  sec = GetFakFactor(hPNSec3D[1],hPDSec3D[1],pt,eta,jet,minEntry1st,false);
	}else if(var_for_corr>=var_2nd && var_for_corr<var_3rd){
	  if(dn>0) nonzeroentries = true;
	  eff = GetEffFactor(hPNEff3D[2],hPDEff3D[2],pt,eta,jet,minEntry1st,nonzeroentries);
	  fak = GetFakFactor(hPNFake3D[2],hPDFake3D[2],pt,eta,jet,minEntry1st,nonzeroentries);
	  mlt = GetFakFactor(hPNMult3D[2],hPDMult3D[2],pt,eta,jet,minEntry1st,false);
	  sec = GetFakFactor(hPNSec3D[2],hPDSec3D[2],pt,eta,jet,minEntry1st,false);
	}else if(var_for_corr>=var_3rd && var_for_corr<var_4th){
	  if(dn>0) nonzeroentries = true;
          eff = GetEffFactor(hPNEff3D[3],hPDEff3D[3],pt,eta,jet,minEntry1st,nonzeroentries);
          fak = GetFakFactor(hPNFake3D[3],hPDFake3D[3],pt,eta,jet,minEntry1st,nonzeroentries);
          mlt = GetFakFactor(hPNMult3D[3],hPDMult3D[3],pt,eta,jet,minEntry1st,false);
          sec = GetFakFactor(hPNSec3D[3],hPDSec3D[3],pt,eta,jet,minEntry1st,false);
	}else if(var_for_corr>=var_4th && var_for_corr<var_5th){
	  if(dn>0) nonzeroentries = true;
          eff = GetEffFactor(hPNEff3D[4],hPDEff3D[4],pt,eta,jet,minEntry1st,nonzeroentries);
          fak = GetFakFactor(hPNFake3D[4],hPDFake3D[4],pt,eta,jet,minEntry1st,nonzeroentries);
          mlt = GetFakFactor(hPNMult3D[4],hPDMult3D[4],pt,eta,jet,minEntry1st,false);
          sec = GetFakFactor(hPNSec3D[4],hPDSec3D[4],pt,eta,jet,minEntry1st,false);
	}else{
	  if(dn>0) nonzeroentries = true;
          eff = GetEffFactor(hPNEff3D[5],hPDEff3D[5],pt,eta,jet,minEntry1st,nonzeroentries);
          fak = GetFakFactor(hPNFake3D[5],hPDFake3D[5],pt,eta,jet,minEntry1st,nonzeroentries);
          mlt = GetFakFactor(hPNMult3D[5],hPDMult3D[5],pt,eta,jet,minEntry1st,false);
          sec = GetFakFactor(hPNSec3D[5],hPDSec3D[5],pt,eta,jet,minEntry1st,false);
	}
      }

      corrLevEff = 0, corrLevFak = 0; // set it to 0 for every iteration

      while(hiOrdCorrLevEff>corrLevEff){
	if(fabs(eff)>98||eff==1) eff = GetEffFactorFromAvgNearPhaseS(xbin,ybin,zbin,nbinX,nbinY,nbinZ,pt,jet,eff,eta,feta,nonzeroentries,corrLevEff+1,0);
	corrLevEff++;
      }

      while(hiOrdCorrLevFak>corrLevFak){
	if(fabs(fak)>98||fak==1) fak = GetEffFactorFromAvgNearPhaseS(xbin,ybin,zbin,nbinX,nbinY,nbinZ,pt,jet,fak,eta,feta,nonzeroentries,corrLevFak+1,1); 
	corrLevFak++;
      }


      if(dn>0 && pt>pt_thres && fabs(eta)<feta){ // kinematic cut for debugging
	
	recTracktotalBin++, recTracktotal = recTracktotal + dn;

	  if(eff==1||fabs(eff)>90){
	    recTrackNotCorrectedEffBin++, recTrackNotCorrectedEff = recTrackNotCorrectedEff + dn;
	    if(pt>=jet) recTrackWithHoaxFragBin++, recTrackWithHoaxFrag = recTrackWithHoaxFrag + dn;

	    if(eff==1) recTrackWithEffOfOneBin++, recTrackWithEffOfOne = recTrackWithEffOfOne + dn;
	    else if(eff==-99) recTrackWithEffOfZeroBin++, recTrackWithEffOfZero = recTrackWithEffOfZero + dn;
	    else if(eff==-999) recTrackWithHoaxEffBin++, recTrackWithHoaxEff = recTrackWithHoaxEff + dn;
	    else recTrackWithNoEffBin++, recTrackWithNoEff = recTrackWithNoEff + dn;
	  }

	   if(fak==1||fabs(fak)>90){
	    recTrackNotCorrectedFakBin++, recTrackNotCorrectedFak = recTrackNotCorrectedFak + dn;
	    if(pt>=jet) recTrackWithHoaxFragBinFak++, recTrackWithHoaxFragFak = recTrackWithHoaxFragFak + dn;

	    if(fak==1) recTrackWithFakOfOneBin++, recTrackWithFakOfOne = recTrackWithFakOfOne + dn;
	    else if(fak==-99) recTrackWithFakOfZeroBin++, recTrackWithFakOfZero = recTrackWithFakOfZero + dn;
	    else if(fak==-999) recTrackWithHoaxFakBin++, recTrackWithHoaxFak = recTrackWithHoaxFak + dn;
	    else recTrackWithNoFakBin++, recTrackWithNoFak = recTrackWithNoFak + dn;
	  }

	}

	// dn/dpt
	dn = dn/(dbin);
	edn = edn/(dbin);


	hdndptdetadet_raw->SetBinContent(xbin+1,ybin+1,zbin+1,dn);
	hdndptdetadet_raw->SetBinError(xbin+1,ybin+1,zbin+1,edn);

	// efficiency  ! if isGEN = true, no correction applied

	if(isGEN || fabs(eff)>98 || eff==1){ 
	  dn = dn;
	  edn = edn;
	}else{
	  dn = dn*(1./eff);
	  edn = edn*(1./eff);
	}

	// fake rate 
	if(isGEN || fabs(fak)>98 || fak==1){ 
	  dn = dn;
	  edn = edn;
	}else{
	  dn = dn*(1.-fak);
	  edn = edn*(1.-fak);
	}

	hdndptdetadet_lev1->SetBinContent(xbin+1,ybin+1,zbin+1,dn);
	hdndptdetadet_lev1->SetBinError(xbin+1,ybin+1,zbin+1,edn);

	// secondary !
	if(isGEN || fabs(sec)>98 || sec==1){
	  dn = dn, edn = edn; // no correction!                                                                                                        
	}else{
	  dn = dn*(1.-sec), edn = edn*(1.-sec);
	}

	hdndptdetadet_lev2->SetBinContent(xbin+1,ybin+1,zbin+1,dn);
	hdndptdetadet_lev2->SetBinError(xbin+1,ybin+1,zbin+1,edn);

	// multiple reconstruction !
	if(isGEN || fabs(mlt)>98 || mlt==1){
	  dn = dn, edn = edn; // no correction! 
	}else{
	  dn = dn*(1./(1+mlt)), edn = edn*(1./(1+mlt));
	}

	hdndptdetadet_full->SetBinContent(xbin+1,ybin+1,zbin+1,dn);
	hdndptdetadet_full->SetBinError(xbin+1,ybin+1,zbin+1,edn);
   }

   cout<<"[Tracking corrections applied for each entires] ========================================================="<<endl;
   cout<<"\n"<<endl;
   
   cout<<"\n"<<endl;
   cout<<"[Higher order corrections]============================================="<<endl;
   cout<<"Efficiency corrected up to  "<<corrLevEff<<" times in higher order correction"<<endl;
   cout<<"Fake rate corrected up to  "<<corrLevFak<<" times in higher order correction"<<endl;
   cout<<"[Higher order corrections]============================================="<<endl;
   cout<<"\n"<<endl;


   printDebug();
   
   
   // to avoid root projeciton bug
   // ProjectionY is buggy when x axis full x-axis range (-2.4 to 2.4)
   // However, the problem does not show up when the 3D histogram is reset, which is the case in this macro
   // , but to make sure in any case, hackedProjectionY is used.
   
   hdndpt_raw = (TH1D*) hackedProjectionY(hdndptdetadet_raw,"hdndpt_raw",eta_min_bin,eta_max_bin,jet_min_bin,jet_max_bin);
   hdndpt_lev1 = (TH1D*) hackedProjectionY(hdndptdetadet_lev1,"hdndpt_lev1",eta_min_bin,eta_max_bin,jet_min_bin,jet_max_bin);
   hdndpt_lev2 = (TH1D*) hackedProjectionY(hdndptdetadet_lev2,"hdndpt_lev2",eta_min_bin,eta_max_bin,jet_min_bin,jet_max_bin);
   hdndpt_full = (TH1D*) hackedProjectionY(hdndptdetadet_full,"hdndpt_full",eta_min_bin,eta_max_bin,jet_min_bin,jet_max_bin);
   
   hdndpt_raw->Scale(1./scaleF);
   hdndpt_lev1->Scale(1./scaleF);
   hdndpt_lev2->Scale(1./scaleF);
   hdndpt_full->Scale(1./scaleF);
   
   if(correc1to3){
     fCorr = new TF1("fitFunction","pol4(0)",0.1,4.5);
     fCorr->SetParameters(1.01645e+00,-9.74159e-03,7.88645e-04,5.03773e-04,-8.27398e-05); // 900 GeV DATA (Nov 02 2010) |eta|<1.0

     hdndpt_raw = (TH1D*) correctedFor1to3(hdndpt_raw);
     hdndpt_lev1 = (TH1D*) correctedFor1to3(hdndpt_lev1);
     hdndpt_lev2 = (TH1D*) correctedFor1to3(hdndpt_lev2);
     hdndpt_full = (TH1D*) correctedFor1to3(hdndpt_full);
   }
   
     hInv_raw = (TH1D*) hdndpt_raw->Clone("hInv_raw");
     hInv_lev1 = (TH1D*) hdndpt_lev1->Clone("hInv_lev1");
     hInv_lev2 = (TH1D*) hdndpt_lev2->Clone("hInv_lev2");
     hInv_full = (TH1D*) hdndpt_full->Clone("hInv_full");

     hInv_raw = (TH1D*) makeItInvHist(hInv_raw, 2.*feta);
     hInv_lev1 = (TH1D*) makeItInvHist(hInv_lev1, 2.*feta);
     hInv_lev2 = (TH1D*) makeItInvHist(hInv_lev2, 2.*feta);
     hInv_full = (TH1D*) makeItInvHist(hInv_full, 2.*feta);

     tdndpt_raw =  (TGraphErrors*) TgraphIt(hdndpt_raw);
     tdndpt_lev1 = (TGraphErrors*) TgraphIt(hdndpt_lev1);
     tdndpt_lev2 = (TGraphErrors*) TgraphIt(hdndpt_lev2);
     tdndpt_full = (TGraphErrors*) TgraphIt(hdndpt_full);

     tInv_raw =  (TGraphErrors*) TgraphIt(hInv_raw);
     tInv_lev1 = (TGraphErrors*) TgraphIt(hInv_lev1);
     tInv_lev2 = (TGraphErrors*) TgraphIt(hInv_lev2);
     tInv_full = (TGraphErrors*) TgraphIt(hInv_full);


     if(drawFig){
	drawDebugPlots();
     }

     if(saveFile){
	outputFile = new TFile(outFile,"recreate");   
	dTypeOne = outputFile->mkdir("corrTypeOne");
	dTypeOne->cd();                                

	hdndpt_raw->Write(), hdndpt_lev1->Write();
	hdndpt_lev2->Write(), hdndpt_full->Write();

	hInv_raw->Write(), hInv_lev1->Write();
	hInv_lev2->Write(), hInv_full->Write();

	tdndpt_raw->Write("tdndpt_raw"),tdndpt_lev1->Write("tdndpt_lev1");
	tdndpt_lev2->Write("tdndpt_lev2"),tdndpt_full->Write("tdndpt_full");

	tInv_raw->Write("tInv_raw"),tInv_lev1->Write("tInv_lev1");
	tInv_lev2->Write("tInv_lev2"),tInv_full->Write("tInv_full");

	cout<<outFile<<" is created"<<endl;
     }
  }


  void drawDebugPlots(){

     call = new TCanvas("call","call",310,470);
     call->cd(), call->SetLogx(), call->SetLogy();
     sprintf(yTitle,"dN/dp_{T}");
     sprintf(xTitle,"p_{T} [GeV/c]");
     dum = GetDummyHist(400,1E-11,1E+9,xTitle,yTitle);
     dum->Draw();

     th1Style1(hdndpt_raw,14,28,1.0,14,1.0,1,1);
     th1Style1(hdndpt_lev1,15,24,1.0,15,1.0,1,1);
     th1Style1(hdndpt_lev2,16,25,1.0,16,1.0,1,1);
     th1Style1(hdndpt_full,17,26,1.0,17,1.0,1,1);

     th1Style1(tdndpt_raw,14,28,1.0,14,1.0,1,2);
     th1Style1(tdndpt_lev1,15,24,1.0,15,1.0,1,2);
     th1Style1(tdndpt_lev2,16,25,1.0,16,1.0,1,2);
     th1Style1(tdndpt_full,17,26,1.0,17,1.0,1,2);

     callR = new TCanvas("callR","callR",310,470);
     callR->cd(), callR->SetLogy();
     dumR = (TH1D*) dum->Clone("dumR");
     dumR->Draw();

     th1Style1(hdndpt_raw,14,28,1.0,14,1.0,1,1);
     th1Style1(hdndpt_lev1,15,24,1.0,15,1.0,1,1);
     th1Style1(hdndpt_lev2,16,25,1.0,16,1.0,1,1);
     th1Style1(hdndpt_full,17,26,1.0,17,1.0,1,1);

     th1Style1(tdndpt_raw,14,28,1.0,14,1.0,1,2);
     th1Style1(tdndpt_lev1,15,24,1.0,15,1.0,1,2);
     th1Style1(tdndpt_lev2,16,25,1.0,16,1.0,1,2);
     th1Style1(tdndpt_full,17,26,1.0,17,1.0,1,2);

  }

void prepareTrkEffCorrection(const char *dirCorr, const char *cTRK1,const char *cTRK2, const char *cTRK3,
			     const char *cTRK4,const char *cTRK5,const char *cTRK6)
  {
     sprintf(hist1,"heff3D"), sprintf(hist2,"hsim3D"), sprintf(hist3,"hfak3D"), sprintf(hist4,"hrec3D");
     sprintf(histMult1,"hmul3D"), sprintf(histMult2,"hsim3D");
     sprintf(histSec1,"hsec3D"), sprintf(histSec2,"hrec3D");

     cout<<"[prepareTrkEffCorrection] N = "<<NHIST<<" files are used"<<endl;
     
     for(int i=0;i<NHIST;i++){

	if(i==0) cFileTRKArray[i] = cTRK1;
	else if(i==1) cFileTRKArray[i] = cTRK2;
	else if(i==2) cFileTRKArray[i] = cTRK3;
	else if(i==3) cFileTRKArray[i] = cTRK4;
        else if(i==4) cFileTRKArray[i] = cTRK5;
        else if(i==5) cFileTRKArray[i] = cTRK6;

	cout<<"[prepareTrkEffCorrection] sample to be used = "<<cFileTRKArray[i]<<endl;

	// trk eff/fr correction                                                                                                                           
	h3DEff[i] = getEffHists(cFileTRKArray[i],dirCorr,hist1,hist2);
	h3DFake[i] = getEffHists(cFileTRKArray[i],dirCorr,hist3,hist4);

	hPNEff3D[i] = h3DEff[i].first, hPDEff3D[i] = h3DEff[i].second;
	hPNFake3D[i] = h3DFake[i].first, hPDFake3D[i] = h3DFake[i].second;

	// multiply reconstructed!                                                                                                                         
	h3DMult[i] = getEffHists(cFileTRKArray[i],dirCorr,histMult1,histMult2);
	hPNMult3D[i] = h3DMult[i].first, hPDMult3D[i] = h3DMult[i].second;

	// secondary !                                                                                                                                     
	h3DSec[i] = getEffHists(cFileTRKArray[i],dirCorr,histSec1,histSec2);
	hPNSec3D[i] = h3DSec[i].first, hPDSec3D[i] = h3DSec[i].second;
     }
     cout<<"[prepareTrkEffCorrection] end of it"<<endl;

  }


void checkEtaRange(double iEta, double fEta, int EtaMin, int EtaMax){
  
  cout<<"\n"<<endl;
  cout<<"[checkEtaRange]-------------------------------------------------"<<endl;
  cout<<" bin number eta min = "<<EtaMin<<" eta max = "<<EtaMax<<endl;
  cout<<"for input eta "<<fEta<<" found max eta (bin center): "<<hdndptdetadet->GetXaxis()->GetBinCenter(EtaMax)<<endl;
  cout<<"for input eta "<<-1.0*fEta<<" found min eta (bin center): "<<hdndptdetadet->GetXaxis()->GetBinCenter(EtaMin)<<endl;
  cout<<"for input eta "<<fEta<<" found max eta (bin up edge): "<<hdndptdetadet->GetXaxis()->GetBinUpEdge(EtaMax)<<endl;
  cout<<"for input eta "<<-1.0*fEta<<" found min eta (bin low edge): "<<hdndptdetadet->GetXaxis()->GetBinLowEdge(EtaMin)<<endl;
  cout<<"Integration range is from "<<hdndptdetadet->GetXaxis()->GetBinLowEdge(EtaMin)<<" to "<<hdndptdetadet->GetXaxis()->GetBinUpEdge(EtaMax)<<endl;
  cout<<"[checkEtaRange]-------------------------------------------------"<<endl;
  cout<<"\n"<<endl;
  
}

void checkEtRange(double iJet, double fJet, int EtMin, int EtMax){
  
  cout<<"[checkEtRange]--------------------"<<endl;
  cout<<" bin number jet min = "<<EtMin<<" jet max = "<<EtMax<<endl;
  cout<<"for input min Et = "<<iJet<<endl;
  cout<<"jet min Et (low edge) = "<<hdndptdetadet->GetZaxis()->GetBinLowEdge(EtMin)<<endl;
  cout<<"jet min Et (up edge) = "<<hdndptdetadet->GetZaxis()->GetBinUpEdge(EtMin)<<endl;
  cout<<"for input max Et = "<<fJet<<endl;
  cout<<"jet max Et (low edge) = "<<hdndptdetadet->GetZaxis()->GetBinLowEdge(EtMax)<<endl;
  cout<<"jet max Et (up edge) = "<<hdndptdetadet->GetZaxis()->GetBinUpEdge(EtMax)<<endl;
  cout<<"Integration range is from "<<hdndptdetadet->GetZaxis()->GetBinLowEdge(EtMin)<<" to "<<hdndptdetadet->GetZaxis()->GetBinUpEdge(EtMax)<<endl;
  cout<<"[checkEtRange]--------------------"<<endl;
  cout<<"\n"<<endl;
  
}

void printDebug(){

  cout<<"\n"<<endl;
  cout<<"[Debugging summary]==================================================="<<"\n"<<endl;
  cout<<"number of total tracks = "<<recTracktotal<<" above pT = "<<pt_thres<<" (GeV/c)"<<endl;
  cout<<"number of total tracks not corrected for eff = "<<recTrackNotCorrectedEff
      <<" (fraction(%) = "<<100.*(recTrackNotCorrectedEff/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks (among not corrected) with (pT >= eT) = "<<recTrackWithHoaxFrag 
      <<" (fraction(%) = "<<100.*(recTrackWithHoaxFrag/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with no efficiency = "<<recTrackWithNoEff
      <<" (fraction(%) = "<<100.*(recTrackWithNoEff/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with efficiency of unity = "<<recTrackWithEffOfOne
      <<" (fraction(%) = "<<100.*(recTrackWithEffOfOne/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with efficiency of 0 = "<<recTrackWithEffOfZero
      <<" (fraction(%) = "<<100.*(recTrackWithEffOfZero/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with non-sense efficiency = "<<recTrackWithHoaxEff
      <<" (fraction(%) = "<<100.*(recTrackWithHoaxEff/recTracktotal)<<")"<<endl;
  
  cout<<""<<endl;
  
  cout<<"number of total bins = "<<recTracktotalBin<<" above pT = "<<pt_thres<<" (GeV/c)"<<endl;
  cout<<"number of total bins not corrected for eff = "<<recTrackNotCorrectedEffBin
      <<" (fraction(%) = "<<100.*((float)recTrackNotCorrectedEffBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins (among not corrected) with (pT >= eT) = "<<recTrackWithHoaxFragBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithHoaxFragBin)/((float)recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with no efficiency = "<<recTrackWithNoEffBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithNoEffBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with efficiency of unity = "<<recTrackWithEffOfOneBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithEffOfOneBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with efficiency of 0 = "<<recTrackWithEffOfZeroBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithEffOfZeroBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with non-sense efficiency = "<<recTrackWithHoaxEffBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithHoaxEffBin)/((float)recTracktotalBin)<<")"<<endl;

  cout<<""<<endl;
  
  cout<<"number of total tracks = "<<recTracktotal<<" above pT = "<<pt_thres<<" (GeV/c)"<<endl;
  cout<<"number of total tracks not corrected for fak = "<<recTrackNotCorrectedFak
      <<" (fraction(%) = "<<100.*(recTrackNotCorrectedFak/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks (among not corrected) with (pT >= eT) = "<<recTrackWithHoaxFragFak 
      <<" (fraction(%) = "<<100.*(recTrackWithHoaxFragFak/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with no fak = "<<recTrackWithNoFak
      <<" (fraction(%) = "<<100.*(recTrackWithNoFak/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with fak of unity = "<<recTrackWithFakOfOne
      <<" (fraction(%) = "<<100.*(recTrackWithFakOfOne/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with fak of 0 = "<<recTrackWithFakOfZero
      <<" (fraction(%) = "<<100.*(recTrackWithFakOfZero/recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with non-sense fak = "<<recTrackWithHoaxFak
      <<" (fraction(%) = "<<100.*(recTrackWithHoaxFak/recTracktotal)<<")"<<endl;
  
  cout<<""<<endl;
  
  cout<<"number of total bins = "<<recTracktotalBin<<" above pT = "<<pt_thres<<" (GeV/c)"<<endl;
  cout<<"number of total bins not corrected for fak = "<<recTrackNotCorrectedFakBin
      <<" (fraction(%) = "<<100.*((float)recTrackNotCorrectedFakBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins (among not corrected) with (pT >= eT) = "<<recTrackWithHoaxFragBinFak
      <<" (fraction(%) = "<<100.*((float)recTrackWithHoaxFragBinFak)/((float)recTracktotal)<<")"<<endl;
  cout<<"number of total tracks with no fak = "<<recTrackWithNoFakBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithNoFakBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with fak of unity = "<<recTrackWithFakOfOneBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithFakOfOneBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with fak of 0 = "<<recTrackWithFakOfZeroBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithFakOfZeroBin)/((float)recTracktotalBin)<<")"<<endl;
  cout<<"number of total bins with non-sense fak = "<<recTrackWithHoaxFakBin
      <<" (fraction(%) = "<<100.*((float)recTrackWithHoaxFakBin)/((float)recTracktotalBin)<<")"<<endl;

  cout<<"\n"<<"[Debugging summary]==================================================="<<endl;
  cout<<"\n"<<endl;

}


std::pair<TH3F*,TH3F*> getEffHists(const char *file, const char *dirC, 
				     const char *histN, const char *histD){

     TFile *efile = new TFile(file,"read");
     TDirectoryFile *efileDIR = (TDirectoryFile*) efile->GetDirectory(dirC);

     TIter next(efileDIR->GetListOfKeys());
     TKey *key;

     Char_t name[100];

     TH3F *hpneff3d=0;
     TH3F *hpdeff3d=0;

     while ((key=(TKey*)next())) {
	sprintf(name,"%s",key->GetName());
	if(strcmp((key->GetName()),(histN))==0){
	  //cout<<"[getEffHists] Your numerator for Eff "<<name<<endl; 
	   hpneff3d = (TH3F*) efileDIR->Get(name);
	}
	if(strcmp((key->GetName()),(histD))==0){
	  //cout<<"[getEffHists] Your denominator for Eff "<<name<<endl; 
	   hpdeff3d = (TH3F*) efileDIR->Get(name);
	}
     }

     //efileDIR->Close(); 
     //efile->Close(); 
     return std::pair<TH3F*,TH3F*>(hpneff3d,hpdeff3d);
  }


void GetEffFactorDEBUG(TH3F* num, TH3F* den, double pt, double eta, double jet){
  
  int num_bin = num->FindBin(eta,pt,jet);
  int den_bin = den->FindBin(eta,pt,jet);
  
  double n_num = num->GetBinContent(num_bin);
  double n_den = den->GetBinContent(den_bin);
  
  if(n_den == 0) cout<<"[GetEffFactorDEBUG den=0] hist = "<<num->GetName()<<" pt = "<<pt<<" eta = "<<eta<<" jet = "<<jet<<endl; 
  if(n_num == 0) cout<<"[GetEffFactorDEBUG num=0] hist = "<<den->GetName()<<" pt = "<<pt<<" eta = "<<eta<<" jet = "<<jet<<endl;
}

double GetEffFactorFromAvgNearPhaseS(int xbin, int ybin, int zbin, int xbinmax, int ybinmax, int zbinmax, double ptorig, 
				     double jetorig, double efforig, double eta, double etacut, bool nonzero, int clevel, int efforfak){

  int newind=0;

  int xbin_orig = xbin+1;
  int ybin_orig = ybin+1;
  int zbin_orig = zbin+1;

  double n_num_new=0, n_den_new=0;
  double effnew = 0;

  int pt_index_max = 0;
  int jet_index_max = 0;

  if(clevel==1) 
    pt_index_max = 3, jet_index_max = 3;
  else if(clevel==2) 
    pt_index_max = 3, jet_index_max = 5;
  else if(clevel==3)
    pt_index_max = 5, jet_index_max = 5;
  else if(clevel==4)
    pt_index_max = 5, jet_index_max = 7;
  else if(clevel==5)
    pt_index_max = 7, jet_index_max = 7;
  else if(clevel==6)
    pt_index_max = 7, jet_index_max = 9;
  else if(clevel==7)
    pt_index_max = 9, jet_index_max = 9;
  else
    cout<<"[GetEffFactorFromAvgNearPhaseS]"<<endl;

  for(int j=0;j<pt_index_max;j++){  // pT' -> pT +- dpt (1 bin)
    
    for(int i=0;i<jet_index_max;i++){ // jeT' -> jeT +- 2.*djeT (2 bins)
      
      int ybin_near = (ybin+1) + (int)(-0.5*(pt_index_max-1)) + i; // pt bin
      int zbin_near = (zbin+1) + (int)(-0.5*(jet_index_max-1)) + j; // et bin

      if(ybin_near<0||ybin_near>ybinmax) ybin_near = ybin_orig;
      if(zbin_near<0||zbin_near>zbinmax) zbin_near = zbin_orig;

      double  pt = hdndptdetadet->GetYaxis()->GetBinCenter(ybin_near);
      double  jet = hdndptdetadet->GetZaxis()->GetBinCenter(zbin_near);

      if(jet<var_1st) newind =  0;
      else if(jet>=var_1st && jet<var_2nd) newind = 1;
      else if(jet>=var_2nd && jet<var_3rd) newind = 2;
      else if(jet>=var_3rd && jet<var_4th) newind = 3;
      else if(jet>=var_4th && jet<var_5th) newind = 4;
      else newind = 5;

      int num_bin = 0, den_bin = 0;
      double n_num = 0, n_den = 0; 

      if(efforfak==0){
	num_bin = hPNEff3D[newind]->FindBin(eta,pt,jet), den_bin = hPDEff3D[newind]->FindBin(eta,pt,jet);
	n_num = hPNEff3D[newind]->GetBinContent(num_bin), n_den = hPDEff3D[newind]->GetBinContent(den_bin);
      }else{
	num_bin = hPNFake3D[newind]->FindBin(eta,pt,jet), den_bin = hPDFake3D[newind]->FindBin(eta,pt,jet);
	n_num = hPNFake3D[newind]->GetBinContent(num_bin), n_den = hPDFake3D[newind]->GetBinContent(den_bin);
      }

      n_num_new = n_num_new + n_num;
      n_den_new = n_den_new + n_den;

    }

  }
  
  if(n_den_new!=0 && n_num_new!=0) effnew = n_num_new/n_den_new;
  else effnew = efforig;
  
  if(nonzero && ptorig>pt_thres && fabs(eta)<etacut)  
    cout<<"[GetEffFactorFromAvgNearPhaseS] (higher) found for pT(original) = "<<ptorig<<" and jet(original) = "
	<<jetorig<<" old eff = "<<efforig<<" new eff = "<<effnew<<" by n_num_new = "<<n_num_new<<" and n_den_new = "<<n_den_new
	<<" and correction level ="<<clevel<<" eff or fake = "<<efforfak<<endl;

  return effnew;

}

double GetEffFactor(TH3F* num, TH3F* den, double pt, double eta, double jet, int entrycut, bool nonzero){

  // Possible eff scenarioes ----------------------------------------------------
  // * n_den = n_num = 0 
  //   - no entries ==> return 99 
  // * n_den != 0 && n_num = 0
  //   - effciency = 0 ==> return -99 (has to be checked explicity before)
  // * n_den = 0 && n_num !=0 
  //   - something wrong because (n_den >= n_num) ==> return -999
  // * n_num/n_den = 1 
  //   - efficiency = 1 ==> return 1 (hmm, but is this possible?)
  // * n_den < entrycut but not n_den = n_num = 0
  //   - ~ no entries ==> return 999 
  // * not above 
  //   - efficiency is greater than 0 less then 1 ==> return efficiency
  // Possible eff scenarioes ---------------------------------------------------- 
  
  int num_bin = num->FindBin(eta,pt,jet);
  int den_bin = den->FindBin(eta,pt,jet);
  
  double n_num = num->GetBinContent(num_bin);
  double n_den = den->GetBinContent(den_bin);
  
  if(n_den != 0  && n_num == 0){  
    if(nonzero && pt>pt_thres && fabs(eta)<eta_thres) 
      cout<<"[GetEffFactor] efficiency is zero for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
	   <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<")"<<endl;
    return -99;
  }else if(n_den == 0 && n_num !=0){
    if(nonzero && pt>pt_thres && fabs(eta)<eta_thres) 
      cout<<"[GetEffFactor] efficiency does not make sense for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta<<endl;
    return  -999;
  }else if(n_den == 0 && n_num == 0){
    if(nonzero && pt>pt_thres && fabs(eta)<eta_thres) 
      cout<<"[GetEffFactor] no efficiency from MC for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta<<endl;
     return 99;
  }else if(n_den<entrycut){
    if(nonzero && pt>pt_thres && fabs(eta)<eta_thres) 
      cout<<"[GetEffFactor] number of entries less than "<<entrycut<<" pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
	  <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<" eff = "<<n_num/n_den<<")"<<endl;
    return 999;
  }else{ 
    if(nonzero && pt>pt_thres && (n_num/n_den)==1 && fabs(eta)<eta_thres) 
      cout<<"[GetEffFactor] efficiency of 1 for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
	  <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<")"<<endl;
    return n_num/n_den;
  }
}


double GetFakFactor(TH3F* num, TH3F* den, double pt, double eta, double jet, int entrycut, bool nonzero){

  // Possible fake scenarioes ---------------------------------------------------- 
  // * n_den = n_num = 0 
  //   - no entries ==> return 99
  // * n_den != 0 && n_num = 0 
  //   - fake = 0 ==> return 0 (has to be checked explicity before)
  // * n_den = 0 && n_num !=0 
  //   - something wrong because (n_den >= n_num) ==> return -999 
  // * n_num/n_den = 1
  //   - fake = 1 ==> return 1 (hmm, but is this possible?)      
  // * n_den < entrycut but not n_den = n_num = 0
  //   - ~ no entries ==> return 999                                                                              
  // * not above 
  //   - fake is greater than 0 less then 1 ==> return fake
  // Possible eff scenarioes ---------------------------------------------------- 

  // this is a temporary solution to ignore jet dependent eff/fake correction

  int num_bin = num->FindBin(eta,pt,jet);
  int den_bin = den->FindBin(eta,pt,jet);

  double n_num = num->GetBinContent(num_bin);
  double n_den = den->GetBinContent(den_bin);

   if(n_den != 0  && n_num == 0){
     if(nonzero && pt>pt_thres && fabs(eta)<eta_thres)
       cout<<"[GetFakFactor] fake is zero for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
	 <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<")"<<endl;
     return -99;
   }else if(n_den == 0 && n_num !=0){
     if(nonzero && pt>pt_thres && fabs(eta)<eta_thres)
       cout<<"[GetFakFactor] fake does not make sense for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta<<endl;
     return  -999;
   }else if(n_den == 0 && n_num == 0){
     if(nonzero && pt>pt_thres && fabs(eta)<eta_thres)
       cout<<"[GetFakFactor] no efficiency from MC for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta<<endl;
     return 99;
   }else if(n_den<entrycut){
     if(nonzero && pt>pt_thres && fabs(eta)<eta_thres) 
       cout<<"[GetFakFactor] number of entries less than "<<entrycut<<" pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
	   <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<" eff = "<<n_num/n_den<<")"<<endl;
     return 999;
   }else{
     if(nonzero && pt>pt_thres && (n_num/n_den)==1 && fabs(eta)<eta_thres)
       cout<<"[GetFakFactor] fake of 1 for pt: "<<pt<<" jet: "<<jet<<" eta: "<<eta
           <<" (n_num: "<<n_num<<" and n_den: "<<n_den<<")"<<endl;
     return n_num/n_den;
   }
}


TH1D *correctedFor1to3(TH1D *hist){

  for(int i=0;i<hist->GetNbinsX();i++){
    double pt = hist->GetBinCenter(i+1);
    double content = hist->GetBinContent(i+1);
    double err = hist->GetBinError(i+1);
    double corr = 1.0;
    if(pt<1.5) corr = fCorr->Eval(pt);
    hist->SetBinContent(i+1,content*corr);
    hist->SetBinError(i+1,err*corr);
  }
  
  return hist;

}


int findIndexOfTheLeast(std::vector<double> inv){
  int ileast = -99;
  double vleast = 1E5;

  //cout<<" size = "<<inv.size()<<endl;
  for(unsigned int i=0;i<inv.size();i++){
    double values = inv[i];
    //cout<<"values = "<<values<<" vleast = "<<vleast<<endl;
    if(values<vleast)
      ileast = i, vleast = values;
  }
  //cout<<"index to be returned = "<<ileast<<endl;
  return ileast;
}

int findIndexBeforeSort(std::vector<double> sortedv, std::vector<float> unsortedv){

  if(sortedv.size()!=unsortedv.size()){
    cout<<"[findIndexBeforeSort] Two vectors have different dimensions!"<<endl;
    //return 1;
  }

  int foundindex = 0;
  bool found = false;
  double value = sortedv[0];

  cout<<"size = "<<unsortedv.size()<<endl;
  for(unsigned i=0;i<sortedv.size();i++){
    // there can be more then one, but doesn't matter
    // as far as it is found
    cout<<"value = "<<value<<" and unsorted = "<<unsortedv[i]<<endl;
    if(fabs(value-(double)unsortedv[(unsigned)i])<0.000001){
      foundindex = (int)i, found = true;
      cout<<"found index = "<<i<<endl;
      //break;
    }
  }

  if(!found) cout<<"[findIndexBeforeSort] no value is found!"<<endl;
  return foundindex;
}
