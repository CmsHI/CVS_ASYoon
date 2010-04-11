#include "common.h"

void vertex(){

//=========Macro generated from canvas: c9/
//=========  (Fri Apr  9 19:11:02 2010) by ROOT version5.22/00a

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);
   MyCanvas->Range(-28.6076,-0.01804519,22.02532,0.1022561);

   double msize = 1.5;

   int mcColor = 2;
   int dataColor = 1;

   /*
   TCanvas *c9 = new TCanvas("c9", "",825,478,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c9->Range(-28.6076,-0.02823174,22.02532,0.1599798);
   c9->SetFillColor(0);
   c9->SetBorderMode(0);
   c9->SetBorderSize(0);
   c9->SetTickx(1);
   c9->SetTicky(1);
   c9->SetLeftMargin(0.17);
   c9->SetRightMargin(0.04);
   c9->SetTopMargin(0.05);
   c9->SetBottomMargin(0.15);
   c9->SetFrameLineColor(0);
   c9->SetFrameBorderMode(0);
   c9->SetFrameLineColor(0);
   c9->SetFrameBorderMode(0);
   */

   TH1 *h2vz = new TH1F("h2vz","",50,-20,20);
   h2vz->GetXaxis()->SetRange(8,42);
   h2vz->SetBinContent(14,5.607487e-06);
   h2vz->SetBinContent(15,7.570108e-05);
   h2vz->SetBinContent(16,0.0002102808);
   h2vz->SetBinContent(17,0.0008607493);
   h2vz->SetBinContent(18,0.002380378);
   h2vz->SetBinContent(19,0.00647104);
   h2vz->SetBinContent(20,0.01416451);
   h2vz->SetBinContent(21,0.02864865);
   h2vz->SetBinContent(22,0.05168701);
   h2vz->SetBinContent(23,0.0815609);
   h2vz->SetBinContent(24,0.1105628);
   h2vz->SetBinContent(25,0.1341563);
   h2vz->SetBinContent(26,0.1427666);
   h2vz->SetBinContent(27,0.1336012);
   h2vz->SetBinContent(28,0.1110899);
   h2vz->SetBinContent(29,0.07903192);
   h2vz->SetBinContent(30,0.05106739);
   h2vz->SetBinContent(31,0.02855613);
   h2vz->SetBinContent(32,0.01364582);
   h2vz->SetBinContent(33,0.006072909);
   h2vz->SetBinContent(34,0.002329911);
   h2vz->SetBinContent(35,0.000765422);
   h2vz->SetBinContent(36,0.000218692);
   h2vz->SetBinContent(37,5.607487e-05);
   h2vz->SetBinContent(38,1.121497e-05);
   h2vz->SetBinContent(39,2.803744e-06);
   h2vz->SetBinError(14,3.965092e-06);
   h2vz->SetBinError(15,1.456868e-05);
   h2vz->SetBinError(16,2.428113e-05);
   h2vz->SetBinError(17,4.912556e-05);
   h2vz->SetBinError(18,8.169437e-05);
   h2vz->SetBinError(19,0.0001346965);
   h2vz->SetBinError(20,0.0001992829);
   h2vz->SetBinError(21,0.000283414);
   h2vz->SetBinError(22,0.0003806798);
   h2vz->SetBinError(23,0.0004782006);
   h2vz->SetBinError(24,0.0005567673);
   h2vz->SetBinError(25,0.0006133025);
   h2vz->SetBinError(26,0.0006326776);
   h2vz->SetBinError(27,0.0006120322);
   h2vz->SetBinError(28,0.0005580929);
   h2vz->SetBinError(29,0.0004707284);
   h2vz->SetBinError(30,0.0003783911);
   h2vz->SetBinError(31,0.0002829559);
   h2vz->SetBinError(32,0.0001956001);
   h2vz->SetBinError(33,0.0001304871);
   h2vz->SetBinError(34,8.082371e-05);
   h2vz->SetBinError(35,4.632545e-05);
   h2vz->SetBinError(36,2.476199e-05);
   h2vz->SetBinError(37,1.253872e-05);
   h2vz->SetBinError(38,5.607487e-06);
   h2vz->SetBinError(39,2.803744e-06);

   h2vz->SetFillColor(mcColor);
   h2vz->SetLineColor(mcColor);
   h2vz->SetLineStyle(0);
   h2vz->SetMarkerColor(mcColor);
   h2vz->SetMarkerStyle(25);
   h2vz->SetMarkerSize(msize);

   h2vz->GetYaxis()->SetNdivisions(405);
   
   h2vz->GetXaxis()->SetTitle("z_{PV} [cm]");
   h2vz->GetYaxis()->SetTitle("Fraction of events");

   h2vz->GetXaxis()->CenterTitle();
   h2vz->GetYaxis()->CenterTitle();
   //h2vz->SetAxisRange(0,0.13,"Y");

   h2vz->Draw("hist");
   //TH1 *hvz11 = hvz1->Clone("hvz11");
   //h2vz11->SetMarkerStyle(0);

   
   /*   
   h2vz->SetEntries(356666);
   h2vz->SetFillColor(1);
   h2vz->SetFillStyle(0);
   h2vz->SetLineColor(2);
   h2vz->SetLineStyle(0);
   h2vz->SetMarkerColor(2);
   h2vz->SetMarkerStyle(25);
   h2vz->SetMarkerSize(0.7);
   h2vz->GetXaxis()->SetTitle("v_{z} (cm)");
   h2vz->GetXaxis()->SetLabelFont(42);
   h2vz->GetXaxis()->SetLabelOffset(0.01);
   h2vz->GetXaxis()->SetLabelSize(0.045);
   h2vz->GetXaxis()->SetTitleSize(0.055);
   h2vz->GetXaxis()->SetTitleFont(42);
   h2vz->GetYaxis()->SetTitle("Arbitrary normalization");
   h2vz->GetYaxis()->SetLabelFont(42);
   h2vz->GetYaxis()->SetLabelOffset(0.01);
   h2vz->GetYaxis()->SetLabelSize(0.045);
   h2vz->GetYaxis()->SetTitleSize(0.055);
   h2vz->GetYaxis()->SetTitleOffset(1.3);
   h2vz->GetYaxis()->SetTitleFont(42);
   h2vz->GetZaxis()->SetLabelFont(42);
   h2vz->GetZaxis()->SetLabelSize(0.045);
   h2vz->GetZaxis()->SetTitleFont(42);
   h2vz->Draw("hist");
   */
   
   TH1 *hvz = new TH1F("hvz","",50,-20,20);
   hvz->SetBinContent(11,5.021442e-06);
   hvz->SetBinContent(13,5.021442e-06);
   hvz->SetBinContent(14,2.510721e-05);
   hvz->SetBinContent(15,3.012865e-05);
   hvz->SetBinContent(16,0.0001657076);
   hvz->SetBinContent(17,0.0005172085);
   hvz->SetBinContent(18,0.001606861);
   hvz->SetBinContent(19,0.004880841);
   hvz->SetBinContent(20,0.01321643);
   hvz->SetBinContent(21,0.02989264);
   hvz->SetBinContent(22,0.05313187);
   hvz->SetBinContent(23,0.08499794);
   hvz->SetBinContent(24,0.1126711);
   hvz->SetBinContent(25,0.1366435);
   hvz->SetBinContent(26,0.1426792);
   hvz->SetBinContent(27,0.1327669);
   hvz->SetBinContent(28,0.1100047);
   hvz->SetBinContent(29,0.08051379);
   hvz->SetBinContent(30,0.05038012);
   hvz->SetBinContent(31,0.02704046);
   hvz->SetBinContent(32,0.01218704);
   hvz->SetBinContent(33,0.004584576);
   hvz->SetBinContent(34,0.001421068);
   hvz->SetBinContent(35,0.0004519298);
   hvz->SetBinContent(36,0.000125536);
   hvz->SetBinContent(37,4.017153e-05);
   hvz->SetBinContent(38,1.004288e-05);
   hvz->SetBinContent(40,5.021442e-06);
   hvz->SetBinError(11,5.021442e-06);
   hvz->SetBinError(13,5.021442e-06);
   hvz->SetBinError(14,1.122828e-05);
   hvz->SetBinError(15,1.229997e-05);
   hvz->SetBinError(16,2.884599e-05);
   hvz->SetBinError(17,5.096207e-05);
   hvz->SetBinError(18,8.982628e-05);
   hvz->SetBinError(19,0.0001565531);
   hvz->SetBinError(20,0.0002576151);
   hvz->SetBinError(21,0.0003874328);
   hvz->SetBinError(22,0.0005165255);
   hvz->SetBinError(23,0.0006533087);
   hvz->SetBinError(24,0.0007521778);
   hvz->SetBinError(25,0.00082834);
   hvz->SetBinError(26,0.0008464369);
   hvz->SetBinError(27,0.0008165055);
   hvz->SetBinError(28,0.0007432242);
   hvz->SetBinError(29,0.0006358422);
   hvz->SetBinError(30,0.000502972);
   hvz->SetBinError(31,0.0003684862);
   hvz->SetBinError(32,0.0002473793);
   hvz->SetBinError(33,0.0001517273);
   hvz->SetBinError(34,8.447372e-05);
   hvz->SetBinError(35,4.763758e-05);
   hvz->SetBinError(36,2.510721e-05);
   hvz->SetBinError(37,1.420278e-05);
   hvz->SetBinError(38,7.101391e-06);
   hvz->SetBinError(40,5.021442e-06);


   hvz->SetLineColor(dataColor);
   hvz->SetMarkerColor(dataColor);
   hvz->SetMarkerStyle(20);
   hvz->SetMarkerSize(msize);
   hvz->Draw("pzsame");

   /*
   hvz->SetEntries(199146);
   hvz->SetFillColor(1);
   hvz->SetFillStyle(0);
   hvz->SetLineStyle(0);
   hvz->SetMarkerStyle(20);
   hvz->SetMarkerSize(0.7);
   hvz->GetXaxis()->SetTitle("v_{z} (cm)");
   hvz->GetXaxis()->SetLabelFont(42);
   hvz->GetXaxis()->SetLabelOffset(0.01);
   hvz->GetXaxis()->SetLabelSize(0.045);
   hvz->GetXaxis()->SetTitleSize(0.055);
   hvz->GetXaxis()->SetTitleFont(42);
   hvz->GetYaxis()->SetTitle("Arbitrary normalization");
   hvz->GetYaxis()->SetLabelFont(42);
   hvz->GetYaxis()->SetLabelOffset(0.01);
   hvz->GetYaxis()->SetLabelSize(0.045);
   hvz->GetYaxis()->SetTitleSize(0.055);
   hvz->GetYaxis()->SetTitleOffset(1.3);
   hvz->GetYaxis()->SetTitleFont(42);
   hvz->GetZaxis()->SetLabelFont(42);
   hvz->GetZaxis()->SetLabelSize(0.045);
   hvz->GetZaxis()->SetTitleFont(42);
   hvz->Draw("same");
   */

   //TLegend *leg = new TLegend(0.1818182,0.7123656,0.5833333,0.922043,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.6154,0.67,.9176,0.87,NULL,"brNDC");
   TLegend *leg = new TLegend(0.65,0.67,.956,0.87,NULL,"brNDC");    
   
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

   /*
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   */
   TLegendEntry *entry=leg->AddEntry("hvz","Data 7 TeV","p");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("h2vz","PYTHIA 7 TeV","l");
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(0.7);
   leg->Draw();


   //c9->Modified();
   //c9->cd();
   //c9->SetSelected(c9);

   printFinalCanvases(MyCanvas,"vertex");

}
