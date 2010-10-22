//---------------------------------------------------------------------------------------
// July 19 2010 Andre S. Yoon
// 
// This macros reads the output of TrackSpectraAnalyzer run with the pureGENmode option
// and extracks dN/dpT first and then an invariant yield with and without corrections
// (i.e. correction for finite bin size) Various histograms are saved in a separate files
//
// dN/dpT is extracted by stiching several histograms after weighting each with appropriate
// cross section, which is knonw from pythia summary output or etc.
// 
//---------------------------------------------------------------------------------------



#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include <utility>
#include <iostream>
#include <vector>

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


vector<TFile*> vf;

TH3F* hdndpt_pre3D_dum=0;

vector<TH1D*> hdndpt_pre1D;
vector<TH1F*> hevt;

TH1D *hdndpt_added=0;
TH1D *hSpecRaw=0, *hSpecCorr=0;

TH1D *hSpec=0, *hSpecR=0;
TH1D *hCorr=0, *hCorrR=0;

TH1D *hInv=0, *hInvR=0; // raw
TGraphErrors *tInv=0, *tInvR=0;

TH1D *hInvCorr=0, *hInvCorrR=0; // corrected invariant yield
TGraphErrors *tInvCorr=0, *tInvCorrR=0;

TH1D *hfitF=0, *hfitF_inv=0;
TF1 *fitF=0, *fitF_inv=0;

vector<float> xsection;

TString fitFormula;

FILE *fdata; 

char outFile[300];

char cFileName1[200], cFileName2[200], cFileName3[200], cFileName4[200], cFileName5[200];
char cFileName6[200], cFileName7[200], cFileName8[200], cFileName9[200], cFileName10[200];
char cFileName11[200];

char cFileXsection[200];

TCanvas *can1=0, *can2=0, *can3=0, *can4=0, *can5=0, *can6=0, *can7=0;
TH1D *dum1=0, *dum2=0, *dum3=0, *dum4=0, *dum5=0, *dum6=0, *dum7=0;

TFile *outputFile=0;
TDirectory *dTypeOne=0;

bool pythia8gen = false;
float sqrts = 0;

//-------------------------------------------------------------------------------------
void  fillXsectionVector();
void drawdNdpT();
void fitdNdpT(float ix, float fx);
TH1D *divideByBinW(TH1D* hist);
TH1D *get1DdNdpT(TFile *f, int bin_eta_min, int bin_eta_max, int ind);
void obtainFitInv(float ix, float fx, float deta);
TH1D *correctedSpectra(TH1D *inputHist_pre, TH1D *corrF_pre);
void checkEtaRange(float iEta, float fEta, int EtaMin, int EtaMax);
//-------------------------------------------------------------------------------------


void ExtractGENTruthNSave(const char *cDir="../root_files/",
			  const char *cDirOut="./rootOutput/",
			  const char *cFile1="TrkHistGEN_july19_qcdPt0to15",
                          const char *cFile2="TrkHistGEN_july19_qcdPt15to20",
                          const char *cFile3="TrkHistGEN_july19_qcdPt20to30",
                          const char *cFile4="TrkHistGEN_july19_qcdPt30to50",
                          const char *cFile5="TrkHistGEN_july19_qcdPt50to80",
                          const char *cFile6="TrkHistGEN_july19_qcdPt80to120",
                          const char *cFile7="TrkHistGEN_july19_qcdPt120to170",
                          const char *cFile8="TrkHistGEN_july19_qcdPt170to230",
                          const char *cFile9="TrkHistGEN_july19_qcdPt230to300",
                          const char *cFile10="TrkHistGEN_july19_qcdPt300to380",
			  const char *cXsection="xsection_pythia6_d6t",
			  const char *dir_ana="preTrackAna",
			  float sqrts_in=900,
			  bool varBin=true,
			  float ijet=0, float fjet=2000,
			  float ieta=0, float feta=2.4,
			  double scaleF=57.62,
			  int rebinF=6, bool pythia8=false,
			  bool drawFig =true, bool saveFile=true
			  )
   
{
   cout<<"\n"<<"\n"<<endl;
   sqrts = sqrts_in;
   cout<<" COM = "<<sqrts<<" GeV"<<endl;

   if(pythia8) pythia8gen = true;

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();

   sprintf(outFile,"%sGEN_%s_eta_%1.1fto%1.1f_jet_%1.1fto%1.1f_%s_varBin%i_rebin%d.root",cDirOut,cFile1,ieta,feta,ijet,fjet,dir_ana,varBin,rebinF);
   cout<<"Output file will be "<<outFile<<endl;
   cout<<"Scale factor to be applied will be "<<scaleF<<endl;
   cout<<"\n"<<endl;

   sprintf(cFileName1,"%s%s.root",cDir,cFile1);
   sprintf(cFileName2,"%s%s.root",cDir,cFile2);
   sprintf(cFileName3,"%s%s.root",cDir,cFile3);
   sprintf(cFileName4,"%s%s.root",cDir,cFile4);
   sprintf(cFileName5,"%s%s.root",cDir,cFile5);
   sprintf(cFileName6,"%s%s.root",cDir,cFile6);
   sprintf(cFileName7,"%s%s.root",cDir,cFile7);
   //sprintf(cFileName8,"%s%s.root",cDir,cFile8);
   //sprintf(cFileName9,"%s%s.root",cDir,cFile9);
   //sprintf(cFileName10,"%s%s.root",cDir,cFile10);
   //sprintf(cFileName11,"%s%s.root",cDir,cFile11);
   
   cout<<"input file "<<cFileName1<<endl;

   vf.push_back(new TFile(cFileName1));
   vf.push_back(new TFile(cFileName2));
   vf.push_back(new TFile(cFileName3));
   vf.push_back(new TFile(cFileName4));
   vf.push_back(new TFile(cFileName5));
   vf.push_back(new TFile(cFileName6));
   vf.push_back(new TFile(cFileName7));
   //vf.push_back(new TFile(cFileName8));
   //vf.push_back(new TFile(cFileName9));
   //vf.push_back(new TFile(cFileName10));
   //vf.push_back(new TFile(cFileName11));

   cout<<"number of input files = "<<vf.size()<<endl;
   for(unsigned i=0;i<vf.size();i++){
      //if(vf[i]==0) cout<<"Hey"<<endl;
      //if(vf[i]->IsOpen==false) Error("[FileLoading]","could not open hist file");
      //else cout<<"[fileloading] : "<<vf[i]<<endl;
   }

   sprintf(cFileXsection,"../data_files/%s.dat",cXsection);
   cout<<"Xsection data file will be "<<cFileXsection<<endl;
   cout<<"\n"<<endl;

   fdata = fopen(cFileXsection,"r");
   if(fdata==0){
      cout<<"data file loading error"<<endl;	
      return;
   }

   fillXsectionVector();

   cout<<"\n"<<endl;
   cout<<"[GEN spectra extracting..]======================================="<<endl;
   if(!pythia8) hdndpt_pre3D_dum = (TH3F*) vf[0]->Get("preTrackAna/threeDHist/hGenTrkPtEtaJetEt_vbin");
   else hdndpt_pre3D_dum = (TH3F*) vf[0]->Get("preTrackAna8/threeDHist/hGenTrkPtEtaJetEt_vbin");
   float small = 0.01; // when the eta value is at the edge (1.0 and 2.4 is at the edges!)
   int binMinEta = hdndpt_pre3D_dum->GetXaxis()->FindBin(-1.0*feta+small);
   int binMaxEta = hdndpt_pre3D_dum->GetXaxis()->FindBin(feta-small);

   checkEtaRange(ieta,feta,binMinEta,binMaxEta);
   
   for(unsigned i=0;i<vf.size();i++){
     if(i==0) hdndpt_added = (TH1D*) get1DdNdpT(vf[i],binMinEta,binMaxEta,i);
     hdndpt_pre1D.push_back(get1DdNdpT(vf[i],binMinEta,binMaxEta,i));
     if(i>0) hdndpt_added->Add(get1DdNdpT(vf[i],binMinEta,binMaxEta,i));
   }
   cout<<"[GEN spectra extracting..]======================================="<<endl;
   cout<<"\n"<<endl;
   
   drawdNdpT();
   hdndpt_added->SetMarkerStyle(20),hdndpt_added->SetMarkerSize(1.0);
   hdndpt_added->Draw("pzsame");

   fitdNdpT(0.5, 0.2*sqrts);

   hfitF = FillFromFunc(hdndpt_added,fitF); // fill from the fit function
   hfitF->Draw("histsame");

   obtainFitInv(0.5,250,2.*feta); //now obtain invariant yield analytically
   hfitF_inv = FillFromFunc(hdndpt_added,fitF_inv);

   can2 = new TCanvas("can2","can2",550,410);
   can2->cd();
   can2->SetLogy();

   dum2 = GetDummyHist(0.5,200,(2E-14),(2E+2),"p_{T}","d^{3}N/d^{3}p",true);
   dum2->Draw();

   fitF_inv->Draw("same");
   hfitF_inv->Draw("histsame");

   // To get correction factor from the fit function-------------------------------
   // "Measured" - note the quotes!
   hSpec = (TH1D*) hfitF->Clone("hSpec");
   hSpec = (TH1D*) makeItInvHist(hSpec,2.*feta);
   hSpecR = (TH1D*) hSpec->Rebin(rebinF,"hSpecR"), hSpecR->Scale((double)(1./rebinF));
   // Correction factor "Measued"/"Truth"
   hCorr = (TH1D*) ratio_hist_to_func(hSpec,fitF_inv); 
   hCorrR = (TH1D*) ratio_hist_to_func(hSpecR,fitF_inv);
   // Plot
   can3 = new TCanvas("can3","can3",550,410), can3->cd();
   dum3 = GetDummyHist(0.5,200,0.7,2.8,"p_{T}^{rec}","Correction factor",false);
   dum3->Draw("");
   hCorr->Draw("pzsame");
   hCorrR->SetMarkerStyle(22), hCorrR->SetMarkerColor(2), hCorrR->Draw("pzsame");
   // -----------------------------------------------------------------------------

   // Now make invariant hist
   hInv = (TH1D*) hdndpt_added->Clone("hInv");
   hInv->SetName("hInv");

   hInv = (TH1D*) makeItInvHist(hInv,2.*feta);
   hInvCorr = (TH1D*) correctedSpectra(hInv,hCorr);
   hInvCorr->SetName("hInvCorr");

   hInvR = (TH1D*) hInv->Rebin(rebinF,"hInvR"), hInvR->Scale((double)(1./rebinF));
   hInvCorrR = (TH1D*) correctedSpectra(hInvR,hCorrR);
   hInvCorrR->SetName("hInvCorrR");
   
   hInv->Scale(1./scaleF), hInvR->Scale(1./scaleF);
   hInvCorr->Scale(1./scaleF), hInvCorrR->Scale(1./scaleF);

   can4 = new TCanvas("can4","can4",550,410);
   can4->cd(), can4->SetLogy();
   dum4 = (TH1D*) dum2->Clone("dum4");
   dum4->Draw();

   hInv->SetMarkerStyle(24), hInv->SetMarkerColor(2);
   hInv->Draw("pzsame");

   hInvR->SetMarkerStyle(22), hInvR->SetMarkerColor(2);
   hInvR->Draw("pzsame");

   hInvCorr->SetMarkerColor(1);
   hInvCorr->Draw("pzsame");

   hInvCorrR->SetMarkerColor(1), hInvCorrR->SetMarkerStyle(22);
   hInvCorrR->Draw("pzsame");
   

   tInv =  (TGraphErrors*) TgraphIt(hInv), tInvR =  (TGraphErrors*) TgraphIt(hInvR);
   tInvCorr =  (TGraphErrors*) TgraphIt(hInvCorr), tInvCorrR =  (TGraphErrors*) TgraphIt(hInvCorrR);

   // Save the hist/tg
   if(saveFile){
     outputFile = new TFile(outFile,"recreate");
     dTypeOne = outputFile->mkdir("corrTypeTwoGEN");
     dTypeOne->cd();

     hInv->Write(), hInvCorr->Write();
     tInv->Write("tInv"),tInvCorr->Write("tInvCorr");

     hInvR->Write(), hInvCorrR->Write();
     tInvR->Write("tInvR"),tInvCorrR->Write("tInvCorrR");

     cout<<outFile<<" is created"<<endl;
   }


}

void drawdNdpT(){
   can1 = new TCanvas("can1","can1",550,410);
   can1->cd();
   can1->SetLogy();

   dum1 = GetDummyHist(0.5,250,2E-11,9E+3,"p_{T}","dN/dp_{T}",true);
   dum1->Draw();

   for(unsigned i=0;i<vf.size();i++){
      th1Style1(hdndpt_pre1D[i],14+i,24,0.2,14+i,1.5,1,1);
   }
}

void  fillXsectionVector(){
   char line[100];
   float x;
   cout<<"[Xsection] ===================="<<endl;
   while(fgets(line,80,fdata)){
      printf("%s",line);
      sscanf(&line[0],"%f\n",&x);
      xsection.push_back(x);
   }
   cout<<"[Xsection] ===================="<<endl;

}


TH1D* get1DdNdpT(TFile *f, int bin_eta_min, int bin_eta_max, int ind){
  char hName_temp[100], hName[100];
  sprintf(hName_temp,"hdndpt1D_temp_%d",ind);
  sprintf(hName,"hdndpt1D_%d",ind);

  cout<<"bin eta min = "<<bin_eta_min<<" and bin eta max = "<<bin_eta_max<<endl;

  TH3F *hdndpt3D_temp=0;
  TH1F *hevt_temp=0;

  if(!pythia8gen){
    hdndpt3D_temp = (TH3F*) f->Get("preTrackAna/threeDHist/hGenTrkPtEtaJetEt_vbin");
    hevt_temp = (TH1F*) f->Get("preTrackAna/hGenNevt");
  }else{
    hdndpt3D_temp = (TH3F*) f->Get("preTrackAna8/threeDHist/hGenTrkPtEtaJetEt_vbin");
    hevt_temp = (TH1F*) f->Get("preTrackAna8/hGenNevt");
  }

   /*
   TH1D *hdndpt1D_temp = (TH1D*) hdndpt3D_temp->ProjectionY("hdndpt1D_temp",bin_eta_min,bin_eta_max,
							    hdndpt3D_temp->GetZaxis()->GetFirst(),
							    hdndpt3D_temp->GetZaxis()->GetLast(),"e");
   */

   TH1D *hdndpt1D_temp = (TH1D*) hackedProjectionY(hdndpt3D_temp,hName_temp,
						   bin_eta_min, bin_eta_max, 
						   hdndpt3D_temp->GetZaxis()->GetFirst(),                                                                                                            
						   hdndpt3D_temp->GetZaxis()->GetLast());
   /*
   int bin_jet_min = hdndpt3D_temp->GetZaxis()->GetFirst();
   int bin_jet_max = hdndpt3D_temp->GetZaxis()->GetLast();
   hdndpt3D_temp->GetXaxis()->SetRange(bin_eta_min,bin_eta_max);
   hdndpt3D_temp->GetZaxis()->SetRange(bin_jet_min,bin_jet_max);
   TH1D *hdndpt1D_temp = (TH1D*) hdndpt3D_temp->Project3D("ye");
   hdndpt1D_temp->SetName("hdndpt1D_temp");
   */

   float xsec_scale = (float) (xsection[ind]/hevt_temp->GetEntries());
   hdndpt1D_temp->Scale(xsec_scale);
   //hdndpt1D_temp->Scale((xsection[ind])/(float)hevt_temp->GetEntries());
   hdndpt1D_temp->SetName(hName);
   hdndpt1D_temp = divideByBinW(hdndpt1D_temp);
   return hdndpt1D_temp;
}


TH1D *divideByBinW(TH1D* hist){
  for(int i=0;i<hist->GetNbinsX();i++){
    double content = hist->GetBinContent(i+1);
    double err = hist->GetBinError(i+1);
    double binW = hist->GetBinWidth(i+1);
    hist->SetBinContent(i+1,content/binW);
    hist->SetBinError(i+1,err/binW);
  }
  return hist;
}

void fitdNdpT(float ix, float fx){

  /*
  can1 = new TCanvas("can1","can1",550,410);
  can1->cd();
  can1->SetLogy();
  */
  
  double scaleF = 1;
  //dum1 = GetDummyHist(0.5,200,(2E-6)*(scaleF),(1E+9)*(scaleF),"p_{T}","dN/dp_{T}",true);
  //dum1->SetTitle("raw dn/dpt fitted"), dum1->SetName("dum1");
  //dum1->Draw();

  fitFormula = "[0]*([5]+(x/[1])+(pow(x,[2])/[3]))^[4]";
  //fitFormula = "[0]*([2]+x/[1])^[3]";
  //fitFormula = "[0]*x*(((1.+(x/[1]))^[2])*((1.-(x/[3]))^[4]))";

  cout<<"\n"<<"[fitdNdpT] fitting function = "<<fitFormula.Data()<<"\n"<<endl;

  fitF = new TF1("fitFunction",fitFormula.Data(),ix,fx);

  //fitF->SetParameters((2.96361e+08)*(scaleF),2.66339e-01,1,1,-5,1);
  fitF->SetParameters(1.e5,2.5,1.0,1.0,-5.,2);
  //fitF->SetParameters((2.96361e+08)*(scaleF),2,1,-5,200,);
  //fitF->SetParameters((2.96361e+08)*(scaleF),2.66339e-01,1,1,-5,1);
  //fitF->SetParameters(1e4,0.5,-4.,sqrts/2.,10.);
  //fitF->SetParLimits(3,sqrts/2.,sqrts/2.);

  fitF->SetLineColor(2);
  fitF->SetLineWidth(2);

  hdndpt_added->Fit(fitF,"NRO");
  // second iteration
  fitF->SetParameters(fitF->GetParameter(0),fitF->GetParameter(1),fitF->GetParameter(2),
	 fitF->GetParameter(3),fitF->GetParameter(4),fitF->GetParameter(5));
  hdndpt_added->Fit(fitF,"NRO");
  fitF->Draw("same");
}


void obtainFitInv(float ix, float fx, float deta){

  fitFormula += "*(1/(2*TMath::Pi()*x*[6]))";
  cout<<"\n"<<"[obtainFitInv] fitting function (invaraint form) = "<<fitFormula.Data()<<"\n"<<endl;

  fitF_inv = new TF1("fitFunctionInv",fitFormula.Data(),ix,fx);
  fitF_inv->SetParameters(fitF->GetParameter(0),fitF->GetParameter(1),fitF->GetParameter(2),
			  fitF->GetParameter(3),fitF->GetParameter(4),fitF->GetParameter(5),
			  deta);

  cout<<"Fit parameters (input) "<<endl;
  cout<<"    p1 = "<<fitF_inv->GetParameter(0)<<endl;
  cout<<"    p2 = "<<fitF_inv->GetParameter(1)<<endl;
  cout<<"    p3 = "<<fitF_inv->GetParameter(2)<<endl;
  cout<<"    p4 = "<<fitF_inv->GetParameter(3)<<endl;
  cout<<"    p5 = "<<fitF_inv->GetParameter(4)<<endl;
  cout<<"    p6 = "<<fitF_inv->GetParameter(5)<<endl;
  cout<<"    p7 = "<<fitF_inv->GetParameter(6)<<endl;


  fitF_inv->SetLineColor(4), fitF_inv->SetLineWidth(2);
  //fitF_inv->Draw("same");                                                                                                                                                                                  

}


TH1D *correctedSpectra(TH1D *inputHist_pre, TH1D *corrF_pre){

  TH1D *inputHist = (TH1D*) inputHist_pre->Clone("inputHist");
  TH1D *corrF = (TH1D*) corrF_pre->Clone("corrF");

  cout<<"[correctedSpectra] number of bins in input hist = "<<inputHist->GetNbinsX()
      <<" and in correction hist = "<<corrF->GetNbinsX()<<endl;

  if(inputHist->GetNbinsX()!=corrF->GetNbinsX()){
    Error("[correctSpectra]","input inv spectra and correction factor has different number of bins!!");
    return 0;
  }
  for(int i=0;i<inputHist->GetNbinsX();i++){
    double yield = inputHist->GetBinContent(i+1);
    double yielderr = inputHist->GetBinError(i+1);
    if(fabs(inputHist->GetBinCenter(i+1)-corrF->GetBinCenter(i+1))>0.1){
      Error("[correctSpectra]","input inv spectra and correction factor has different pt bins!");
      return 0;
    }
    double corrR = corrF->GetBinContent(i+1);
    //cout<<"corr factor ="<<corrR<<" for pt = "<<corrF->GetBinCenter(i+1)<<endl;                                                                                                                           
    if(corrR==0) corrR = 1; // corrR=0 when yield = 0;                                                                                                                                                      
    inputHist->SetBinContent(i+1,yield/corrR);
    inputHist->SetBinError(i+1,yielderr/corrR);
  }

  return inputHist;
}


void checkEtaRange(float iEta, float fEta, int EtaMin, int EtaMax){

  cout<<"\n"<<endl;
  cout<<"[checkEtaRange]-------------------------------------------------"<<endl;
  cout<<"for input eta "<<fEta<<" found max eta (bin center): "<<hdndpt_pre3D_dum->GetXaxis()->GetBinCenter(EtaMax)<<endl;
  cout<<"for input eta "<<-1.0*fEta<<" found min eta (bin center): "<<hdndpt_pre3D_dum->GetXaxis()->GetBinCenter(EtaMin)<<endl;
  cout<<"for input eta "<<fEta<<" found max eta (bin up edge): "<<hdndpt_pre3D_dum->GetXaxis()->GetBinUpEdge(EtaMax)<<endl;
  cout<<"for input eta "<<-1.0*fEta<<" found min eta (bin low edge): "<<hdndpt_pre3D_dum->GetXaxis()->GetBinLowEdge(EtaMin)<<endl;
  cout<<"Integration range is from "<<hdndpt_pre3D_dum->GetXaxis()->GetBinLowEdge(EtaMin)<<" to "<<hdndpt_pre3D_dum->GetXaxis()->GetBinUpEdge(EtaMax)<<endl;
  cout<<"[checkEtaRange]-------------------------------------------------"<<endl;
  cout<<"\n"<<endl;

}
