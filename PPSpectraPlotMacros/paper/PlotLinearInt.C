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

  xt_min = 0.4, xt_max = 10.1;
  ymin = 3e3, ymax = 2e23;    
  //ymin_r = 0.0025, ymax_r = 0.22;
  ymin_r = 0.0025, ymax_r = 0.52;


  //TFile *fData = new TFile("../rootOutput_postApp_3rd/feb252010/output_interpolation.root");
  TFile *fData = new TFile("../rootOutput_postApp_3rd/feb282011/output_interpolation.root");

  TGraphErrors *tg_data_900_3gev = (TGraphErrors*) fData->Get("gXS900_2");
  TGraphErrors *tg_data_900_9gev = (TGraphErrors*) fData->Get("gXS900_5");
  
  TGraphErrors *tg_data_1960_3gev = (TGraphErrors*) fData->Get("gXS1960_2");
  TGraphErrors *tg_data_1960_9gev = (TGraphErrors*) fData->Get("gXS1960_5");

  TGraphErrors *tg_data_7000_3gev = (TGraphErrors*) fData->Get("gXS7000_2");
  TGraphErrors *tg_data_7000_9gev = (TGraphErrors*) fData->Get("gXS7000_5");

  TGraphErrors *tg_data_630_3gev = (TGraphErrors*) fData->Get("gXS630_2");
  
  TGraphErrors *tg_data_1800_3gev = (TGraphErrors*) fData->Get("gXS1800_2");

  TGraphErrors *tg_data_2360_3gev = (TGraphErrors*) fData->Get("gXS2360_2");

  TF1 *tf1_fit_3gev = (TF1*) fData->Get("fitXS2");
  TF1 *tf1_fit_9gev = (TF1*) fData->Get("fitXS5");
  
  TH1F *th1_dum_3gev = (TH1F*) fData->Get("dumXS2");
  TH1F *th1_dum_9gev = (TH1F*) fData->Get("dumXS5");

  TGraphErrors *tg_int_2760_3gev = (TGraphErrors*) fData->Get("gXS2_2");
  TGraphErrors *tg_int_2760_9gev = (TGraphErrors*) fData->Get("gXS2_5");

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
  pp1->SetLogx(), pp1->SetLogy();

  char xTitle[100],yTitle[100];

  sprintf(yTitle,"Ed^{3}#sigma/dp^{3} [mb GeV^{-2}c^{3}]");
  sprintf(xTitle,"#sqrt{s} [TeV]");

  gStyle->SetOptFit(0);

  dum1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1->GetXaxis()->SetNdivisions(908);
  dum1->GetYaxis()->SetNdivisions(507);
  setUpperPad(dum1);
  dum1->Draw("");

  float msize = 1.3;
  //tf1_fit_3gev->SetLineStyle(9);
  //tf1_fit_3gev->SetLineWidth(2.0);
  tf1_fit_3gev->Draw("same");
  th1Style1(tg_data_630_3gev,18,27,msize,18,1.5,1,1);
  th1Style1(tg_data_900_3gev,2,20,msize,2,1.5,1,1);
  th1Style1(tg_data_1800_3gev,17,28,msize,17,1.5,1,1);
  th1Style1(tg_data_1960_3gev,19,30,msize,19,1.5,1,1);
  th1Style1(tg_data_2360_3gev,24,20,msize,24,1.5,1,1);    
  th1Style1(tg_data_7000_3gev,1,20,msize,1,1.5,1,1);
  th1Style1(tg_int_2760_3gev,4,25,msize,4,1.5,1,1);


  //putCMSPrel();
  putA();
  pt1->Draw();

  //putIntLum();
  //putB();

  //putIntLum2();
  //if(!onlyCMS) putA();
  //else putB();

  //TLegend *leg1 = new TLegend(0.19,0.50,0.52,0.76);
  TLegend *leg1 = new TLegend(0.19,0.75,0.52,0.95);
  //leg1->SetNColumns(2);
  //leg1->SetColumnSeparation(0.04);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextSize(0.040);
  //leg1->SetHeader("   #sqrt{s} = 2.76");
  leg1->AddEntry(tg_int_2760_3gev,"Linear interp.","p"); 
  leg1->AddEntry(tg_xt_9GeV,"x_{T} scaling interp.","p");
  //leg1->Draw("");

  //TLegend *leg2 = new TLegend(0.19,0.62,0.68,0.98);
  TLegend *leg2 = new TLegend(0.24,0.50,0.73,0.86);
  leg2->SetNColumns(2);
  leg2->SetColumnSeparation(0.04);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextSize(0.041);
  leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)");
  leg2->AddEntry(tg_data_7000_3gev,"CMS 7 TeV","p");
  leg2->AddEntry(tg_data_2360_3gev,"CMS 2.36 TeV","p");
  leg2->AddEntry(tg_data_900_3gev,"CMS 0.9 TeV","p");
  leg2->AddEntry(tg_data_1960_3gev,"CDF 1.96 TeV","p");
  leg2->AddEntry(tg_data_1800_3gev,"CDF 1.8 TeV","p");
  leg2->AddEntry(tg_data_630_3gev,"CDF 0.63 TeV","p");
  leg2->Draw(""); 



  // ----- pad 2         
  pp1_1->cd();
  pp1_1->SetLogx(), pp1_1->SetLogy();


  sprintf(yTitle,"Ed^{3}#sigma/dp^{3} [mb GeV^{-2}c^{3}] x 10^{3}");

  //ymin_r = 3E-6, ymax_r = 8E-4;
  ymin_r = 3E-6, ymax_r = 3E-4;

  dum1_1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1_1->GetXaxis()->SetNdivisions(908);
  dum1_1->GetYaxis()->SetNdivisions(505);
  dum1_1->GetYaxis()->SetDecimals(1);
  setUpperPad(dum1_1);
  dum1_1->Draw(""); 


  tf1_fit_9gev->Draw("same");
  th1Style1(tg_data_900_9gev,2,20,msize,2,1.5,1,1);
  th1Style1(tg_data_1960_9gev,19,30,msize,19,1.5,1,1);
  th1Style1(tg_data_7000_9gev,1,20,msize,1,1.5,1,1);
  th1Style1(tg_int_2760_9gev,4,25,msize,4,1.5,1,1);
  th1Style1(tg_xt_9GeV,4,24,msize,4,1.5,1,1);

  pt2->Draw();

  /*
  TLegend *leg2 = new TLegend(0.19,0.62,0.68,0.98);
  leg2->SetNColumns(2);
  leg2->SetColumnSeparation(0.04);
  leg2->SetBorderSize(0);
  leg2->SetFillStyle(0);
  leg2->SetTextSize(0.038);
  leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)");
  leg2->AddEntry(tg_data_630_3gev,"#sqrt{s} = 0.63 (CDF)","pl");
  leg2->AddEntry(tg_data_900_3gev,"#sqrt{s} = 0.9 (CMS)","pl");
  leg2->AddEntry(tg_data_1800_3gev,"#sqrt{s} = 1.8 (CDF)","pl");
  leg2->AddEntry(tg_data_1960_3gev,"#sqrt{s} = 1.96 (CDF)","pl");
  leg2->AddEntry(tg_data_2360_3gev,"#sqrt{s} = 2.36 (CMS)","pl");
  //leg2->AddEntry(tg_int_2760_3gev,"#sqrt{s} = 2.76 (Linear interp.)","pl");
  leg2->AddEntry(tg_data_7000_3gev,"#sqrt{s} = 7.0 (CMS)","pl");
  //leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.63, 1.8, 1.96 (CDF)","pl");
  //leg2->AddEntry(tg_data_3gev,"#sqrt{s} = 0.9, 7.0 (CMS)","pl");
  //leg2->AddEntry(tg_xt_9GeV,"#sqrt{s} = 2.76 (x_{T} scaling interp.)","pl");
  //leg2->AddEntry(tf1_fit_3gev,"2^{nd} order polynomial","l");
  //leg2->Draw("");
  */

  leg1->Draw("");


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

