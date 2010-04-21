#include "common.h"

void dNdeta_vs_roots() {
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");


  bool ErrorFlag = true;
  bool theory = true;
  bool pythia = true;
//  theory = false;

  //****************************************************
  Bool_t bw = 1;       // 1: BLACK AND WHITE, 0: COLOR
  Float_t msize = 1.8; // MARKER SIZE
  //****************************************************
  
  TCanvas *c = new TCanvas("c","c",550,600);

  //  gStyle->SetTitleYSize(.060);
  gStyle->SetTitleYOffset(1.4);

  c->SetLogx();
  //  c->SetLeftMargin(0.15);

  TH1F *dummy = new TH1F("dummy","dummy",100,9,15000);
  dummy->SetMaximum(7.5);
  dummy->SetMinimum(0);
  dummy->SetXTitle("#sqrt{s} [GeV]");
  dummy->SetYTitle("dN_{ch}/d#eta#cbar_{ #eta#approx0}");
  /*
  dummy->GetYaxis()->SetNdivisions(505);
  dummy->GetXaxis()->SetNdivisions(505);
  dummy->GetXaxis()->SetLabelSize(0.05);
  dummy->GetYaxis()->SetLabelSize(0.05);
  dummy->GetXaxis()->SetTitleSize(0.05);
  dummy->GetYaxis()->SetTitleSize(0.05);
  dummy->GetXaxis()->SetLabelOffset(0.00);
  dummy->GetXaxis()->SetTitleOffset(1.0);
  dummy->GetYaxis()->SetTitleOffset(0.75);
  */
  dummy->GetYaxis()->CenterTitle();
  dummy->GetXaxis()->CenterTitle();
  dummy->Draw();


  // ---- fits ----
  TF1 *fitISR = new TF1("fitISR","0.161+0.201*2*log(x)",12,80);
  fitISR->SetLineColor(kBlack);
  fitISR->SetLineWidth(2);
  fitISR->SetLineStyle(3);
  fitISR->Draw("same");


  //TF1 *fitUA5 = new TF1("fitUA5","2.420-0.244*log(x^2)+0.0236*(log(x^2))^2",40,8000);
  //TF1 *fitUA5 = new TF1("fitUA5","3.183-0.384*log(x^2)+0.0297*(log(x^2))^2",40,8000);     
  TF1 *fitUA5 = new TF1("fitUA5","3.167-0.381*log(x^2)+0.0296*(log(x^2))^2",40,8000);   
  fitUA5->SetLineColor(kBlue);
  if(bw)fitUA5->SetLineColor(kBlack);
  fitUA5->SetLineWidth(2);
  fitUA5->SetLineStyle(2);
  fitUA5->Draw("same");

  // fit to UA5 and CMS inelastic points 
  TF1 *fitUA5inel = new TF1("fitUA5inel","1.54-2*0.096*log(x)+0.0155*4*log(x)*log(x)",40,8000);
  fitUA5inel->SetLineColor(kGreen);
  if(bw)fitUA5inel->SetLineColor(kBlack);
  fitUA5inel->SetLineWidth(2);
  fitUA5inel->SetLineStyle(26);
  fitUA5inel->Draw("same");

  // ---- PYTHIA D6T ----
  //  900 GeV NSD: 2.808
  // 2360 GeV NSD: 3.328
  // 7000 GeV NSD:�4.09

  TF1 *pythia1 = new TF1("pythia1","2.808+(log(x)-log(900))/(log(2360)-log(900))*(3.328-2.808)",900,2360);
  pythia1->SetLineColor(kBlue+2);
  pythia1->SetLineWidth(3);
  pythia1->SetLineStyle(1);
  if(pythia) pythia1->Draw("same");

  TF1 *pythia2 = new TF1("pythia2","3.328+(log(x)-log(2360))/(log(7000)-log(2360))*(4.09-3.328)",2360,7000);
  pythia2->SetLineColor(kBlue+2);
  pythia2->SetLineWidth(3);
  pythia2->SetLineStyle(1);
  if(pythia) pythia2->Draw("same");

  // ---- PHOJET ----
  //  900 GeV NSD:  3.474
  // 2360 GeV NSD:  3.979
  // 7000 GeV NSD:  4.57

  TF1 *phojet1 = new TF1("phojet1","3.474+(log(x)-log(900))/(log(2360)-log(900))*(3.979-3.474)",900,2360);
  TF1 *phojet2 = new TF1("phojet2","3.979+(log(x)-log(2360))/(log(7000)-log(2360))*(4.57-3.979)",2360,7000);
  phojet1->SetLineColor(kGreen);
  phojet2->SetLineColor(kGreen);
  phojet1->SetLineWidth(2);
  phojet2->SetLineWidth(2);
  phojet1->SetLineStyle(2);
  phojet2->SetLineStyle(2);
//  if(theory) phojet1->Draw("same");
//  if(theory) phojet2->Draw("same");

  // ---- PYTHIA ATLAS ----
  //  900 GeV NSD:  3.25
  // 2360 GeV NSD:  4.20
  // 7000 GeV NSD:  5.62

  TF1 *atlas1 = new TF1("atlas1","3.25+(log(x) -log(900))/(log(2360)- log(900))*(4.20-3.25)",900,2360);
  TF1 *atlas2 = new TF1("atlas2","4.20+(log(x)-log(2360))/(log(7000)-log(2360))*(5.62-4.20)",2360,7000);
  atlas1->SetLineColor(kGreen+2);
  atlas2->SetLineColor(kGreen+2);
  atlas1->SetLineWidth(3);
  atlas2->SetLineWidth(3);
  if(pythia) atlas1->Draw("same");
  if(pythia) atlas2->Draw("same");

  // ---- G. Levin ----

   Double_t x[8]  = {200, 546, 900,1800,2360,7000,10000,14000};
   Double_t y[8]  = {2.405081,3.125669,3.462567,4.042781,4.248663,4.931818,5.203209,5.493316};
   Double_t ex[8] = {0,0,0,0,0,0,0,0};
   Double_t ey[8] = {0,0,0,0,0,0,0,0};
   gr = new TGraphErrors(8,x,y,ex,ey);
   gr->SetLineColor(kRed);
   gr->SetLineWidth(2);
   gr->SetLineStyle(9);
   if(theory) gr->Draw("L");

// ---- ISR ---

  Double_t x1[4] =  { 23.6,  30.8,  45.2,  62.8 }; 
  Double_t y1[4] =  {  1.382, 1.570, 1.655, 1.878 };
  Double_t exl1[4]= { 0, 0, 0, 0 };
  Double_t exh1[4]= { 0, 0, 0, 0 };
  Double_t eyl1[4]= { 0.056, 0.066, 0.072, 0.105 };
  Double_t eyh1[4]= { 0.056, 0.066, 0.072, 0.105 };

  TGraphAsymmErrors *isr=new TGraphAsymmErrors(4,x1,y1,exl1,exh1,eyl1,eyh1);
  isr->SetMarkerColor(kBlack);
  isr->SetMarkerStyle(24);
  if(bw)isr->SetMarkerStyle(28);
  //if(bw)isr->SetMarkerStyle(22);  
  isr->SetMarkerSize(msize);
  isr->SetLineColor(kBlack);
  isr->Draw("PE");

  /*
//  TF1 *fitISR = new TF1("fitISR","0.01+0.44*log(x)",12,80);
  TF1 *fitISR = new TF1("fitISR","0.161+0.201*2*log(x)",12,80);
  fitISR->SetLineColor(kBlack);
  fitISR->SetLineWidth(2);
  fitISR->SetLineStyle(1);    
  fitISR->Draw("same");
  */

// ---- UA5 NSD ---
  Double_t x2[4] =    {    53,   200,   546,   900 }; // checked value on paper
  Double_t y2[4] =  {  1.93,  2.48,  3.05,  3.48 };
  Double_t exl2[4]= { 0, 0, 0, 0 };
  Double_t exh2[4]= { 0, 0, 0, 0 };
//  Double_t eyl2[4]= { 0.135, 0.106, 0.0948, 0.139 }; // statistical + systematic
//  Double_t eyh2[4]= { 0.135, 0.106, 0.0948, 0.139 };
  Double_t eyl2[4]= { 0.10, 0.08, 0.09, 0.12 }; //  systematic
  Double_t eyh2[4]= { 0.10, 0.08, 0.09, 0.12 };
  if ( ErrorFlag == false)
    {
      eyl2[0]= 0;
      eyh2[0]= 0;
      eyl2[1]= 0;
      eyh2[1]= 0;
      eyl2[2]= 0;
      eyh2[2]= 0;
      eyl2[3]= 0;
      eyh2[3]= 0;

    }


  TGraphAsymmErrors *ua5nsd=new TGraphAsymmErrors(4,x2,y2,exl2,exh2,eyl2,eyh2);
  ua5nsd->SetMarkerColor(kBlue);
  if(bw)ua5nsd->SetMarkerColor(kBlack);
  ua5nsd->SetMarkerStyle(20);
  //if(bw)ua5nsd->SetMarkerStyle(25);
  //if(bw)ua5nsd->SetMarkerStyle(23);
  if(bw)ua5nsd->SetMarkerStyle(22);
  ua5nsd->SetMarkerSize(msize);
  ua5nsd->SetLineColor(kBlue);
  if(bw)ua5nsd->SetLineColor(kBlack);
  //ua5nsd->Draw("PE");
  //  ua5nsd->Draw("PZ");  

  /*  
//  TF1 *fitUA5 = new TF1("fitUA5","2.5-0.5*log(x)+0.023*4*log(x)*log(x)",40,8000);
//  TF1 *fitUA5 = new TF1("fitUA5","2.26-2*0.207*log(x)+0.0215*4*log(x)*log(x)",40,8000);
  // fit with CMS 900, 2360 GeV Points
  TF1 *fitUA5 = new TF1("fitUA5","2.420-0.244*log(x^2)+0.0236*(log(x^2))^2",40,8000);
//  TF1 *fitUA5 = new TF1("funcTh","0.929+0.0644*exp(sqrt(log(x^2)))",18,100000);
  fitUA5->SetLineColor(kBlue);
  if(bw)fitUA5->SetLineColor(kBlack);
  fitUA5->SetLineWidth(2);
  fitUA5->SetLineStyle(2);    
  fitUA5->Draw("same");

  // fit to UA5 and CMS inelastic points
  TF1 *fitUA5inel = new TF1("fitUA5inel","1.54-2*0.096*log(x)+0.0155*4*log(x)*log(x)",40,8000);
  fitUA5inel->SetLineColor(kGreen);
  if(bw)fitUA5inel->SetLineColor(kBlack);
  fitUA5inel->SetLineWidth(2);
  fitUA5inel->SetLineStyle(26);    
  fitUA5inel->Draw("same");
  */

// ---- UA5 INEL ---
  Double_t x3[4] =  {    53,  200,     546,  900 };  // checked from paper
  Double_t y3[4] =  {  1.76, 2.29,    2.79, 3.14 };
  Double_t exl3[4]= { 0, 0, 0, 0 };
  Double_t exh3[4]= { 0, 0, 0, 0 };
  Double_t eyl3[4]= { 0.09, 0.07, 0.08, 0.09 };
  Double_t eyh3[4]= { 0.09, 0.07, 0.08, 0.09 };
  if ( ErrorFlag == false)
    {
      eyl3[0]= 0;
      eyh3[0]= 0;
      eyl3[1]= 0;
      eyh3[1]= 0;
      eyl3[2]= 0;
      eyh3[2]= 0;
      eyl3[3]= 0;
      eyh3[3]= 0;
    }

  TGraphAsymmErrors *ua5inel=new TGraphAsymmErrors(4,x3,y3,exl3,exh3,eyl3,eyh3);
  ua5inel->SetMarkerColor(kBlack);
  ua5inel->SetMarkerStyle(26);
  ua5inel->SetMarkerSize(msize);
  ua5inel->SetLineColor(kBlack);
  //ua5inel->Draw("PE");
  ua5inel->Draw("PZ");

// ---- FNAL INEL ---
  Double_t x4[2] =  { 13.76,  19.42 };  // approx values
  Double_t y4[2] =  {  1.210, 1.414 };
  Double_t exl4[2]= { 0, 0, };
  Double_t exh4[2]= { 0, 0, };
//  Double_t eyl4[2]= { 0.050, 0.065 };
//  Double_t eyh4[2]= { 0.050, 0.065 };
  Double_t eyl4[2]= { 0.000, 0.00 }; // error bar smaller than circle, drop it
  Double_t eyh4[2]= { 0.000, 0.00 };
  if ( ErrorFlag == false)
    {
      eyl4[0]= 0;
      eyh4[0]= 0;
      eyl4[1]= 0;
      eyh4[1]= 0;
         }
  TGraphAsymmErrors *fnalinel=new TGraphAsymmErrors(2,x4,y4,exl4,exh4,eyl4,eyh4);
  fnalinel->SetMarkerColor(kBlack);
  //fnalinel->SetMarkerStyle(22);
  fnalinel->SetMarkerStyle(4);
  fnalinel->SetMarkerSize(msize);
  fnalinel->SetLineColor(kBlack);
  //fnalinel->Draw("PE");
  fnalinel->Draw("PZ");

// ---- CDF NSD ---
  Double_t x5[2] =  { 630,  1800 };  
  Double_t y5[2] =  {  3.18, 3.95 };
  Double_t exl5[2]= { 0, 0, };
  Double_t exh5[2]= { 0, 0, };
  Double_t eyl5[2]= { 0.10, 0.13 };
  Double_t eyh5[2]= { 0.10, 0.13 };
  if ( ErrorFlag == false)
    {
      eyl5[0]= 0;
      eyh5[0]= 0;
      eyl5[1]= 0;
      eyh5[1]= 0;
    }


  TGraphAsymmErrors *cdf=new TGraphAsymmErrors(2,x5,y5,exl5,exh5,eyl5,eyh5);
  cdf->SetMarkerColor(kBlue);
  if(bw)cdf->SetMarkerColor(kBlack);
  cdf->SetMarkerStyle(21);
  if(bw)cdf->SetMarkerStyle(21);
  cdf->SetMarkerSize(msize);
  cdf->SetLineColor(kBlue);
  if(bw)cdf->SetLineColor(kBlack);
  //cdf->Draw("PE");
  cdf->Draw("PZ"); 

  TGraph* cdf04 = cdf->Clone("cdf04");
  cdf04->SetMarkerStyle(0);
  cdf04->Draw("PZsame");



  // ---- UA1 NSD ---                                                              
  Double_t xua1[7] =  { 200,  260, 380, 500, 620, 790, 900 };
  Double_t yua1[7] =  {  2.65, 2.71, 2.94, 3.05, 3.15, 3.41, 3.48 };
  Double_t exlua1[7]= {0,0,0,0,0,0,0  };
//  Double_t eylua1[7]= {0.08.0.08,0.09,0.09,0.09,0.10,0.10 };
  Double_t eylua1[7]= {0.29.0.30,0.32,0.34,0.35,0.38,0.38 };

  TGraphAsymmErrors *ua1nsd=new TGraphAsymmErrors(7,xua1,yua1,exlua1,exlua1,eylua1,eylua1);
  ua1nsd->SetName("ua1nsd");
  ua1nsd->SetMarkerColor(1);
  ua1nsd->SetMarkerStyle(3);
  ua1nsd->SetMarkerSize(msize);
  ua1nsd->SetLineColor(1);
  ua1nsd->Draw("PZsame");

  // ---- ALICE NSD ------
  Double_t x10[2] =  {  900};
  Double_t y10[2] =  {  3.51};
  /*
  Double_t exl10[2]= {  0.25};
  Double_t exh10[2]= { 0.25};
  Double_t eyl10[2]= { 0.25};
  Double_t eyh10[2]= { 0.25};
  */
  Double_t exl10[2]= {  0};
  Double_t exh10[2]= { 0};
  Double_t eyl10[2]= { 0.25};
  Double_t eyh10[2]= { 0.25};

  TGraphAsymmErrors *alicensd=new TGraphAsymmErrors(2,x10,y10,exl10,exh10,eyl10,eyh10);
  alicensd->SetMarkerColor(kBlack);
  alicensd->SetMarkerStyle(29);
  alicensd->SetMarkerSize(msize*1.5);
  alicensd->SetLineColor(kBlack);
  alicensd->Draw("PZsame");

// ---- CMS NSD ---
  const int NCMS=3;
  Double_t x11[NCMS] =  { 900, 2360, 7000 }; 
  //Double_t y11[NCMS] =  {  3.4984, 4.46, 5.84 };
  Double_t y11[NCMS] =  {  3.4984, 4.46, 5.82 }; 
  Double_t cmsSysErr = (y11[0]+y11[1])/2. *0.037;

  // for now we don't show sys error for everyone
  Bool_t errorX = false;
  if(errorX){
     //Arbitary error
     Double_t exl11[NCMS]= { 200.,0 ,0};
     Double_t exh11[NCMS]= { 1000.,0 ,0};
  }else{
     Double_t exl11[NCMS]= { 0.,0 ,0};
     Double_t exh11[NCMS]= { 0.,0 ,0};
  }  

  Double_t eyld11[NCMS]= { 500,50,50 };
  Double_t eyhd11[NCMS]= { 500,50,50 };
  Double_t exld11[NCMS]= { 0.00,0.00,0 };
  Double_t exhd11[NCMS]= { 0.00,0.00,0 };


  Double_t eyl11[NCMS]= { 0.037*y11[0] , 0.037*y11[1] , 1.*0.04*y11[2]};
  Double_t eyh11[NCMS]= { 0.037*y11[0] , 0.037*y11[1] , 1.*0.04*y11[2]};
  
  TGraphAsymmErrors *cmsnsd=new TGraphAsymmErrors(NCMS,x11,y11,exl11,exh11,eyl11,eyh11);
  //TGraphBentErrors *cmsnsd = new TGraphBentErrors(NCMS,x11,y11,exl11,exh11,eyl11,eyh11,exld11,exhd11,eyld11,eyhd11); 

  cmsnsd->SetMarkerColor(kRed);
  //if(bw)cmsnsd->SetMarkerColor(kBlack);
  if(bw)cmsnsd->SetMarkerColor(kRed+2);
  cmsnsd->SetMarkerStyle(kFullStar);
  if(bw)cmsnsd->SetMarkerStyle(20);
  cmsnsd->SetMarkerSize(msize*1.115);
  //cmsnsd->SetMarkerSize(msize*1.2);
  cmsnsd->SetLineColor(kRed+3);
  //if(bw)cmsnsd->SetLineColor(kBlack);
  if(bw)cmsnsd->SetLineColor(kRed+2);
  //cmsnsd->Draw("PE");
  ua5nsd->Draw("PZsame");
  cmsnsd->Draw("PZsame");
  //cmsnsd->Draw("same");   

  // to fill the white gap around the marker
  TGraph* cmsnsd04 = cmsnsd->Clone("cmsnsd04");
  cmsnsd04->SetMarkerStyle(0);
  cmsnsd04->SetLineWidth(2);
  cmsnsd04->Draw("PZsame");

  // to draw vertical lines at the end 
  TGraph* cmsnsd05 = cmsnsd->Clone("cmsnsd05");
  gStyle->SetEndErrorSize(3);
  cmsnsd05->SetMarkerStyle(0);
  cmsnsd05->Draw("||");

  // ---- ALICE INEL ------
  Double_t x12[1] =  {  900};
  Double_t y12[1] =  {  3.10};
  /*
  Double_t exl12[1]= {  0.22};
  Double_t exh12[1]= { 0.22};
  Double_t eyl12[1]= { 0.22};
  Double_t eyh12[1]= { 0.22};
  */
  // for now we don't show sys error for everyone
  Double_t exl12[1]= {  0};
  Double_t exh12[1]= { 0};
  Double_t eyl12[1]= { 0.22};
  Double_t eyh12[1]= { 0.22};

  TGraphAsymmErrors *aliceinel=new TGraphAsymmErrors(2,x12,y12,exl12,exh12,eyl12,eyh12);
  aliceinel->SetMarkerColor(kBlack);
  aliceinel->SetMarkerStyle(30);
  aliceinel->SetMarkerSize(msize*1.5);
  aliceinel->SetLineColor(kBlack);
  aliceinel->Draw("PZsame");

  // ---- Phobos INEL ------
  Double_t x13[1] =  { 200 };
  Double_t y13[1] =  {  2.32 };
  Double_t exl13[1]= { 0 };
  Double_t exh13[1]= { 0 };
  Double_t eyl13[1]= { 0.15};
  Double_t eyh13[1]= { 0.30};
  if ( ErrorFlag == false)
    {
      eyl13[0]= 0;
      eyh13[0]= 0;
    }



  
  
  TGraphAsymmErrors *phobosinel=new TGraphAsymmErrors(1,x13,y13,exl13,exh13,eyl13,eyh13);
  phobosinel->SetMarkerColor(kBlack);
  phobosinel->SetMarkerStyle(27);
  phobosinel->SetMarkerSize(msize);
  phobosinel->SetLineColor(kBlack);
  phobosinel->Draw("PZsame");

  // ---- STAR NSD ------
  Double_t x14[1] = {  200};
  Double_t y14[1] = {  2.98};
  /*
  Double_t exl14[1]= {  0.34};
  Double_t exh14[1]= { 0.34};
  Double_t eyl14[1]= { 0.34};
  Double_t eyh14[1]= { 0.34};
  */
  // for now we don't show sys error for everyone
  Double_t exl14[1]= {  0};
  Double_t exh14[1]= { 0};
  Double_t eyl14[1]= { 0.34};
  Double_t eyh14[1]= { 0.34};

  TGraphAsymmErrors *starnsd=new TGraphAsymmErrors(2,x14,y14,exl14,exh14,eyl14,eyh14);
  starnsd->SetMarkerColor(kBlack);
  starnsd->SetMarkerStyle(23);
  starnsd->SetMarkerSize(msize);
  starnsd->SetLineColor(kBlack);
  starnsd->Draw("PZsame");

  TGraph* starnsd04 = starnsd->Clone("starnsd04");
  starnsd04->SetMarkerStyle(0);
  starnsd04->Draw("PZsame");



 /*
// ---- CMS INEL ---
  Double_t x7[2] =  { 900,  900 }; 
//  Double_t y7[2] =  {  2.36, 3.80 };  // from Yen-Jie PAS (PYTHIA)
  Double_t y7[2] =  {  2.93, 2.93 };  // guesstimate!!
  Double_t exl7[2]= { 0, 0, };
  Double_t exh7[2]= { 0, 0, };
  Double_t eyl7[2]= { 0.231, 0.231 };
  Double_t eyh7[2]= { 0.231, 0.231 };

  TGraphAsymmErrors *cmsinel=new TGraphAsymmErrors(2,x7,y7,exl7,exh7,eyl7,eyh7);
  cmsinel->SetMarkerColor(kRed);
  //if(bw)cmsinel->SetMarkerColor(kBlack);
  if(bw)cmsinel->SetMarkerColor(kRed);
  //cmsinel->SetMarkerStyle(21);
  cmsinel->SetMarkerStyle(20);
  cmsinel->SetMarkerSize(msize);
  cmsinel->SetLineColor(kRed);
  if(bw)cmsinel->SetLineColor(kBlack);
  //cmsinel->Draw("PE");
  cmsinel->Draw("PZ");
  */

  TLegend* leg = new TLegend(0.50,0.92 - 0.045*5,0.80,0.92);
  //if(theory) TLegend* leg3 = new TLegend(0.50,0.92 - 0.045*6,0.80,0.92);
  //if(theory && pythia) TLegend* leg3 = new TLegend(0.50,0.92 - 0.045*8,0.80,0.92);

    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    if(bw){
      leg->AddEntry(fnalinel,"NAL B.C. inel.","p");
      leg->AddEntry(isr,"ISR inel.","p");
      leg->AddEntry(ua5inel,"UA5 inel.","p");
      leg->AddEntry(phobosinel,"PHOBOS inel.","p");
      leg->AddEntry(aliceinel,"ALICE inel.","p");
      leg->SetTextSize(0.03); 
    }
    else{
    leg->AddEntry(fnalinel,"FNAL inel.","p");
    leg->AddEntry(isr,"ISR inel.","p");
    leg->AddEntry(ua5inel,"UA5 inel.","p");
    leg->AddEntry(ua1nsd,"UA1 NSD","p");
    leg->AddEntry(ua5nsd,"UA5 NSD","p");
    leg->AddEntry(cdf,"CDF NSD","p");
    leg->AddEntry(cmsnsd,"CMS NSD","p");
    //leg->AddEntry(phojet1,"PHOJET 1.12","l");
    leg->AddEntry(pythia1,"PYTHIA D6T","l");
    leg->AddEntry(atlas1,"PYTHIA ATLAS","l");
    leg->AddEntry(gr,"E. Levin et al.","l");
    leg->SetTextSize(0.03);

    }
    //    leg->Draw();


    TLegend* leg3 = new TLegend(0.20,0.92 - 0.045*6,0.68,0.92);
    if(theory) TLegend* leg3 = new TLegend(0.20,0.92 - 0.045*7,0.68,0.92);
    if(theory && pythia) TLegend* leg3 = new TLegend(0.20,0.92 - 0.045*9,0.68,0.92);

    leg3->SetFillColor(0);

    leg3->SetBorderSize(0);
    if(bw){
      leg3->AddEntry(ua1nsd,"UA1 NSD","p");
      leg3->AddEntry(starnsd,"STAR NSD","p");
      leg3->AddEntry(ua5nsd,"UA5 NSD","p");
      leg3->AddEntry(cdf,"CDF NSD","p");
      leg3->AddEntry(alicensd,"ALICE NSD","p");
      leg3->AddEntry(cmsnsd,"CMS NSD","p");
      if(theory){
//	 leg3->AddEntry(phojet1,"PHOJET 1.12","l");
	 leg3->AddEntry(gr,"E. Levin et al.","l");
      }
      if(pythia){
	 leg3->AddEntry(atlas1,"PYTHIA ATLAS","l");
         leg3->AddEntry(pythia1,"PYTHIA D6T","l");
      }
      leg3->SetTextSize(0.03);
    }
    leg3->Draw();
    leg->Draw();

    //TLegend* leg5 = new TLegend(0.60,0.4 - 0.045*2,0.95,0.4);
    //leg5->SetFillColor(0);
    //leg5->SetBorderSize(0);
    //leg5->AddEntry(phojet1,"PHOJET 1.12","l");
    //leg5->AddEntry(pythia1,"PYTHIA 6.420 D6T","l");
    //leg5->AddEntry(gr,"E. Levin et al.","l");
    //leg5->SetTextSize(0.03);
    //if(theory) leg5->Draw();


    //TLegend leg2(0.38,0.15,0.88,0.29);
    //TLegend leg2(0.22,0.55,0.46,0.89);
    //TLegend leg2(0.22,0.52,0.5,0.91);
    //TLegend leg2(0.38,0.15,0.89,0.3);
    //TLegend leg2(0.41,0.15,0.91,0.3);
    TLegend *leg2 = new TLegend(0.39,0.3-0.045*3,0.91,0.3,NULL,"brNDC"); 
    //TLegend *leg2 = new TLegend(0.22,0.34,0.6,0.911,NULL,"brNDC");
    leg2->SetFillColor(0);
    leg2->SetBorderSize(0);
    leg2->AddEntry(fitISR,"0.161 + 0.201 ln(s)","l");
    //leg2->AddEntry(fitUA5,"2.26 - 0.207 ln(s) + 0.0215 ln^{2}(s)","l");
    // fit with CMS 900, 2360 GeV Points
    //leg2->AddEntry(fitUA5,"3.18 - 0.384 ln(s) + 0.0297 ln^{2}(s)","l");
    leg2->AddEntry(fitUA5,"3.17 - 0.381 ln(s) + 0.0296 ln^{2}(s)","l");
    //leg2->AddEntry(fitUA5,"0.929 + 0.0644 exp(#sqrt{ln(s)})","l");
    leg2->AddEntry(fitUA5inel,"1.54 - 0.096 ln(s) + 0.0155 ln^{2}(s)","l");
    leg2->SetTextSize(0.03);
    leg2->Draw();

    TLatex t_sys(70.,5.2,"}");
    t_sys.SetTextSize(0.15);
    t_sys.SetTextColor(1);
    t_sys.SetTextAlign(32);

    

    printFinalCanvases(c,"dNdeta_vs_roots_wmodels",0,2);
}





