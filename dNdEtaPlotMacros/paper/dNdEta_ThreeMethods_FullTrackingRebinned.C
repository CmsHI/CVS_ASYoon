#include "common.h"
void dNdEta_ThreeMethods_FullTrackingRebinned() {
//=========Macro generated from canvas: MyCanvas/MyCanvas
//=========  (Thu Dec 10 11:52:00 2009) by ROOT version5.22/00d

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");

   TCanvas *MyCanvas = new TCanvas("MyCanvas", "Final result",1,360,550,600); 
   TH1 *corr_result_all = new TH1D("corr_result_all","",14,-3.5,3.5);
   corr_result_all->GetXaxis()->SetRange(2,13);

   // ========================= Cluster Counting =======================

   
   corr_result_all->SetBinContent(4,4.043821);  // -2.0 to -1.5
   corr_result_all->SetBinContent(5,3.821537);  // -1.5 to -1.0 
   corr_result_all->SetBinContent(6,3.611029); // -1.0 to -0.5
   corr_result_all->SetBinContent(7,3.501129); // -0.5 to 0.0
   corr_result_all->SetBinContent(8,3.51732);      
   corr_result_all->SetBinContent(9,3.632249);      
   corr_result_all->SetBinContent(10,3.747706);    
   corr_result_all->SetBinContent(11,4.01596);  

   corr_result_all->SetBinError(4,0.177928124);
   corr_result_all->SetBinError(5,0.168147628);
   corr_result_all->SetBinError(6,0.158885276);
   corr_result_all->SetBinError(7,0.154049676);
   corr_result_all->SetBinError(8,0.15476208);
   corr_result_all->SetBinError(9,0.159818956);
   corr_result_all->SetBinError(10,0.164899064);
   corr_result_all->SetBinError(11,0.17670224);


   /*
   corr_result_all->SetBinContent(4,4.043821);  // -2.0 to -1.5
   corr_result_all->SetBinContent(5,3.821537);  // -1.5 to -1.0 
   corr_result_all->SetBinContent(6,3.611029); // -1.0 to -0.5
   corr_result_all->SetBinContent(7,3.501129); // -0.5 to 0.0
   corr_result_all->SetBinContent(8,3.51732);      
   corr_result_all->SetBinContent(9,3.632249);      
   corr_result_all->SetBinContent(10,3.747706);    
   corr_result_all->SetBinContent(11,4.01596);  

   corr_result_all->SetBinError(4,0.181971945);     
   corr_result_all->SetBinError(5,0.171969165);     
   corr_result_all->SetBinError(6,0.162496305);     
   corr_result_all->SetBinError(7,0.157550805);    
   corr_result_all->SetBinError(8,0.1582794);     
   corr_result_all->SetBinError(9,0.163451205);    
   corr_result_all->SetBinError(10,0.16864677);    
   corr_result_all->SetBinError(11,0.1807182);    
   */

   /*
   corr_result_all->SetBinContent(4,3.954);  // -2.0 to -1.5    
   corr_result_all->SetBinContent(5,3.770);  // -1.5 to -1.0
   corr_result_all->SetBinContent(6,3.607); // -1.0 to -0.5
   corr_result_all->SetBinContent(7,3.548); // -0.5 to 0.0

   corr_result_all->SetBinContent(8,3.567); 
   corr_result_all->SetBinContent(9,3.681); 
   corr_result_all->SetBinContent(10,3.791); 
   corr_result_all->SetBinContent(11,4.025); 

   corr_result_all->SetBinError(4,0.1779);
   corr_result_all->SetBinError(5,0.1697);
   corr_result_all->SetBinError(6,0.1623);
   corr_result_all->SetBinError(7,0.1597);
   corr_result_all->SetBinError(8,0.1605);
   corr_result_all->SetBinError(9,0.1657);
   corr_result_all->SetBinError(10,0.1706);
   corr_result_all->SetBinError(11,0.1811);
   */

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
   corr_result_all->SetMaximum(6.0); 
   corr_result_all->SetMarkerStyle(20);  
   //corr_result_all->SetMarkerSize(1.5); // use rootlogon size 
   corr_result_all->SetMarkerColor(kRed);
   corr_result_all->SetLineColor(2);

   corr_result_all->GetYaxis()->SetTitle("dN_{ch}/d#eta");
   corr_result_all->GetXaxis()->SetTitle("#eta"); 
   corr_result_all->GetXaxis()->CenterTitle();
   corr_result_all->GetYaxis()->CenterTitle();
   corr_result_all->GetXaxis()->SetNdivisions(405);
   //corr_result_all->GetYaxis()->SetNdivisions(1005);
   corr_result_all->GetYaxis()->SetNdivisions(506);

   corr_result_all->Draw("pz");

   // ======= YJ Tracklet three layer combination averaged (updated with dead modules..) ======
   //                        1     2   3     4   5     6  7    8  9   10 11   12
   Double_t xAxis5[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3}; 
   
   TH1 *hMeasuredFinal = new TH1D("hMeasuredFinal","",12, xAxis5);

   hMeasuredFinal->SetBinContent(3,3.7459);
   hMeasuredFinal->SetBinContent(4,3.65462);
   hMeasuredFinal->SetBinContent(5,3.55475);
   hMeasuredFinal->SetBinContent(6,3.45008);
   hMeasuredFinal->SetBinContent(7,3.44329);
   hMeasuredFinal->SetBinContent(8,3.5244);
   hMeasuredFinal->SetBinContent(9,3.59575);
   hMeasuredFinal->SetBinContent(10,3.6612);

   hMeasuredFinal->SetBinError(3,0.1385983);
   hMeasuredFinal->SetBinError(4,0.13522094);
   hMeasuredFinal->SetBinError(5,0.13152575);
   hMeasuredFinal->SetBinError(6,0.12765296);
   hMeasuredFinal->SetBinError(7,0.12740173);
   hMeasuredFinal->SetBinError(8,0.1304028);
   hMeasuredFinal->SetBinError(9,0.13304275);
   hMeasuredFinal->SetBinError(10,0.1354644);

   /*
   hMeasuredFinal->SetBinError(3,0.142344);
   hMeasuredFinal->SetBinError(4,0.138876);
   hMeasuredFinal->SetBinError(5,0.13508);
   hMeasuredFinal->SetBinError(6,0.131103);
   hMeasuredFinal->SetBinError(7,0.130845);
   hMeasuredFinal->SetBinError(8,0.133927);
   hMeasuredFinal->SetBinError(9,0.136638);
   hMeasuredFinal->SetBinError(10,0.139126);
   */

   hMeasuredFinal->SetMarkerColor(kBlue);   
   hMeasuredFinal->SetLineColor(4);
   hMeasuredFinal->SetMarkerStyle(21); 
   //hMeasuredFinal->SetMarkerSize(1.5); // use rootlogon size 

   hMeasuredFinal->Draw("pzsame");

   /// ==================================================== Ferenc's dN/dEta   (rebinned)
   Double_t xAxis6[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3}; 
   TH1 *hMeasuredFinal2 = new TH1D("hMeasuredFinal2","",12, xAxis6);

   // Hight Stat
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

   hMeasuredFinal2->SetBinError(2,0.08646672);
   hMeasuredFinal2->SetBinError(3,0.08782272);
   hMeasuredFinal2->SetBinError(4,0.08567376);
   hMeasuredFinal2->SetBinError(5,0.08433048);
   hMeasuredFinal2->SetBinError(6,0.08369976);

   hMeasuredFinal2->SetBinError(7,0.08339136);
   hMeasuredFinal2->SetBinError(8,0.08433048);
   hMeasuredFinal2->SetBinError(9,0.0854844);
   hMeasuredFinal2->SetBinError(10,0.08758416);
   hMeasuredFinal2->SetBinError(11,0.08646672);


   /*
   hMeasuredFinal2->SetBinContent(2,3.65413);
   hMeasuredFinal2->SetBinContent(3,3.68883);
   hMeasuredFinal2->SetBinContent(4,3.73805);
   hMeasuredFinal2->SetBinContent(5,3.62817);
   hMeasuredFinal2->SetBinContent(6,3.52704);

   hMeasuredFinal2->SetBinContent(7,3.47443);
   hMeasuredFinal2->SetBinContent(8,3.63319);
   hMeasuredFinal2->SetBinContent(9,3.7577);
   hMeasuredFinal2->SetBinContent(10,3.67975);
   hMeasuredFinal2->SetBinContent(11,3.65413);
   */
   /*
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
   */


   // Systematic error of 3.1%  --> to 2.4%
   /*
   hMeasuredFinal2->SetBinError(2,0.08769912);
   hMeasuredFinal2->SetBinError(3,0.08853192);
   hMeasuredFinal2->SetBinError(4,0.0897132);
   hMeasuredFinal2->SetBinError(5,0.08707608);
   hMeasuredFinal2->SetBinError(6,0.08464896);
   hMeasuredFinal2->SetBinError(7,0.08338632);
   hMeasuredFinal2->SetBinError(8,0.08719656);
   hMeasuredFinal2->SetBinError(9,0.0901848);
   hMeasuredFinal2->SetBinError(10,0.088314);
   hMeasuredFinal2->SetBinError(11,0.08769912);
   */
   /*
   // Systematic error of 3.1%  --> to 2.3%
   hMeasuredFinal2->SetBinError(2,0.084045);
   hMeasuredFinal2->SetBinError(3,0.0848431);
   hMeasuredFinal2->SetBinError(4,0.0859752);
   hMeasuredFinal2->SetBinError(5,0.0834479);
   hMeasuredFinal2->SetBinError(6,0.0811219);
   hMeasuredFinal2->SetBinError(7,0.0799119);
   hMeasuredFinal2->SetBinError(8,0.0835634);
   hMeasuredFinal2->SetBinError(9,0.0864271);
   hMeasuredFinal2->SetBinError(10,0.0846342);
   hMeasuredFinal2->SetBinError(11,0.084045);
   */

   hMeasuredFinal2->SetMarkerColor(kBlack);
   hMeasuredFinal2->SetLineColor(1);
   hMeasuredFinal2->SetMarkerStyle(22);
   //hMeasuredFinal2->SetMarkerSize(1.5); use root logon size
   hMeasuredFinal2->Draw("pzsame");


   
   // ================== 2.36 TeV
   // ========================= Cluster Counting ======================= 
   TH1 *corr_result_all236 = new TH1D("corr_result_all236","",14,-3.5,3.5);
   corr_result_all236->GetXaxis()->SetRange(2,13);


   corr_result_all236->SetBinContent(4,5.107068);
   corr_result_all236->SetBinContent(5,4.809771);
   corr_result_all236->SetBinContent(6,4.656923);
   corr_result_all236->SetBinContent(7,4.45438);
   corr_result_all236->SetBinContent(8,4.479947);
   corr_result_all236->SetBinContent(9,4.654554);
   corr_result_all236->SetBinContent(10,4.800785);
   corr_result_all236->SetBinContent(11,5.08702);

   corr_result_all236->SetBinError(4,0.224710992);
   corr_result_all236->SetBinError(5,0.211629924);
   corr_result_all236->SetBinError(6,0.204904612);
   corr_result_all236->SetBinError(7,0.19599272);
   corr_result_all236->SetBinError(8,0.197117668);
   corr_result_all236->SetBinError(9,0.204800376);
   corr_result_all236->SetBinError(10,0.21123454);
   corr_result_all236->SetBinError(11,0.22382888);

   /*
   corr_result_all236->SetBinError(4,0.22981806);
   corr_result_all236->SetBinError(5,0.216439695);
   corr_result_all236->SetBinError(6,0.209561535);
   corr_result_all236->SetBinError(7,0.2004471);
   corr_result_all236->SetBinError(8,0.201597615);
   corr_result_all236->SetBinError(9,0.20945493);
   corr_result_all236->SetBinError(10,0.216035325);
   corr_result_all236->SetBinError(11,0.2289159);
   */

   /*
   corr_result_all236->SetBinContent(4,5.203552);
   corr_result_all236->SetBinContent(5,4.913457);
   corr_result_all236->SetBinContent(6,4.710017);
   corr_result_all236->SetBinContent(7,4.44485);
   corr_result_all236->SetBinContent(8,4.448675);
   corr_result_all236->SetBinContent(9,4.659581);
   corr_result_all236->SetBinContent(10,4.856712);
   corr_result_all236->SetBinContent(11,5.065867);

   corr_result_all236->SetBinError(4,0.23416);
   corr_result_all236->SetBinError(5,0.221106);
   corr_result_all236->SetBinError(6,0.211951);
   corr_result_all236->SetBinError(7,0.200018);
   corr_result_all236->SetBinError(8,0.20019);
   corr_result_all236->SetBinError(9,0.209681);
   corr_result_all236->SetBinError(10,0.218552);
   corr_result_all236->SetBinError(11,0.227964);
   */

   corr_result_all236->SetMarkerColor(kRed);
   corr_result_all236->SetLineColor(2);
   corr_result_all236->SetMarkerStyle(24);

   corr_result_all236->Draw("pzsame");



   /// ==================================================== Yenjie 2.36 TeV
   //                        1     2   3     4   5     6  7    8  9   10 11   12
   TH1 *hTracklet236 = new TH1D("hTracklet236","",12, xAxis5);

   hTracklet236->SetBinContent(3,4.73663);
   hTracklet236->SetBinContent(4,4.69978);
   hTracklet236->SetBinContent(5,4.61061);
   hTracklet236->SetBinContent(6,4.40814);

   hTracklet236->SetBinContent(7,4.38437);
   hTracklet236->SetBinContent(8,4.51905);
   hTracklet236->SetBinContent(9,4.6502);
   hTracklet236->SetBinContent(10,4.80977);

   hTracklet236->SetBinError(3,0.17525531);
   hTracklet236->SetBinError(4,0.17389186);
   hTracklet236->SetBinError(5,0.17059257);
   hTracklet236->SetBinError(6,0.16310118);
   hTracklet236->SetBinError(7,0.16222169);
   hTracklet236->SetBinError(8,0.16720485);
   hTracklet236->SetBinError(9,0.1720574);
   hTracklet236->SetBinError(10,0.17796149);

   
   // 4.8 % Systematic Error 
   /*
   hTracklet236->SetBinError(3,0.179992);
   hTracklet236->SetBinError(4,0.178592);
   hTracklet236->SetBinError(5,0.175203);
   hTracklet236->SetBinError(6,0.167509);
   hTracklet236->SetBinError(7,0.166606);
   hTracklet236->SetBinError(8,0.171724);
   hTracklet236->SetBinError(9,0.176707);
   hTracklet236->SetBinError(10,0.182771);
   */

   hTracklet236->SetMarkerColor(4);   
   hTracklet236->SetLineColor(4);
   hTracklet236->SetMarkerStyle(kOpenSquare); 
   //hTracklet236->SetMarkerSize(1.5); // use rootlogon size

   hTracklet236->Draw("pzsame");

   /// ==================================================== Ferenc's dN/dEta   (rebinned) 
   Double_t xAxis7[13] = {-3, -2.5, -2, -1.5, -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3};
   TH1 *hMeasuredFinal2236 = new TH1D("hMeasuredFinal2","",12, xAxis7);


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

   hMeasuredFinal2236->SetBinError(2,0.11479104);
   hMeasuredFinal2236->SetBinError(3,0.11375352);
   hMeasuredFinal2236->SetBinError(4,0.11089056);
   hMeasuredFinal2236->SetBinError(5,0.11160432);
   hMeasuredFinal2236->SetBinError(6,0.10799232);
   hMeasuredFinal2236->SetBinError(7,0.10803624);
   hMeasuredFinal2236->SetBinError(8,0.11032584);
   hMeasuredFinal2236->SetBinError(9,0.1106184);
   hMeasuredFinal2236->SetBinError(10,0.11345616);
   hMeasuredFinal2236->SetBinError(11,0.11479104);


   /*
   hMeasuredFinal2236->SetBinContent(2,4.9689);
   hMeasuredFinal2236->SetBinContent(3,4.93581);
   hMeasuredFinal2236->SetBinContent(4,4.67197);
   hMeasuredFinal2236->SetBinContent(5,4.70044);
   hMeasuredFinal2236->SetBinContent(6,4.52142);

   hMeasuredFinal2236->SetBinContent(7,4.55674);
   hMeasuredFinal2236->SetBinContent(8,4.61255);
   hMeasuredFinal2236->SetBinContent(9,4.67611);
   hMeasuredFinal2236->SetBinContent(10,4.87402);
   hMeasuredFinal2236->SetBinContent(11,4.96891);

   hMeasuredFinal2236->SetBinError(2,0.1192536);
   hMeasuredFinal2236->SetBinError(3,0.11845944);
   hMeasuredFinal2236->SetBinError(4,0.11212728);
   hMeasuredFinal2236->SetBinError(5,0.11281056);
   hMeasuredFinal2236->SetBinError(6,0.10851408);
   hMeasuredFinal2236->SetBinError(7,0.10936176);
   hMeasuredFinal2236->SetBinError(8,0.1107012);
   hMeasuredFinal2236->SetBinError(9,0.11222664);
   hMeasuredFinal2236->SetBinError(10,0.11697648);
   hMeasuredFinal2236->SetBinError(11,0.11925384);
   */

   // Systematic error of 3.1% --> 2.3%
   /*
   hMeasuredFinal2236->SetBinError(2,0.114285);
   hMeasuredFinal2236->SetBinError(3,0.113524);
   hMeasuredFinal2236->SetBinError(4,0.107455);
   hMeasuredFinal2236->SetBinError(5,0.10811);
   hMeasuredFinal2236->SetBinError(6,0.103993);
   hMeasuredFinal2236->SetBinError(7,0.104805);
   hMeasuredFinal2236->SetBinError(8,0.106089);
   hMeasuredFinal2236->SetBinError(9,0.107551);
   hMeasuredFinal2236->SetBinError(10,0.112102);
   hMeasuredFinal2236->SetBinError(11,0.114285);
   */

   hMeasuredFinal2236->SetMarkerColor(kBlack);
   hMeasuredFinal2236->SetLineColor(1);
   hMeasuredFinal2236->SetMarkerStyle(26);
   //hMeasuredFinal2->SetMarkerSize(1.5); use root logon size                                                              
   hMeasuredFinal2236->Draw("pzsame");
   


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

   //TLegend *leg = new TLegend(0.20,0.27,0.53,0.47,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.20,0.35,0.53,0.47,NULL,"brNDC"); 
   Float_t ywidth = 0.045*5;

   //TLegend *leg = new TLegend(0.27,0.26,0.70,0.26+ywidth,NULL,"brNDC");
   TLegend *leg = new TLegend(0.39,0.21,0.82,0.21+ywidth,NULL,"brNDC");

   //leg->SetNColumns(2);
   leg->SetBorderSize(0);
   leg->SetMargin(0.5);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->SetTextSize(0.033); 
   leg->SetHeader("      2.36 TeV");
   leg->AddEntry(corr_result_all236,"Cluster counting","P");
   leg->AddEntry(hTracklet236,"Tracklet","P");
   leg->AddEntry(hMeasuredFinal2236,"Tracking","P");


   //cout<<"Number of column "<<leg->GetNColumns()<<endl;
   /*
   leg->AddEntry(corr_result_all236,"","P");
   leg->AddEntry(hTracklet236,"","P"); 
   leg->AddEntry(hMeasuredFinal2236,"","P");
   */

   //TLegend *leg2 = new TLegend(0.20,0.22,0.53,0.35,NULL,"brNDC");
   //TLegend *leg2 = new TLegend(0.50,0.26,0.93,0.47,NULL,"brNDC");
   //TLegend *leg2 = new TLegend(0.39,0.26,0.82,0.26+ywidth,NULL,"brNDC");
   TLegend *leg2 = new TLegend(0.27,0.21,0.70,0.21+ywidth,NULL,"brNDC"); 
   leg2->SetMargin(0.37);
   leg2->SetBorderSize(0);
   leg2->SetTextFont(62);
   leg2->SetLineColor(1);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(0);
   //leg2->SetFillStyle(1001);
   leg2->SetFillStyle(0); 
   leg2->SetTextSize(0.033);
   leg2->SetHeader("   0.9 TeV");
   leg2->AddEntry(corr_result_all,"","P");
   leg2->AddEntry(hMeasuredFinal,"","P"); 
   leg2->AddEntry(hMeasuredFinal2,"","P");

   leg->Draw();
   leg2->Draw();

   printFinalCanvases(MyCanvas,"dNdeta_ThreeMethods",0,2);
}
