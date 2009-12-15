{
//=========Macro generated from canvas: MyCanvas/My Canvas
//=========  (Tue Dec 15 18:00:56 2009) by ROOT version5.25/04

   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);

   /*
   TH1D *hDist = new TH1D("hDist","hDist",20,1.5,20.5);
   hDist->SetMinimum(0);
   hDist->SetMaximum(0.12);
   hDist->SetLineStyle(0);
   hDist->Draw("");
   */

   // Pos SIM
   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,0,0.122026);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.13044);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.134152);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.0956241);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.0796047);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.0579687);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.0502909);
   gre->SetPointError(6,0.5,0);
   gre->SetPoint(7,7,0.0480457);
   gre->SetPointError(7,0.5,0);
   gre->SetPoint(8,8,0.0543287);
   gre->SetPointError(8,0.5,0);
   gre->SetPoint(9,9,0.0618722);
   gre->SetPointError(9,0.5,0);
   gre->SetPoint(10,10,0.0611089);
   gre->SetPointError(10,0.5,0);
   gre->SetPoint(11,11,0.0452685);
   gre->SetPointError(11,0.5,0);
   gre->SetPoint(12,12,0.0253158);
   gre->SetPointError(12,0.5,0);
   gre->SetPoint(13,13,0.0124142);
   gre->SetPointError(13,0.5,0);
   gre->SetPoint(14,14,0.00689458);
   gre->SetPointError(14,0.5,0);
   gre->SetPoint(15,15,0.00476629);
   gre->SetPointError(15,0.5,0);
   gre->SetPoint(16,16,0.00357782);
   gre->SetPointError(16,0.5,0);
   gre->SetPoint(17,17,0.00271507);
   gre->SetPointError(17,0.5,0);
   gre->SetPoint(18,18,0.00184734);
   gre->SetPointError(18,0.5,0);
   gre->SetPoint(19,19,0.000997016);
   gre->SetPointError(19,0.5,0);
   gre->SetPoint(20,20,0.000452511);
   gre->SetPointError(20,0.5,0);
   gre->SetPoint(21,21,0.000203879);
   gre->SetPointError(21,0.5,0);
   gre->SetPoint(22,22,6.21581e-05);
   gre->SetPointError(22,0.5,0);
   gre->SetPoint(23,23,1.74043e-05);
   gre->SetPointError(23,0.5,0);
   gre->SetPoint(24,24,2.48633e-06);
   gre->SetPointError(24,0.5,0);
   gre->SetPoint(25,25,0);
   gre->SetPointError(25,0.5,0);
   gre->SetPoint(26,26,2.48633e-06);
   gre->SetPointError(26,0.5,0);
   gre->SetPoint(27,27,0);
   gre->SetPointError(27,0.5,0);
   gre->SetPoint(28,28,0);
   gre->SetPointError(28,0.5,0);
   gre->SetPoint(29,29,0);
   gre->SetPointError(29,0.5,0);

   Double_t *ydata = gre->GetY();
   Double_t *yerr = gre->GetEY();

   TH1F *Graph5 = new TH1F("Graph5","Graph",21,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...

   for(Int_t i = 0; i<20; i++){
      Graph5->SetBinContent(i+1,ydata[i]);
      Graph5->SetBinError(i+1,yerr[i]);
   }


   //Graph5->GetXaxis()->SetRange(3,21);
   //Graph5->SetMaximum(0.12);
   //Graph5->Draw("hist");

   /*
   TH1F *Graph5 = new TH1F("Graph5","Graph",100,-3.5,32.5); 
   gre->SetHistogram(Graph5);
   gre->Draw("pz");
   */

   // Neg SIM
   TGraphErrors *gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,0,0.105311);
   gre->SetPointError(0,0.5,0);
   gre->SetPoint(1,1,0.0936328);
   gre->SetPointError(1,0.5,0);
   gre->SetPoint(2,2,0.0947743);
   gre->SetPointError(2,0.5,0);
   gre->SetPoint(3,3,0.0911254);
   gre->SetPointError(3,0.5,0);
   gre->SetPoint(4,4,0.0920249);
   gre->SetPointError(4,0.5,0);
   gre->SetPoint(5,5,0.0838582);
   gre->SetPointError(5,0.5,0);
   gre->SetPoint(6,6,0.0715229);
   gre->SetPointError(6,0.5,0);
   gre->SetPoint(7,7,0.061756);
   gre->SetPointError(7,0.5,0);
   gre->SetPoint(8,8,0.0596181);
   gre->SetPointError(8,0.5,0);
   gre->SetPoint(9,9,0.0636186);
   gre->SetPointError(9,0.5,0);
   gre->SetPoint(10,10,0.0625178);
   gre->SetPointError(10,0.5,0);
   gre->SetPoint(11,11,0.0489288);
   gre->SetPointError(11,0.5,0);
   gre->SetPoint(12,12,0.029395);
   gre->SetPointError(12,0.5,0);
   gre->SetPoint(13,13,0.0162238);
   gre->SetPointError(13,0.5,0);
   gre->SetPoint(14,14,0.00876804);
   gre->SetPointError(14,0.5,0);
   gre->SetPoint(15,15,0.00519814);
   gre->SetPointError(15,0.5,0);
   gre->SetPoint(16,16,0.00392918);
   gre->SetPointError(16,0.5,0);
   gre->SetPoint(17,17,0.00297619);
   gre->SetPointError(17,0.5,0);
   gre->SetPoint(18,18,0.00212003);
   gre->SetPointError(18,0.5,0);
   gre->SetPoint(19,19,0.00134285);
   gre->SetPointError(19,0.5,0);
   gre->SetPoint(20,20,0.0007415);
   gre->SetPointError(20,0.5,0);
   gre->SetPoint(21,21,0.000349091);
   gre->SetPointError(21,0.5,0);
   gre->SetPoint(22,22,0.000175819);
   gre->SetPointError(22,0.5,0);
   gre->SetPoint(23,23,6.87989e-05);
   gre->SetPointError(23,0.5,0);
   gre->SetPoint(24,24,2.03849e-05);
   gre->SetPointError(24,0.5,0);
   gre->SetPoint(25,25,2.54811e-06);
   gre->SetPointError(25,0.5,0);
   gre->SetPoint(26,26,0);
   gre->SetPointError(26,0.5,0);
   gre->SetPoint(27,27,0);
   gre->SetPointError(27,0.5,0);
   gre->SetPoint(28,28,0);
   gre->SetPointError(28,0.5,0);
   gre->SetPoint(29,29,0);
   gre->SetPointError(29,0.5,0);

   //TH1F *Graph7 = new TH1F("Graph7","Graph",100,-3.5,32.5);

   Double_t *ydata = gre->GetY();
   Double_t *yerr = gre->GetEY();

   TH1F *Graph6 = new TH1F("Graph6","Graph",21,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...                                                                                                     
   for(Int_t i = 0; i<20; i++){
      Graph6->SetBinContent(i+1,ydata[i]);
      Graph6->SetBinError(i+1,yerr[i]);
   }
   
   /*
   Graph6->GetXaxis()->SetRange(3,21);
   Graph6->SetMaximum(0.12); 
   Graph6->Draw("hist"); 
   */
   
   Graph5->Sumw2();
   Graph6->Sumw2();

   Graph6->Add(Graph5);
   Graph6->Scale(1./2); //(h+ + h-)/2

   Graph6->SetLineWidth(1.0);
   Graph6->GetXaxis()->SetRange(3,21); 
   Graph6->SetMaximum(0.12);  
   //Graph6->SetMaximum(1);   
   Graph6->Draw("hist");

   // Pos DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);


   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#000000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetPoint(0,0,0.136786);
   gre->SetPointError(0,0,0.00468348);
   gre->SetPoint(1,1,0.13855);
   gre->SetPointError(1,0,0.00471358);
   gre->SetPoint(2,2,0.139994);
   gre->SetPointError(2,0,0.00473807);
   gre->SetPoint(3,3,0.0970173);
   gre->SetPointError(3,0,0.00394431);
   gre->SetPoint(4,4,0.0777742);
   gre->SetPointError(4,0,0.00353155);
   gre->SetPoint(5,5,0.057569);
   gre->SetPointError(5,0,0.00303837);
   gre->SetPoint(6,6,0.0501924);
   gre->SetPointError(6,0,0.00283704);
   gre->SetPoint(7,7,0.045542);
   gre->SetPointError(7,0,0.00270242);
   gre->SetPoint(8,8,0.0516357);
   gre->SetPointError(8,0,0.00287754);
   gre->SetPoint(9,9,0.062059);
   gre->SetPointError(9,0,0.00315464);
   gre->SetPoint(10,10,0.0586915);
   gre->SetPointError(10,0,0.00306785);
   gre->SetPoint(11,11,0.0397691);
   gre->SetPointError(11,0,0.00252534);
   gre->SetPoint(12,12,0.0192431);
   gre->SetPointError(12,0,0.00175665);
   gre->SetPoint(13,13,0.00769724);
   gre->SetPointError(13,0,0.001111);
   gre->SetPoint(14,14,0.0043297);
   gre->SetPointError(14,0,0.000833251);
   gre->SetPoint(15,15,0.00336754);
   gre->SetPointError(15,0,0.000734858);
   gre->SetPoint(16,16,0.00288647);
   gre->SetPointError(16,0,0.000680346);
   gre->SetPoint(17,17,0.00320718);
   gre->SetPointError(17,0,0.000717148);
   gre->SetPoint(18,18,0.00208467);
   gre->SetPointError(18,0,0.000578183);
   gre->SetPoint(19,19,0.000801796);
   gre->SetPointError(19,0,0.000358574);
   gre->SetPoint(20,20,0.000160359);
   gre->SetPointError(20,0,0.000160359);
   gre->SetPoint(21,21,0.000481078);
   gre->SetPointError(21,0,0.00027775);
   gre->SetPoint(22,22,0.000160359);
   gre->SetPointError(22,0,0.000160359);
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
   
   Double_t *ydata = gre->GetY();
   Double_t *yerr = gre->GetEY();

   TH1F *Graph7 = new TH1F("Graph7","Graph",21,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...

   for(Int_t i = 0; i<20; i++){
      Graph7->SetBinContent(i+1,ydata[i]);
      Graph7->SetBinError(i+1,yerr[i]);
   }

   // Neg DATA
   gre = new TGraphErrors(30);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetPoint(0,0,0.115638);
   gre->SetPointError(0,0,0.00430657);
   gre->SetPoint(1,1,0.0971933);
   gre->SetPointError(1,0,0.00394821);
   gre->SetPoint(2,2,0.0959102);
   gre->SetPointError(2,0,0.00392206);
   gre->SetPoint(3,3,0.0894948);
   gre->SetPointError(3,0,0.00378862);
   gre->SetPoint(4,4,0.0832398);
   gre->SetPointError(4,0,0.00365382);
   gre->SetPoint(5,5,0.0882117);
   gre->SetPointError(5,0,0.00376136);
   gre->SetPoint(6,6,0.0752205);
   gre->SetPointError(6,0,0.00347336);
   gre->SetPoint(7,7,0.0655974);
   gre->SetPointError(7,0,0.00324358);
   gre->SetPoint(8,8,0.0631917);
   gre->SetPointError(8,0,0.00318355);
   gre->SetPoint(9,9,0.0582197);
   gre->SetPointError(9,0,0.00305574);
   gre->SetPoint(10,10,0.0598236);
   gre->SetPointError(10,0,0.00309755);
   gre->SetPoint(11,11,0.0458701);
   gre->SetPointError(11,0,0.00271236);
   gre->SetPoint(12,12,0.0245389);
   gre->SetPointError(12,0,0.00198385);
   gre->SetPoint(13,13,0.0171612);
   gre->SetPointError(13,0,0.00165903);
   gre->SetPoint(14,14,0.00737771);
   gre->SetPointError(14,0,0.00108778);
   gre->SetPoint(15,15,0.00417001);
   gre->SetPointError(15,0,0.000817806);
   gre->SetPoint(16,16,0.00417001);
   gre->SetPointError(16,0,0.000817806);
   gre->SetPoint(17,17,0.00192462);
   gre->SetPointError(17,0,0.00055559);
   gre->SetPoint(18,18,0.00160385);
   gre->SetPointError(18,0,0.000507182);
   gre->SetPoint(19,19,0.000801925);
   gre->SetPointError(19,0,0.000358632);
   gre->SetPoint(20,20,0.000160385);
   gre->SetPointError(20,0,0.000160385);
   gre->SetPointError(20,0,0.000160385);
   gre->SetPoint(21,21,0.00032077);
   gre->SetPointError(21,0,0.000226819);
   gre->SetPoint(22,22,0);
   gre->SetPointError(22,0,0);
   gre->SetPoint(23,23,0);
   gre->SetPointError(23,0,0);
   gre->SetPoint(24,24,0.000160385);
   gre->SetPointError(24,0,0.000160385);
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

   TH1F *Graph8 = new TH1F("Graph8","Graph",21,-0.5,20.5);//-0.5 ~ 0.5, 0.5 ~ 1.5, ...

   for(Int_t i = 0; i<20; i++){
      Graph8->SetBinContent(i+1,ydata[i]);
      Graph8->SetBinError(i+1,yerr[i]);
   }

   Graph7->Sumw2();
   Graph8->Sumw2();

   Graph8->Add(Graph7);
   Graph8->Scale(1./2); //(h+ + h-)/2                                                                                                                                                      
   Graph8->SetMarkerStyle(20);
   Graph8->SetMarkerSize(1.5);
   Graph8->SetMarkerColor(2);
   Graph8->SetLineColor(2);
   Graph8->Draw("pzsame");


   //TLegend *leg = new TLegend(0.24,0.79,0.55,0.93,NULL,"brNDC");
   TLegend *leg = new TLegend(0.33,0.76,0.64,0.90,NULL,"brNDC");  
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


   TLatex *tex = new TLatex(17.8,0.11,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   MyCanvas->Print("strips_pos_neg_v2.eps");
   MyCanvas->Print("strips_pos_neg_v2.gif");
   MyCanvas->Print("strips_pos_neg_v2.pdf");
   

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
   MyCanvas->Modified();
   MyCanvas->cd();
   MyCanvas->SetSelected(MyCanvas);
   */
}
