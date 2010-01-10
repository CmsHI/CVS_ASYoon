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

   Double_t xAxis7[13] = {-3, -2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4, 3};
   TH1 *hMeasuredFinal3 = new TH1D("hMeasuredFinal3","",12, xAxis7);
   
   hMeasuredFinal3->GetXaxis()->SetRange(1,13);

   hMeasuredFinal3->SetMinimum(0);
   hMeasuredFinal3->SetMaximum(5.5);

   hMeasuredFinal3->SetBinContent(2,3.6853);  // -2.4 to -2.0 
   hMeasuredFinal3->SetBinContent(3,3.7034); //-2 to -1.5 
   hMeasuredFinal3->SetBinContent(4,3.7568);        // -1.5 to -1.0 
   hMeasuredFinal3->SetBinContent(5,3.6523); // -1.0 to -0.5
   hMeasuredFinal3->SetBinContent(6,3.4984);        // -0.5 to 0

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
   hMeasuredFinal3->GetYaxis()->SetNdivisions(1005);

   hMeasuredFinal3->SetMarkerColor(2);
   hMeasuredFinal3->SetMarkerStyle(20);
   //hMeasuredFinal3->SetMarkerSize(1.8); // use rootlogon size
   
   hMeasuredFinal3->Draw("pz");

   // Clone above for systematic band!
   /// ==================================================== Weighted mean of all three method! 
   //Double_t xAxis8[13] = {-3, -2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4, 3};
   TH1D * hMeasuredFinal4 = (TH1D*)hMeasuredFinal3->Clone("hMeasuredFinal4");
   double sysError = 0.0603;
   TGraph *gErrorBand = GetErrorBand((TH1F*)hMeasuredFinal4,sysError,sysError,0.25); 
   gErrorBand->Draw("f");

   hMeasuredFinal3->Draw("pzsame");  


   /// ==================================================== CMS 2.36 GeV
   TH1F *hMeasuredFinal236 = (TH1F*)hMeasuredFinal3->Clone("hMeasuredFinal236");
   hMeasuredFinal236->GetXaxis()->SetRange(3,10);
   hMeasuredFinal236->SetMarkerColor(kBlue);

   //hMeasuredFinal236->SetBinContent(2,3.6853);  // -2.4 to -2.0 
   hMeasuredFinal236->SetBinContent(3,4.32647); //-2 to -1.5 
   hMeasuredFinal236->SetBinContent(4,4.4065);        // -1.5 to -1.0 
   hMeasuredFinal236->SetBinContent(5,4.3577); // -1.0 to -0.5
   hMeasuredFinal236->SetBinContent(6,4.23402);        // -0.5 to 0

   hMeasuredFinal236->SetBinContent(7,hMeasuredFinal236->GetBinContent(6)); // 0 to 0.5 
   hMeasuredFinal236->SetBinContent(8,hMeasuredFinal236->GetBinContent(5)); // 0.5 to 1.0
   hMeasuredFinal236->SetBinContent(9,hMeasuredFinal236->GetBinContent(4)); // 1.0 to 1.5 
   hMeasuredFinal236->SetBinContent(10,hMeasuredFinal236->GetBinContent(3)); // 1.5 to 2.0 
   //hMeasuredFinal236->SetBinContent(11,hMeasuredFinal236->GetBinContent(2)); // 2.0 to 2.4 

   /// --- draw the error bands ---
   TH1F *hMeasuredFinal236EB = (TH1F*)hMeasuredFinal236->Clone("hMeasuredFinal236EB");
   hMeasuredFinal236EB->SetBinContent(2,4.32647);
   hMeasuredFinal236EB->SetBinContent(11,4.32647);
   TGraph *gErrorBand236 = GetErrorBand((TH1F*)hMeasuredFinal236EB,sysError,sysError,0.25);
   gErrorBand236->Draw("f");

   hMeasuredFinal236->Draw("pzsame");



   /// ====================================================  ALICE 
   Double_t xAxis9[8] = {-1.4, -1.0, -0.6, -0.2, 0.2, 0.6, 1.0, 1.4};
   TH1 *hEta_ALICE_NSD = new TH1D("hEta_ALICE_NSD","",7, xAxis9);

   // ALICE data points! 
   /*
     -1.4    3.875   0.458
     -1.0    3.867   0.285
     -0.6    3.469   0.234 
     -0.2    3.408   0.234 
      0.2     3.624   0.234 
      0.6     3.910   0.242
      1.0     3.590   0.251 
      1.4     3.590   0.329
   */

   hEta_ALICE_NSD->SetBinContent(1,3.875);
   hEta_ALICE_NSD->SetBinContent(2,3.867);
   hEta_ALICE_NSD->SetBinContent(3,3.469);
   hEta_ALICE_NSD->SetBinContent(4,3.408);
   hEta_ALICE_NSD->SetBinContent(5,3.624);
   hEta_ALICE_NSD->SetBinContent(6,3.910);
   hEta_ALICE_NSD->SetBinContent(7,3.590);
   hEta_ALICE_NSD->SetBinContent(8,3.590);

   hEta_ALICE_NSD->SetBinError(1,0.458);
   hEta_ALICE_NSD->SetBinError(2,0.285);
   hEta_ALICE_NSD->SetBinError(3,0.234);
   hEta_ALICE_NSD->SetBinError(4,0.234);
   hEta_ALICE_NSD->SetBinError(5,0.234);
   hEta_ALICE_NSD->SetBinError(6,0.242);
   hEta_ALICE_NSD->SetBinError(7,0.251);
   hEta_ALICE_NSD->SetBinError(8,0.329);


   hEta_ALICE_NSD->SetMarkerColor(1);
   hEta_ALICE_NSD->SetMarkerStyle(20);
   hEta_ALICE_NSD->SetLineColor(kBlack);
   //hEta_ALICE_NSD->SetMarkerSize(1.5);
   hEta_ALICE_NSD->SetMarkerSize(1.25);
   hEta_ALICE_NSD->Draw("pzsame");


   /// ====================================================  UA5 Data

   TH1F* hEta_UA5_NSD = new TH1F("hEta_UA5_NSD",";#eta;dN/d#eta",50,-3,3);

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


   TLegend *leg = new TLegend(0.20,0.27,0.53,0.47,"","brNDC");   
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->SetTextSize(0.03);  
   //leg->SetHeader("    Systematic error (6% total)");
   
   leg->AddEntry(hMeasuredFinal236,"CMS NSD (2.36 TeV), three methods combined","P");
   leg->AddEntry(hMeasuredFinal3,"CMS NSD (900 GeV), three methods combined","P");
   leg->AddEntry(hEta_ALICE_NSD,"ALICE NSD (900 GeV)","P");
   leg->AddEntry(hEta_UA5_NSD,"UA5 NSD (900 GeV)","P");
   leg->Draw();

   printFinalCanvases(MyCanvas,"dNdeta_ThreeMethodsCombined",0,2);
}
