// For plotting
#include "GraphErrorsBand.h"
// Standard library
#include <math.h>
#include <iostream.h>
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
void dNdEta_ThreeMethodsCombined_v2_BU_Compile(){
//=========Macro generated from canvas: MyCanvas/MyCanvas
//=========  (Thu Dec 10 11:52:00 2009) by ROOT version5.22/00d

   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");

   gStyle->SetPadLeftMargin(0.18);
   gStyle->SetTitleYOffset(1.1);
   gStyle->SetTitleXOffset(1.1);
   gStyle->SetTitleXSize(.060);
   gStyle->SetTitleYSize(.060);

   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,650,600);
   
   MyCanvas->Range(-4.9,-0.8560975,3.85,5.729268);
   
   /// ==================================================== Weighted mean of all three method!

   Double_t xAxis7[13] = {-3, -2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4, 3};
   TH1 *hMeasuredFinal3 = new TH1D("hMeasuredFinal3","",12, xAxis7);
   
   hMeasuredFinal3->GetXaxis()->SetRange(1,13);

   hMeasuredFinal3->SetMinimum(0);
   hMeasuredFinal3->SetMaximum(5.0);

   hMeasuredFinal3->SetBinContent(2,3.69453);  // -2.4 to -2.0 
   hMeasuredFinal3->SetBinContent(3,3.776349117); //-2 to -1.5 
   hMeasuredFinal3->SetBinContent(4,3.795637495);        // -1.5 to -1.0 
   hMeasuredFinal3->SetBinContent(5,3.684385446); // -1.0 to -0.5
   hMeasuredFinal3->SetBinContent(6,3.468729064);        // -0.5 to 0

   hMeasuredFinal3->SetBinContent(7,3.468729064); // 0 to 0.5 
   hMeasuredFinal3->SetBinContent(8,3.684385446); // 0.5 to 1.0
   hMeasuredFinal3->SetBinContent(9,3.795637495); // 1.0 to 1.5 
   hMeasuredFinal3->SetBinContent(10,3.776349117); // 1.5 to 2.0 
   hMeasuredFinal3->SetBinContent(11,3.69453); // 2.0 to 2.4 

   // Systematic error of 6.0%        
   /*
   hMeasuredFinal3->SetBinError(2,0.0);
   hMeasuredFinal3->SetBinError(3,0.0);
   hMeasuredFinal3->SetBinError(4,0.0);
   hMeasuredFinal3->SetBinError(5,0.0);
   hMeasuredFinal3->SetBinError(6,0.0);

   hMeasuredFinal3->SetBinError(7,0.0);
   hMeasuredFinal3->SetBinError(8,0.0);
   hMeasuredFinal3->SetBinError(9,0.0);
   hMeasuredFinal3->SetBinError(10,0.0);
   hMeasuredFinal3->SetBinError(11,0.0);
   */

   // Systematic error of 6.0% 
   /*
   hMeasuredFinal3->SetBinError(2,0.2216718);
   hMeasuredFinal3->SetBinError(3,0.226580947);
   hMeasuredFinal3->SetBinError(4,0.22773825);
   hMeasuredFinal3->SetBinError(5,0.221063127);
   hMeasuredFinal3->SetBinError(6,0.208123744);

   hMeasuredFinal3->SetBinError(7,0.208123744);
   hMeasuredFinal3->SetBinError(8,0.221063127);
   hMeasuredFinal3->SetBinError(9,0.22773825);
   hMeasuredFinal3->SetBinError(10,0.226580947);
   hMeasuredFinal3->SetBinError(11,0.2216718);
   */
   hMeasuredFinal3->GetYaxis()->SetTitle("dN/d#eta");
   hMeasuredFinal3->GetXaxis()->SetTitle("#eta");
   hMeasuredFinal3->GetXaxis()->CenterTitle();
   hMeasuredFinal3->GetYaxis()->CenterTitle();


   hMeasuredFinal3->GetXaxis()->SetNdivisions(405);
   hMeasuredFinal3->GetYaxis()->SetNdivisions(1005);


   hMeasuredFinal3->SetMarkerColor(2);
   hMeasuredFinal3->SetMarkerStyle(20);
   hMeasuredFinal3->SetMarkerSize(1.8);
   
   hMeasuredFinal3->Draw("pz");

   // Clone above for systematic band!
   /// ==================================================== Weighted mean of all three method! 
   Double_t xAxis8[13] = {-3, -2.4, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.4, 3};
   TH1 *hMeasuredFinal4 = new TH1D("hMeasuredFinal4","",12, xAxis8);

   hMeasuredFinal4->SetMinimum(0);
   hMeasuredFinal4->SetMaximum(5.0);


   hMeasuredFinal4->SetBinContent(2,3.69453);  // -2.4 to -2.0 
   hMeasuredFinal4->SetBinContent(3,3.731267249); //-2 to -1.5 
   hMeasuredFinal4->SetBinContent(4,3.806498985);        // -1.5 to -1.0
   hMeasuredFinal4->SetBinContent(5,3.705663267); // -1.0 to -0.5 
   hMeasuredFinal4->SetBinContent(6,3.516000083);        // -0.5 to 0 

   hMeasuredFinal4->SetBinContent(7,3.516000083); // 0 to 0.5 
   hMeasuredFinal4->SetBinContent(8,3.705663267); // 0.5 to 1.0
   hMeasuredFinal4->SetBinContent(9,3.806498985); // 1.0 to 1.5 
   hMeasuredFinal4->SetBinContent(10,3.731267249); // 1.5 to 2.0 
   hMeasuredFinal4->SetBinContent(11,3.69453); // 2.0 to 2.4

   // Systematic error of 6.0% 
   hMeasuredFinal4->SetBinError(2,0.2216718);
   hMeasuredFinal4->SetBinError(3,0.223876035);
   hMeasuredFinal4->SetBinError(4,0.228389939);
   hMeasuredFinal4->SetBinError(5,0.222339796);
   hMeasuredFinal4->SetBinError(6,0.210960005);

   hMeasuredFinal4->SetBinError(7,0.210960005);
   hMeasuredFinal4->SetBinError(8,0.222339796);
   hMeasuredFinal4->SetBinError(9,0.228389939);
   hMeasuredFinal4->SetBinError(10,0.223876035);
   hMeasuredFinal4->SetBinError(11,0.2216718);
   ////////


   /*
   double systematicError900GeV[13] = 
      {0.129,0.129,0.129,0.088,0.082,0.082,0.079,0.079,0.082,0.082,0.088,0.129,0.129};

   double systematicError10TeV[13] = 
      {0.129,0.132,0.132,0.093,0.085,0.084,0.083,0.083,0.084,0.085,0.093,0.132,0.132};
   */

   double systematicErrorUp[13] =   
      {0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06};
      //{0,0.2216718,0.226580947,0.22773825,0.221063127,0.208123744,0.208123744,0.221063127,0.22773825,0.226580947,0.2216718,0};
   double systematicErrorDown[13] =
      {0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06,0.06};
      //{0,0.2216718,0.226580947,0.22773825,0.221063127,0.208123744,0.208123744,0.221063127,0.22773825,0.226580947,0.2216718,0};



   TGraph *gErrorBand;
   
   gErrorBand = GetErrorBand((TH1F*)hMeasuredFinal4,systematicErrorUp,systematicErrorDown,0.25); 

   //hMeasuredFinal3->Draw("pz");     
   gErrorBand->Draw("f");

   hMeasuredFinal3->Draw("pzsame");  


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


   hEta_ALICE_NSD->SetMarkerColor(4);
   hEta_ALICE_NSD->SetMarkerStyle(24);
   hEta_ALICE_NSD->SetLineColor(4);
   //hEta_ALICE_NSD->SetMarkerSize(1.5);
   hEta_ALICE_NSD->SetMarkerSize(1.0);
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
   hEta_UA5_NSD->SetMarkerSize(1.0);
   hEta_UA5_NSD->Draw("psame");


   TLatex *tex = new TLatex(2.2,4.61,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   //TLatex *tex2 = new TLatex(-2.8,4.61,"#sqrt{s}=900 GeV, NSD");
   TLatex *tex2 = new TLatex(-2.8,4.61,"#sqrt{s}=900 GeV");
   tex2->SetTextSize(0.04);
   tex2->SetLineWidth(2);
   tex2->Draw();


   //TLegend *leg = new TLegend(0.27,0.19,0.72,0.50,NULL,"brNDC"); 
   //TLegend *leg = new TLegend(0.27,0.23,0.72,0.42,NULL,"brNDC");       
   //TLegend *leg = new TLegend(0.22,0.22,0.67,0.41,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.28,0.22,0.73,0.41,NULL,"brNDC");
   TLegend *leg = new TLegend(0.22,0.215,0.67,0.41,NULL,"brNDC");   
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   //leg->SetTextSize(0.04);
   leg->SetTextSize(0.037);  
   //leg->SetHeader("    Systematic error (6% total)");
   

   TLegendEntry *entry=leg->AddEntry("","CMS NSD, all three methods combined","P");
   entry->SetLineColor(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.8);


   entry=leg->AddEntry("","ALICE NSD","P");
   entry->SetLineColor(4);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.8);


   entry=leg->AddEntry("","UA5 NSD","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.8);

   /*
   entry=leg->AddEntry("","ALICE NSD","P");
   entry->SetLineColor(4);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.8);
   */
   /*
   entry=leg->AddEntry("","CMS, all three methods combined","P"); 
   //entry=leg->AddEntry("","CMS NSD","P");
   entry->SetLineColor(1);               
   entry->SetMarkerColor(2); 
   entry->SetMarkerStyle(20); 
   entry->SetMarkerSize(1.8);            
   */
   leg->Draw();

   /*
   entry=leg->AddEntry("","Hit counting, 3 layer averaged","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.8);

   //entry=leg->AddEntry("corr_result_2_all","Rec. dN/d#eta, 2. layer","P");
   entry=leg->AddEntry("","Tracklet, 3 combinations averaged","P"); 
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   //entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.8);

   entry=leg->AddEntry("","Full tracking","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.8);
   */

   //leg->Draw();

   //MyCanvas->Print("dNdeta-900GeV_cluster_avg_tracklet_avg.eps");
   //MyCanvas->Print("dNdeta-900GeV_cluster_avg_tracklet_avg.pdf");
   //MyCanvas->Print("dNdeta-900GeV_cluster_avg_tracklet_avg.gif");


   //MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.eps");   
   //MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.gif");
   //MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.vpdf");



   MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.eps");  
   MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.gif");                                                                                                                                                   
   MyCanvas->Print("dNdeta_ThreeMethodsCombined_v2.pdf");


}
