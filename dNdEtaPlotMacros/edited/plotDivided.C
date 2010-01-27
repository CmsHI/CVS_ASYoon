#include "common.h"


void plotDivided(){

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,550,600); 

   //gStyle->SetPadLeftMargin(0.5);

   // ================================== 900 GeV ==================================
   Double_t staterr900 = 0.005; // 0.5 % error

   // 1. cluster counting
   TH1 *corr_result_all = new TH1D("corr_result_all","",14,-3.5,3.5);
   corr_result_all->Sumw2();
   corr_result_all->GetXaxis()->SetRange(2,13);
   corr_result_all->SetBinContent(4,4.043821);  // -2.0 to -1.5
   corr_result_all->SetBinContent(5,3.821537);  // -1.5 to -1.0 
   corr_result_all->SetBinContent(6,3.611029); // -1.0 to -0.5
   corr_result_all->SetBinContent(7,3.501129); // -0.5 to 0.0
   corr_result_all->SetBinContent(8,3.51732);      
   corr_result_all->SetBinContent(9,3.632249);      
   corr_result_all->SetBinContent(10,3.747706);    
   corr_result_all->SetBinContent(11,4.01596);  

   corr_result_all->SetBinError(4,staterr900*corr_result_all->GetBinContent(4));
   corr_result_all->SetBinError(5,staterr900*corr_result_all->GetBinContent(5));
   corr_result_all->SetBinError(6,staterr900*corr_result_all->GetBinContent(6));
   corr_result_all->SetBinError(7,staterr900*corr_result_all->GetBinContent(7));
   corr_result_all->SetBinError(8,staterr900*corr_result_all->GetBinContent(8));
   corr_result_all->SetBinError(9,staterr900*corr_result_all->GetBinContent(9));
   corr_result_all->SetBinError(10,staterr900*corr_result_all->GetBinContent(10));
   corr_result_all->SetBinError(11,staterr900*corr_result_all->GetBinContent(11));
   
   // 2. tracklet 
   Double_t xAxis5[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3};
   TH1 *hMeasuredFinal = new TH1D("hMeasuredFinal","",12, xAxis5);
   hMeasuredFinal->Sumw2();
   hMeasuredFinal->SetBinContent(3,3.7459);
   hMeasuredFinal->SetBinContent(4,3.65462);
   hMeasuredFinal->SetBinContent(5,3.55475);
   hMeasuredFinal->SetBinContent(6,3.45008);
   hMeasuredFinal->SetBinContent(7,3.44329);
   hMeasuredFinal->SetBinContent(8,3.5244);
   hMeasuredFinal->SetBinContent(9,3.59575);
   hMeasuredFinal->SetBinContent(10,3.6612);

   hMeasuredFinal->SetBinError(3,staterr900*hMeasuredFinal->GetBinContent(3));
   hMeasuredFinal->SetBinError(4,staterr900*hMeasuredFinal->GetBinContent(4));
   hMeasuredFinal->SetBinError(5,staterr900*hMeasuredFinal->GetBinContent(5));
   hMeasuredFinal->SetBinError(6,staterr900*hMeasuredFinal->GetBinContent(6));
   hMeasuredFinal->SetBinError(7,staterr900*hMeasuredFinal->GetBinContent(7));
   hMeasuredFinal->SetBinError(8,staterr900*hMeasuredFinal->GetBinContent(8));
   hMeasuredFinal->SetBinError(9,staterr900*hMeasuredFinal->GetBinContent(9));
   hMeasuredFinal->SetBinError(10,staterr900*hMeasuredFinal->GetBinContent(10));

   // 3. full tracking
   Double_t xAxis6[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3}; 
   TH1 *hMeasuredFinal2 = new TH1D("hMeasuredFinal2","",12, xAxis6);
   hMeasuredFinal2->Sumw2();
   hMeasuredFinal2->SetBinContent(2,3.60278);
   hMeasuredFinal2->SetBinContent(3,3.65928);
   hMeasuredFinal2->SetBinContent(4,3.56974);
   hMeasuredFinal2->SetBinContent(5,3.51377);
   hMeasuredFinal2->SetBinContent(6,3.48749);
   hMeasuredFinal2->SetBinContent(7,3.47464);
   hMeasuredFinal2->SetBinContent(8,3.51377);
   hMeasuredFinal2->SetBinContent(9,3.56185);
   hMeasuredFinal2->SetBinContent(10,3.64934);
   hMeasuredFinal2->SetBinContent(11,3.60278);

   hMeasuredFinal2->SetBinError(2,staterr900*hMeasuredFinal2->GetBinContent(2));
   hMeasuredFinal2->SetBinError(3,staterr900*hMeasuredFinal2->GetBinContent(3));
   hMeasuredFinal2->SetBinError(4,staterr900*hMeasuredFinal2->GetBinContent(4));
   hMeasuredFinal2->SetBinError(5,staterr900*hMeasuredFinal2->GetBinContent(5));
   hMeasuredFinal2->SetBinError(6,staterr900*hMeasuredFinal2->GetBinContent(6));
   hMeasuredFinal2->SetBinError(7,staterr900*hMeasuredFinal2->GetBinContent(7));
   hMeasuredFinal2->SetBinError(8,staterr900*hMeasuredFinal2->GetBinContent(8));
   hMeasuredFinal2->SetBinError(9,staterr900*hMeasuredFinal2->GetBinContent(9));
   hMeasuredFinal2->SetBinError(10,staterr900*hMeasuredFinal2->GetBinContent(10));
   hMeasuredFinal2->SetBinError(11,staterr900*hMeasuredFinal2->GetBinContent(11));



   // ================================== 2.36 TeV =================================
   Double_t staterr2360 = 0.008; // 0.8 % error

   // 1. cluster counting
   TH1 *corr_result_all236 = new TH1D("corr_result_all236","",14,-3.5,3.5);
   corr_result_all236->Sumw2();
   corr_result_all236->GetXaxis()->SetRange(2,13);
   corr_result_all236->SetBinContent(4,5.107068);
   corr_result_all236->SetBinContent(5,4.809771);
   corr_result_all236->SetBinContent(6,4.656923);
   corr_result_all236->SetBinContent(7,4.45438);
   corr_result_all236->SetBinContent(8,4.479947);
   corr_result_all236->SetBinContent(9,4.654554);
   corr_result_all236->SetBinContent(10,4.800785);
   corr_result_all236->SetBinContent(11,5.08702);

   corr_result_all236->SetBinError(4,staterr2360*corr_result_all236->GetBinContent(4));
   corr_result_all236->SetBinError(5,staterr2360*corr_result_all236->GetBinContent(5));
   corr_result_all236->SetBinError(6,staterr2360*corr_result_all236->GetBinContent(6));
   corr_result_all236->SetBinError(7,staterr2360*corr_result_all236->GetBinContent(7));
   corr_result_all236->SetBinError(8,staterr2360*corr_result_all236->GetBinContent(8));
   corr_result_all236->SetBinError(9,staterr2360*corr_result_all236->GetBinContent(9));
   corr_result_all236->SetBinError(10,staterr2360*corr_result_all236->GetBinContent(10));
   corr_result_all236->SetBinError(11,staterr2360*corr_result_all236->GetBinContent(11));

   // 2. tracklet   
   TH1 *hTracklet236 = new TH1D("hTracklet236","",12, xAxis5);
   hTracklet236->Sumw2();
   hTracklet236->SetBinContent(3,4.73663);
   hTracklet236->SetBinContent(4,4.69978);
   hTracklet236->SetBinContent(5,4.61061);
   hTracklet236->SetBinContent(6,4.40814);
   hTracklet236->SetBinContent(7,4.38437);
   hTracklet236->SetBinContent(8,4.51905);
   hTracklet236->SetBinContent(9,4.6502);
   hTracklet236->SetBinContent(10,4.80977);

   hTracklet236->SetBinError(3,staterr2360*hTracklet236->GetBinContent(3));
   hTracklet236->SetBinError(4,staterr2360*hTracklet236->GetBinContent(4));
   hTracklet236->SetBinError(5,staterr2360*hTracklet236->GetBinContent(5));
   hTracklet236->SetBinError(6,staterr2360*hTracklet236->GetBinContent(6));
   hTracklet236->SetBinError(7,staterr2360*hTracklet236->GetBinContent(7));
   hTracklet236->SetBinError(8,staterr2360*hTracklet236->GetBinContent(8));
   hTracklet236->SetBinError(9,staterr2360*hTracklet236->GetBinContent(9));
   hTracklet236->SetBinError(10,staterr2360*hTracklet236->GetBinContent(10));


   // 3. full tracking
   Double_t xAxis7[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3};
   TH1 *hMeasuredFinal2236 = new TH1D("hMeasuredFinal2","",12, xAxis7);
   hMeasuredFinal2236->Sumw2();
   hMeasuredFinal2236->SetBinContent(2,4.78296);
   hMeasuredFinal2236->SetBinContent(3,4.73973);
   hMeasuredFinal2236->SetBinContent(4,4.62044);
   hMeasuredFinal2236->SetBinContent(5,4.65018);
   hMeasuredFinal2236->SetBinContent(6,4.49968);
   hMeasuredFinal2236->SetBinContent(7,4.50151);
   hMeasuredFinal2236->SetBinContent(8,4.59691);
   hMeasuredFinal2236->SetBinContent(9,4.6091);
   hMeasuredFinal2236->SetBinContent(10,4.72734);
   hMeasuredFinal2236->SetBinContent(11,4.78296);

   hMeasuredFinal2236->SetBinError(2,staterr2360*hMeasuredFinal2236->GetBinContent(2));
   hMeasuredFinal2236->SetBinError(3,staterr2360*hMeasuredFinal2236->GetBinContent(3));
   hMeasuredFinal2236->SetBinError(4,staterr2360*hMeasuredFinal2236->GetBinContent(4));
   hMeasuredFinal2236->SetBinError(5,staterr2360*hMeasuredFinal2236->GetBinContent(5));
   hMeasuredFinal2236->SetBinError(6,staterr2360*hMeasuredFinal2236->GetBinContent(6));
   hMeasuredFinal2236->SetBinError(7,staterr2360*hMeasuredFinal2236->GetBinContent(7));
   hMeasuredFinal2236->SetBinError(8,staterr2360*hMeasuredFinal2236->GetBinContent(8));
   hMeasuredFinal2236->SetBinError(9,staterr2360*hMeasuredFinal2236->GetBinContent(9));
   hMeasuredFinal2236->SetBinError(10,staterr2360*hMeasuredFinal2236->GetBinContent(10));
   hMeasuredFinal2236->SetBinError(11,staterr2360*hMeasuredFinal2236->GetBinContent(11));

   // ================================== Division  =================================
   // 0. dummy plot!
   // 0. preperation

   // SUMW2!

   Double_t minR = 1.13;
   Double_t maxR = 1.4;
   // 1. cluster counting  
   Bool_t indicator=false;
   if(!indicator){
      corr_result_all236->GetXaxis()->SetRange(6,9);
   }
   corr_result_all236->Divide(corr_result_all);

   corr_result_all236->SetMinimum(minR);    
   corr_result_all236->SetMaximum(maxR); 

   corr_result_all236->SetMarkerStyle(20);  
   corr_result_all236->SetMarkerColor(kRed);
   corr_result_all236->SetLineColor(2);

   corr_result_all236->GetYaxis()->SetTitle("(dN_{ch}/d#eta_{2.36 TeV})/(dN_{ch}/d#eta_{0.9 TeV})");
   corr_result_all236->GetXaxis()->SetTitle("#eta"); 
   corr_result_all236->GetXaxis()->CenterTitle();
   corr_result_all236->GetYaxis()->CenterTitle();
   corr_result_all236->GetXaxis()->SetNdivisions(405);
   //corr_result_all->GetYaxis()->SetNdivisions(1005);
   corr_result_all236->GetYaxis()->SetNdivisions(506);
   corr_result_all236->GetXaxis()->SetDecimals(2);

   TPad *call_pd = (TPad*)gPad;
   MyCanvas->cd();
   //gPad->SetGridx(), gPad->SetGridy();  

   const Int_t ninput = 12;
   Double_t ratio[ninput];

   cout<<"======== [Cluster counting] ========"<<endl;
   // 6,7,8,9
   Int_t iCluster = 6;
   for(Int_t i = 0; i<4; i++){
      cout<<"R["<<corr_result_all236->GetBinCenter(iCluster+i)<<"] = "<<corr_result_all236->GetBinContent(iCluster+i)<<endl;
      ratio[i] = corr_result_all236->GetBinContent(iCluster+i);
   }
   corr_result_all236->Draw("pz");
   
   // 2. tracklet
   hTracklet236->Divide(hMeasuredFinal);
   hTracklet236->SetMarkerColor(kBlue);   
   hTracklet236->SetLineColor(4);
   hTracklet236->SetMarkerStyle(21); 

   cout<<"======== [Tracklet method] ========"<<endl;
   // 5,6,7,8
   Int_t iTracklet = 5;
   for(Int_t i = 0; i<4; i++){
      cout<<"R["<<hTracklet236->GetBinCenter(iTracklet+i)<<"] = "<<hTracklet236->GetBinContent(iTracklet+i)<<endl;
      ratio[i+4]=hTracklet236->GetBinContent(iTracklet+i);
   }
   hTracklet236->Draw("pzsame");

   // 3. full tracking 
   hMeasuredFinal2236->Divide(hMeasuredFinal2);
   hMeasuredFinal2236->SetMarkerColor(kBlack);
   hMeasuredFinal2236->SetLineColor(1);
   hMeasuredFinal2236->SetMarkerStyle(22);

   cout<<"======== [Tracking method] ========"<<endl;
   // 5,6,7,8               
   Int_t iTracking = 5;
   for(Int_t i = 0; i<4; i++){
      cout<<"R["<<hMeasuredFinal2236->GetBinCenter(iTracking+i)<<"] = "<<hMeasuredFinal2236->GetBinContent(iTracking+i)<<endl;
      ratio[i+4+4]=hMeasuredFinal2236->GetBinContent(iTracking+i);
   }
   hMeasuredFinal2236->Draw("pzsame");

   
   if(indicator){
      TLine *rline = new TLine(-3,1.14171805,3,1.14171805);
   rline->SetLineStyle(2);
      rline->SetLineWidth(2);
      rline->Draw();
      
      TLatex *tex = new TLatex(0.65,1.145,"ln(2360)/ln(900)");
      tex->SetTextSize(0.04);
      tex->SetLineWidth(2);
      //tex->SetNDC();
      tex->Draw();
   }
   
   Float_t ywidth = 0.045*4;
   //TLegend *leg = new TLegend(0.39,0.21,0.82,0.21+ywidth,NULL,"brNDC");
   TLegend *leg = new TLegend(0.125,0.185,0.555,0.365,NULL,"brNDC");
   //leg->SetNColumns(2);
   leg->SetBorderSize(0);
   leg->SetMargin(0.5);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.03); 
   leg->AddEntry(corr_result_all236,"Cluster counting","P");
   leg->AddEntry(hTracklet236,"Tracklet","P");
   leg->AddEntry(hMeasuredFinal2236,"Global tracking","P");

   leg->Draw();

   // 4. Distribution of the ratio!
   cout<<"======== [Checking...] ========"<<endl;
   for(Int_t i = 0; i<12; i++){
      cout<<"check: "<<ratio[i]<<endl;
   }

   TCanvas *MyCanvas2 = new TCanvas("MyCanvas2", "",1,360,550,600);
   MyCanvas2->cd();

   TH1 *ratioDist = new TH1D("ratioDist","",55,1.20,1.40);
   for(Int_t i = 0; i<12; i++){
      ratioDist->Fill(ratio[i]);
   }

   ratioDist->GetXaxis()->SetNdivisions(909);
   ratioDist->GetYaxis()->SetNdivisions(104);
   ratioDist->GetXaxis()->SetDecimals(2);

   ratioDist->GetXaxis()->CenterTitle();
   ratioDist->GetXaxis()->SetTitle("(dN_{ch}/d#eta_{2.36 TeV})/(dN_{ch}/d#eta_{0.9 TeV})");

   ratioDist->Draw("");



   TF1 *f1 = new TF1("f1", "gaus", 1.21, 1.38);
   ratioDist->Fit("f1","R");  


   /*
   TF1 pois("pois",poissonf,1.25,1.37,2);
   pois->SetParameter(0,2);
   pois->SetParameter(1,1.3);
   ratioDist->Fit("pois","R");
   */
   
   if(indicator){
      printFinalCanvases(MyCanvas,"plotDivide",0,2);
   }else{
      printFinalCanvases(MyCanvas,"plotDivideNarrow",0,2);
   }
   printFinalCanvases(MyCanvas2,"plotDivideDist",0,0);

}

Double_t poissonf(Double_t*x,Double_t*par)                                         
{                                                                              
   return par[0]*TMath::Poisson(x[0],par[1]);
}          

//Double_t abGausian(Double_t*x, 
