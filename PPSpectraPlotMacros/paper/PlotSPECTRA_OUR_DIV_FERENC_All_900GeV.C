//-----------------------------------------------------------------
// July 06 2010    Andre S. Yoon 
//-----------------------------------------------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include "utilities.h"
#include "commonStyle.h"
#include "cms900GeV_Tsalis.h"

#include "TLine.h"
#include "TLegend.h"
#include "TSpline.h"
#endif


TFile *file1=0, *file2=0, *file3=0;

TH1D *hdndpt1=0, *hdndpt2=0, *hdndpt3=0;
TH1D *hdndpt1_cln=0, *hdndpt2_cln=0, *hdndpt3_cln=0;
TH1D *hdndpt1_div=0, *hdndpt2_div=0, *hdndpt3_div=0;

TGraphErrors *tdndpt1_div=0;

TGraphErrors *cms_900GeV=0;
TGraphErrors *cms_900GeV_div=0;

TGraph *cms_900GeV_tsalis=0;
TGraph *cms_900GeV_tsalis_full=0;
TSpline3 *cms_900GeV_tsalis_TS=0;
TGraphErrors *cms_900GeV_tsalis_int=0;


TF1 *fitF=0;

TPad *pp1=0, *pp1_1=0;
TH1D *dum1=0, *dum1_1=0;

TCanvas *can2=0, *can3=0, *can4=0, *can5=0, *can6=0, *can7=0;
TH1D *dum2=0, *dum3=0, *dum4=0, *dum5=0, *dum6=0, *dum7=0;

TString fitFormula;

TLegend *leg1=0;
TLatex *tex=0, *tex2=0;
//-------------------------------------------------
void setPad(TCanvas *can);
void setLowerPad(TH1D *dum_low);
void putCMSPrel();
void putIntLum();
TH1D* setHistErrors(TH1D *hist, double cer);
void putA();
//------------------------------------------------- 

void PlotSPECTRA_OUR_DIV_FERENC_All_900GeV(bool save=false){

   bool lowpT = true;

   float pt_min, pt_max;
   float ymin, ymax;
   float ymin_r, ymax_r;

   if(lowpT){
     pt_min = 0.5, pt_max = 4.2;
     //pt_min = 0.5, pt_max = 5.2;
     ymin = 2E-5, ymax = 5E+1;
      ymin_r = 0.6, ymax_r = 1.3;
   }else{
      pt_min = 0.5, pt_max = 80;
      ymin = 2E-13, ymax = 5E+1;
      ymin_r = 0.6, ymax_r = 1.3;
   }
   
   
   // file loading -----------------------------------------
   file1 = (TFile*) loadFile(file1,
			     "./../rootOutput_2nd/feb142011/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     //"./../rootOutput_2nd/feb142011/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc1102_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     //"../rootOutput/CORRv1_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     //"../rootOutput/CORR_MB-C10-May6RR-MB900GeVskim-v1_proc0831_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0.root");
			     //"../corrections/rootOutput_aug3/CORR_TEST1_MB-C10-PR9-M6RR-JTMskim_Merged_0to2.4_proc0710.root");
			     //"./rootOutput/CORR_TEST1_trkhists_r132440_eta_0.0to2.4_jet_0.0to2000.0_trackAna_STD_GEN0_varBin1.root");
			     //"./rootOutput/CORR_All_Merged_witScale_Rebin4.root");
			     //"./rootOutput/CORR_ALL_Merged_FixedProjection.root");
   
   hdndpt1 = (TH1D*) file1->Get("corrTypeTwo/hInvCorrTwoLev2R");
   if(hdndpt1==0) {
      Error("[HistLoading]","could not get histogram");
      return;
   }

   hdndpt1->GetXaxis()->SetRange(3,hdndpt1->GetXaxis()->GetLast());

   
   // Normalization 
   float N_evt = 1.13643e+07;
   //hdndpt1->Scale(1/N_evt);


   //--------------------------- CMS measurement ---------------------------
   cms_900GeV = (TGraphErrors*) CMS_900GEV(1);   
   cms_900GeV_tsalis = (TGraph*) CMS_900GEV_TSALIS(false,true); // this is used for drawing but not for tspline
   cms_900GeV_tsalis_full = (TGraph*) CMS_900GEV_TSALIS(false,false);
   cms_900GeV_tsalis_TS = new TSpline3("cms_900GeV_tsalis_TS",cms_900GeV_tsalis_full);
   //cms_900GeV_tsalis_TS = new TSpline3("cms_900GeV_tsalis_TS",cms_900GeV_tsalis,"",0.5,5.0);   
   //cout<<"test evaluation - "<<cms_900GeV_tsalis_TS->Eval(3)<<endl;

   //---------------------------- fits --------------------------------------
   TF1 *f2 = new TF1("fitTsallis","[0]*(1+(sqrt(0.1396**2+x**2)-0.1396)/([1]*[2]))**(-[2])",0.5,200);                                                                            
   f2->SetParameters(1.82045e+01,1.53540e-01,7.06942e+00); // fit the fit (used in paper)                                                                                        
   f2->SetLineColor(2), f2->SetLineWidth(2), f2->SetLineStyle(9);

   // Basic canvas and dummy histogram
   TCanvas *call = new TCanvas("call","call",510,670);
   setPad(call);

   // ----- pad 1 
   pp1->cd();
   pp1->SetLogy();

   dum1 = GetDummyHist(0,pt_max,ymin,ymax,"p_{T} [GeV/c]","Ed^{3}N/dp^{3} [GeV^{-2}c^{3}]",false);
   dum1->Draw("");

   // set error
   //double cerr = 0.032; // overall normalization scale uncertainty 3.5% for 7TeV
   // Feb 14 2011
   double cerr = 0.0287; // lower range
   //double cerr = 0.0344;  // upper range
   hdndpt1 = setHistErrors(hdndpt1, cerr);

   //f2->Draw("same");
   //th1Style1(cms_900GeV_tsalis_full,13,30,1.3,2,2,9,2);
   th1Style1(cms_900GeV_tsalis,13,30,1.3,2,2,9,2); 
   th1Style1(cms_900GeV,13,30,1.3,13,1,1,1);
   th1Style1(hdndpt1,1,20,1.0,1,1.5,1,1);

   
   //leg1 = new TLegend(0.46,0.48,0.96,0.84);
   //leg1 = new TLegend(0.48,0.48,0.90,0.84);
   //leg1 = new TLegend(0.46,0.47,0.88,0.83);
   leg1 = new TLegend(0.46,0.54,0.88,0.90);
   leg1->SetBorderSize(0), leg1->SetFillStyle(0);
   leg1->SetTextSize(0.034);
   leg1->SetHeader("     #sqrt{s} = 0.9 TeV,  |#eta|<2.4");
   //leg1->AddEntry(hdndpt1,"CMS (2010 data)","pl");
   leg1->AddEntry(hdndpt1,"CMS     #scale[0.7]{#int}Ldt = 231 #mub^{-1}","pl");
   leg1->AddEntry(cms_900GeV,"CMS (JHEP 02 (2010) 041)","pl");
   leg1->AddEntry(cms_900GeV_tsalis,"Tsallis fit (JHEP 02 (2010) 041)","l");
   leg1->Draw();

   //putCMSPrel();
   //putIntLum();

   putA();

   // ----- pad 2 
   pp1_1->cd();

   dum1_1 = GetDummyHist(0,pt_max,ymin_r,ymax_r,"p_{T} [GeV/c]","Data / Fit",false);
   setLowerPad(dum1_1);
   dum1_1->Draw("");

   TLine *line = new TLine(0,1,pt_max,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();

   hdndpt1_cln = (TH1D*) hdndpt1->Clone("hdndpt1_cln");
   hdndpt1_div = (TH1D*) ratio_hist_to_tspline(hdndpt1_cln,cms_900GeV_tsalis_TS,0.4,9.0);
   //hdndpt1_div = (TH1D*) ratio_hist_to_func(hdndpt1_cln,f2,0.4,9.0);
   
   //cms_900GeV_div = (TGraphErrors*) ratio_func_to_func(cms_900GeV,f2,0.4,6.0);
   cms_900GeV_div = (TGraphErrors*) ratio_func_to_tspline(cms_900GeV,cms_900GeV_tsalis_TS,0.4,6.0);

   th1Style1(cms_900GeV_div,13,30,1.3,13,1,1,1);
   //th1Style1(hdndpt1_div,1,20,1.0,1,1.5,1,1);
   
   int fillsty = 3001;

   tdndpt1_div = (TGraphErrors*) TgraphIt(hdndpt1_div);
   //tdndpt1_div = setErrors(tdndpt1_div, cerr);
   tdndpt1_div->SetFillColor(kGray);
   tdndpt1_div->SetFillStyle(fillsty);
   //tdndpt1_div->SetMarkerSize(1);
   tdndpt1_div->Draw("3");
   //tdndpt1_div->Draw("pzsame");    

   TH1D *hdndpt1_div_dum = (TH1D*) hdndpt1_div->Clone("hdndpt1_div_dum");
   hdndpt1_div_dum = setHistErrors(hdndpt1_div_dum, 0);
   th1Style1(hdndpt1_div_dum,1,20,1.0,1,1.5,1,1);
   //hdndpt1_div->Draw("psame");

   //save it
   if(save){
     printCanvases(call, "CMS_old_vs_new_with_tsallis_900GeV_v1",0);
   }
}




void setLowerPad(TH1D *dum_low){

   //Just to make lower pannel lable appearing as similar size as upper one                                                                                                  
   dum_low->GetYaxis()->SetLabelSize(0.07);
   dum_low->GetYaxis()->SetTitleSize(0.09);
   dum_low->GetYaxis()->SetTitleOffset(0.95);

   dum_low->GetXaxis()->SetLabelSize(0.09);
   dum_low->GetXaxis()->SetLabelOffset(0.05);
   dum_low->GetXaxis()->SetTitleSize(0.11);
   dum_low->GetXaxis()->SetTitleOffset(1.47);

   dum_low->GetYaxis()->SetNdivisions(405);
   dum_low->GetYaxis()-> SetDecimals(true);
   dum_low->Draw();

}

TH1D *setHistErrors(TH1D *hist, double cer){
  for(int i=0;i<hist->GetNbinsX();i++){
    double content = hist->GetBinContent(i+1);
    double err = hist->GetBinError(i+1);
    double nerr = content*cer;
    hist->SetBinContent(i+1,content);
    hist->SetBinError(i+1,nerr); // in the histogram error bar will be + and - nerr! (twice the length!)
  }
  return hist;
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

void putA(){
  TLatex * texA;
  texA = new TLatex(0.2,0.88,"(a)");
  texA->SetTextSize(0.04);
  texA->SetLineWidth(2);
  texA->SetNDC();
  texA->Draw();
}

void putCMSPrel(){
  tex = new TLatex(0.66,0.86,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
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
