// For plotting
#include "GraphErrorsBand.h"
#include "common.h"
// Standard library
#include <cmath>
#include <iostream>
#include <fstream>

// ROOT Library
#include <TROOT.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TProfile.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TLine.h>
#include <TF1.h>
#include <TCut.h>
#include <TPad.h>
#include <TText.h>
#include <TLatex.h>
#include <TLegendEntry.h>

//void Draw(){
void dNdEta_ThreeMethodsCombined_BU_Compile(){
//=========Macro generated from canvas: MyCanvas/MyCanvas
//=========  (Thu Dec 10 11:52:00 2009) by ROOT version5.22/00d

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,550,600);
   /// ==================================================== Weighted mean of all three method!

   Double_t xAxis7[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3};
   TH1 *hMeasuredFinal3 = new TH1D("hMeasuredFinal3","",12, xAxis7);
   
   hMeasuredFinal3->GetXaxis()->SetRange(1,13);

   hMeasuredFinal3->SetMinimum(0);
   hMeasuredFinal3->SetMaximum(7.0);

   hMeasuredFinal3->SetBinContent(2,3.60278);  // -2.4 to -2.0    
   hMeasuredFinal3->SetBinContent(3,3.731399616); //-2 to -1.5 
   hMeasuredFinal3->SetBinContent(4,3.618227783);        // -1.5 to -1.0 
   hMeasuredFinal3->SetBinContent(5,3.538766473); // -1.0 to -0.5 
   hMeasuredFinal3->SetBinContent(6,3.477522368);        // -0.5 to 0

   /*
   hMeasuredFinal3->SetBinContent(2,3.65413);  // -2.4 to -2.0    
   hMeasuredFinal3->SetBinContent(3,3.744095779); //-2 to -1.5 
   hMeasuredFinal3->SetBinContent(4,3.726157315);        // -1.5 to -1.0 
   hMeasuredFinal3->SetBinContent(5,3.6087225); // -1.0 to -0.5 
   hMeasuredFinal3->SetBinContent(6,3.489931761);        // -0.5 to 0
   */


   /*
   hMeasuredFinal3->SetBinContent(2,3.6541);  // -2.4 to -2.0 
   hMeasuredFinal3->SetBinContent(3,3.7376); //-2 to -1.5 
   hMeasuredFinal3->SetBinContent(4,3.7255);        // -1.5 to -1.0 
   hMeasuredFinal3->SetBinContent(5,3.6123); // -1.0 to -0.5
   hMeasuredFinal3->SetBinContent(6,3.4977);        // -0.5 to 0
   */

   hMeasuredFinal3->SetBinContent(7,hMeasuredFinal3->GetBinContent(6)); // 0 to 0.5 
   hMeasuredFinal3->SetBinContent(8,hMeasuredFinal3->GetBinContent(5)); // 0.5 to 1.0
   hMeasuredFinal3->SetBinContent(9,hMeasuredFinal3->GetBinContent(4)); // 1.0 to 1.5 
   hMeasuredFinal3->SetBinContent(10,hMeasuredFinal3->GetBinContent(3)); // 1.5 to 2.0 
   hMeasuredFinal3->SetBinContent(11,hMeasuredFinal3->GetBinContent(2)); // 2.0 to 2.4 


   // --- Stat error ---
   double statError= 0.01767767;
   

   for (int i=2; i<12; ++i) {
     hMeasuredFinal3->SetBinError(i,hMeasuredFinal3->GetBinContent(i)*statError);
     cout << "stat error (" << i << "): " << hMeasuredFinal3->GetBinError(i) << endl;
   }

   hMeasuredFinal3->GetYaxis()->SetTitle("dN_{ch}/d#eta");
   hMeasuredFinal3->GetXaxis()->SetTitle("#eta");
   hMeasuredFinal3->GetXaxis()->CenterTitle();
   hMeasuredFinal3->GetYaxis()->CenterTitle();


   hMeasuredFinal3->GetXaxis()->SetNdivisions(405);
   //hMeasuredFinal3->GetYaxis()->SetNdivisions(1005);
   hMeasuredFinal3->GetYaxis()->SetNdivisions(506);


   //hMeasuredFinal3->SetMarkerColor(kRed);
   hMeasuredFinal3->SetMarkerColor(kBlack);
   hMeasuredFinal3->SetMarkerStyle(20);
   //hMeasuredFinal3->SetLineColor(kRed);
   hMeasuredFinal3->SetLineColor(kBlack);
   hMeasuredFinal3->SetMarkerSize(1.8); 
   
   hMeasuredFinal3->Draw("pz");

   // Clone above for systematic band!
   /// ==================================================== Weighted mean of all three method! 
   //Double_t xAxis8[13] = {-3, -2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4, 3};
   TH1D * hMeasuredFinal4 = (TH1D*)hMeasuredFinal3->Clone("hMeasuredFinal4");
   //   double sysError = 0.0603;
   //double sysError = 0.035;
   double sysError = 0.037;
   

   TGraph *gErrorBand = GetErrorBand((TH1F*)hMeasuredFinal4,sysError,sysError,0.25,0.06); 
   gErrorBand->Draw("f");

   hMeasuredFinal3->Draw("pzsame");  


   /// ==================================================== CMS 2.36 GeV
   TH1F *hMeasuredFinal236 = (TH1F*)hMeasuredFinal3->Clone("hMeasuredFinal236");
   //hMeasuredFinal236->GetXaxis()->SetRange(3,10);
   hMeasuredFinal236->GetXaxis()->SetRange(1,13);
   //hMeasuredFinal236->SetMarkerColor(kRed);
   //hMeasuredFinal236->SetLineColor(kRed);
   hMeasuredFinal236->SetMarkerColor(kBlack);
   hMeasuredFinal236->SetLineColor(kBlack);
   hMeasuredFinal236->SetMarkerStyle(20);
   hMeasuredFinal236->SetMarkerSize(1.8);

   hMeasuredFinal236->SetBinContent(2,4.78296);  // -2.4 to -2.0  
   hMeasuredFinal236->SetBinContent(3,4.806189822); //-2 to -1.5
   hMeasuredFinal236->SetBinContent(4,4.662502625);        // -1.5 to -1.0 
   hMeasuredFinal236->SetBinContent(5,4.614742045); // -1.0 to -0.5 
   hMeasuredFinal236->SetBinContent(6,4.469256947);        // -0.5 to 0

   /*
   hMeasuredFinal236->SetBinContent(2,4.968905);  // -2.4 to -2.0  
   hMeasuredFinal236->SetBinContent(3,4.906105606); //-2 to -1.5
   hMeasuredFinal236->SetBinContent(4,4.695318198);        // -1.5 to -1.0 
   hMeasuredFinal236->SetBinContent(5,4.635741157); // -1.0 to -0.5 
   hMeasuredFinal236->SetBinContent(6,4.495389263);        // -0.5 to 0
   */
   /*
   hMeasuredFinal236->SetBinContent(2,4.9689);  // -2.4 to -2.0 
   hMeasuredFinal236->SetBinContent(3,4.9122); //-2 to -1.5 
   hMeasuredFinal236->SetBinContent(4,4.7081);        // -1.5 to -1.0 
   hMeasuredFinal236->SetBinContent(5,4.6404); // -1.0 to -0.5
   hMeasuredFinal236->SetBinContent(6,4.4921);        // -0.5 to 0
   */

   hMeasuredFinal236->SetBinContent(7,hMeasuredFinal236->GetBinContent(6)); // 0 to 0.5 
   hMeasuredFinal236->SetBinContent(8,hMeasuredFinal236->GetBinContent(5)); // 0.5 to 1.0
   hMeasuredFinal236->SetBinContent(9,hMeasuredFinal236->GetBinContent(4)); // 1.0 to 1.5 
   hMeasuredFinal236->SetBinContent(10,hMeasuredFinal236->GetBinContent(3)); // 1.5 to 2.0 
   hMeasuredFinal236->SetBinContent(11,hMeasuredFinal236->GetBinContent(2)); // 2.0 to 2.4 

   /// --- draw the error bands ---
   TH1F *hMeasuredFinal236EB = (TH1F*)hMeasuredFinal236->Clone("hMeasuredFinal236EB");
   //hMeasuredFinal236EB->SetBinContent(2,4.32647);
   //hMeasuredFinal236EB->SetBinContent(11,4.32647);
   TGraph *gErrorBand236 = GetErrorBand((TH1F*)hMeasuredFinal236EB,sysError,sysError,0.25);
   gErrorBand236->Draw("f");

   hMeasuredFinal236->Draw("pzsame");



   /// ====================================================  ALICE 
   //Double_t xAxis9[9] = {-1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4};
   //Double_t xAxis9[9] = {-1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4};
   //Double_t xAxis9[9] = {-1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6};
   //Double_t xAxis9[9] = {-1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6};  
   Double_t xAxis9[15] = {-1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0, 
			 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4};

   //TH1 *hEta_ALICE_NSD = new TH1D("hEta_ALICE_NSD","",8, xAxis9);
   TH1 *hEta_ALICE_NSD = new TH1D("hEta_ALICE_NSD","",14, xAxis9);
   double sysErr_alice = 0.033;
   // ALICE data points! 
   
   /* ALICE, NSD updated
      -1.3 3.893
      -1.1 3.893
      -0.9 3.807
      -0.7 3.702
      -0.5 3.635
      -0.3 3.578
      -0.1 3.521
      0.1 3.569
      0.3 3.588
      0.5 3.607
      0.7 3.731
      0.9 3.798
      1.1 3.865
      1.3 3.950
   */

   hEta_ALICE_NSD->SetBinContent(1,3.893);
   hEta_ALICE_NSD->SetBinContent(2,3.893);
   hEta_ALICE_NSD->SetBinContent(3,3.807);
   hEta_ALICE_NSD->SetBinContent(4,3.702);
   hEta_ALICE_NSD->SetBinContent(5,3.635);
   hEta_ALICE_NSD->SetBinContent(6,3.578);
   hEta_ALICE_NSD->SetBinContent(7,3.521);
   hEta_ALICE_NSD->SetBinContent(8,3.569);
   hEta_ALICE_NSD->SetBinContent(9,3.588);
   hEta_ALICE_NSD->SetBinContent(10,3.607);
   hEta_ALICE_NSD->SetBinContent(11,3.731);
   hEta_ALICE_NSD->SetBinContent(12,3.798);
   hEta_ALICE_NSD->SetBinContent(13,3.865);
   hEta_ALICE_NSD->SetBinContent(14,3.950);

   
   hEta_ALICE_NSD->SetBinError(1,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(1)));
   hEta_ALICE_NSD->SetBinError(2,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(2)));
   hEta_ALICE_NSD->SetBinError(3,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(3)));
   hEta_ALICE_NSD->SetBinError(4,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(4)));
   hEta_ALICE_NSD->SetBinError(5,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(5)));
   hEta_ALICE_NSD->SetBinError(6,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(6)));
   hEta_ALICE_NSD->SetBinError(7,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(7)));
   hEta_ALICE_NSD->SetBinError(8,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(8)));
   hEta_ALICE_NSD->SetBinError(9,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(9)));
   hEta_ALICE_NSD->SetBinError(10,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(10)));
   hEta_ALICE_NSD->SetBinError(11,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(11)));
   hEta_ALICE_NSD->SetBinError(12,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(12)));
   hEta_ALICE_NSD->SetBinError(13,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(13)));
   hEta_ALICE_NSD->SetBinError(14,sysErr_alice*(hEta_ALICE_NSD->GetBinContent(14)));


   hEta_ALICE_NSD->SetMarkerColor(1);
   hEta_ALICE_NSD->SetMarkerStyle(26);
   hEta_ALICE_NSD->SetLineColor(kBlack);
   hEta_ALICE_NSD->SetMarkerSize(1.5);
   //hEta_ALICE_NSD->SetMarkerSize(1.25);
   hEta_ALICE_NSD->Draw("pzsame");

   // ------------ 2.36 TeV
   /*
     etadN/deta
     2.36 TeV (syst error: +3.7%-2.7%)
     -1.3 4.790
     -1.1 4.714
     -0.9 4.695
     -0.7 4.561
     -0.5 4.437
     -0.3 4.475
     -0.1 4.389
     0.1 4.370
     0.3 4.466
     0.5 4.494
     0.7 4.637
     0.9 4.723
     1.1 4.761
     1.3 4.895
   */
   double sysAlice_hi = 0.037;
   double sysAlice_lo = 0.027;

   Double_t x[14]  ={-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3};
   Double_t y[14]  ={4.790,4.714,4.695,4.561,4.437,4.475,4.389,4.370,4.466,4.494,4.637,4.723,4.761,4.895};
   Double_t exl[14];
   Double_t exh[14];
   Double_t eyl[14];
   Double_t eyh[14];
   for(int n = 0; n<14;n++){
      exl[n] = exh[n] = 0.0;
      eyl[n] = y[n]*sysAlice_lo;
      eyh[n] = y[n]*sysAlice_hi;
      cout<<"eyl:"<<eyl[n]<<" and eyh : "<<eyh[n]<<endl;
   }

   TGraphAsymmErrors* alice_236 = new TGraphAsymmErrors(14,x,y,exl,exh,eyl,eyh);
   alice_236->SetMarkerColor(1);
   alice_236->SetMarkerStyle(26);
   alice_236->SetMarkerSize(1.5);
   alice_236->Draw("pzsame"); // draw later 

   //dum hist
   TH1 *halice_236 = new TH1D();
   halice_236->SetMarkerColor(1);
   halice_236->SetMarkerStyle(26);
   halice_236->SetMarkerSize(1.25);
   
   /// ====================================================  UA5 Data

   //TH1F* hEta_UA5_NSD = new TH1F("hEta_UA5_NSD",";#eta;dN/d#eta",50,-3,3);
   //TH1F* hEta_UA5_NSD = new TH1F("hEta_UA5_NSD",";#eta;dN/d#eta",100,-3,3);
   TH1F* hEta_UA5_NSD = new TH1F("hEta_UA5_NSD",";#eta;dN/d#eta",26,-3.25,3.25);  

   // positive eta
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.125),3.48);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.375),3.38);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.625),3.52);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.875),3.68);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.125),3.71);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.375),3.86);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.625),3.76);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.875),3.66);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.125),3.72);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.375),3.69);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.625),3.56);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.875),3.41);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(3.125),3.15);

   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(3.125),0.07);


   //negative eta
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.125),3.48);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.375),3.38);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.625),3.52);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.875),3.68);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.125),3.71);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.375),3.86);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.625),3.76);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.875),3.66);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.125),3.72);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.375),3.69);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.625),3.56);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.875),3.41);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-3.125),3.15);

   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-3.125),0.07);

   hEta_UA5_NSD->SetMarkerStyle(25);
   hEta_UA5_NSD->SetMarkerSize(1.25);
   hEta_UA5_NSD->Draw("psame");

   // Draw one more time to put CMS point on top of every other experiemnt's data points!
   hMeasuredFinal3->Draw("pzsame");
   hMeasuredFinal236->Draw("pzsame");


   //------------------------ 7 TeV measurement is added -------------------
   sysError = 0.04;
   TH1F *hMeasuredFinal7 = (TH1F*)hMeasuredFinal3->Clone("hMeasuredFinal7");
   hMeasuredFinal7->GetXaxis()->SetRange(1,13);
   //hMeasuredFinal7->SetMarkerColor(kRed);
   //hMeasuredFinal7->SetLineColor(kRed);
   hMeasuredFinal7->SetMarkerColor(kBlack);
   hMeasuredFinal7->SetLineColor(kBlack);
   hMeasuredFinal7->SetMarkerStyle(20);
   hMeasuredFinal7->SetMarkerSize(1.8);
   
   hMeasuredFinal7->SetBinContent(2,6.1769);  // -2.4 to -2.0       
   hMeasuredFinal7->SetBinContent(3,6.2635); //-2 to -1.5 
   hMeasuredFinal7->SetBinContent(4,6.1370);        // -1.5 to -1.0 
   hMeasuredFinal7->SetBinContent(5,6.0060); // -1.0 to -0.5 
   hMeasuredFinal7->SetBinContent(6,5.7825);        // -0.5 to 0

   /*
   hMeasuredFinal7->SetBinContent(2,6.192219583);  // -2.4 to -2.0 
   hMeasuredFinal7->SetBinContent(3,6.282615295); //-2 to -1.5        
   hMeasuredFinal7->SetBinContent(4,6.160073591);        // -1.5 to -1.0 
   hMeasuredFinal7->SetBinContent(5,6.029742284); // -1.0 to -0.5 
   hMeasuredFinal7->SetBinContent(6,5.820368328);        // -0.5 to 0
   */
   /*
   hMeasuredFinal7->SetBinContent(2,6.185906584);  // -2.4 to -2.0 
   hMeasuredFinal7->SetBinContent(3,6.289866674); //-2 to -1.5
   hMeasuredFinal7->SetBinContent(4,6.171406418);        // -1.5 to -1.0 
   hMeasuredFinal7->SetBinContent(5,6.034369977); // -1.0 to -0.5 
   hMeasuredFinal7->SetBinContent(6,5.828669611);        // -0.5 to 0 
   */

   hMeasuredFinal7->SetBinContent(7,hMeasuredFinal7->GetBinContent(6)); // 0 to 0.5
   hMeasuredFinal7->SetBinContent(8,hMeasuredFinal7->GetBinContent(5)); // 0.5 to 1.0
   hMeasuredFinal7->SetBinContent(9,hMeasuredFinal7->GetBinContent(4)); // 1.0 to 1.5
   hMeasuredFinal7->SetBinContent(10,hMeasuredFinal7->GetBinContent(3)); // 1.5 to 2.0
   hMeasuredFinal7->SetBinContent(11,hMeasuredFinal7->GetBinContent(2)); // 2.0 to 2.4

   /// --- draw the error bands ---
   TH1F *hMeasuredFinal7EB = (TH1F*)hMeasuredFinal7->Clone("hMeasuredFinal7EB");

   TGraph *gErrorBand7 = GetErrorBand((TH1F*)hMeasuredFinal7EB,sysError,sysError,0.25);
   gErrorBand7->Draw("f");
   hMeasuredFinal7->Draw("pzsame");



   
   Float_t ywidth = 0.045*3;

   //TLegend *leg = new TLegend(0.20,0.27,0.53,0.27+ywidth,"","brNDC");   
   //TLegend *leg = new TLegend(0.48,0.27,0.81,0.27+ywidth,"","brNDC");
   TLegend *leg = new TLegend(0.19,0.21,0.699,0.21+ywidth,NULL,"brNDC");
   leg->SetMargin(0.37);
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.033);  
   leg->SetHeader("  0.9 TeV");
   
   //leg->AddEntry(hMeasuredFinal236,"CMS NSD (2.36 TeV)","P");
   leg->AddEntry(hMeasuredFinal3,"","P");
   leg->AddEntry(hEta_ALICE_NSD,"","P");
   leg->AddEntry(hEta_UA5_NSD,"","P");
   
   Float_t ywidth2 = 0.045*2;
   
   //TLegend *leg2 = new TLegend(0.38,0.27,0.81,0.27+ywidth2,"","brNDC");
   TLegend *leg2 = new TLegend(0.31,0.21,0.82,0.21+ywidth,NULL,"brNDC");

   leg2->SetMargin(0.5);
   leg2->SetBorderSize(0);
   leg2->SetTextFont(62);
   leg2->SetLineColor(1);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(0);
   //leg->SetFillStyle(1001);
   leg2->SetFillStyle(0);
   leg2->SetTextSize(0.033);
   leg2->SetHeader("     2.36 TeV");
   leg2->AddEntry(hMeasuredFinal236,"","P");
   leg2->AddEntry(halice_236,"","P"); 
   leg2->AddEntry(hEta_UA5_NSD,"","");
   //leg2->SetHeader("     7 TeV");
   //leg2->AddEntry(hMeasuredFinal236,"CMS NSD","P");
   //leg2->AddEntry(hEta_ALICE_NSD,"ALICE NSD","");
   //leg2->AddEntry(hEta_UA5_NSD,"UA5 NSD","");
   
   //TLegend *leg3 = new TLegend(0.50,0.21,0.99,0.21+ywidth,NULL,"brNDC");
   TLegend *leg3 = new TLegend(0.3,0.21,0.8,0.21+ywidth,NULL,"brNDC");  
   //leg3->SetMargin(0.5);
   leg3->SetMargin(0.4); 
   leg3->SetBorderSize(0);
   leg3->SetTextFont(62);
   leg3->SetLineColor(1);
   leg3->SetLineStyle(1);
   leg3->SetLineWidth(1);
   leg3->SetFillColor(0);
   leg3->SetFillStyle(0);
   leg3->SetTextSize(0.033);
   //leg3->SetHeader("     7 TeV");
   leg3->AddEntry(hMeasuredFinal7,"CMS NSD","P");
   leg3->AddEntry(hEta_ALICE_NSD,"ALICE NSD","P");
   leg3->AddEntry(hEta_UA5_NSD,"UA5 NSD","P");


   leg3->Draw();
   //leg2->Draw();
   //leg->Draw();

   Float_t tsize = 0.035;

   TLatex *   tex = new TLatex(-2.7,3.05,"0.9 TeV");
   tex->SetLineWidth(2);
   tex->SetTextSize(tsize);
   tex->Draw();

   TLatex *   tex2 = new TLatex(-2.7,4.2,"2.36 TeV");
   tex2->SetLineWidth(2);
   tex2->SetTextSize(tsize);
   tex2->Draw();
   
   TLatex *   tex3 = new TLatex(-2.7,5.6,"7 TeV");
   tex3->SetLineWidth(2);
   tex3->SetTextSize(tsize);
   tex3->Draw();



   printFinalCanvases(MyCanvas,"dNdeta_ThreeMethodsCombined",0,2);
}
