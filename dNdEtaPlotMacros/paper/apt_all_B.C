{
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Thu Dec  3 18:47:52 2009) by ROOT version5.25/04
   
   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   double msize = 1.8;
   
   TCanvas *MyCanvas = new TCanvas("MyCanvas", "My Canvas",0,0,550,600);

   MyCanvas->SetLogx();

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
   

   // ============================= ISR?
   TGraphErrors *gre = new TGraphErrors(4);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(msize);

   gre->SetPoint(0,22.1269,0.36151);
   gre->SetPointError(0,0.00355619,0.00478821);
   gre->SetPoint(1,31.2682,0.363904);
   gre->SetPointError(1,0.0997339,0.00497238);
   gre->SetPoint(2,45.2369,0.366667);
   gre->SetPointError(2,0.144569,0.00478821);
   gre->SetPoint(3,52.9691,0.367956);
   gre->SetPointError(3,0.00884053,0.00497238);

   
   TH1F *Graph1 = new TH1F("Graph1","Graph",100,19.03788,56.0634);
   Graph1->SetMinimum(0.3551011);
   Graph1->SetMaximum(0.374549);

   gre->SetHistogram(Graph1);
   gre->Draw("pz");


   // ============================= UA1?   
   gre = new TGraphErrors(7);
   gre->SetName("Graph");
   gre->SetTitle("Graph");


   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(msize);

   gre->SetPoint(0,201.626,0.391897);
   gre->SetPointError(0,0.0211879,0.00313076);
   gre->SetPoint(1,261.197,0.403867);
   gre->SetPointError(1,0.912236,0.00405157);
   gre->SetPoint(2,381.723,0.407919);
   gre->SetPointError(2,0.0519114,0.00405157);
   gre->SetPoint(3,501.169,0.418785);
   gre->SetPointError(3,1.61094,0.00423573);
   gre->SetPoint(4,623.515,0.426519);
   gre->SetPointError(4,0.096356,0.00460405);
   gre->SetPoint(5,796.869,0.434991);
   gre->SetPointError(5,2.57127,0.0038674);
   gre->SetPoint(6,902.622,0.447698);
   gre->SetPointError(6,0.0669543,0.00220994);
   
   TH1F *Graph2 = new TH1F("Graph2","Graph",100,131.4964,972.7974);
   Graph2->SetMinimum(0.3826521);
   Graph2->SetMaximum(0.4560221);

   gre->SetHistogram(Graph2);
   gre->Draw("pz");
   

   // ============================= E735?
   gre = new TGraphErrors(4);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(msize);
      
   gre->SetPoint(0,300.629,0.392818);
   gre->SetPointError(0,0.908721,0.00994475);
   gre->SetPoint(1,543.419,0.430018);
   gre->SetPointError(1,2.00539,0.00994475);
   gre->SetPoint(2,905.668,0.447882);
   gre->SetPointError(2,3.33661,0.00976059);
   gre->SetPoint(3,1809.47,0.467772);
   gre->SetPointError(3,6.66633,0.00976059);
   
   TH1F *Graph3 = new TH1F("Graph3","Graph",100,148.0787,1967.778);
   Graph3->SetMinimum(0.3734073);
   Graph3->SetMaximum(0.4869985);

   gre->SetHistogram(Graph3);
   
   gre->Draw("pz");
   
   // ============================= CDF
   gre = new TGraphErrors(2);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(msize);

   gre->SetPoint(0,636.31,0.431676);
   gre->SetPointError(0,0.0825999,0.0038674);
   gre->SetPoint(1,1817.2,0.495028);
   gre->SetPointError(1,0.864938,0.0141805);
   
   TH1F *Graph4 = new TH1F("Graph4","Graph",100,518.0436,1936.249);
   Graph4->SetMinimum(0.4196686);
   Graph4->SetMaximum(0.5173485);
   gre->SetHistogram(Graph4);
   
   gre->Draw("pz");
   
   // ============================= CMS?
   gre = new TGraphErrors(1);
   gre->SetName("Graph");
   gre->SetTitle("Graph");

   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(msize);
   gre->SetMarkerColor(2);
   gre->SetLineColor(2);

   /*
   gre->SetPoint(0,900,0.44);
   gre->SetPointError(0,0,0.018);
   */
   
   //Now real measurement
   gre->SetPoint(0,900,0.46);
   gre->SetPointError(0,0,0.02);

   
   TH1F *Graph5 = new TH1F("Graph5","Graph",100,899.9,901.1);
   Graph5->SetMinimum(0.4184);
   Graph5->SetMaximum(0.4616);
   gre->SetHistogram(Graph5);
   gre->Draw("pz");
   
   
   // Fit function
   TF1 *func = new TF1("func","0.40-0.03*log(x)+0.0053*log(x)^2",10,100000);
   func->SetLineColor(1);
   func->SetLineWidth(1.5);
   func->Draw("same");
   
   TLegend *leg = new TLegend(0.25,0.49,0.62,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);


   TLegendEntry *entry=leg->AddEntry("Graph1","ISR inel.","P");
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(2.0);

   entry=leg->AddEntry("Graph2","UA1 inel.","P");
   entry->SetMarkerStyle(26);   
   entry->SetMarkerSize(2.0);   

   entry=leg->AddEntry("Graph3","E735 inel.","P");
   entry->SetMarkerStyle(25);   
   entry->SetMarkerSize(2.0); 

   entry=leg->AddEntry("Graph4","CDF inel.","P");
   entry->SetMarkerStyle(21);    
   entry->SetMarkerSize(2.0);    

   entry=leg->AddEntry("Graph5","CMS NSD","P");
   entry->SetMarkerStyle(20);  
   entry->SetMarkerColor(2);
   entry->SetMarkerSize(2.0);  

   leg->Draw();  

   TLegend *leg2 = new TLegend(0.245,0.20,0.55,0.26,NULL,"brNDC");

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

   //TLegendEntry *entry=leg2->AddEntry("func","0.40 - 0.03ln(#sqrt{s})+0.0053ln^{2}(#sqrt{s})","l"); ln(sqrt(s)) == 0.5*ln(s)
   TLegendEntry *entry=leg2->AddEntry("func","0.40 - 0.015 ln(s) + 0.00265 ln^{2}(s)","l");
   entry->SetTextSize(0.045);
   entry->SetMarkerSize(0);
   leg2->Draw();

   TLatex *tex = new TLatex(4364,0.58,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();


   tex = new TLatex(12,0.58,"(b)");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();


   MyCanvas->Print("apt_all_B.eps");
   MyCanvas->Print("apt_all_B.pdf");
   MyCanvas->Print("apt_all_B.gif");


}

