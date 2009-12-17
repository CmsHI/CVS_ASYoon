{
//=========Macro generated from canvas: MyCanvas/MyCanvas
//=========  (Thu Dec 10 11:52:00 2009) by ROOT version5.22/00d

   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");

   gStyle->SetPadLeftMargin(0.18);
   gStyle->SetTitleYOffset(1.1);
   gStyle->SetTitleXOffset(1.1);
   gStyle->SetTitleXSize(.060);
   gStyle->SetTitleYSize(.060);
   //gStyle->SetErrorX(0); 

   //TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,650,500);
   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,550,600); 

   MyCanvas->Range(-4.9,-0.8560975,3.85,5.729268);
   
   TH1 *corr_result_all = new TH1D("corr_result_all","",14,-3.5,3.5);
   corr_result_all->GetXaxis()->SetRange(2,13);

   // ========================= Cluster Counting =======================
   //Three layer averaged (updated with Ed's cut + bit 40)
   corr_result_all->SetBinContent(4,3.801373);      
   corr_result_all->SetBinContent(5,3.8391785); 
   corr_result_all->SetBinContent(6,3.630001); 
   corr_result_all->SetBinContent(7,3.57286667); 
   corr_result_all->SetBinContent(8,3.52753333); 
   corr_result_all->SetBinContent(9,3.62393533); 
   corr_result_all->SetBinContent(10,3.750916); 
   corr_result_all->SetBinContent(11,3.9227); 

   corr_result_all->SetBinError(4,0.17017249); 
   corr_result_all->SetBinError(5,0.17186489); 
   corr_result_all->SetBinError(6,0.16250084); 
   corr_result_all->SetBinError(7,0.15994316); 
   corr_result_all->SetBinError(8,0.15791376); 
   corr_result_all->SetBinError(9,0.1622293); 
   corr_result_all->SetBinError(10,0.16791373); 
   corr_result_all->SetBinError(11,0.17560382); 

   /*
   corr_result_all->SetBinContent(4,3.860561);  
   corr_result_all->SetBinContent(5,4.017106); 
   corr_result_all->SetBinContent(6,3.747674); 
   corr_result_all->SetBinContent(7,3.733059667); 
   corr_result_all->SetBinContent(8,3.664392); 
   corr_result_all->SetBinContent(9,3.633568); 
   corr_result_all->SetBinContent(10,3.730831); 
   corr_result_all->SetBinContent(11,3.857099); 

   
   corr_result_all->SetBinError(4,0.239354782);     
   corr_result_all->SetBinError(5,0.249060572); 
   corr_result_all->SetBinError(6,0.232355788); 
   corr_result_all->SetBinError(7,0.231449699); 
   corr_result_all->SetBinError(8,0.227192304); 
   corr_result_all->SetBinError(9,0.225281216); 
   corr_result_all->SetBinError(10,0.231311522); 
   corr_result_all->SetBinError(11,0.239140138); 
   */

   corr_result_all->SetMinimum(0);    
   //corr_result_all->SetMaximum(5.4);  
   corr_result_all->SetMaximum(5.0); 
   corr_result_all->SetMarkerStyle(20);  
   corr_result_all->SetMarkerSize(1.5);  
   corr_result_all->SetMarkerColor(2);
   corr_result_all->SetLineColor(2);


   corr_result_all->GetYaxis()->SetTitle("dN/d#eta");
   corr_result_all->GetXaxis()->SetTitle("#eta"); 
   corr_result_all->GetXaxis()->CenterTitle();
   corr_result_all->GetYaxis()->CenterTitle();
   corr_result_all->GetXaxis()->SetNdivisions(405);
   corr_result_all->GetYaxis()->SetNdivisions(1005);

   corr_result_all->Draw("pz");

   // ======= YJ Tracklet three layer combination averaged (updated with dead modules..) ======
   //                        1     2   3     4   5     6  7    8  9   10 11   12
   Double_t xAxis5[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3}; 
   
   TH1 *hMeasuredFinal = new TH1D("hMeasuredFinal","",12, xAxis5);


   hMeasuredFinal->SetBinContent(3,3.49038);
   hMeasuredFinal->SetBinContent(4,3.77519);
   hMeasuredFinal->SetBinContent(5,3.61123);
   hMeasuredFinal->SetBinContent(6,3.40686);
   hMeasuredFinal->SetBinContent(7,3.44304);
   hMeasuredFinal->SetBinContent(8,3.61126);
   hMeasuredFinal->SetBinContent(9,3.64045);
   hMeasuredFinal->SetBinContent(10,3.69915);


   hMeasuredFinal->SetBinError(3,0.132634);
   hMeasuredFinal->SetBinError(4,0.143457);
   hMeasuredFinal->SetBinError(5,0.137227);
   hMeasuredFinal->SetBinError(6,0.129461);
   hMeasuredFinal->SetBinError(7,0.130835);
   hMeasuredFinal->SetBinError(8,0.137228);
   hMeasuredFinal->SetBinError(9,0.138337);
   hMeasuredFinal->SetBinError(10,0.140568);

   hMeasuredFinal->SetMarkerColor(4);   
   hMeasuredFinal->SetLineColor(4);
   hMeasuredFinal->SetMarkerStyle(21); 
   //hMeasuredFinal->SetMarkerStyle(25);  
   hMeasuredFinal->SetMarkerSize(1.5); 

   hMeasuredFinal->Draw("pzsame");

   /// ==================================================== Ferenc's dN/dEta   (rebinned)
   Double_t xAxis6[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3}; 
   TH1 *hMeasuredFinal2 = new TH1D("hMeasuredFinal2","",12, xAxis6);
   
   hMeasuredFinal2->SetBinContent(2,3.68115);
   hMeasuredFinal2->SetBinContent(3,3.71015);
   hMeasuredFinal2->SetBinContent(4,3.9022);
   hMeasuredFinal2->SetBinContent(5,3.723);
   hMeasuredFinal2->SetBinContent(6,3.56699);
   hMeasuredFinal2->SetBinContent(7,3.4943);
   hMeasuredFinal2->SetBinContent(8,3.67308);
   hMeasuredFinal2->SetBinContent(9,3.65335);
   hMeasuredFinal2->SetBinContent(10,3.7142);
   hMeasuredFinal2->SetBinContent(11,3.69061);

   // Systematic error of 4.6%
   hMeasuredFinal2->SetBinError(2,0.112864);
   hMeasuredFinal2->SetBinError(3,0.0996178);
   hMeasuredFinal2->SetBinError(4,0.0830812);
   hMeasuredFinal2->SetBinError(5,0.0954954);
   hMeasuredFinal2->SetBinError(6,0.0750412);
   hMeasuredFinal2->SetBinError(7,0.0899691);
   hMeasuredFinal2->SetBinError(8,0.0769857);
   hMeasuredFinal2->SetBinError(9,0.0870444);
   hMeasuredFinal2->SetBinError(10,0.0870007);
   hMeasuredFinal2->SetBinError(11,0.101766);
   

   hMeasuredFinal2->SetMarkerColor(1);
   hMeasuredFinal2->SetLineColor(1);
   hMeasuredFinal2->SetMarkerStyle(22);
   hMeasuredFinal2->SetMarkerSize(1.5);
   hMeasuredFinal2->Draw("pzsame");


   /// ==================================================== Ferenc's dN/dEta
   //TH1D *corr_result_2 = new TH1D("corr_result_2","corr_result_2",24,-2.4,2.4);

   /*
   corr_result_2->SetBinContent(12,3.34657);
   corr_result_2->SetBinContent(11,3.48056);
   corr_result_2->SetBinContent(10,3.63994);
   corr_result_2->SetBinContent(9,3.54276);
   corr_result_2->SetBinContent(8,4.00832);
   corr_result_2->SetBinContent(7,3.74562);
   corr_result_2->SetBinContent(6,3.98601);
   corr_result_2->SetBinContent(5,3.70017);
   corr_result_2->SetBinContent(4,3.76348);
   corr_result_2->SetBinContent(3,3.65828);
   corr_result_2->SetBinContent(2,3.87362);
   corr_result_2->SetBinContent(1,3.51544);


   //systematic error of 4.6%
   corr_result_2->SetBinError(12,0.15394222);       
   corr_result_2->SetBinError(11,0.16010576); 
   corr_result_2->SetBinError(10,0.16743724); 
   corr_result_2->SetBinError(9,0.16296696); 
   corr_result_2->SetBinError(8,0.18438272); 
   corr_result_2->SetBinError(7,0.17229852); 
   corr_result_2->SetBinError(6,0.18335646); 
   corr_result_2->SetBinError(5,0.17020782); 
   corr_result_2->SetBinError(4,0.17312008); 
   corr_result_2->SetBinError(3,0.16828088); 
   corr_result_2->SetBinError(2,0.17818652); 
   corr_result_2->SetBinError(1,0.16171024); 
   

   corr_result_2->SetBinContent(13,3.34657);
   corr_result_2->SetBinContent(14,3.48056);
   corr_result_2->SetBinContent(15,3.63994);
   corr_result_2->SetBinContent(16,3.54276);
   corr_result_2->SetBinContent(17,4.00832);
   corr_result_2->SetBinContent(18,3.74562);
   corr_result_2->SetBinContent(19,3.98601);
   corr_result_2->SetBinContent(20,3.70017);
   corr_result_2->SetBinContent(21,3.76348);
   corr_result_2->SetBinContent(22,3.65828);
   corr_result_2->SetBinContent(23,3.87362);
   corr_result_2->SetBinContent(24,3.51544);

   //systematic error of 4.6%                                                                                                                                                                                 
   corr_result_2->SetBinError(13,0.15394222);
   corr_result_2->SetBinError(14,0.16010576);
   corr_result_2->SetBinError(15,0.16743724);
   corr_result_2->SetBinError(16,0.16296696);
   corr_result_2->SetBinError(17,0.18438272);
   corr_result_2->SetBinError(18,0.17229852);
   corr_result_2->SetBinError(19,0.18335646);
   corr_result_2->SetBinError(20,0.17020782);
   corr_result_2->SetBinError(21,0.17312008);
   corr_result_2->SetBinError(22,0.16828088);
   corr_result_2->SetBinError(23,0.17818652);
   corr_result_2->SetBinError(24,0.16171024);
   */

   /*
   corr_result_2->SetMarkerColor(1);
   corr_result_2->SetMarkerStyle(22);
   //corr_result_2->SetMarkerStyle(26);
   corr_result_2->SetMarkerSize(1.5);

   corr_result_2->Draw("pzsame");
   */

   /// ====================================================  UA5 Data

   TH1F* hEta_UA5_NSD = new TH1F("hEta_UA5_NSD",";#eta;dN/d#eta",50,-3,3);

   // positive eta
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.125),3.48);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.375),3.38);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.625),3.52);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(0.875),3.68);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.125),3.71);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.375),3.86);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.625),3.76);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(1.875),3.66);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.125),3.72);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.375),3.69);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.625),3.56);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(2.875),3.41);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(3.125),3.15);

   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(0.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(1.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(2.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(3.125),0.07);


   //negative eta
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.125),3.48);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.375),3.38);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.625),3.52);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-0.875),3.68);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.125),3.71);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.375),3.86);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.625),3.76);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-1.875),3.66);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.125),3.72);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.375),3.69);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.625),3.56);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-2.875),3.41);
   hEta_UA5_NSD->SetBinContent(hEta_UA5_NSD->FindBin(-3.125),3.15);

   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-0.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-1.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.125),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.375),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.625),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-2.875),0.07);
   hEta_UA5_NSD->SetBinError(hEta_UA5_NSD->FindBin(-3.125),0.07);

   hEta_UA5_NSD->SetMarkerStyle(25);
   hEta_UA5_NSD->SetMarkerSize(1.0);
   //hEta_UA5_NSD->Draw("psame");

   TLatex *   tex = new TLatex(2.2,4.61,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   TLatex *   tex = new TLatex(-2.8,4.61,"(a)");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   TLatex *   tex = new TLatex(0.69,4.344,"#sqrt{s}=900 GeV, NSD");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   //TLegend *leg = new TLegend(0.27,0.19,0.72,0.50,NULL,"brNDC"); 
   //TLegend *leg = new TLegend(0.19,0.20,0.51,0.46,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.21,0.20,0.53,0.46,NULL,"brNDC");
   TLegend *leg = new TLegend(0.29,0.22,0.61,0.42,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   //leg->SetTextSize(0.04);
   //leg->SetTextSize(0.037);  
   leg->SetTextSize(0.035); 
   //leg->SetHeader("   Systematic error (excluding 5 % common error)");

   /*
   TLegendEntry *entry=leg->AddEntry("","UA5 NSD","P");  
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.8);
   */

   entry=leg->AddEntry("","Hit counting, 3 layer averaged","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.8);

   //entry=leg->AddEntry("corr_result_2_all","Rec. dN/d#eta, 2. layer","P");
   entry=leg->AddEntry("","Tracklet, 3 combinations averaged","P"); 
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(21);
   //entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.8);

   entry=leg->AddEntry("","Global tracking","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.8);


   leg->Draw();

   MyCanvas->Print("dNdeta_ThreeMethods_A.eps");   
   MyCanvas->Print("dNdeta_ThreeMethods_A.gif");
   MyCanvas->Print("dNdeta_ThreeMethods_A.pdf");


}
