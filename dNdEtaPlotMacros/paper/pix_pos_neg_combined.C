#include "common.h"


void pix_pos_neg_combined(){
	//=========Macro generated from canvas: MyCanvas/My Canvas
	//=========  (Tue Dec 15 18:00:56 2009) by ROOT version5.25/04
	
	gROOT->Reset();
	gROOT->ProcessLine(".x dndeta_rootlogon.C");
	TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);
	
	bool do2TeV = false;
	double msize = 1.8;

	TH1D *hDist = new TH1D("hDist","hDist",20,1.5,5.5);
	hDist->SetMinimum(0);
	hDist->SetMaximum(1);
	hDist->SetFillColor(1);
	hDist->SetFillStyle(0);
	hDist->SetLineStyle(0);
	hDist->SetMarkerStyle(20);
	hDist->SetMarkerSize(1.25);
	hDist->GetXaxis()->SetTitle("Number of pixel hits on track");
	hDist->GetXaxis()->SetLabelFont(42);
	hDist->GetXaxis()->SetLabelOffset(0.01);
	hDist->GetXaxis()->SetLabelSize(0.045);
	hDist->GetXaxis()->SetTitleSize(0.055);
	hDist->GetXaxis()->SetTitleFont(42);
	hDist->GetYaxis()->SetTitle("Fraction of tracks");
	hDist->GetYaxis()->SetLabelFont(42);
	hDist->GetYaxis()->SetLabelOffset(0.01);
	hDist->GetYaxis()->SetLabelSize(0.045);
	hDist->GetYaxis()->SetTitleSize(0.055);
	hDist->GetYaxis()->SetTitleOffset(1.3);
	hDist->GetYaxis()->SetTitleFont(42);
	hDist->GetZaxis()->SetLabelFont(42);
	hDist->GetZaxis()->SetLabelSize(0.045);
	hDist->GetZaxis()->SetTitleFont(42);
	hDist->GetXaxis()->CenterTitle();
	hDist->GetYaxis()->CenterTitle();
hDist->GetXaxis()->SetNdivisions(4);

	hDist->Draw("");

   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.25);
   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.00063215);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.0888403);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.759757);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.141622);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.00894177);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.000207145);
   gre->SetPointError(6,0.5,0);
   gre->SetPoint(7,7,0);
   gre->SetPointError(7,0.5,0);
   gre->SetPoint(8,8,0);
   gre->SetPointError(8,0.5,0);
   gre->SetPoint(9,9,0);
   gre->SetPointError(9,0.5,0);
   gre->SetPoint(10,10,0);
   gre->SetPointError(10,0.5,0);
   gre->SetPoint(11,11,0);
   gre->SetPointError(11,0.5,0);
   gre->SetPoint(12,12,0);
   gre->SetPointError(12,0.5,0);
   gre->SetPoint(13,13,0);
   gre->SetPointError(13,0.5,0);
   gre->SetPoint(14,14,0);
   gre->SetPointError(14,0.5,0);
   gre->SetPoint(15,15,0);
   gre->SetPointError(15,0.5,0);
   gre->SetPoint(16,16,0);
   gre->SetPointError(16,0.5,0);
   gre->SetPoint(17,17,0);
   gre->SetPointError(17,0.5,0);
   gre->SetPoint(18,18,0);
   gre->SetPointError(18,0.5,0);
   gre->SetPoint(19,19,0);
   gre->SetPointError(19,0.5,0);
   gre->SetPoint(20,20,0);
   gre->SetPointError(20,0.5,0);
   gre->SetPoint(21,21,0);
   gre->SetPointError(21,0.5,0);
   gre->SetPoint(22,22,0);
   gre->SetPointError(22,0.5,0);
   gre->SetPoint(23,23,0);
   gre->SetPointError(23,0.5,0);
   gre->SetPoint(24,24,0);
   gre->SetPointError(24,0.5,0);
   gre->SetPoint(25,25,0);
   gre->SetPointError(25,0.5,0);
   gre->SetPoint(26,26,0);
   gre->SetPointError(26,0.5,0);
   gre->SetPoint(27,27,0);
   gre->SetPointError(27,0.5,0);
   gre->SetPoint(28,28,0);
   gre->SetPointError(28,0.5,0);
   gre->SetPoint(29,29,0);
   gre->SetPointError(29,0.5,0);
//   gre->Draw("hist");
   	Double_t *ydata = gre->GetY();
	Double_t *yerr = gre->GetEY();

	TH1D *Graph6 = new TH1D("Graph6","Graph6",6,-0.5,5.5);
	
	Graph6->SetLineColor(2);
	Graph6->SetLineWidth(2);
	

	Graph6->GetXaxis()->CenterTitle();
	Graph6->GetYaxis()->CenterTitle();
	
	for(Int_t i = 0; i<6; i++){
		Graph6->SetBinContent(i+1,ydata[i]);
		Graph6->SetBinError(i+1,yerr[i]);
	}
	
//	Graph6->SetMaximum(0.15);
	Graph6->Draw("hist same");
	
	
	gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(1.25);
   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1,0.000781103);
   gre->SetPointError(1,0,4.42213e-05);
   gre->SetPoint(2,2,0.0897718);
   gre->SetPointError(2,0,0.000474075);
   gre->SetPoint(3,3,0.754393);
   gre->SetPointError(3,0,0.00137428);
   gre->SetPoint(4,4,0.145788);
   gre->SetPointError(4,0,0.000604141);
   gre->SetPoint(5,5,0.00887003);
   gre->SetPointError(5,0,0.000149018);
   gre->SetPoint(6,6,0.000393055);
   gre->SetPointError(6,0,3.13692e-05);
   gre->SetPoint(7,7,2.50354e-06);
   gre->SetPointError(7,0,2.50354e-06);
   gre->SetPoint(8,8,0);
   gre->SetPointError(8,0,0);
   gre->SetPoint(9,9,0);
   gre->SetPointError(9,0,0);
   gre->SetPoint(10,10,0);
   gre->SetPointError(10,0,0);
   gre->SetPoint(11,11,0);
   gre->SetPointError(11,0,0);
   gre->SetPoint(12,12,0);
   gre->SetPointError(12,0,0);
   gre->SetPoint(13,13,0);
   gre->SetPointError(13,0,0);
   gre->SetPoint(14,14,0);
   gre->SetPointError(14,0,0);
   gre->SetPoint(15,15,0);
   gre->SetPointError(15,0,0);
   gre->SetPoint(16,16,0);
   gre->SetPointError(16,0,0);
   gre->SetPoint(17,17,0);
   gre->SetPointError(17,0,0);
   gre->SetPoint(18,18,0);
   gre->SetPointError(18,0,0);
   gre->SetPoint(19,19,0);
   gre->SetPointError(19,0,0);
   gre->SetPoint(20,20,0);
   gre->SetPointError(20,0,0);
   gre->SetPoint(21,21,0);
   gre->SetPointError(21,0,0);
   gre->SetPoint(22,22,0);
   gre->SetPointError(22,0,0);
   gre->SetPoint(23,23,0);
   gre->SetPointError(23,0,0);
   gre->SetPoint(24,24,0);
   gre->SetPointError(24,0,0);
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
   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,0,31.9);
   Graph1->SetMinimum(0);
   Graph1->SetMaximum(0.831344);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->SetFillColor(1);
   Graph1->SetFillStyle(0);
   Graph1->SetLineStyle(0);
   Graph1->SetMarkerStyle(20);
   Graph1->SetMarkerSize(1.25);
   Graph1->GetXaxis()->SetLabelFont(42);
   Graph1->GetXaxis()->SetLabelOffset(0.01);
   Graph1->GetXaxis()->SetLabelSize(0.045);
   Graph1->GetXaxis()->SetTitleSize(0.055);
   Graph1->GetXaxis()->SetTitleFont(42);
   Graph1->GetYaxis()->SetLabelFont(42);
   Graph1->GetYaxis()->SetLabelOffset(0.01);
   Graph1->GetYaxis()->SetLabelSize(0.045);
   Graph1->GetYaxis()->SetTitleSize(0.055);
   Graph1->GetYaxis()->SetTitleOffset(1.35);
   Graph1->GetYaxis()->SetTitleFont(42);
   Graph1->GetZaxis()->SetLabelFont(42);
   Graph1->GetZaxis()->SetLabelSize(0.045);
   Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph1);
   
//   gre->Draw("p");
	
	Double_t *ydata = gre->GetY();
	Double_t *yerr = gre->GetEY();
	
	TH1D *Graph8 = new TH1D("Graph8","Graph",6,-0.5,5.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...
	Graph8->SetMarkerSize(msize);
	Graph8->SetMarkerStyle(20);
	Graph8->SetMarkerColor(1);
	Graph8->SetLineColor(1);
	for(Int_t i = 0; i<6; i++){
		Graph8->SetBinContent(i+1,ydata[i]);
		Graph8->SetBinError(i+1,yerr[i]);
   }
	Graph8->Draw("pzsame");

	
	
	
	
	
	TLegend *leg = new TLegend(0.61,0.77,.91,0.87,NULL,"brNDC");
	
	leg->SetBorderSize(0);
	leg->SetTextFont(62);
	leg->SetTextSize(0.038);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->SetMargin(0.32);
	
	TLegendEntry *entry=leg->AddEntry("","Data 0.9 TeV","p");
	entry->SetLineColor(1);
	entry->SetLineWidth(1);
	entry->SetMarkerColor(1);
	entry->SetMarkerStyle(20);
	entry->SetMarkerSize(msize);
	
	entry=leg->AddEntry("","Pythia 0.9 TeV","l");
	entry->SetLineWidth(2);
	entry->SetLineColor(2);
	leg->Draw();

	
	printFinalCanvases(MyCanvas,"pixels_pos_neg");
	
	
}
