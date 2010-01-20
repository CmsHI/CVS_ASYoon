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
	gre->SetPoint(0,0,0.114053);
	gre->SetPointError(0,0.5,0);
	gre->SetPoint(1,1,0.112188);
	gre->SetPointError(1,0.5,0);
	gre->SetPoint(2,2,0.114834);
	gre->SetPointError(2,0.5,0);
	gre->SetPoint(3,3,0.0935118);
	gre->SetPointError(3,0.5,0);
	gre->SetPoint(4,4,0.0856736);
	gre->SetPointError(4,0.5,0);
	gre->SetPoint(5,5,0.0707282);
	gre->SetPointError(5,0.5,0);
	gre->SetPoint(6,6,0.0606507);
	gre->SetPointError(6,0.5,0);
	gre->SetPoint(7,7,0.0547376);
	gre->SetPointError(7,0.5,0);
	gre->SetPoint(8,8,0.0569292);
	gre->SetPointError(8,0.5,0);
	gre->SetPoint(9,9,0.0625781);
	gre->SetPointError(9,0.5,0);
	gre->SetPoint(10,10,0.0617174);
	gre->SetPointError(10,0.5,0);
	gre->SetPoint(11,11,0.0470994);
	gre->SetPointError(11,0.5,0);
	gre->SetPoint(12,12,0.0273253);
	gre->SetPointError(12,0.5,0);
	gre->SetPoint(13,13,0.0143026);
	gre->SetPointError(13,0.5,0);
	gre->SetPoint(14,14,0.00783343);
	gre->SetPointError(14,0.5,0);
	gre->SetPoint(15,15,0.00500839);
	gre->SetPointError(15,0.5,0);
	gre->SetPoint(16,16,0.00378338);
	gre->SetPointError(16,0.5,0);
	gre->SetPoint(17,17,0.00282622);
	gre->SetPointError(17,0.5,0);
	gre->SetPoint(18,18,0.00200955);
	gre->SetPointError(18,0.5,0);
	gre->SetPoint(19,19,0.00115716);
	gre->SetPointError(19,0.5,0);
	gre->SetPoint(20,20,0.000595245);
	gre->SetPointError(20,0.5,0);
	gre->SetPoint(21,21,0.000273813);
	gre->SetPointError(21,0.5,0);
	gre->SetPoint(22,22,0.00012143);
	gre->SetPointError(22,0.5,0);
	gre->SetPoint(23,23,4.76196e-05);
	gre->SetPointError(23,0.5,0);
	gre->SetPoint(24,24,1.19049e-05);
	gre->SetPointError(24,0.5,0);
	gre->SetPoint(25,25,2.38098e-06);
	gre->SetPointError(25,0.5,0);
	gre->SetPoint(26,26,1.19049e-06);
	gre->SetPointError(26,0.5,0);
	gre->SetPoint(27,27,0);
	gre->SetPointError(27,0.5,0);
	gre->SetPoint(28,28,0);
	gre->SetPointError(28,0.5,0);
	gre->SetPoint(29,29,0);
	gre->SetPointError(29,0.5,0);
	Double_t *ydata = gre->GetY();
	Double_t *yerr = gre->GetEY();

   TH1D *Graph6 = new TH1D("Graph6","Graph6",21,-0.5,20.5);

   Graph6->SetLineColor(2);
   Graph6->SetLineWidth(2);

   Graph6->GetXaxis()->SetTitle("Number of strip hits on track");
   Graph6->GetYaxis()->SetTitle("Fraction of tracks");
   Graph6->GetXaxis()->CenterTitle();
   Graph6->GetYaxis()->CenterTitle();

   for(Int_t i = 0; i<21; i++){
      Graph6->SetBinContent(i+1,ydata[i]);
      Graph6->SetBinError(i+1,yerr[i]);
   }
   
   Graph6->SetMaximum(0.15);
   Graph6->Draw("hist");

   // DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
	gre->SetPoint(0,0,0.124256);
	gre->SetPointError(0,0,0.000557744);
	gre->SetPoint(1,1,0.121144);
	gre->SetPointError(1,0,0.000550715);
	gre->SetPoint(2,2,0.118272);
	gre->SetPointError(2,0,0.000544149);
	gre->SetPoint(3,3,0.094521);
	gre->SetPointError(3,0,0.000486453);
	gre->SetPoint(4,4,0.0847422);
	gre->SetPointError(4,0,0.000460603);
	gre->SetPoint(5,5,0.0723647);
	gre->SetPointError(5,0,0.000425638);
	gre->SetPoint(6,6,0.0609962);
	gre->SetPointError(6,0,0.000390776);
	gre->SetPoint(7,7,0.0533103);
	gre->SetPointError(7,0,0.000365328);
	gre->SetPoint(8,8,0.0539537);
	gre->SetPointError(8,0,0.000367526);
	gre->SetPoint(9,9,0.0579343);
	gre->SetPointError(9,0,0.000380842);
	gre->SetPoint(10,10,0.0575112);
	gre->SetPointError(10,0,0.000379449);
	gre->SetPoint(11,11,0.043186);
	gre->SetPointError(11,0,0.000328813);
	gre->SetPoint(12,12,0.0253308);
	gre->SetPointError(12,0,0.000251826);
	gre->SetPoint(13,13,0.012758);
	gre->SetPointError(13,0,0.000178718);
	gre->SetPoint(14,14,0.00647164);
	gre->SetPointError(14,0,0.000127287);
	gre->SetPoint(15,15,0.00414085);
	gre->SetPointError(15,0,0.000101817);
	gre->SetPoint(16,16,0.00315195);
	gre->SetPointError(16,0,8.88314e-05);
	gre->SetPoint(17,17,0.00236334);
	gre->SetPointError(17,0,7.69201e-05);
	gre->SetPoint(18,18,0.00159475);
	gre->SetPointError(18,0,6.31864e-05);
	gre->SetPoint(19,19,0.00102144);
	gre->SetPointError(19,0,5.0569e-05);
	gre->SetPoint(20,20,0.000543267);
	gre->SetPointError(20,0,3.68794e-05);
	gre->SetPoint(21,21,0.000262871);
	gre->SetPointError(21,0,2.56536e-05);
	gre->SetPoint(22,22,0.000102645);
	gre->SetPointError(22,0,1.60305e-05);
	gre->SetPoint(23,23,4.50637e-05);
	gre->SetPointError(23,0,1.06216e-05);
	gre->SetPoint(24,24,1.75248e-05);
	gre->SetPointError(24,0,6.62373e-06);
	gre->SetPoint(25,25,5.00707e-06);
	gre->SetPointError(25,0,3.54053e-06);   
	
	
	Double_t *ydata = gre->GetY();
	Double_t *yerr = gre->GetEY();

   TH1D *Graph8 = new TH1D("Graph8","Graph",21,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...
   Graph8->SetMarkerSize(msize);
   Graph8->SetMarkerStyle(20);
   Graph8->SetMarkerColor(1);
   Graph8->SetLineColor(1);
   Graph8->Draw("pzsame");
   for(Int_t i = 0; i<21; i++){
      Graph8->SetBinContent(i+1,ydata[i]);
      Graph8->SetBinError(i+1,yerr[i]);
   }
   //hack
   TH1F *Graph82 = Graph8->Clone("Graph82");
   Graph82->SetMarkerStyle(0);
   Graph82->Draw("pzsame");

	TLegend *leg = new TLegend(0.61,0.77,.91,0.87,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.038);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetMargin(0.32);
   
   leg->AddEntry(Graph8,"Data 0.9 TeV","p");
   leg->AddEntry(Graph6,"Pythia 0.9 TeV","l");
   leg->Draw();
   
   printFinalCanvases(MyCanvas,"strips_pos_neg");

}
