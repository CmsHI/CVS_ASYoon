{
  gROOT->Reset();
  gROOT->ProcessLine(".x dndeta_rootlogon.C");


  //****************************************************
  Bool_t bw = 1;       // 1: BLACK AND WHITE, 0: COLOR
  Float_t msize = 1.8; // MARKER SIZE
  if(bw) msize = 1.8;
  //****************************************************
  
  TCanvas *c = new TCanvas("c","c",550,600);

  gStyle->SetTitleYSize(.060);
  gStyle->SetTitleYOffset(1.);

  c->SetLogx();
  c->SetLeftMargin(0.15);

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
  if(bw)isr->SetMarkerStyle(23);
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
  if(bw)ua5nsd->SetMarkerStyle(25);
  ua5nsd->SetMarkerSize(msize);
  ua5nsd->SetLineColor(kBlue);
  if(bw)ua5nsd->SetLineColor(kBlue);
  //ua5nsd->Draw("PE");
  ua5nsd->Draw("PZ");  
  
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
  ua5inel->SetMarkerStyle(21);
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
  fnalinel->SetMarkerStyle(29);
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
  if(bw)cdf->SetMarkerStyle(27);
  cdf->SetMarkerSize(msize);
  cdf->SetLineColor(kBlue);
  if(bw)cdf->SetLineColor(kBlue);
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
  ua1nsd->SetMarkerStyle(28);
  ua1nsd->SetMarkerSize(msize);
  ua1nsd->SetLineColor(1);
  ua1nsd->Draw("PZsame");

// ---- CMS NSD ---
  Double_t x6[2] =  { 900,  900 }; 
  //Double_t y6[2] =  {  3.3, 3.3 };  // guesstimate!
  Double_t y6[2] =  {  3.52, 3.52 };
  //Double_t exl6[2]= { 0, 0, };
  Double_t exl6[2]= {0.211, 0.211 };
  //Double_t exh6[2]= { 0, 0, };
  Double_t exh6[2]= { 0.211, 0.211 };  
  Double_t eyl6[2]= { 0.211, 0.211 };  
  Double_t eyh6[2]= { 0.211, 0.211 };
  //Double_t eyl6[2]= { 0.275, 0.275 };
  //Double_t eyh6[2]= { 0.275, 0.275 };

  TGraphAsymmErrors *cmsnsd=new TGraphAsymmErrors(2,x6,y6,exl6,exh6,eyl6,eyh6);
  cmsnsd->SetMarkerColor(kRed);
  //if(bw)cmsnsd->SetMarkerColor(kBlack);
  if(bw)cmsnsd->SetMarkerColor(kRed);
  cmsnsd->SetMarkerStyle(29);
  if(bw)cmsnsd->SetMarkerStyle(29);
  cmsnsd->SetMarkerSize(msize*1.2);
  cmsnsd->SetLineColor(kRed);
  //if(bw)cmsnsd->SetLineColor(kBlack);
  if(bw)cmsnsd->SetLineColor(kRed);
  //cmsnsd->Draw("PE");
  cmsnsd->Draw("PZsame");
  
  // ---- ALICE NSD ------
  Double_t x6[2] =  {  900,  900 };
  Double_t y6[2] =  {  3.51, 3.51 };
  Double_t exl6[2]= {  0.25, 0.25 };
  Double_t exh6[2]= { 0.25, 0.25 };
  Double_t eyl6[2]= { 0.25, 0.25 };
  Double_t eyh6[2]= { 0.25, 0.25 };

  TGraphAsymmErrors *alicensd=new TGraphAsymmErrors(2,x6,y6,exl6,exh6,eyl6,eyh6);
  alicensd->SetMarkerColor(kBlack);
  alicensd->SetMarkerStyle(24);
  alicensd->SetMarkerSize(msize);
  alicensd->SetLineColor(kBlack);
  alicensd->Draw("PZsame");

  // ---- ALICE INEL ------
  Double_t x6[2] =  {  900,  900 };
  Double_t y6[2] =  {  3.10, 3.10 };
  Double_t exl6[2]= {  0.22, 0.22 };
  Double_t exh6[2]= { 0.22, 0.22 };
  Double_t eyl6[2]= { 0.22, 0.22 };
  Double_t eyh6[2]= { 0.22, 0.22 };

  TGraphAsymmErrors *aliceinel=new TGraphAsymmErrors(2,x6,y6,exl6,exh6,eyl6,eyh6);
  aliceinel->SetMarkerColor(kBlack);
  aliceinel->SetMarkerStyle(20);
  aliceinel->SetMarkerSize(msize);
  aliceinel->SetLineColor(kBlack);
  aliceinel->Draw("PZsame");

  // ---- Phobos INEL ------
  Double_t x10[1] =  { 200 };
  Double_t y10[1] =  {  2.32 };
  Double_t exl10[1]= { 0 };
  Double_t exh10[1]= { 0 };
  Double_t eyl10[1]= { 0.20};
  Double_t eyh10[1]= { 0.20};

  TGraphAsymmErrors *phobosinel=new TGraphAsymmErrors(1,x10,y10,exl10,exh10,eyl10,eyh10);
  phobosinel->SetMarkerColor(kBlack);
  phobosinel->SetMarkerStyle(22);
  phobosinel->SetMarkerSize(msize);
  phobosinel->SetLineColor(kBlack);
  phobosinel->Draw("PZsame");

  // ---- STAR NSD ------
  Double_t x6[2] = {  200,  200 };
  Double_t y6[2] = {  2.98, 2.98 };
  Double_t exl6[2]= {  0.34, 0.34 };
  Double_t exh6[2]= { 0.34, 0.34 };
  Double_t eyl6[2]= { 0.34, 0.34 };
  Double_t eyh6[2]= { 0.34, 0.34 };

  TGraphAsymmErrors *starnsd=new TGraphAsymmErrors(2,x6,y6,exl6,exh6,eyl6,eyh6);
  starnsd->SetMarkerColor(kBlack);
  starnsd->SetMarkerStyle(30);
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

  TLegend* leg = new TLegend(0.25,0.444,0.48,0.90);
    leg->SetFillColor(0);

    leg.SetBorderSize(0);
    if(bw){
    leg.AddEntry(fnalinel,"FNAL inel.","p");
    leg.AddEntry(isr,"ISR inel.","p");
    leg.AddEntry(ua5inel,"UA5 inel.","p");
    leg.AddEntry(aliceinel,"ALICE inel.","p");
    leg.AddEntry(phobosinel,"PHOBOS inel.","p");
    leg.AddEntry(ua1nsd,"UA1 NSD","p");
    leg.AddEntry(ua5nsd,"UA5 NSD","p");
    leg.AddEntry(starnsd,"STAR NSD","p");
    leg.AddEntry(cdf,"CDF NSD","p");
    leg.AddEntry(alicensd,"ALICE NSD","p");
    leg.AddEntry(cmsnsd,"CMS NSD","p");
    }
    else{
    leg.AddEntry(fnalinel,"FNAL inel.","p");
    leg.AddEntry(isr,"ISR inel.","p");
    leg.AddEntry(ua5inel,"UA5 inel.","p");
    leg.AddEntry(ua1nsd,"UA1 NSD","p");
    leg.AddEntry(ua5nsd,"UA5 NSD","p");
    leg.AddEntry(cdf,"CDF NSD","p");
    
    leg.AddEntry(cmsnsd,"CMS NSD","p");
    }
    leg.Draw();

    //TLegend leg2(0.38,0.15,0.88,0.29);
    //TLegend leg2(0.22,0.55,0.46,0.89);
    //TLegend leg2(0.22,0.52,0.5,0.91);
    //TLegend leg2(0.38,0.15,0.89,0.3);
    //TLegend leg2(0.41,0.15,0.91,0.3);
    TLegend *leg2 = new TLegend(0.411,0.18,0.91,0.33,NULL,"brNDC"); 
    //TLegend *leg2 = new TLegend(0.22,0.48,0.6,0.911,NULL,"brNDC");
    leg2.SetFillColor(0);
    leg2.SetBorderSize(0);
    leg2.AddEntry(fitISR,"0.161 + 0.201 ln(s)","l");
    leg2.AddEntry(fitUA5,"2.26 - 0.207 ln(s) + 0.0215 ln^{2}(s)","l");
    leg2.AddEntry(fitUA5inel,"1.54 - 0.096 ln(s) + 0.0155 ln^{2}(s)","l");
    leg2.Draw();

    TLatex t_sys(70.,5.2,"}");
    t_sys.SetTextSize(0.15);
    t_sys.SetTextColor(1);
    t_sys.SetTextAlign(32);

    //    TLatex* tex = new TLatex(12,7.,"(a)");
    //    tex->SetTextSize(0.04);
    //    tex->SetLineWidth(2);
    //    tex->Draw();

    TLatex *tex = new TLatex(3950,6.96,"CMS");
    tex->SetTextSize(0.04);
    tex->SetLineWidth(2);
    tex->Draw();

    c->Print("Fig.eps");
//    t_sys.Draw();

//   c->Print("Fig.eps");
    c->Print("dNdeta_vs_roots.eps");
//    c->Print("dNdeta_vs_roots.pdf"); // don't print, use eps2pdf
    c->Print("dNdeta_vs_roots.gif");
}

