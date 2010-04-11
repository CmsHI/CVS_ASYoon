#include "common.h"

void apt_all(){
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Thu Dec  3 18:47:52 2009) by ROOT version5.25/04
   
   Bool_t theory = false;

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   gStyle->SetTitleYOffset(1.5);
   TCanvas *MyCanvas = new TCanvas("MyCanvas", "My Canvas",0,0,550,600);

   MyCanvas->SetLogx();

   double msize = 2;

   //TH1D *hDist = new TH1D("hDist","hDist",20,9,10000);
   TH1D *hDist = new TH1D("hDist","hDist",20,9,15000);
   hDist->GetXaxis()->SetRange(1,20);
   hDist->SetMinimum(0.3);
   //hDist->SetMaximum(0.7);
   hDist->SetMaximum(0.6);  
   hDist->SetLineStyle(0);
   hDist->GetXaxis()->SetTitle("#sqrt{s} [GeV]");
   hDist->GetYaxis()->SetTitle("#LTp_{T}#GT [GeV/c]");
   hDist->GetXaxis()->CenterTitle();
   hDist->GetYaxis()->CenterTitle();
   hDist->GetYaxis()->SetNdivisions(510);
   hDist->Draw("");
   
   // Fit function                                                                                                                                 
   //TF1 *func = new TF1("func","0.426-0.0198*log(x^2)+0.00156*log(x^2)^2",18,100000); 
   //TF1 *func = new TF1("func","0.430-0.0207*log(x^2)+0.00161*log(x^2)^2",18,100000); 
   //TF1 *func = new TF1("func","0.425-0.0197*log(x^2)+0.00156*log(x^2)^2",18,100000);
   TF1 *func = new TF1("func","0.409-0.0163*log(x^2)+0.00139*log(x^2)^2",18,100000);
   func->SetLineColor(1);
   func->SetLineWidth(2.0);
   func->Draw("same");

   //0.337 + 6.52e-3 * s^(0.207)
   if(theory){
   TF1 *func2 = new TF1("func2","0.337+6.52e-3*pow(x^2,0.207)",18,100000);
   func2->SetLineColor(13);
   func2->SetLineStyle(9);
   func2->SetLineWidth(2.0);
   func2->Draw("same");
   }


   // ============================= ISR
   // OK, from http://www.slac.stanford.edu/spires/find/hep/www?j=NUPHA,B84,269

   TGraphErrors *gre = new TGraphErrors(4);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(msize);

   gre->SetPoint(0,23.32,0.362);// plab = 289
   gre->SetPointError(0,0,0.004);  // errors are not verified! 
   gre->SetPoint(1,30.59,0.364);// plab = 498
   gre->SetPointError(1,0,0.00497238);
   gre->SetPoint(2,44.61,0.366); // plab = 1060
   gre->SetPointError(2,0,0.00478821);
   gre->SetPoint(3,53.06,0.368); // plab = 1500
   gre->SetPointError(3,0,0.00497238);

   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,19.03788,56.0634);
   Graph1->SetMinimum(0.3551011);
   Graph1->SetMaximum(0.374549);

   gre->SetHistogram(Graph1);
   gre->Draw("pz");

   TGraph* gre01 = gre->Clone("gre01");
   gre01->SetMarkerStyle(0);
   //   gre01->Draw("pzsame");

   // ============================= UA1  
   // OK, from  http://dx.doi.org/10.1016/0550-3213(90)90493-W

   gre = new TGraphErrors(7);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(3);
   gre->SetMarkerSize(msize);
   gre->SetPoint(0,200,0.392);
   gre->SetPointError(0,0,0.003);
   gre->SetPoint(1,260,0.404);
   gre->SetPointError(1,0,0.004);
   gre->SetPoint(2,380,0.408);
   gre->SetPointError(2,0,0.004);
   gre->SetPoint(3,500,0.419);
   gre->SetPointError(3,0,0.004);
   gre->SetPoint(4,620,0.426);
   gre->SetPointError(4,0,0.004);
   gre->SetPoint(5,790,0.435);
   gre->SetPointError(5,0,0.004);
   gre->SetPoint(6,900,0.447);
   gre->SetPointError(6,0,0.003);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,131.4964,972.7974);
   Graph2->SetMinimum(0.3826521);
   Graph2->SetMaximum(0.4560221);

   gre->SetHistogram(Graph2);
   gre->Draw("pz");
   
   TGraph* gre02 = gre->Clone("gre02");
   gre02->SetMarkerStyle(0);
   //   gre02->Draw("pzsame");

   // ============================= E735?
   // OK, from https://twiki.cern.ch/twiki/pub/CMS/DNdEtaBib/e735numbers.pdf
   gre = new TGraphErrors(4);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(msize);
   gre->SetPoint(0,300,0.393);
   gre->SetPointError(0,0,0.01);
   gre->SetPoint(1,540,0.430);
   gre->SetPointError(1,0,0.01);
   gre->SetPoint(2,900,0.448);
   gre->SetPointError(2,0,0.01);
   gre->SetPoint(3,1800,0.468);
   gre->SetPointError(3,0,0.01);

   TH1F *Graph3 = new TH1F("Graph3","Graph",100,148.0787,1967.778);
   Graph3->SetMinimum(0.3734073);
   Graph3->SetMaximum(0.4869985);

   gre->SetHistogram(Graph3);
   gre->Draw("pz");

   TGraph* gre03 = gre->Clone("gre03");
   gre03->SetMarkerStyle(0);
   gre03->Draw("pzsame");
   
   // ============================= CDF
   // OK, from http://www.slac.stanford.edu/spires/find/hep/www?j=PRLTA,61,1819

   gre = new TGraphErrors(2);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(msize);

   gre->SetPoint(0,630,0.432);
   gre->SetPointError(0,0,0.004);
   gre->SetPoint(1,1800,0.495);
   gre->SetPointError(1,0,0.014);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,518.0436,1936.249);
   Graph4->SetMinimum(0.4196686);
   Graph4->SetMaximum(0.5173485);
   gre->SetHistogram(Graph4);
   
   gre->Draw("pz");
   
   TGraph* gre04 = gre->Clone("gre04");
   gre04->SetMarkerStyle(0);
   gre04->Draw("pzsame");

   // ============================= CMS?
   gre = new TGraphErrors(1);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(msize);
   gre->SetMarkerColor(kRed+2);
   gre->SetLineColor(kRed+2);

   /*
   gre->SetPoint(0,900,0.44);
   gre->SetPointError(0,0,0.018);
   */
   
   //Now real measurement
   Float_t cmsSysError = 0.028;
   gre->SetPoint(0,900,0.46);
   //gre->SetPointError(0,0,0.46*cmsSysError);
   // updated to sqrt (0.01*0.01+0.46*0.46*0.028*0.028) , where 0.01 is stat err. 
   gre->SetPointError(0,0,0.0163); 
   gre->SetPoint(1,2360,0.50);
   //gre->SetPointError(1,0,0.50*cmsSysError);
   gre->SetPointError(1,0,0.0172);// 3.44%

   gre->SetPoint(2,7000,0.53);

   //gre->SetPointError(2,0,0.005);//stat only
   gre->SetPointError(2,0,0.018232);// 3.44%

   TGraph* greOnT = gre->Clone("greOnT");
   greOnT->SetMarkerStyle(0);
   greOnT->SetLineWidth(2);
   greOnT->Draw("PZsame");

   TGraph* greOnT2 = gre->Clone("cmsnsd05");
   gStyle->SetEndErrorSize(3);
   greOnT2->SetMarkerStyle(0);
   greOnT2->Draw("||");

   
   TH1F *Graph5 = new TH1F("Graph5","Graph",100,899.9,901.1);
   Graph5->SetMinimum(0.4184);
   Graph5->SetMaximum(0.4616);
   gre->SetHistogram(Graph5);
   gre->SetMarkerSize(msize*1.2);
   gre->Draw("pz");
   
   TGraph* gre05 = gre->Clone("gre05");
   gre05->SetMarkerStyle(0);
   //   gre05->Draw("pzsame");
   
   /*
   // Fit function
   //TF1 *func = new TF1("func","0.426-0.0198*log(x^2)+0.00156*log(x^2)^2",18,100000);
   //TF1 *func = new TF1("func","0.430-0.0207*log(x^2)+0.00161*log(x^2)^2",18,100000);  
   TF1 *func = new TF1("func","0.425-0.0197*log(x^2)+0.00156*log(x^2)^2",18,100000);  
   func->SetLineColor(1);
   func->SetLineWidth(1.5);
   func->Draw("same");
   */

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
   entry=leg->AddEntry("Graph2","UA1 NSD","P");
   entry->SetMarkerStyle(3);   
   entry->SetMarkerSize(msize);   

   entry=leg->AddEntry("Graph3","E735 NSD","P");
   entry->SetMarkerStyle(22);   
   entry->SetMarkerSize(msize); 

   entry=leg->AddEntry("Graph4","CDF NSD","P");
   entry->SetMarkerStyle(21);    
   entry->SetMarkerSize(msize);    

   entry=leg->AddEntry("Graph5","CMS NSD (|#eta|<2.4)","P");
   entry->SetMarkerStyle(20);  
   entry->SetMarkerColor(kRed+2);
   entry->SetMarkerSize(msize*1.0);  
   leg->Draw();  

   if(theory) TLegend *leg2 = new TLegend(0.35,0.20,0.91,0.26,NULL,"brNDC");
   //TLegend *leg2 = new TLegend(0.411,0.18,0.91,0.33,NULL,"brNDC");     
   else TLegend *leg2 = new TLegend(0.35,0.20,0.91,0.31,NULL,"brNDC");  
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
   //TLegendEntry *entry=leg2->AddEntry("func","0.40 - 0.015 ln(s) + 0.001325 ln^{2}(s)","l");
   //TLegendEntry *entry=leg2->AddEntry("func","0.425 - 0.0197 ln(s) + 0.00156 ln^{2}(s)","l");
   if(theory)TLegendEntry *entry=leg2->AddEntry("func2","0.337 + 0.00652 s^{0.207}","l");
   TLegendEntry *entry=leg2->AddEntry("func","0.409 - 0.0163 ln(s) + 0.00139 ln^{2}(s)","l");
   
   //TLegendEntry *entry=leg2->AddEntry("func2","0.337 + 0.00652 s^{0.207}","l");
   //TF1 *func2 = new TF1("func2","0.337+6.52e-3*pow(x^2,0.207)",18,100000);
   
   //TLegendEntry *entry=leg2->AddEntry("func","0.430 - 0.0207 ln(s) + 0.00161 ln^{2}(s)","l");


   entry->SetTextSize(0.03);
   entry->SetMarkerSize(0);
   leg2->Draw();

   printFinalCanvases(MyCanvas,"apt_all");

}




