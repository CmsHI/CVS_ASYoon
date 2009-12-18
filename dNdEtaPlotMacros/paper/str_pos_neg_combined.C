#include "common.h"


void str_pos_neg_combined(){
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Tue Dec 15 18:00:56 2009) by ROOT version5.25/04

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);

   double msize = 1.5;
   int mcColor = 2;
   int dataColor = 1;

   // SIM
   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetMarkerSize(msize);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(mcColor);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,0,0.113669);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.112036);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.114463);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.0933748);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.0858148);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.0709134);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.0609069);
   gre->SetPointError(6,0.5,0);
   gre->SetPoint(7,7,0.0549009);
   gre->SetPointError(7,0.5,0);
   gre->SetPoint(8,8,0.0569734);
   gre->SetPointError(8,0.5,0);
   gre->SetPoint(9,9,0.0627454);
   gre->SetPointError(9,0.5,0);
   gre->SetPoint(10,10,0.0618134);
   gre->SetPointError(10,0.5,0);
   gre->SetPoint(11,11,0.0470987);
   gre->SetPointError(11,0.5,0);
   gre->SetPoint(12,12,0.0273554);
   gre->SetPointError(12,0.5,0);
   gre->SetPoint(13,13,0.014319);
   gre->SetPointError(13,0.5,0);
   gre->SetPoint(14,14,0.00783131);
   gre->SetPointError(14,0.5,0);
   gre->SetPoint(15,15,0.00498221);
   gre->SetPointError(15,0.5,0);
   gre->SetPoint(16,16,0.0037535);
   gre->SetPointError(16,0.5,0);
   gre->SetPoint(17,17,0.00284563);
   gre->SetPointError(17,0.5,0);
   gre->SetPoint(18,18,0.00198369);
   gre->SetPointError(18,0.5,0);
   gre->SetPoint(19,19,0.00116993);
   gre->SetPointError(19,0.5,0);
   gre->SetPoint(20,20,0.000597006);
   gre->SetPointError(20,0.5,0);
   gre->SetPoint(21,21,0.000276485);
   gre->SetPointError(21,0.5,0);
   gre->SetPoint(22,22,0.000118989);
   gre->SetPointError(22,0.5,0);
   gre->SetPoint(23,23,4.31016e-05);
   gre->SetPointError(23,0.5,0);
   gre->SetPoint(24,24,1.14356e-05);
   gre->SetPointError(24,0.5,0);
   gre->SetPoint(25,25,1.27406e-06);
   gre->SetPointError(25,0.5,0);
   gre->SetPoint(26,26,1.24316e-06);
   gre->SetPointError(26,0.5,0);
   gre->SetPoint(27,27,0);
   gre->SetPointError(27,0.5,0);
   gre->SetPoint(28,28,0);
   gre->SetPointError(28,0.5,0);
   gre->SetPoint(29,29,0);
   gre->SetPointError(29,0.5,0);

   Double_t *ydata = gre->GetY();
   Double_t *yerr = gre->GetEY();

   TH1D *Graph6 = new TH1D("Graph6","Graph6",20,-0.5,20.5);

   Graph6->SetLineColor(2);
   Graph6->SetLineWidth(2);

   Graph6->GetXaxis()->SetTitle("Number of strip hits on track");
   Graph6->GetYaxis()->SetTitle("Fraction");
   Graph6->GetXaxis()->CenterTitle();
   Graph6->GetYaxis()->CenterTitle();

   for(Int_t i = 0; i<20; i++){
      Graph6->SetBinContent(i+1,ydata[i]);
      Graph6->SetBinError(i+1,yerr[i]);
   }
   
   Graph6->SetMaximum(0.15);
   Graph6->Draw("hist");

   // DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetPoint(0,0,0.126212);
   gre->SetPointError(0,0,0.00318125);
   gre->SetPoint(1,1,0.117872);
   gre->SetPointError(1,0,0.00307434);
   gre->SetPoint(2,2,0.117952);
   gre->SetPointError(2,0,0.00307538);
   gre->SetPoint(3,3,0.0932561);
   gre->SetPointError(3,0,0.00273456);
   gre->SetPoint(4,4,0.080507);
   gre->SetPointError(4,0,0.00254078);
   gre->SetPoint(5,5,0.0728904);
   gre->SetPointError(5,0,0.00241762);
   gre->SetPoint(6,6,0.0627064);
   gre->SetPointError(6,0,0.00224238);
   gre->SetPoint(7,7,0.0555697);
   gre->SetPointError(7,0,0.00211092);
   gre->SetPoint(8,8,0.0574137);
   gre->SetPointError(8,0,0.00214565);
   gre->SetPoint(9,9,0.0601394);
   gre->SetPointError(9,0,0.00219598);
   gre->SetPoint(10,10,0.0592575);
   gre->SetPointError(10,0,0.00217982);
   gre->SetPoint(11,11,0.0428196);
   gre->SetPointError(11,0,0.00185299);
   gre->SetPoint(12,12,0.021891);
   gre->SetPointError(12,0,0.0013249);
   gre->SetPoint(13,13,0.0124292);
   gre->SetPointError(13,0,0.000998336);
   gre->SetPoint(14,14,0.0058537);
   gre->SetPointError(14,0,0.000685123);
   gre->SetPoint(15,15,0.00376878);
   gre->SetPointError(15,0,0.000549732);
   gre->SetPoint(16,16,0.00352824);
   gre->SetPointError(16,0,0.000531902);
   gre->SetPoint(17,17,0.0025659);
   gre->SetPointError(17,0,0.000453592);
   gre->SetPoint(18,18,0.00184426);
   gre->SetPointError(18,0,0.000384555);
   gre->SetPoint(19,19,0.000801861);
   gre->SetPointError(19,0,0.000253571);
   gre->SetPoint(20,20,0.000160372);
   gre->SetPointError(20,0,0.0001134);
   gre->SetPoint(21,21,0.000400924);
   gre->SetPointError(21,0,0.000179299);
   gre->SetPoint(22,22,8.01795e-05);
   gre->SetPointError(22,0,8.01795e-05);
   gre->SetPoint(23,23,0);
   gre->SetPointError(23,0,0);
   gre->SetPoint(24,24,8.01925e-05);
   gre->SetPointError(24,0,8.01925e-05);
   gre->SetPoint(25,25,0);
   gre->SetPointError(25,0,0);
   gre->SetPoint(26,26,0);
   gre->SetPointError(26,0,0);
   gre->SetPoint(27,27,0);
   gre->SetPointError(27,0,0);
   gre->SetPoint(28,28,0);
   gre->SetPointError(28,0,0);
   gre->SetPoint(29,29,0);
   gre->SetPointError(29,0,0);

   Double_t *ydata = gre->GetY();
   Double_t *yerr = gre->GetEY();

   TH1D *Graph8 = new TH1D("Graph8","Graph",20,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...
   Graph8->SetMarkerSize(msize);
   Graph8->SetMarkerStyle(20);
   Graph8->SetMarkerColor(1);
   Graph8->SetLineColor(1);
   Graph8->Draw("pzsame");
   for(Int_t i = 0; i<20; i++){
      Graph8->SetBinContent(i+1,ydata[i]);
      Graph8->SetBinError(i+1,yerr[i]);
   }
   //hack
   TH1F *Graph82 = Graph8->Clone("Graph82");
   Graph82->SetMarkerStyle(0);
   Graph82->Draw("pzsame");

   TLegend *leg = new TLegend(0.63,0.71,1.0,0.83,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.038);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetMargin(0.32);
   
   leg->AddEntry(Graph8,"Data","p");
   leg->AddEntry(Graph6,"PYTHIA D6T","l");
   leg->Draw();
   
   printFinalCanvases(MyCanvas,"strips_pos_neg");

}
