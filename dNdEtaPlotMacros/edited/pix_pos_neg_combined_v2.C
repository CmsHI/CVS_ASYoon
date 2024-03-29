{
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Tue Dec 15 18:00:56 2009) by ROOT version5.25/04

   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);

   /*
   TH1D *hDist = new TH1D("hDist","hDist",20,1.5,5.5); // bin size = 0.2
   hDist->SetMinimum(0);
   hDist->SetMaximum(0.12);
   hDist->SetLineStyle(0);
   hDist->GetXaxis()->SetTitle("Number of pixel hits on track");
   hDist->GetYaxis()->SetTitle("Fraction");
   hDist->Draw("");
   */

   //Postive SIM
   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.000489806);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.0833864);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.763657);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.144364);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.00787668);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.000226256);

   Double_t xAxis[7] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5};
   TH1F *Graph1 = new TH1F("Graph1","Graph",6,xAxis);

   Graph1->SetMinimum(0);
   Graph1->SetMaximum(0.12);
   Graph1->GetXaxis()->SetRange(2,5);

   Graph1->SetBinContent(1,0.000489806); // x = 1     
   Graph1->SetBinContent(2,0.0833864); // x = 2 
   Graph1->SetBinContent(3,0.763657);// x = 3 
   Graph1->SetBinContent(4,0.144364);// x = 4 
   Graph1->SetBinContent(5,0.00787668);// x= 5
   Graph1->SetBinContent(6,0.000226256);// x= 6  
   
   Graph1->SetBinError(1,0);
   Graph1->SetBinError(2,0);
   Graph1->SetBinError(3,0);
   Graph1->SetBinError(4,0);
   Graph1->SetBinError(5,0);
   Graph1->SetBinError(6,0);
   
   //Negative SIM 
   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.00079501);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.0943157);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.755919);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.13866);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.0101007);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.000208945);


   TH1F *Graph2 = new TH1F("Graph2","Graph",6,xAxis);

   Graph2->SetMinimum(0);
   Graph2->SetMaximum(0.12);
   Graph2->GetXaxis()->SetRange(2,5);

   Graph2->SetBinContent(1,0.00079501); // x = 1
   Graph2->SetBinContent(2,0.0943157); // x = 2
   Graph2->SetBinContent(3,0.755919);// x = 3
   Graph2->SetBinContent(4,0.13866);// x = 4
   Graph2->SetBinContent(5,0.0101007);// x= 5
   Graph2->SetBinContent(6,0.000208945);// x= 6

   Graph2->SetBinError(1,0);
   Graph2->SetBinError(2,0);
   Graph2->SetBinError(3,0);
   Graph2->SetBinError(4,0);
   Graph2->SetBinError(5,0);
   Graph2->SetBinError(6,0);

   /*   
   Graph2->SetMarkerStyle(22);
   Graph2->SetMarkerSize(2);
   Graph2->Draw("p");

   Graph1->SetMarkerStyle(20);
   Graph1->SetMarkerSize(1);
   Graph1->Draw("psame");
   */

   Graph1->Sumw2();
   Graph2->Sumw2();

   Graph2->Add(Graph1);
   Graph2->Scale(1./2);


   Graph2->SetLineWidth(1.0);
   Graph2->GetXaxis()->SetTitle("Number of pixel hits on track");
   Graph2->GetYaxis()->SetTitle("Fraction");
   Graph2->GetXaxis()->CenterTitle();
   Graph2->GetYaxis()->CenterTitle();
   Graph2->GetXaxis()->SetNdivisions(505);
   Graph2->GetYaxis()->SetDecimals(1);

   Graph2->SetMaximum(1);
   Graph2->Draw("hist");  





   // Positive DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1,0.000801796);
   gre->SetPointError(1,0,0.000358574);
   gre->SetPoint(2,2,0.0845093);
   gre->SetPointError(2,0,0.00368128);
   gre->SetPoint(3,3,0.757216);
   gre->SetPointError(3,0,0.0110194);
   gre->SetPoint(4,4,0.148813);
   gre->SetPointError(4,0,0.00488504);
   gre->SetPoint(5,5,0.0086594);
   gre->SetPointError(5,0,0.00117839);
   
   TH1F *Graph3 = new TH1F("Graph3","Graph",6,xAxis);

   Graph3->SetMinimum(0);
   Graph3->SetMaximum(0.12);
   Graph3->GetXaxis()->SetRange(2,5);

   Graph3->SetBinContent(1,0.000801796); // x = 1
   Graph3->SetBinContent(2,0.0845093); // x = 2
   Graph3->SetBinContent(3,0.757216);// x = 3
   Graph3->SetBinContent(4,0.148813);// x = 4
   Graph3->SetBinContent(5,0.0086594);// x= 5
   Graph3->SetBinContent(6,0);// x= 6
   
   Graph3->SetBinError(1,0.000358574);
   Graph3->SetBinError(2,0.00368128);
   Graph3->SetBinError(3,0,0.0110194);
   Graph3->SetBinError(4,0.00488504);
   Graph3->SetBinError(5,0.00117839);
   Graph3->SetBinError(6,0);
   

   // Negative DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,1,0.00096231);
   gre->SetPointError(1,0,0.000392861);
   gre->SetPoint(2,2,0.0936648);
   gre->SetPointError(2,0,0.00387588);
   gre->SetPoint(3,3,0.752366);
   gre->SetPointError(3,0,0.0109849);
   gre->SetPoint(4,4,0.142582);
   gre->SetPointError(4,0,0.00478205);
   gre->SetPoint(5,5,0.0102646);
   gre->SetPointError(5,0,0.00128308);
   gre->SetPoint(6,6,0.000160385);
   gre->SetPointError(6,0,0.000160385);


   TH1F *Graph4 = new TH1F("Graph4","Graph",6,xAxis);

   Graph4->SetMinimum(0);
   Graph4->SetMaximum(0.12);
   Graph4->GetXaxis()->SetRange(2,5);

   Graph4->SetBinContent(1,0.00096231); // x = 1
   Graph4->SetBinContent(2,0.0936648); // x = 2
   Graph4->SetBinContent(3,0.752366);// x = 3
   Graph4->SetBinContent(4,0.142582);// x = 4
   Graph4->SetBinContent(5,0.0102646);// x= 5
   Graph4->SetBinContent(6,0.000160385);// x= 6

   Graph4->SetBinError(1,0.000392861);
   Graph4->SetBinError(2,0.00387588);
   Graph4->SetBinError(3,0.0109849);
   Graph4->SetBinError(4,0.00478205);
   Graph4->SetBinError(5,0.00128308);
   Graph4->SetBinError(6,0.000160385);                             

   Graph3->Sumw2();
   Graph4->Sumw2();

   Graph4->Add(Graph3);
   Graph4->Scale(1./2);

   Graph4->SetMarkerStyle(20);
   Graph4->SetMarkerSize(1.5);
   Graph4->SetMarkerColor(2);
   Graph4->SetLineColor(2);
   Graph4->Draw("pzsame");


   //TLegend *leg = new TLegend(0.22,0.80,0.62,0.94,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.61,0.58,0.92,0.72,NULL,"brNDC");  
   TLegend *leg = new TLegend(0.24,0.79,0.55,0.93,NULL,"brNDC");   
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.038);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetMargin(0.32);

   TLegendEntry *entry=leg->AddEntry("","Run 123596","p");
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.8);

   entry=leg->AddEntry("","PYTHIA D6T","l");
   entry->SetLineWidth(2);
   leg->Draw();


   TLatex *tex = new TLatex(4.9,0.92,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();



   MyCanvas->Print("pixels_pos_neg_v2.eps");
   MyCanvas->Print("pixels_pos_neg_v2.gif");
   MyCanvas->Print("pixels_pos_neg_v2.pdf");



   /*
   TLegend *leg = new TLegend(0.65,0.65,0.95,0.95,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

   TLegendEntry *entry=leg->AddEntry("Graph","data","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Graph","simulation","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   */
   /*
   MyCanvas->Modified();
   MyCanvas->cd();
   MyCanvas->SetSelected(MyCanvas);
   */
}
