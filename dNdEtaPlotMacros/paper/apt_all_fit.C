#include "common.h"

void apt_all_fit(){
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Thu Dec  3 18:47:52 2009) by ROOT version5.25/04
   
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   gStyle->SetTitleYOffset(1.5);
   TCanvas *MyCanvas = new TCanvas("MyCanvas", "My Canvas",0,0,550,600);

   MyCanvas->SetLogx();

   double msize = 2;

   TH1D *hDist = new TH1D("hDist","hDist",20,9,10000);
   hDist->GetXaxis()->SetRange(1,20);
   hDist->SetMinimum(0.3);
   //hDist->SetMaximum(0.7);
   hDist->SetMaximum(0.6);  
   hDist->SetLineStyle(0);
   hDist->GetXaxis()->SetTitle("#sqrt{s} [GeV]");
   hDist->GetYaxis()->SetTitle("#LTp_{T}#GT [GeV/c]");
   hDist->GetXaxis()->CenterTitle();
   hDist->GetYaxis()->CenterTitle();
   hDist->Draw("");
   

   Int_t N = 100;
   Int_t ip = 0;
   // ============================= ISR?
   TGraphErrors *gre = new TGraphErrors(N);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(msize);

   gre->SetPoint(ip,22.1269,0.36151);
   gre->SetPointError(ip,0.00355619,0.00478821);
   gre->SetPoint(++ip,31.2682,0.363904);
   gre->SetPointError(ip,0.0997339,0.00497238);
   gre->SetPoint(++ip,45.2369,0.366667);
   gre->SetPointError(ip,0.144569,0.00478821);
   gre->SetPoint(++ip,52.9691,0.367956);
   gre->SetPointError(ip,0.00884053,0.00497238);
   gre->Draw("pz");

   // ============================= UA1?   
   gre->SetPoint(++ip,201.626,0.391897);
   gre->SetPointError(ip,0.0211879,0.00313076);
   gre->SetPoint(++ip,261.197,0.403867);
   gre->SetPointError(ip,0.912236,0.00405157);
   gre->SetPoint(++ip,381.723,0.407919);
   gre->SetPointError(ip,0.0519114,0.00405157);
   gre->SetPoint(++ip,501.169,0.418785);
   gre->SetPointError(ip,1.61094,0.00423573);
   gre->SetPoint(++ip,623.515,0.426519);
   gre->SetPointError(ip,0.096356,0.00460405);
   gre->SetPoint(++ip,796.869,0.434991);
   gre->SetPointError(ip,2.57127,0.0038674);
   gre->SetPoint(++ip,902.622,0.447698);
   gre->SetPointError(ip,0.0669543,0.00220994);
   
   // ============================= E735?
   gre->SetPoint(++ip,300.629,0.392818);
   gre->SetPointError(ip,0.908721,0.00994475);
   gre->SetPoint(++ip,543.419,0.430018);
   gre->SetPointError(ip,2.00539,0.00994475);
   gre->SetPoint(++ip,905.668,0.447882);
   gre->SetPointError(ip,3.33661,0.00976059);
   gre->SetPoint(++ip,1809.47,0.467772);
   gre->SetPointError(ip,6.66633,0.00976059);
   
   // ============================= CDF
   gre->SetPoint(++ip,636.31,0.431676);
   gre->SetPointError(ip,0.0825999,0.0038674);
   gre->SetPoint(++ip,1817.2,0.495028);
   gre->SetPointError(ip,0.864938,0.0141805);
   
   // ============================= CMS?
   //Now real measurement
   Float_t cmsSysError = 0.028;
   gre->SetPoint(++ip,900,0.46);
   gre->SetPointError(ip,0,0.46*cmsSysError);
   gre->SetPoint(++ip,2360,0.50);
   gre->SetPointError(ip,0,0.50*cmsSysError);

   // Fit function
   //TF1 *func = new TF1("func","0.40-0.03*log(x)+0.0053*log(x)^2",18,100000);
   TF1 *func = new TF1("func","[0]+[1]*log(x^2)+[2]*(log(x^2))^2",18,100000);
   func->SetLineColor(1);
   func->SetLineWidth(1.5);

   // fit
   //func->SetParameters(0.4,0.03,0.0053);
   gre->Fit("func","R","",18,3000);
   func->Draw("same");
   func->Print();
   
   TLegend *leg = new TLegend(0.25,0.90-0.045*5,0.5,0.90,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.03);

   TLegendEntry *entry=leg->AddEntry("Graph1","ISR inel.","P");
   entry->SetMarkerStyle(28);
   entry->SetMarkerSize(msize);
   entry=leg->AddEntry("Graph2","UA1 inel.","P");
   entry->SetMarkerStyle(5);   
   entry->SetMarkerSize(msize);   

   entry=leg->AddEntry("Graph3","E735 inel.","P");
   entry->SetMarkerStyle(27);   
   entry->SetMarkerSize(msize); 

   entry=leg->AddEntry("Graph4","CDF inel.","P");
   entry->SetMarkerStyle(25);    
   entry->SetMarkerSize(msize);    

   entry=leg->AddEntry("Graph5","CMS NSD","P");
   entry->SetMarkerStyle(20);  
   entry->SetMarkerColor(2);
   entry->SetMarkerSize(msize*0.85);  
   leg->Draw();  

   TLegend *leg2 = new TLegend(0.35,0.20,0.91,0.26,NULL,"brNDC");
   //TLegend *leg2 = new TLegend(0.411,0.18,0.91,0.33,NULL,"brNDC");     
   leg2->SetBorderSize(0);
   leg2->SetTextFont(62);
   leg2->SetTextSize(0.035);
   leg2->SetLineColor(1);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(0);
   leg2->SetFillStyle(0);
   leg2->SetMargin(0.15);
   leg2->SetTextSize(0.03);

   //   TLegendEntry *entry=leg2->AddEntry("func","0.40 - 0.015 #times ln(s) + 0.001325 #times ln^{2}(s)","l");
   TLegendEntry *entry=leg2->AddEntry("func","0.40 - 0.015 ln(s) + 0.001325 ln^{2}(s)","l");

   entry->SetTextSize(0.03);
   entry->SetMarkerSize(0);
   leg2->Draw();

   printFinalCanvases(MyCanvas,"apt_all");

}

