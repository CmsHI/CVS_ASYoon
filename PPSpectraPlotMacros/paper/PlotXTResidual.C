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

void PlotXTResidual(bool save=false){

  // only CMS
  bool onlyCMS = false;

  // range
  float xt_min, xt_max;
  float ymin, ymax;
  float ymin_r, ymax_r;

  xt_min = 0.0003, xt_max = 0.07;
  ymin = 3e3, ymax = 2e23;    
  //ymin_r = 0.15, ymax_r = 2.5;
  ymin_r = 0.15, ymax_r = 3.5;      

  //TFile *fData = new TFile("../rootOutput_postApp_3rd/feb212011/output_xtscaling.root");
  //TFile *fNLO = new TFile("../rootOutput_postApp_3rd/feb212011/output_nlo.root");

  //TFile *fData = new TFile("../rootOutput_postApp_3rd/feb222011/output_xtscaling.root");
  TFile *fNLO = new TFile("../rootOutput_postApp_3rd/feb222011/output_nlo.root");

  TFile *fData = new TFile("../rootOutput_postApp_3rd/feb282011/output_xtscaling.root");

  

  TGraphErrors *tg_rat_cdf_1960 = (TGraphErrors*) fData->Get("ratio_cdf_1960_g");
  TGraphErrors *tg_rat_cms_900 = (TGraphErrors*) fData->Get("ratio_cms_900_g");
  TGraphErrors *tg_rat_cms_7000 = (TGraphErrors*) fData->Get("ratio_cms_7000_g");

  TF1 *tf_intep = (TF1*) fData->Get("merge_ratio_fit");
  TF1 *tf_inter_up = (TF1*) fData->Get("merge_ratio_fit_up");
  TF1 *tf_inter_dn = (TF1*) fData->Get("merge_ratio_fit_dn");

  TH1F *h1f_scaled900 = (TH1F*) fData->Get("scaled900");
  TH1F *h1f_scaled1960 =(TH1F*) fData->Get("scaled1960");
  TH1F *h1f_scaled7000 =(TH1F*) fData->Get("scaled7000");

  TPolyLine *tp_error_band = (TPolyLine*) fData->Get("TPolyLine");

  /*
  TGraph *tg_rat_nlo_900 =  (TGraph*) fNLO->Get("ratio_900_g");
  TGraph *tg_rat_nlo_1960 =  (TGraph*) fNLO->Get("ratio_1960_g");
  TGraph *tg_rat_nlo_2750 =  (TGraph*) fNLO->Get("ratio_2750_g");
  TGraph *tg_rat_nlo_7000 =  (TGraph*) fNLO->Get("ratio_7000_g");
  */

  TGraph *tg_rat_nlo_900 =  (TGraph*) fNLO->Get("scale900");
  TGraph *tg_rat_nlo_1960 =  (TGraph*) fNLO->Get("scale1960");
  TGraph *tg_rat_nlo_2750 =  (TGraph*) fNLO->Get("scale2750");
  TGraph *tg_rat_nlo_7000 =  (TGraph*) fNLO->Get("scale7000");



  // canvas setting
  TCanvas *call1 = new TCanvas("call1","call1",510,670);
  call1->SetLogx(), call1->SetLogy();

  setPad(call1);

  // ----- pad 1               
  pp1->cd();
  //pp1->SetLogy();
  //pp1->SetLogx();
  

  char xTitle[100],yTitle[100];

  //sprintf(yTitle,"Data / Fit");
  sprintf(yTitle,"(#sqrt{s}/GeV)^{4.9}Ed^{3}#sigma/dp^{3} / Fit");  
  sprintf(xTitle,"x_{T}");

  gStyle->SetOptFit(0);



  dum1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1->GetXaxis()->SetNdivisions(908);
  dum1->GetYaxis()->SetNdivisions(507);
  setUpperPad(dum1);
  dum1->Draw("");

  int fillsty = 3001;
  tp_error_band->SetLineColor(kWhite);
  //tp_error_band->SetLineWidth(2.5);
  tp_error_band->SetFillStyle(fillsty), tp_error_band->SetFillColor(kGray+1);
  tp_error_band->Draw("f");

  float msize =0.9;

  th1Style1(tg_rat_cdf_1960,19,30,msize,19,1.5,1,1);
  th1Style1(tg_rat_cms_900,2,20,msize,2,1.5,1,1);
  th1Style1(tg_rat_cms_7000,1,20,msize,1,1.5,1,1);

  //tf_intep->Draw("same");
  h1f_scaled900->SetLineColor(kBlue), h1f_scaled900->Draw("xlsame");
  h1f_scaled1960->SetLineColor(kBlue), h1f_scaled1960->Draw("xlsame");
  h1f_scaled7000->SetLineColor(kBlue), h1f_scaled7000->Draw("xlsame");
  //kOrange-5
  //h1f_scaled900->SetLineColor(kOrange-5), h1f_scaled900->Draw("xlsame");
  //h1f_scaled1960->SetLineColor(kOrange-5), h1f_scaled1960->Draw("xlsame");
  //h1f_scaled7000->SetLineColor(kOrange-5), h1f_scaled7000->Draw("xlsame");


  

  //TGaxis *A1 = new TGaxis(0.0003,2.0,0.07,2.0,1380*0.0003,1380*0.07,410,"-");
  //TGaxis *A1 = new TGaxis(0.0003,2.108,0.07,2.108,1380*0.0003,1380*0.07,410,"-");
  TGaxis *A1 = new TGaxis(0.0003,ymax_r,0.07,ymax_r,1380*0.0003,1380*0.07,410,"-"); 

  A1->SetTitle("p_{T} (GeV/c) for #sqrt{s}=2.76 TeV");
  A1->SetLabelSize(14);
  A1->SetLabelFont(43);
  A1->SetLabelOffset(0.002);
  A1->SetTitleSize(14);
  A1->SetTitleFont(43);
  A1->SetTitleOffset(2.0);
  A1->SetNdivisions(410);
  A1->Draw();
  gPad->SetTickx(0);


  //putCMSPrel();
  //putIntLum();
  putB();

  //putIntLum2();
  //if(!onlyCMS) putA();
  //else putB();


  //TLegend *leg1 = new TLegend(0.19,0.47,0.59,0.79);
  //TLegend *leg1 = new TLegend(0.22,0.47,0.61,0.7);
  TLegend *leg1 = new TLegend(0.27,0.59,0.66,0.88); 
  //leg1->SetNColumns(3);
  leg1->SetColumnSeparation(0.04);
  leg1->SetBorderSize(0);
  leg1->SetFillStyle(0);
  leg1->SetTextSize(0.031);
  //leg1->SetHeader("     Data");
  leg1->AddEntry(tg_rat_cms_7000,"CMS 7 TeV (2.96 pb^{-1})","p");
  leg1->AddEntry(tg_rat_cms_900,"CMS 0.9 TeV (231 #mub^{-1})","p");
  leg1->AddEntry(tg_rat_cdf_1960,"CDF 1.96 TeV","p");
  leg1->AddEntry(tp_error_band,"2.76 TeV x_{T} interpolation","f");
  leg1->Draw();
  

  // ----- pad 2         
  pp1_1->cd();

  //sprintf(yTitle,"NLO / NLO at  #sqrt{s} = 2.76 TeV");
  //sprintf(yTitle,"NLO ratio to  #sqrt{s} = 2.75 TeV");
  //sprintf(yTitle,"(#sqrt{s}/GeV)^{4.9}Ed^{3}#sigma/dp^{3} ratio to 2.76 TeV");
  //sprintf(yTitle,"NLO ratio to #sqrt{s} = 2.75 TeV");
  sprintf(yTitle,"NLO ratio");
  sprintf(xTitle,"x_{T}");

  //ymin_r = 0.85, ymax_r = 1.75;
  ymin_r = 0.94, ymax_r = 1.45;

  dum1_1 = GetDummyHist(xt_min,xt_max,ymin_r,ymax_r,xTitle,yTitle,false);
  dum1_1->GetXaxis()->SetNdivisions(908);
  dum1_1->GetYaxis()->SetNdivisions(407);
  //setUpperPad(dum1_1);
  setLowerPad(dum1_1);  
  dum1_1->Draw(""); 

  //tg_rat_nlo_7000->GetXaxis()->SetRangeUser(0.05,0.07);
  //tg_rat_nlo_7000->GetXaxis()->SetLimits(0, 0.1);
  //TGraph *tg_rat_nlo_7000_re = recasted(tg_rat_nlo_7000);

  tg_rat_nlo_900->RemovePoint(0);
  tg_rat_nlo_1960->RemovePoint(0);
  tg_rat_nlo_7000->RemovePoint(0);
  //for(int i=1;i<50;i++) 
  //tg_rat_nlo_7000->RemovePoint(i);
  tg_rat_nlo_2750->RemovePoint(0);

  th1Style1(tg_rat_nlo_900,2,20,msize,2,2.5,1,2);
  th1Style1(tg_rat_nlo_7000,1,20,msize,1,2.5,1,2);   
  //th1Style1(tg_rat_nlo_7000_re,1,20,msize,1,2.5,1,2);
  //th1Style1(tg_rat_nlo_2750,4,20,msize,4,2.5,2,2);
  th1Style1(tg_rat_nlo_1960,19,20,msize,19,2.5,1,2);


  //TLegend *leg2 = new TLegend(0.22,0.62,0.62,0.96);  
  TLegend *leg2 = new TLegend(0.22,0.733,0.75,0.98);    
  leg2->SetNColumns(3);
  leg2->SetColumnSeparation(0.00);
  leg2->SetBorderSize(0); 
  leg2->SetFillStyle(0); 
  leg2->SetTextSize(0.05); 
  leg2->SetMargin(0.25);
  //leg2->SetHeader("   pp(#bar{p}) #rightarrow 0.5(h^{+}+h^{-}) + X (|#eta|<1.0)"); 
  //leg2->SetHeader("#sqrt{s}/GeV)^{4.9}Ed^{3}#sigma/dp^{3}  #sqrt{s} = 0.9, 1.96, 2.75, 7  /  #sqrt{s} = 2.75 ");
  leg2->SetHeader("   #sqrt{s} = 0.9, 1.96, 2.75, 7  /  #sqrt{s} = 2.75 "); 
  leg2->AddEntry(tg_rat_nlo_900,"#sqrt{s} = 0.9 TeV","l"); 
  leg2->AddEntry(tg_rat_nlo_1960,"#sqrt{s} = 1.96 TeV","l");
  //leg2->AddEntry(tg_rat_nlo_2750,"#sqrt{s} = 2.75 TeV","l");
  leg2->AddEntry(tg_rat_nlo_7000,"#sqrt{s} = 7 TeV","l");
  //leg2->AddEntry(tp_error_band,"#sqrt{s} = 2.76 TeV (x_{T} interpolation)","lf");
  leg2->Draw();
  

  if(save){
    printCanvases(call1, "xT_ratio_data_nlo_v1",1);
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

  pp1 = new TPad("p1","p1",0,0.34,1,1,0,0,0);
  pp1->SetBottomMargin(0.0);
  pp1->SetTopMargin(0.07*(1/0.72));

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

  /*
  can->cd();

  //pp1 = new TPad("p1","p1",0,0.34,1,1,0,0,0);
  //pp1 = new TPad("p1","p1",0,0.53,1,1,0,0,0);  
  pp1 = new TPad("p1","p1",0,0.33,1,1,0,0,0);
  pp1->SetBottomMargin(0.0);
  //pp1->SetTopMargin(0.05*(1/0.72));
  pp1->SetTopMargin(0.09*(1/0.72));       

  pp1->Draw();
  pp1->cd();
  pp1->SetNumber(1);

  can->cd();

  //pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.34,0,0,0);
  //pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.53,0,0,0);
  pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.33,0,0,0);  
  pp1_1->SetTopMargin(0);
  //pp1_1->SetBottomMargin(0.14*(1/0.34));
  pp1_1->SetBottomMargin(0.14*(1/0.55)); 
  pp1_1->Draw();
  pp1_1->cd();
  pp1_1->SetNumber(2);
  */
}

/*
void setLowerPad(TH1D *dum_low){

  dum_low->GetYaxis()->SetLabelSize(0.07);
  dum_low->GetYaxis()->SetTitleSize(0.08);
  dum_low->GetYaxis()->SetTitleOffset(1.0);

  dum_low->GetXaxis()->SetLabelSize(0.09);
  dum_low->GetXaxis()->SetLabelOffset(0.05);
  dum_low->GetXaxis()->SetTitleSize(0.11);
  dum_low->GetXaxis()->SetTitleOffset(1.47);

  dum_low->GetYaxis()->SetNdivisions(409);
  dum_low->GetYaxis()-> SetDecimals(true);
  dum_low->Draw();

}
*/
/*
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
*/

void setLowerPad(TH1D *dum_low){

  //Just to make lower pannel lable appearing as similar size as upper one                                                                             
  dum_low->GetYaxis()->SetLabelSize(0.065);
  dum_low->GetYaxis()->SetTitleSize(0.076);
  dum_low->GetYaxis()->SetTitleOffset(1.05);

  dum_low->GetXaxis()->SetLabelSize(0.09);
  dum_low->GetXaxis()->SetLabelOffset(0.05);
  dum_low->GetXaxis()->SetTitleSize(0.11);
  dum_low->GetXaxis()->SetTitleOffset(1.47);

  //dum_low->GetYaxis()->SetNdivisions(405);                                                                                                           
  dum_low->GetYaxis()->SetNdivisions(409);
  dum_low->GetYaxis()-> SetDecimals(true);
  dum_low->Draw();

}


void setUpperPad(TH1D *dum_up){

  dum_up->GetXaxis()->SetLabelSize(17);
  dum_up->GetXaxis()->SetLabelFont(43);
  dum_up->GetXaxis()->SetLabelOffset(0.04);
  dum_up->GetXaxis()->SetTitleSize(21);
  dum_up->GetXaxis()->SetTitleFont(43);
  dum_up->GetXaxis()->SetTitleOffset(2.0);
  dum_up->GetXaxis()->CenterTitle();

  dum_up->GetYaxis()->SetLabelSize(15);
  dum_up->GetYaxis()->SetLabelFont(43);
  //dum_up->GetYaxis()->SetTitleSize(16);
  dum_up->GetYaxis()->SetTitleSize(18);
  dum_up->GetYaxis()->SetTitleFont(43);
  //dum_up->GetYaxis()->SetTitleOffset(3.2);
  dum_up->GetYaxis()->SetTitleOffset(2.8);      
  dum_up->GetYaxis()->CenterTitle();
  
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
  //texB = new TLatex(0.20,0.80,"(b)");
  //texB->SetTextSize(0.055);
  texB = new TLatex(0.2,0.81,"(b)");
  texB->SetTextSize(0.04);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();
}


void putCMSPrel(){
  //tex = new TLatex(0.7,0.80,"CMS Preliminary");
  //tex->SetTextSize(0.05);
  tex = new TLatex(0.66,0.81,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}



void putIntLum(){
  //tex2 = new TLatex(0.66,0.83,"#intLdt = 10.2 nb^{-1} for 7 TeV");
  //tex2->SetTextSize(0.032);
  tex2 = new TLatex(0.48,0.75,"#intLdt = 231 #mub^{-1} (2.96 pb^{-1}) for 0.9 (7) TeV");  
  tex2->SetTextSize(0.031); 
  //tex2->SetTextSize(0.0374); 
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();
}

void putIntLum2(){
  tex3 = new TLatex(0.64,0.73,"#intLdt = 240 #mub^{-1} for 0.9 TeV");
  //tex3->SetTextSize(0.032);
  tex3->SetTextSize(0.025);
  tex3->SetLineWidth(2);
  tex3->SetNDC();
  tex3->Draw();
}

