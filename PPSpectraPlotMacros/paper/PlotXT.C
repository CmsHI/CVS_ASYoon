//-------------------------------------------------------------------
// July 29 2010 Andre S. Yoon
// Plot xT spectra from the output of ExtractXTSpectraNSave
//-------------------------------------------------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include "utilities.h"
#include "commonStyle.h"

#include "TLine.h"
#include "TLegend.h"
#endif


TFile *file1=0, *file2=0, *file3=0, *file4=0, *file5=0, *file6=0, *file7=0, *file8=0;
TGraphErrors *tgxtspec1=0, *tgxtspec2=0, *tgxtspec3=0;
TGraphErrors *tgxtspec4=0, *tgxtspec5=0, *tgxtspec6=0, *tgxtspec7=0, *tgxtspec8=0;

TH1D *dum1=0, *dum2=0;


TLatex *tex=0, *tex2=0, *tex3=0;

//-----------------------------------
void putCMSPrel();
void putIntLum();
void putIntLum2();
void putA();
void putB();
//-----------------------------------

void PlotXT(bool save=false){

  // only CMS
  bool onlyCMS = false;

  // range
  float xt_min, xt_max;
  float ymin, ymax;
  
  xt_min = 0.00005, xt_max = 0.2;
  //ymin = 8e2, ymax = 8e22;
  //ymin = 7e4, ymax = 2e23; 
  ymin = 7e3, ymax = 2e21;    

  // file loading
  /*
  file1 = (TFile*) loadFile(file1,"./rootOutput/XT_Spectra_ua1_xsection_200GeV_v2_expnt5.1.root");
  file2 = (TFile*) loadFile(file2,"./rootOutput/XT_Spectra_ua1_xsection_500GeV_v2_expnt5.1.root");
  file3 = (TFile*) loadFile(file3,"./rootOutput/XT_Spectra_ua1_xsection_900GeV_v2_expnt5.1.root");
  file4 = (TFile*) loadFile(file4,"./rootOutput/XT_Spectra_cdf_xsection_630GeV_expnt5.1.root");
  file5 = (TFile*) loadFile(file5,"./rootOutput/XT_Spectra_cdf_xsection_1800GeV_expnt5.1.root");
  //file6 = (TFile*) loadFile(file6,"./rootOutput/XT_Spectra_cdf_xsection_1960GeV_v2_expnt5.1.root");
  file6 = (TFile*) loadFile(file6,"./rootOutput/XT_Spectra_cdf_1960_fromAddendum_expnt5.1.root");
  //file7 = (TFile*) loadFile(file7,"./rootOutput/XT_Spectra_cms_xsection_7000GeV_july23_etav2_v2_expnt5.1.root");
  //file7 = (TFile*) loadFile(file7,"./rootOutput/XT_Spectra_cms_xsection_7000GeV_eta1.0_71.3mb_hp_hm_expnt5.1.root");
  file7 = (TFile*) loadFile(file7,"./rootOutput/XT_Spectra_cms_xsection_7000GeV_eta1.0_56.47mb_hp_hm_expnt5.1.root");
  //file8 = (TFile*) loadFile(file8,"./rootOutput/XT_Spectra_cms_xsection_900GeV_oct29_eta1_v1_expnt5.1.root");
  //file8 = (TFile*) loadFile(file8,"./rootOutput/XT_Spectra_cms_xsection_900GeV_nov022010_v1_expnt5.1.root");
  //file8 = (TFile*) loadFile(file8,"./rootOutput/XT_Spectra_cms_xsection_900GeV_eta1.0_52.43mb_hp_hm_expnt5.1.root");
  //file8 = (TFile*) loadFile(file8,"./rootOutput/XT_Spectra_cms_xsection_900GeV_eta1.0_36.99mb_hp_hm_expnt5.1.root");
  file8 = (TFile*) loadFile(file8,"./rootOutput/XT_Spectra_cms_xsection_900GeV_eta1.0_38.42mb_hp_hm_feb152011_expnt5.1.root");
  */

  file1 = (TFile*) loadFile(file1,"./rootOutput/feb202011/XT_Spectra_ua1_xsection_200GeV_v2_expnt4.9.root");
  file2 = (TFile*) loadFile(file2,"./rootOutput/feb202011/XT_Spectra_ua1_xsection_500GeV_v2_expnt4.9.root");
  file3 = (TFile*) loadFile(file3,"./rootOutput/feb202011/XT_Spectra_ua1_xsection_900GeV_v2_expnt4.9.root");
  file4 = (TFile*) loadFile(file4,"./rootOutput/feb202011/XT_Spectra_cdf_xsection_630GeV_expnt4.9.root");
  file5 = (TFile*) loadFile(file5,"./rootOutput/feb202011/XT_Spectra_cdf_xsection_1800GeV_expnt4.9.root");
  file6 = (TFile*) loadFile(file6,"./rootOutput/feb202011/XT_Spectra_cdf_1960_fromAddendum_expnt4.9.root");
  //file7 = (TFile*) loadFile(file7,"./rootOutput/feb202011/XT_Spectra_cms_xsection_7000GeV_eta1.0_56.47mb_hp_hm_expnt4.9.root");
  file7 = (TFile*) loadFile(file7,"./rootOutput/feb202011/XT_Spectra_cms_xsection_7000GeV_eta1.0_56.47mb_hp_hm_feb222011_expnt4.9.root");
  file8 = (TFile*) loadFile(file8,"./rootOutput/feb202011/XT_Spectra_cms_xsection_900GeV_eta1.0_38.42mb_hp_hm_feb152011_expnt4.9.root");

  tgxtspec1 = (TGraphErrors*) file1->Get("tgXtSpec");
  tgxtspec2 = (TGraphErrors*) file2->Get("tgXtSpec");
  tgxtspec3 = (TGraphErrors*) file3->Get("tgXtSpec");
  tgxtspec4 = (TGraphErrors*) file4->Get("tgXtSpec");
  tgxtspec5 = (TGraphErrors*) file5->Get("tgXtSpec");
  tgxtspec6 = (TGraphErrors*) file6->Get("tgXtSpec");
  tgxtspec7 = (TGraphErrors*) file7->Get("tgXtSpec");
  tgxtspec8 = (TGraphErrors*) file8->Get("tgXtSpec");

  if(tgxtspec1==0||tgxtspec2==0||tgxtspec3==0||tgxtspec4==0||
     tgxtspec5==0||tgxtspec6==0||tgxtspec7==0||tgxtspec8==0) {
    Error("[TGraphLoading]","could not get histogram");
    return;
  }

  // canvas setting
  TCanvas *call1 = new TCanvas("call1","call1",510,670);
  call1->SetLogx(), call1->SetLogy();

  char xTitle[100],yTitle[100];

  sprintf(yTitle,"(#sqrt{s}/GeV)^{4.9}Ed^{3}#sigma/dp^{3} [mb GeV^{-2}c^{3}]");
  sprintf(xTitle,"x_{T}");

  dum1 = GetDummyHist(xt_min,xt_max,ymin,ymax,xTitle,yTitle,false);
  dum1->Draw("");
  dum1->GetXaxis()->SetNdivisions(908);
  dum1->GetYaxis()->SetNdivisions(407);

  // plotting
  float msize =0.9;
  if(!onlyCMS){
    th1Style1(tgxtspec1,14,3,msize,14,1.5,1,1);
    th1Style1(tgxtspec2,15,25,msize,15,1.5,1,1);
    th1Style1(tgxtspec3,16,26,msize,16,1.5,1,1);
    th1Style1(tgxtspec4,18,27,msize,18,1.5,1,1);
    th1Style1(tgxtspec6,19,30,msize,19,1.5,1,1);
    th1Style1(tgxtspec5,17,28,msize,17,1.5,1,1);
  }
  th1Style1(tgxtspec7,1,20,msize,1,1.5,1,1);
  th1Style1(tgxtspec8,2,20,msize,2,1.5,1,1);


  // legend 
  //TLegend *leg2 = new TLegend(0.21,0.17,0.70,0.45);
  TLegend *leg2 = new TLegend(0.19,0.17,0.68,0.45);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextSize(0.031);
  leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)");
  leg2->AddEntry(tgxtspec7,"CMS 7 TeV (2.96 pb^{-1})","p");
  leg2->AddEntry(tgxtspec8,"CMS 0.9 TeV (231 #mub^{-1})","p");
  if(!onlyCMS){
  leg2->AddEntry(tgxtspec6,"CDF 1.96 TeV","p");
  leg2->AddEntry(tgxtspec5,"CDF 1.8 TeV","p");
  leg2->AddEntry(tgxtspec4,"CDF 0.63 TeV","p");
  leg2->AddEntry(tgxtspec3,"UA1 0.90 TeV (|#eta|<2.5)","p");
  leg2->AddEntry(tgxtspec2,"UA1 0.50 TeV (|#eta|<2.5)","p");
  leg2->AddEntry(tgxtspec1,"UA1 0.20 TeV (|#eta|<2.5)","p");
  }
  leg2->Draw();
  
  //putCMSPrel();
  //putIntLum();
  //putIntLum2();
  if(!onlyCMS) putA();
  else putB();

  if(save){
    if(!onlyCMS) printCanvases(call1, "xT_spectra_compiled_v4",1);
    else printCanvases(call1, "xT_spectra_compiled_onlyCMS_v4",1);
  }

}


void putA(){
  TLatex * texA;
  texA = new TLatex(0.2,0.90,"(a)");
  texA->SetTextSize(0.04);
  texA->SetLineWidth(2);
  texA->SetNDC();
  texA->Draw();
}

void putB(){
  TLatex * texB;
  texB = new TLatex(0.2,0.90,"(b)");
  texB->SetTextSize(0.04);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();
}


void putCMSPrel(){
  tex = new TLatex(0.66,0.90,"CMS Preliminary");
  tex->SetTextSize(0.035);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}



void putIntLum(){
  //tex2 = new TLatex(0.66,0.83,"#intLdt = 10.2 nb^{-1} for 7 TeV");
  //tex2->SetTextSize(0.032);
  tex2 = new TLatex(0.46,0.83,"#intLdt = 231 #mub^{-1} (2.96 pb^{-1}) for 0.9 (7) TeV");  
  tex2->SetTextSize(0.028); 
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();
}

void putIntLum2(){
  tex3 = new TLatex(0.66,0.73,"#intLdt = 231 #mub^{-1} for 0.9 TeV");
  //tex3->SetTextSize(0.032);
  tex3->SetTextSize(0.025);
  tex3->SetLineWidth(2);
  tex3->SetNDC();
  tex3->Draw();
}

