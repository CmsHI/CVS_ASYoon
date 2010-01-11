#include "common.h"

void dNdeta_vs_roots() {
  gROOT->Reset();
  gROOT->ProcessLine(".x rootlogon.C");


  //****************************************************
  Bool_t bw = 1;       // 1: BLACK AND WHITE, 0: COLOR
  Float_t msize = 2.; // MARKER SIZE
  //****************************************************
  
  TCanvas *c = new TCanvas("c","c",550,600);

  //  gStyle->SetTitleYSize(.060);
  gStyle->SetTitleYOffset(1.4);

  c->SetLogx();
  //  c->SetLeftMargin(0.15);

  TH1F *dummy = new TH1F("dummy","dummy",100,9,10000);
  dummy->SetMaximum(7.5);
  dummy->SetMinimum(0);
  dummy->SetXTitle("#sqrt{s} [GeV]");
  dummy->SetYTitle("dN_{ch}/d#eta|_{#eta=0}");
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
  if(bw)isr->SetMarkerStyle(26);
  //if(bw)isr->SetMarkerStyle(22);  
  isr->SetMarkerSize(msize);
  isr->SetLineColor(kBlack);
  isr->Draw("PE");

//  TF1 *fitISR = new TF1("fitISR","0.01+0.44*log(x)",12,80);
  TF1 *fitISR = new TF1("fitISR","0.161+0.201*2*log(x)",12,80);
  fitISR->SetLineColor(kBlack);
  fitISR->SetLineWidth(2);
  fitISR->SetLineStyle(1);    
  fitISR->Draw("same");

// ---- UA5 NSD ---
Double_t x2[4] =  { 51.5,  200,     532,  886 };  // approx values
  Double_t y2[4] =  {  1.982, 2.474, 3.047, 3.478 };
  Double_t exl2[4]= { 0, 0, 0, 0 };
  Double_t exh2[4]= { 0, 0, 0, 0 };
  Double_t eyl2[4]= { 0.090, 0.078, 0.099, 0.090 };
  Double_t eyh2[4]= { 0.090, 0.078, 0.099, 0.090 };

  TGraphAsymmErrors *ua5nsd=new TGraphAsymmErrors(4,x2,y2,exl2,exh2,eyl2,eyh2);
  ua5nsd->SetMarkerColor(kBlue);
  if(bw)ua5nsd->SetMarkerColor(kBlack);
  ua5nsd->SetMarkerStyle(20);
  //if(bw)ua5nsd->SetMarkerStyle(25);
  //if(bw)ua5nsd->SetMarkerStyle(23);
  if(bw)ua5nsd->SetMarkerStyle(21);
  ua5nsd->SetMarkerSize(msize);
  ua5nsd->SetLineColor(kBlue);
  if(bw)ua5nsd->SetLineColor(kBlack);
  //ua5nsd->Draw("PE");
  //  ua5nsd->Draw("PZ");  
  
//  TF1 *fitUA5 = new TF1("fitUA5","2.5-0.5*log(x)+0.023*4*log(x)*log(x)",40,8000);
  TF1 *fitUA5 = new TF1("fitUA5","2.26-2*0.207*log(x)+0.0215*4*log(x)*log(x)",40,8000);
  fitUA5->SetLineColor(kBlue);
  if(bw)fitUA5->SetLineColor(kBlack);
  fitUA5->SetLineWidth(2);
  fitUA5->SetLineStyle(2);    
  //fitUA5->Draw("same");
  fitUA5->Draw("same");  

  // fit to UA5 and CMS inelastic points
  TF1 *fitUA5inel = new TF1("fitUA5inel","1.54-2*0.096*log(x)+0.0155*4*log(x)*log(x)",40,8000);
  fitUA5inel->SetLineColor(kGreen);
  if(bw)fitUA5inel->SetLineColor(kBlack);
  fitUA5inel->SetLineWidth(2);
  fitUA5inel->SetLineStyle(7);    
  fitUA5inel->Draw("same");

// ---- UA5 INEL ---
  Double_t x3[4] =  { 51.5,  200,     532,  886 };  // approx values
  Double_t y3[4] =  {  1.761, 2.205, 2.785, 3.137 };
  Double_t exl3[4]= { 0, 0, 0, 0 };
  Double_t exh3[4]= { 0, 0, 0, 0 };
  Double_t eyl3[4]= { 0.090, 0.078, 0.099, 0.090 };
  Double_t eyh3[4]= { 0.090, 0.078, 0.099, 0.090 };

  TGraphAsymmErrors *ua5inel=new TGraphAsymmErrors(4,x3,y3,exl3,exh3,eyl3,eyh3);
  ua5inel->SetMarkerColor(kBlack);
  ua5inel->SetMarkerStyle(25);
  ua5inel->SetMarkerSize(msize);
  ua5inel->SetLineColor(kBlack);
  //ua5inel->Draw("PE");
  ua5inel->Draw("PZ");

// ---- FNAL INEL ---
  Double_t x4[2] =  { 13.76,  19.42 };  // approx values
  Double_t y4[2] =  {  1.210, 1.414 };
  Double_t exl4[2]= { 0, 0, };
  Double_t exh4[2]= { 0, 0, };
  Double_t eyl4[2]= { 0.050, 0.065 };
  Double_t eyh4[2]= { 0.050, 0.065 };

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
  Double_t eyl5[2]= { 0.117, 0.133 };
  Double_t eyh5[2]= { 0.117, 0.133 };

  TGraphAsymmErrors *cdf=new TGraphAsymmErrors(2,x5,y5,exl5,exh5,eyl5,eyh5);
  cdf->SetMarkerColor(kBlue);
  if(bw)cdf->SetMarkerColor(kBlack);
  cdf->SetMarkerStyle(21);
  if(bw)cdf->SetMarkerStyle(22);
  cdf->SetMarkerSize(msize);
  cdf->SetLineColor(kBlue);
  if(bw)cdf->SetLineColor(kBlack);
  //cdf->Draw("PE");
  cdf->Draw("PZ"); 


  // ---- UA1 NSD ---                                                              
  Double_t xua1[7] =  { 200,  260, 380, 500, 620, 790, 900 };
  Double_t yua1[7] =  {  2.65, 2.71, 2.94, 3.05, 3.15, 3.41, 3.48 };
  Double_t exlua1[7]= {0,0,0,0,0,0,0  };
  Double_t eylua1[7]= {0.08.0.08,0.09,0.09,0.09,0.10,0.10 };

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
  // for now we don't show sys error for everyone
  Double_t exl10[2]= {  0};
  Double_t exh10[2]= { 0};
  Double_t eyl10[2]= { 0};
  Double_t eyh10[2]= { 0};

  TGraphAsymmErrors *alicensd=new TGraphAsymmErrors(2,x10,y10,exl10,exh10,eyl10,eyh10);
  alicensd->SetMarkerColor(kBlack);
  alicensd->SetMarkerStyle(29);
  alicensd->SetMarkerSize(msize);
  alicensd->SetLineColor(kBlack);
  alicensd->Draw("PZsame");

// ---- CMS NSD ---
  const int NCMS=2;
  Double_t x11[NCMS] =  { 900, 2360 }; 
  //Double_t y11[2] =  {  3.3, 3.3 };  // guesstimate!
  Double_t y11[NCMS] =  {  3.4984, 4.23402 };
  Double_t  cmsSysErr = (y11[0]+y11[1])/2. *0.035;
  /*
  Double_t exl11[NCMS]= { 0. };
  Double_t exh11[NCMS]= { 0. };
  Double_t eyl11[NCMS]= { 0.2108 };
  Double_t eyh11[NCMS]= { 0.2108 };
  */
  // for now we don't show sys error for everyone
  Double_t exl11[NCMS]= { 0. };
  Double_t exh11[NCMS]= { 0. };
  Double_t eyl11[NCMS]= { 0};
  Double_t eyh11[NCMS]= { 0};

  TGraphAsymmErrors *cmsnsd=new TGraphAsymmErrors(NCMS,x11,y11,exl11,exh11,eyl11,eyh11);
  cmsnsd->SetMarkerColor(kRed);
  //if(bw)cmsnsd->SetMarkerColor(kBlack);
  if(bw)cmsnsd->SetMarkerColor(kRed);
  cmsnsd->SetMarkerStyle(kFullStar);
  if(bw)cmsnsd->SetMarkerStyle(20);
  cmsnsd->SetMarkerSize(msize*1.3);
  cmsnsd->SetLineColor(kRed);
  //if(bw)cmsnsd->SetLineColor(kBlack);
  if(bw)cmsnsd->SetLineColor(kRed);
  //cmsnsd->Draw("PE");
  cmsnsd->Draw("PEsame");
  ua5nsd->Draw("PZsame");

  TGraphAsymmErrors * cmsnsdSysError = cmsnsd->Clone();
  cmsnsdSysError->SetPoint(0,220,3.86);
  cmsnsdSysError->SetPointError(0,0,0,cmsSysErr,cmsSysErr);
  cmsnsdSysError->SetMarkerStyle(0);
  cmsnsdSysError->SetMarkerColor(kGray);
  cmsnsdSysError->SetLineColor(kGray);
  cmsnsdSysError->SetLineWidth(10);
  cmsnsdSysError->Draw("PEsame");
  TLatex *tex11 = new TLatex(15,3.8,"CMS Sys. Uncertainty");
  tex11->SetTextSize(0.03);
  tex11->SetLineWidth(2);
  //tex11->SetNDC();
  tex11->Draw();

  
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
  Double_t eyl12[1]= { 0};
  Double_t eyh12[1]= { 0};

  TGraphAsymmErrors *aliceinel=new TGraphAsymmErrors(2,x12,y12,exl12,exh12,eyl12,eyh12);
  aliceinel->SetMarkerColor(kBlack);
  aliceinel->SetMarkerStyle(30);
  aliceinel->SetMarkerSize(msize);
  aliceinel->SetLineColor(kBlack);
  aliceinel->Draw("PZsame");

  // ---- Phobos INEL ------
  Double_t x13[1] =  { 200 };
  Double_t y13[1] =  {  2.32 };
  Double_t exl13[1]= { 0 };
  Double_t exh13[1]= { 0 };
  Double_t eyl13[1]= { 0.20};
  Double_t eyh13[1]= { 0.20};

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
  Double_t eyl14[1]= { 0};
  Double_t eyh14[1]= { 0};

  TGraphAsymmErrors *starnsd=new TGraphAsymmErrors(2,x14,y14,exl14,exh14,eyl14,eyh14);
  starnsd->SetMarkerColor(kBlack);
  starnsd->SetMarkerStyle(23);
  starnsd->SetMarkerSize(msize);
  starnsd->SetLineColor(kBlack);
  starnsd->Draw("PZsame");




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

  TLegend* leg = new TLegend(0.45,0.65,0.8,0.90);
    leg->SetFillColor(0);

    leg->SetBorderSize(0);
    if(bw){
      leg->AddEntry(fnalinel,"FNAL inel.","p");
      leg->AddEntry(isr,"ISR inel.","p");
      leg->AddEntry(ua5inel,"UA5 inel.","p");
      leg->AddEntry(aliceinel,"ALICE inel.","p");
      leg->AddEntry(phobosinel,"PHOBOS inel.","p");
    }
    else{
    leg->AddEntry(fnalinel,"FNAL inel.","p");
    leg->AddEntry(isr,"ISR inel.","p");
    leg->AddEntry(ua5inel,"UA5 inel.","p");
    leg->AddEntry(ua1nsd,"UA1 NSD","p");
    leg->AddEntry(ua5nsd,"UA5 NSD","p");
    leg->AddEntry(cdf,"CDF NSD","p");
    
    leg->AddEntry(cmsnsd,"CMS NSD","p");
    }
    //    leg->Draw();


    TLegend* leg3 = new TLegend(0.25,0.6,0.48,0.90);
    leg3->SetFillColor(0);

    leg3->SetBorderSize(0);
    if(bw){
      leg3->AddEntry(ua1nsd,"UA1 NSD","p");
      leg3->AddEntry(ua5nsd,"UA5 NSD","p");
      leg3->AddEntry(starnsd,"STAR NSD","p");
      leg3->AddEntry(cdf,"CDF NSD","p");
      leg3->AddEntry(alicensd,"ALICE NSD","p");
      leg3->AddEntry(cmsnsd,"CMS NSD","p");
    }
    leg3->Draw();
    leg->Draw();

    //TLegend leg2(0.38,0.15,0.88,0.29);
    //TLegend leg2(0.22,0.55,0.46,0.89);
    //TLegend leg2(0.22,0.52,0.5,0.91);
    //TLegend leg2(0.38,0.15,0.89,0.3);
    //TLegend leg2(0.41,0.15,0.91,0.3);
    TLegend *leg2 = new TLegend(0.411,0.18,0.91,0.33,NULL,"brNDC"); 
    //TLegend *leg2 = new TLegend(0.22,0.48,0.6,0.911,NULL,"brNDC");
    leg2->SetFillColor(0);
    leg2->SetBorderSize(0);
    leg2->AddEntry(fitISR,"0.161 + 0.201 ln(s)","l");
    leg2->AddEntry(fitUA5,"2.26 - 0.207 ln(s) + 0.0215 ln^{2}(s)","l");
    leg2->AddEntry(fitUA5inel,"1.54 - 0.096 ln(s) + 0.0155 ln^{2}(s)","l");
    leg2->Draw();

    TLatex t_sys(70.,5.2,"}");
    t_sys.SetTextSize(0.15);
    t_sys.SetTextColor(1);
    t_sys.SetTextAlign(32);

    printFinalCanvases(c,"dNdeta_vs_roots",0,0);
    /*
    // add some text labels
    double ndcX = 0.2;
    double ndcY = 0.9;
    TLatex *tex = new TLatex(0.85,ndcY,"CMS");
    tex->SetTextSize(0.04);
    tex->SetLineWidth(2);
    tex->SetNDC();
    tex->Draw();

    c->Print("dNdeta_vs_roots.eps");
    c->Print("dNdeta_vs_roots.pdf");
    c->Print("dNdeta_vs_roots.gif");

    tex = new TLatex(ndcX,ndcY,"(a)");
    tex->SetTextSize(0.04);
    tex->SetLineWidth(2);
    tex->SetNDC();
    tex->Draw();

    c->Print("dNdeta_vs_roots_A.eps");
    c->Print("dNdeta_vs_roots_A.gif");
    c->Print("dNdeta_vs_roots_A.pdf");

    tex->Delete();
    tex = new TLatex(ndcX,ndcY,"(b)");
    tex->SetTextSize(0.04);
    tex->SetLineWidth(2);
    tex->SetNDC();
    tex->Draw();

    c->Print("dNdeta_vs_roots_B.eps");
    c->Print("dNdeta_vs_roots_B.gif");
    c->Print("dNdeta_vs_roots_B.pdf");
    */
}

