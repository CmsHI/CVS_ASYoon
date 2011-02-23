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
#include "TPaveStats.h"
#include "TGaxis.h"
#include "TPolyLine.h"
#endif


TFile *file1=0, *file2=0, *file3=0, *file4=0, *file5=0, *file6=0, *file7=0, *file8=0;
TGraphErrors *tgxtspec1=0, *tgxtspec2=0, *tgxtspec3=0;
TGraphErrors *tgxtspec4=0, *tgxtspec5=0, *tgxtspec6=0, *tgxtspec7=0, *tgxtspec8=0;

TPad *pp1=0, *pp1_1=0;
TH1D *dum1=0, *dum1_1=0;


TLatex *tex=0, *tex2=0, *tex3=0;

//-----------------------------------
TGraphErrors* ratio_func_to_func(TGraphErrors* num, double minx, double maxx, double sqrts);
void setPad(TCanvas *can);
void setLowerPad(TH1D *dum_low);
void setUpperPad(TH1D *dum_up);
TGraph *recasted(TGraph *tg);
void putCMSPrel();
void putIntLum();
void putIntLum2();
void putA();
void putB();
//-----------------------------------

void PlotLinearInt(bool save=false){

  // only CMS
  bool onlyCMS = false;

  // range
  float xt_min, xt_max;
  float ymin, ymax;
  float ymin_r, ymax_r;

  xt_min = 0.00, xt_max = 8.1;
  ymin = 3e3, ymax = 2e23;    
  ymin_r = 0.001, ymax_r = 0.08;


  TFile *fData = new TFile("../rootOutput_postApp_3rd/feb222011/output_interpolation.root");

  TGraph *tg_data_3gev = (TGraph*) fData->Get("gXS2");
  TGraph *tg_data_9gev = (TGraph*) fData->Get("gXS5");
  
  TF1 *tf1_fit_3gev = (TF1*) fData->Get("fitXS2");
  TF1 *tf1_fit_9gev = (TF1*) fData->Get("fitXS5");
  
  TH1F *th1_dum_3gev = (TH1F*) fData->Get("dumXS2");
  TH1F *th1_dum_9gev = (TH1F*) fData->Get("dumXS5");

  TGraphErrors *tg_xt_9GeV = (TGraphErrors*) fData->Get("gXS1_5");

  // canvas setting
  TCanvas *call1 = new TCanvas("call1","call1",510,670);
  call1->SetLogx(), call1->SetLogy();

  setPad(call1);

  TLatex *pt1, *pt2;
  pt1 = new TLatex(0.75,0.10,"p_{T} = 3 GeV/c");
  pt1->SetTextSize(0.055);
  pt1->SetLineWidth(1.0);
  pt1->SetNDC();
  
  pt2 = new TLatex(0.75,0.34,"p_{T} = 9 GeV/c");
  pt2->SetTextSize(0.048);
  pt2->SetLineWidth(1.0);
  pt2->SetNDC();



  // ----- pad 1               
  pp1->cd();

  char xTitle[100],yTitle[100];

  sprintf(yTitle,"Ed^{3}#sigma/dp^{3} [mb GeV^{-2}c^{3}]");
  sprintf(xTitle,"#sqrt{s} [TeV]");

  gStyle->SetOptFit(0);

  dum1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1->GetXaxis()->SetNdivisions(908);
  dum1->GetYaxis()->SetNdivisions(507);
  setUpperPad(dum1);
  dum1->Draw("");

  float msize =0.9;     
  //tf1_fit_3gev->SetLineStyle(9);
  //tf1_fit_3gev->SetLineWidth(2.0);
  tf1_fit_3gev->Draw("same");
  th1Style1(tg_data_3gev,1,20,msize,1,1.5,1,1);

  putCMSPrel();
  putA();
  pt1->Draw();

  //putIntLum();
  //putB();

  //putIntLum2();
  //if(!onlyCMS) putA();
  //else putB();

  /*
  TLegend *leg2 = new TLegend(0.21,0.51,0.62,0.78); 
  leg2->SetColumnSeparation(0.04);
  leg2->SetBorderSize(0); 
  leg2->SetFillStyle(0); 
  leg2->SetTextSize(0.038); 
  leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)"); 
  leg2->AddEntry(tf1_fit_3gev,"3rd order polynomial","l");    
  leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.63, 1.86, 1.96 (CDF)","pl");
  leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.9, 7.0 (CMS)","pl");
  leg2->AddEntry(tg_xt_9GeV,"#sqrt{s} = 2.76 (x_{T} scaling interp.)","pl");
  leg2->Draw("");
  */

  // ----- pad 2         
  pp1_1->cd();

  sprintf(yTitle,"Ed^{3}#sigma/dp^{3} [mb GeV^{-2}c^{3}] x 10^{3}");

  ymin_r = 0.0, ymax_r = 1.55E-4;

  dum1_1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1_1->GetXaxis()->SetNdivisions(908);
  dum1_1->GetYaxis()->SetNdivisions(505);
  dum1_1->GetYaxis()->SetDecimals(1);
  setUpperPad(dum1_1);
  dum1_1->Draw(""); 

  
  tf1_fit_9gev->Draw("same");
  th1Style1(tg_data_9gev,1,20,msize,1,1.5,1,1);
  th1Style1(tg_xt_9GeV,4,24,msize,4,1.5,1,1);

  pt2->Draw();



  TLegend *leg2 = new TLegend(0.19,0.60,0.68,0.96);
  leg2->SetColumnSeparation(0.04);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextSize(0.038);
  leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)");
  leg2->AddEntry(tf1_fit_3gev,"2^{nd} order polynomial","l");
  leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.63, 1.8, 1.96 (CDF)","pl");
  leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.9, 7.0 (CMS)","pl");
  leg2->AddEntry(tg_xt_9GeV,"#sqrt{s} = 2.76 (x_{T} scaling interp.)","pl");
  leg2->Draw("");


  if(save){
    printCanvases(call1, "linear_xsect_inter_v1",1);
  }

}


TGraphErrors* ratio_func_to_func(TGraphErrors* num, double minx, double maxx, double sqrts){

  cout<<"[Ratio to fit used]"<<endl;

  TF1 *f3=0;
  f3 = new TF1("f3","[0]*pow((1+(x/[1])),-1.*[2])",0.0015,0.05);
  //f3->SetParameters(4.751E+22,0.0002754,6.963);                                                                                                              
  //f3->SetParameters(1.361E+23,0.0001977,6.517);                                                                                                              
  //f3->SetParameters(1.404E+23,0.0001957,6.503); // CMS 900 GeV Nov 02                                                                                          
  //f3->SetParameters(9.96242e+22,1.37197e-04,6.24343e+00);  // n = 4.9 with all measurements
  //f3->SetParameters(7.53725e+22,1.66768e-04,6.63062e+00);
  f3->SetParameters(1.018e+19,0.0008856,7);


  TGraphErrors *tg;
  double min_xt = 2.*(minx)/sqrts;

  int nbin = num->GetN();

  const int nlines = nbin;
  double pt[nlines], pterr[nlines];
  double xsec[nlines], xsecerr[nlines];
  double ratio[nlines], ratioerr[nlines];

  for(int i=0;i<nbin;i++){

    num->GetPoint(i,pt[i],xsec[i]);
    xsecerr[i] = num->GetErrorY(i);
    double cms_value = (double) f3->Eval(pt[i]);
    if(pt[i]>min_xt && pt[i]<maxx){
      ratio[i] = xsec[i]/cms_value;
      ratioerr[i] = (xsecerr[i]/xsec[i])*ratio[i];
      //ratioerr[i] = xsecerr[i]/cms_value;                                                                                                                    
    }else{
      ratio[i] = -999;
      ratioerr[i] = 0.0;
    }

    pterr[i] = 0;
  }

  tg = new TGraphErrors(nlines,pt,ratio,pterr,ratioerr);
  return tg;
}

TGraph *recasted(TGraph *tg){
  TGraph *ntg;
  int nbin = tg->GetN();
  const int nlines = nbin-3;
  double pt[nlines], pterr[nlines];
  double ratio[nlines], ratioerr[nlines];

  for(int i=3;i<nbin;i++){
    tg->GetPoint(i,pt[i],ratio[i]);
  }
  
  ntg = new TGraph(nlines,pt,ratio);
  return ntg;
}



void setPad(TCanvas *can){

  can->cd();

  //pp1 = new TPad("p1","p1",0,0.34,1,1,0,0,0);
  pp1 = new TPad("p1","p1",0,0.53,1,1,0,0,0);  
  pp1->SetBottomMargin(0.0);
  //pp1->SetTopMargin(0.05*(1/0.72));
  pp1->SetTopMargin(0.09*(1/0.72));       

  pp1->Draw();
  pp1->cd();
  pp1->SetNumber(1);

  can->cd();

  //pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.34,0,0,0);
  pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.53,0,0,0);
  pp1_1->SetTopMargin(0);
  //pp1_1->SetBottomMargin(0.14*(1/0.34));
  pp1_1->SetBottomMargin(0.14*(1/0.55)); 
  pp1_1->Draw();
  pp1_1->cd();
  pp1_1->SetNumber(2);
}

void setLowerPad(TH1D *dum_low){

  //Just to make lower pannel lable appearing as similar size as upper one 
  dum_low->GetYaxis()->SetLabelSize(0.045);
  dum_low->GetYaxis()->SetTitleSize(0.05);
  dum_low->GetYaxis()->SetTitleOffset(1.5);

  dum_low->GetXaxis()->SetLabelSize(0.05);
  dum_low->GetXaxis()->SetLabelOffset(0.05);
  dum_low->GetXaxis()->SetTitleSize(0.065);
  dum_low->GetXaxis()->SetTitleOffset(1.47);

  //dum_low->GetYaxis()->SetNdivisions(405);                                                                                 
  dum_low->GetYaxis()->SetNdivisions(409);
  dum_low->GetYaxis()-> SetDecimals(true);

}

void setUpperPad(TH1D *dum_up){

  dum_up->GetXaxis()->SetLabelSize(17);
  dum_up->GetXaxis()->SetLabelFont(43);
  dum_up->GetXaxis()->SetLabelOffset(0.04);
  dum_up->GetXaxis()->SetTitleSize(21);
  dum_up->GetXaxis()->SetTitleFont(43);
  dum_up->GetXaxis()->SetTitleOffset(3.1);
  dum_up->GetXaxis()->CenterTitle();

  dum_up->GetYaxis()->SetLabelSize(15);
  dum_up->GetYaxis()->SetLabelFont(43);
  dum_up->GetYaxis()->SetTitleSize(17);
  dum_up->GetYaxis()->SetTitleFont(43);
  dum_up->GetYaxis()->SetTitleOffset(3.2);
  dum_up->GetYaxis()->CenterTitle();
  
}



void putA(){
  TLatex * texA;
  texA = new TLatex(0.2,0.80,"(a)");
  texA->SetTextSize(0.055);
  texA->SetLineWidth(2);
  texA->SetNDC();
  texA->Draw();
}

void putB(){
  TLatex * texB;
  texB = new TLatex(0.20,0.80,"(b)");
  texB->SetTextSize(0.055);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();
}


void putCMSPrel(){
  tex = new TLatex(0.7,0.80,"CMS Preliminary");
  tex->SetTextSize(0.05);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}



void putIntLum(){
  //tex2 = new TLatex(0.66,0.83,"#intLdt = 10.2 nb^{-1} for 7 TeV");
  //tex2->SetTextSize(0.032);
  tex2 = new TLatex(0.55,0.72,"#intLdt = 231 #mub^{-1} (2.96 pb^{-1}) for 0.9 (7) TeV");  
  tex2->SetTextSize(0.038); 
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();
}

void putIntLum2(){
  tex3 = new TLatex(0.66,0.73,"#intLdt = 240 #mub^{-1} for 0.9 TeV");
  //tex3->SetTextSize(0.032);
  tex3->SetTextSize(0.025);
  tex3->SetLineWidth(2);
  tex3->SetNDC();
  tex3->Draw();
}

