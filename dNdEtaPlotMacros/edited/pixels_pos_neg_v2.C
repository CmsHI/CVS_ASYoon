{

   //Macro generated from Andre
   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);

   Double_t xAxis[5] = {1.5,2.5,3.5,4.5,5.5};
   TH1 *hSIM = new TH1D("hSIM","",4,xAxis);

   hSIM->SetMinimum(-0.02);
   hSIM->SetMaximum(1.0);

   hSIM->GetXaxis()->SetTitle("Number of pixel hits on track");
   hSIM->GetYaxis()->SetTitle("Fraction");
   hSIM->GetXaxis()->CenterTitle();
   hSIM->GetYaxis()->CenterTitle();
   hSIM->GetXaxis()->SetNdivisions(505);

   hSIM->SetBinContent(1,0.0946828);
   hSIM->SetBinContent(2,0.756732);
   hSIM->SetBinContent(3,0.1387405);
   hSIM->SetBinContent(4,0.008696175);

   hSIM->SetBinError(1,0.0);
   hSIM->SetBinError(2,0.0);
   hSIM->SetBinError(3,0.0);
   hSIM->SetBinError(4,0.0);

   hSIM->SetLineWidth(1.0);
   //hSIM->SetLineStyle(2);

   hSIM->Draw("hist");


   TH1 *hDATA = new TH1D("hDATA","",4,xAxis);

   hDATA->SetBinContent(1,0.0906199);
   hDATA->SetBinContent(2,0.7574945);
   hDATA->SetBinContent(3,0.141262);
   hDATA->SetBinContent(4,0.009716415);

   hDATA->SetBinError(1,0.004845569);
   hDATA->SetBinError(2,0.01400909);
   hDATA->SetBinError(3,0.00604962);
   hDATA->SetBinError(4,0.001586682);

   hDATA->SetMarkerStyle(20);
   hDATA->SetMarkerSize(1.6);
   hDATA->SetMarkerColor(2);
   hDATA->SetLineColor(2);
   hDATA->Draw("pzsame");

   TLegend *leg = new TLegend(0.22,0.80,0.62,0.94,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   //leg->SetLineColor(1);
   //leg->SetLineStyle(1);
   //leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetMargin(0.30);

   TLegendEntry *entry=leg->AddEntry("hDATA","Run 123596","p");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2.0);

   entry=leg->AddEntry("","PYTHIA D6T","l");
   entry->SetLineWidth(2);

   leg->Draw();


   TLatex *tex = new TLatex(4.85,0.921,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   MyCanvas->Print("pixels_pos_neg_v2.eps");       
   MyCanvas->Print("pixels_pos_neg_v2.gif"); 
   MyCanvas->Print("pixels_pos_neg_v2.pdf"); 

}
