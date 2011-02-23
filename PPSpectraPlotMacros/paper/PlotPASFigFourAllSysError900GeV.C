//-----------------------------------------------------------------
// July 06 2010    Andre S. Yoon 
//-----------------------------------------------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include "utilities.h"
#include "commonStyle.h"



#include "TLine.h"
#include "TLegend.h"
#endif


TFile *file1=0, *file2=0, *file3=0, *file4=0, *file5=0, *file6=0;

TH1D *hdndpt1=0, *hdndpt2=0, *hdndpt3=0, *hdndpt4=0, *hdndpt5=0, *hdndpt6=0;

TH1D *hdndpt1_cln=0, *hdndpt2_cln=0, *hdndpt3_cln=0, *hdndpt4_cln=0, *hdndpt5_cln=0, *hdndpt6_cln=0;
TH1D *hdndpt1_div=0, *hdndpt2_div=0, *hdndpt3_div=0, *hdndpt4_div=0, *hdndpt5_div=0, *hdndpt6_div=0;
TH1D *hdndpt1_2_cln=0, *hdndpt1_3_cln=0, *hdndpt1_4_cln=0, *hdndpt1_5_cln=0, *hdndpt1_6_cln=0;

TGraphErrors *tdndpt1=0, *tdndpt2=0, *tdndpt3=0, *tdndpt4=0, *tdndpt5=0, *tdndpt6=0;

TGraphAsymmErrors *tasydndpt1=0;

TF1 *fsyserr=0;
TH1D *hsyserr=0;
TGraphErrors *tsyserr=0;


TGraphErrors *cms_900GeV=0;
TGraphErrors *cms_900GeV_div=0;

TF1 *fitF=0;

TPad *pp1=0, *pp1_1=0;
TH1D *dum1=0, *dum1_1=0;

TCanvas *can2=0, *can3=0, *can4=0, *can5=0, *can6=0, *can7=0;
TH1D *dum2=0, *dum3=0, *dum4=0, *dum5=0, *dum6=0, *dum7=0;

TString fitFormula;

TLatex *tex=0, *tex2=0;

//-------------------------------------------------
void setPad(TCanvas *can);
void setLowerPad(TH1D *dum_low);
void putCMSPrel();
void putIntLum();
void setSysErrorFunction();
void createSysStatErrorHist(TH1D *hist_pre, double maxpt);
TH1D *resetSysStatError(TH1D *hist);
TGraphAsymmErrors* TGraphAsyErrIt(TH1D* hist);
void putB();
void putA();
//------------------------------------------------- 

void PlotPASFigFourAllSysError900GeV(bool save=false){

   bool lowpT = false;
   bool atlas = false;

   float pt_min, pt_max;
   float ymin, ymax;
   float ymin_r, ymax_r;
   
   //double sigma_nsd = 52.4;
   //double sigma_nsd = 4.076E+01; // Pythia NSD
   //double sigma_nsd = 4.076E+01; 
   //sigma_nsd = sigma_nsd * 0.5;
   //double sigma_nsd = 1.0;

   //double sigma_nsd = 52.43;
   //double sigma_nsd = 36.99; // Nnsd/L
   double sigma_nsd = 38.42;
   sigma_nsd = 1.0;

   if(lowpT){
      pt_min = 0.5, pt_max = 7;
      ymin = 6E-6, ymax = 5E+1;
      ymin_r = 0.7, ymax_r = 1.3;
   }else{
      pt_min = 0.4, pt_max = 39;
      ymin = 2E-15, ymax = 5E+1;
      //ymin_r = 0.24, ymax_r = 1.56;
      ymin_r = 0.54, ymax_r = 1.91;
   }
   
   setSysErrorFunction();
   
   // file loading -----------------------------------------
   file1 = (TFile*) loadFile(file1,
			     //"./../rootOutput_2nd/feb142011/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to1.0_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     "./../rootOutput_2nd/feb142011/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to1.0_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to1.0_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to1.0_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0_rebin4.root");
   //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   //"../rootOutput/CORR_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
   
   hdndpt1 = (TH1D*) file1->Get("corrTypeTwo/hInvCorrTwoLev2R");
   TH1D *hdndpt1_temp = 0;
   hdndpt1_temp = (TH1D*) hdndpt1->Clone("hdndpt1_temp");
   hdndpt1_temp = (TH1D*) resetSysStatError(hdndpt1_temp);
   tasydndpt1 =  (TGraphAsymmErrors*) TGraphAsyErrIt(hdndpt1_temp);
   //tdndpt1 = (TGraphErrors*) TgraphIt(hdndpt1_temp, true);
   //tdndpt1 = (TGraphErrors*) file1->Get("corrTypeTwo/tInvCorrTwoLev2R");

   if(hdndpt1==0) {
      Error("[HistLoading]","could not get histogram");
      return;
   }


   // D6T
   file2 = (TFile*) loadFile(file2,
			     "../rootOutput/GEN_TrkHistGEN_900GeV_d6t_oct24_qcdNSD_D6T_Pt0to5_V2_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");
			     //"../rootOutput/GEN_TrkHistGEN_900GeV_oct14v2_qcdNSD_D6T_Pt0to5_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");
   hdndpt2 = (TH1D*) file2->Get("corrTypeTwoGEN/hInvCorrR");
   tdndpt2 = (TGraphErrors*) file2->Get("corrTypeTwoGEN/tInvCorr");
   if(hdndpt2==0 || tdndpt2==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }


   // P0
   file3 = (TFile*) loadFile(file3,
			     "../rootOutput/GEN_TrkHistGEN_900GeV_p0_oct24_qcdNSD_P0_Pt0to5_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");

   hdndpt3 = (TH1D*) file3->Get("corrTypeTwoGEN/hInvCorrR");
   tdndpt3 = (TGraphErrors*) file3->Get("corrTypeTwoGEN/tInvCorr");
   if(hdndpt3==0 || tdndpt3==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   // PYTHIA 8
   file4 = (TFile*) loadFile(file4,
			     "../rootOutput/GEN_TrkHistGEN_900GeV_py8_oct24_qcdNSD_PY8T1_Pt0to5_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");

   hdndpt4 = (TH1D*) file4->Get("corrTypeTwoGEN/hInvCorrR");
   tdndpt4 = (TGraphErrors*) file4->Get("corrTypeTwoGEN/tInvCorr");
   if(hdndpt4==0 || tdndpt4==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   // ProQ20
   file5 = (TFile*) loadFile(file5,
			     "../rootOutput/GEN_TrkHistGEN_900GeV_d6t_oct24_qcdNSD_ProQ20_Pt0to5_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");

   hdndpt5 = (TH1D*) file5->Get("corrTypeTwoGEN/hInvCorrR");
   tdndpt5 = (TGraphErrors*) file5->Get("corrTypeTwoGEN/tInvCorr");
   if(hdndpt5==0 || tdndpt5==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   /*
   // Atlas
   if(atlas){
     file6 = (TFile*) loadFile(file6,
			       "../corrections/rootOutput/GEN_TrkHistGEN_july28_atlas_qcdPt0to20_eta_0.0to2.4_jet_0.0to2000.0_preTrackAna_varBin1_rebin4.root");
     hdndpt6 = (TH1D*) file6->Get("corrTypeTwoGEN/hInvCorrR");
     tdndpt6 = (TGraphErrors*) file6->Get("corrTypeTwoGEN/tInvCorr");
     if(hdndpt6==0 || tdndpt6==0) {
       Error("[HistLoading]","could not get histogram");
       return;
     }
   }
   */

   
   // Normalization 
   //float N_evt = 1.13643e+07;
   //float N_evt = 1.;
   hdndpt1->Scale(sigma_nsd);
   
   //--------------------------- CMS measurement ---------------------------
   //cms_7000GeV = (TGraphErrors*) CMS_7TEV(1);
   cms_900GeV = (TGraphErrors*) CMS_900GEV(1);   
   
   //---------------------------- fits --------------------------------------
   TF1 *f2 = new TF1("fitTsallis","[0]*(1+(sqrt(0.1396**2+x**2)-0.1396)/([1]*[2]))**(-[2])",0.5,200);                                                                            
   f2->SetParameters(1.82045e+01,1.53540e-01,7.06942e+00); // fit the fit (used in paper)                                                                                        
   f2->SetLineColor(2), f2->SetLineWidth(2);

   // Basic canvas and dummy histogram
   TCanvas *call = new TCanvas("call","call",510,670);
   setPad(call);

   // ----- pad 1 
   pp1->cd();
   pp1->SetLogy();
   pp1->SetLogx();

   dum1 = GetDummyHist(pt_min,pt_max,ymin,ymax,"p_{T} [GeV/c]","Ed^{3}N/dp^{3} [GeV^{-2}c^{3}]",false);
   dum1->Draw("");
   dum1->GetXaxis()->SetNdivisions(908);
   dum1->GetYaxis()->SetNdivisions(407);

   int fillsty = 3001;

   th1Style2(tdndpt2,2,20,1.0,2,2,1,2,true);
   th1Style2(tdndpt3,4,20,1.0,4,2,2,2,false);
   th1Style2(tdndpt4,6,20,1.0,6,2,4,2,false);
   //th1Style2(tdndpt5,19,20,1.0,19,2,3,3,false);
   th1Style2(tdndpt5,20,20,1.0,20,2,9,3,false); 
   //if(atlas) th1Style2(tdndpt6,20,20,1.0,20,2,4,3,false);
   //th1Style1(hdndpt2,1,24,1.0,1,1.5,1,1); 
   cout<<"Number of bins = "<<hdndpt2->GetXaxis()->GetNbins()<<endl;
   cout<<"Number of bins = "<<hdndpt1->GetXaxis()->GetNbins()<<endl;

   tasydndpt1->SetMarkerSize(1.0); tasydndpt1->SetFillStyle(fillsty), tasydndpt1->SetFillColor(kGray);
   tasydndpt1->Draw("2");

   th1Style1(hdndpt1,1,20,1.0,1,1.5,1,1);  // draw the measurement on top of everything


   //TLegend *leg1 = new TLegend(0.37,0.47,0.74,0.85);
   TLegend *leg1 = new TLegend(0.22,0.09,0.59,0.47);
   leg1->SetMargin(0.3), leg1->SetBorderSize(0);
   leg1->SetFillColor(kWhite), leg1->SetFillStyle(0);
   leg1->SetTextSize(0.039), leg1->SetMargin(0.3);
   leg1->SetHeader("    #sqrt{s} = 0.9 TeV,   |#eta|<2.4");
   leg1->AddEntry(tasydndpt1,"CMS    #scale[0.7]{#int}Ldt = 231 #mub^{-1}","plf");
   leg1->AddEntry(tdndpt2,"PYTHIA D6T","l");
   leg1->AddEntry(tdndpt3,"PYTHIA Perugia0","l");
   leg1->AddEntry(tdndpt5,"PYTHIA ProQ20","l");
   leg1->AddEntry(tdndpt4,"PYTHIA 8","l");
   //if(atlas) leg1->AddEntry(tdndpt6,"PYTHIA Atlas","l");

   leg1->Draw();

   putCMSPrel();
   //putIntLum();
   putA();

   // ----- pad 2 
   pp1_1->cd();
   pp1_1->SetLogx();
   
   dum1_1 = GetDummyHist(pt_min,pt_max,ymin_r,ymax_r,"p_{T} [GeV/c]","DATA / MC",false);
   setLowerPad(dum1_1);
   dum1_1->Draw("");

   TLine *line = new TLine(0,1,pt_max,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();

   hdndpt1_2_cln = (TH1D*) hdndpt1->Clone("hdndpt1_2_cln");
   hdndpt1_3_cln = (TH1D*) hdndpt1->Clone("hdndpt1_3_cln");
   hdndpt1_4_cln = (TH1D*) hdndpt1->Clone("hdndpt1_4_cln");
   hdndpt1_5_cln = (TH1D*) hdndpt1->Clone("hdndpt1_5_cln");

   hdndpt2_cln = (TH1D*) hdndpt2->Clone("hdndpt2_cln");
   hdndpt3_cln = (TH1D*) hdndpt3->Clone("hdndpt3_cln");
   hdndpt4_cln = (TH1D*) hdndpt4->Clone("hdndpt4_cln");
   hdndpt5_cln = (TH1D*) hdndpt5->Clone("hdndpt5_cln");

   //hdndpt1_2_cln->Divide(hdndpt2_cln);

   /*
   hdndpt1_2_cln = (TH1D*) ratio_hist_to_hist(hdndpt1,hdndpt2);
   hdndpt1_3_cln = (TH1D*) ratio_hist_to_hist(hdndpt1,hdndpt3);
   hdndpt1_4_cln = (TH1D*) ratio_hist_to_hist(hdndpt1,hdndpt4);
   hdndpt1_5_cln = (TH1D*) ratio_hist_to_hist(hdndpt1,hdndpt5);
   */

   hdndpt1_2_cln->Divide(hdndpt2_cln);
   hdndpt1_3_cln->Divide(hdndpt3_cln);
   hdndpt1_4_cln->Divide(hdndpt4_cln);
   hdndpt1_5_cln->Divide(hdndpt5_cln);


   if(atlas){
     hdndpt1_6_cln = (TH1D*) hdndpt1->Clone("hdndpt1_6_cln");
     hdndpt6_cln = (TH1D*) hdndpt6->Clone("hdndpt6_cln");
     hdndpt1_6_cln->Divide(hdndpt6_cln);
   }
   
   // Draw sys + stat combined error   

   createSysStatErrorHist(hdndpt1,32);
   tsyserr = (TGraphErrors*) TgraphIt(hsyserr);
   tsyserr->SetFillColor(kGray);
   tsyserr->SetFillStyle(fillsty);
   
   tsyserr->Draw("3");
   //hsyserr->Draw("pzsame");          


   //th1Style1(cms_900GeV_div,13,30,1.0,13,1,1,1);

   th1Style1(hdndpt1_2_cln,2,20,1.0,2,2.0,1,3);
   th1Style1(hdndpt1_3_cln,4,20,1.0,4,2.0,2,3);
   //th1Style1(hdndpt1_4_cln,6,20,1.0,6,2.0,9,3);
   th1Style1(hdndpt1_4_cln,6,20,1.0,6,2.0,4,3);
   //th1Style1(hdndpt1_5_cln,19,20,1.0,19,2.0,3,3);
   th1Style1(hdndpt1_5_cln,20,20,1.0,20,2.0,9,3);  

   if(atlas)  th1Style1(hdndpt1_6_cln,20,20,1.0,20,2.0,5,3);


   // print Xsection 
   PrintXsection(hdndpt1,1.);

   // save canvas 
   if(save){
   if(atlas) printCanvases(call, "spectra_inv_cms_vs_pythia_all_v2_900GeV",0);
   else printCanvases(call, "spectra_inv_cms_vs_pythia_v2_900GeV",0);
   }
}

void setSysErrorFunction(){

  // 7 TeV
  //fsyserr = new TF1("functionSysErr","pol2(0)+[3]/(1.0+exp([4]*(x-[5])))",0.5,200);
  //fsyserr->SetParameters(4.65506e-02,2.15971e-05,4.59143e-07,1.56432e-02,-2.81957e-01,3.65004e+01);

  // 900 GeV
  //fsyserr = new TF1("functionSysErr","pol3(0)",0.5,100);
  //fsyserr->SetParameters(4.67529e-02,7.08662e-05,-5.36923e-06,1.45228e-07);

  // 900 GeV data (Nov 02)
  //fsyserr = new TF1("functionSysErr","pol3(0)",0.5,100);
  //fsyserr->SetParameters(4.45545e-02,7.32198e-05,-5.54754e-06,1.50647e-07);
  
  // 900 GeV data (Feb 14 2011)
  fsyserr = new TF1("functionSysErr","pol3(0)",0.5,100); 
  fsyserr->SetParameters(4.29257e-02,8.11031e-05,-5.79042e-06,1.51412e-07);


}


void createSysStatErrorHist(TH1D *hist_pre, double maxpt){

  // * even if hist_pre is already normalized, as far as it was normalized
  //   properly in a way that statistical error bar was scaled accordingly,
  //   statiscal error obtained here should be same otherwise. 

  TH1D *histErr = (TH1D*) hist_pre->Clone("histErr");
  hsyserr = (TH1D*) hist_pre->Clone("hsyserr");
  hsyserr->Reset(), hsyserr->Sumw2();

  int maxpt_bin = histErr->GetXaxis()->FindBin(maxpt);
  cout<<"[setSysStatError] max pt "<<maxpt<<" found bin = "<<maxpt_bin
      <<" cross checked pt (low edge) = "<<histErr->GetXaxis()->GetBinLowEdge(maxpt_bin)
      <<" pt (up edge) = "<<histErr->GetXaxis()->GetBinUpEdge(maxpt_bin);
  
  cout<<""<<endl;
  for(int i=0;i<histErr->GetNbinsX();i++){ 
    double pt = histErr->GetBinCenter(i+1);
    
    double statferr = (histErr->GetBinContent(i+1)!=0) ? 
      histErr->GetBinError(i+1)/histErr->GetBinContent(i+1) : 0.0; 

    if(pt>maxpt) 
      statferr = histErr->GetBinError(maxpt_bin)/histErr->GetBinContent(maxpt_bin); // freeze stat error

    double sysferr = fsyserr->Eval(pt);
    double sumferr = sqrt(statferr*statferr + sysferr*sysferr);
    double sumerr = 1.*sumferr;
    hsyserr->SetBinContent(i+1,1);
    hsyserr->SetBinError(i+1,sumerr);
    cout<<"[setSysStatError] pt = "<<pt<<" stat err (frac): "<<statferr<<" syst err (fac): "<<sysferr<<" combined (frac): "<<sumferr<<endl;
  }

}


TH1D *resetSysStatError(TH1D *hist){

  for(int i=0;i<hist->GetNbinsX();i++){ 
    double pt = hist->GetBinCenter(i+1);
    double content = hist->GetBinContent(i+1);
    double statferr = hist->GetBinError(i+1)/content;
    if(i==(hist->GetNbinsX()-1)) statferr = 0.9; // last bin treatment
    double sysferr = fsyserr->Eval(pt);
    double sumferr = sqrt(statferr*statferr + sysferr*sysferr);
    double sumerr = content*sumferr;
    hist->SetBinContent(i+1,content);
    hist->SetBinError(i+1,sumerr);
  }
  return hist;
}

TGraphAsymmErrors* TGraphAsyErrIt(TH1D* hist){

  TGraphAsymmErrors *tg;
  int nbins = hist->GetNbinsX();

  const int nlines = nbins;

  float pt[nlines], xsec[nlines];
  float pterrl[nlines], xsecerrl[nlines];
  float pterrh[nlines], xsecerrh[nlines];

  for(int i = 0; i<nbins; i++ ){
    pt[i] = hist->GetBinCenter(i+1);
    xsec[i] = hist->GetBinContent(i+1);

    xsecerrl[i] = hist->GetBinError(i+1);
    xsecerrh[i] = hist->GetBinError(i+1);

    pterrl[i] = pt[i]*0.12;
    pterrh[i] = pt[i]*0.12;
    //pterrh[i] = pt[i]/(0.2);

  }

  tg = new TGraphAsymmErrors(nlines,pt,xsec,pterrl,pterrh,xsecerrl,xsecerrh);
  return tg;
}



void setLowerPad(TH1D *dum_low){

   //Just to make lower pannel lable appearing as similar size as upper one                                                                                                  
   dum_low->GetYaxis()->SetLabelSize(0.07);
   dum_low->GetYaxis()->SetTitleSize(0.08);
   dum_low->GetYaxis()->SetTitleOffset(1.0);

   dum_low->GetXaxis()->SetLabelSize(0.09);
   dum_low->GetXaxis()->SetLabelOffset(0.05);
   dum_low->GetXaxis()->SetTitleSize(0.11);
   dum_low->GetXaxis()->SetTitleOffset(1.47);

   //dum_low->GetYaxis()->SetNdivisions(405);
   dum_low->GetYaxis()->SetNdivisions(409); 
   dum_low->GetYaxis()-> SetDecimals(true);
   dum_low->Draw();

}



void setPad(TCanvas *can){

   can->cd();

   pp1 = new TPad("p1","p1",0,0.34,1,1,0,0,0);
   pp1->SetBottomMargin(0.0);
   pp1->SetTopMargin(0.05*(1/0.72));

   pp1->Draw();
   pp1->cd();
   pp1->SetNumber(1);

   can->cd();

   pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.34,0,0,0);
   pp1_1->SetTopMargin(0);
   pp1_1->SetBottomMargin(0.14*(1/0.34));
   pp1_1->Draw();
   pp1_1->cd();
   pp1_1->SetNumber(2);
}


void putCMSPrel(){
  tex = new TLatex(0.66,0.86,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}

void putA(){
  TLatex * texA;
  texA = new TLatex(0.2,0.88,"(a)");
  texA->SetTextSize(0.04);
  texA->SetLineWidth(2);
  texA->SetNDC();
  texA->Draw();
}


void putB(){
  TLatex * texB;
  texB= new TLatex(0.2,0.88,"(b)");
  texB->SetTextSize(0.04);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();
}

void putIntLum(){
  //tex2 = new TLatex(0.67,0.77,"#intLdt = 10.2 nb^{-1}");
  //tex2 = new TLatex(0.43,0.85,"#intLdt = 10.2 nb^{-1}");
  tex2 = new TLatex(0.68,0.78,"#intLdt = 10.2 nb^{-1}");
  tex2->SetTextSize(0.034);
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();
}
