#include "common.h"

void DeltaEta() {

//=========Macro generated from canvas: c62/
//=========  (Fri Apr  9 19:11:16 2010) by ROOT version5.22/00a

   gROOT->Reset();
   gROOT->ProcessLine(".x rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);
   Bool_t logscale = true;

   int mcColor = 2;
   int dataColor = 1;

   double msize = 1.5;
   
   if(logscale){
      MyCanvas->SetLogy();  
   }

   /*
   TCanvas *c62 = new TCanvas("c62", "",825,49,400,400);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c62->Range(-0.286076,-3.657653,0.2202532,-0.1937258);
   c62->SetFillColor(0);
   c62->SetBorderMode(0);
   c62->SetBorderSize(0);
   c62->SetLogy();
   c62->SetTickx(1);
   c62->SetTicky(1);
   c62->SetLeftMargin(0.17);
   c62->SetRightMargin(0.04);
   c62->SetTopMargin(0.05);
   c62->SetBottomMargin(0.15);
   c62->SetFrameLineColor(0);
   c62->SetFrameBorderMode(0);
   c62->SetFrameLineColor(0);
   c62->SetFrameBorderMode(0);
   */

   TH1 *hdeta = new TH1F("hdeta","",50,-0.2,0.2);

   if(logscale){
      hdeta->SetMaximum(1.1);
      hdeta->SetMinimum(0.0011);
   }else{
      hdeta->SetMaximum(0.3);
      hdeta->SetMinimum(-0.01);
   }

   
   //TH1 *hdeta = new TH1F("hdeta","",50,-0.2,0.2);
   hdeta->SetBinContent(0,0.1466907);
   hdeta->SetBinContent(1,0.001473301);
   hdeta->SetBinContent(2,0.001512659);
   hdeta->SetBinContent(3,0.00158176);
   hdeta->SetBinContent(4,0.001641118);
   hdeta->SetBinContent(5,0.001708424);
   hdeta->SetBinContent(6,0.001778935);
   hdeta->SetBinContent(7,0.001839318);
   hdeta->SetBinContent(8,0.001937265);
   hdeta->SetBinContent(9,0.002023673);
   hdeta->SetBinContent(10,0.002163798);
   hdeta->SetBinContent(11,0.002280078);
   hdeta->SetBinContent(12,0.002451099);
   hdeta->SetBinContent(13,0.00263366);
   hdeta->SetBinContent(14,0.002907628);
   hdeta->SetBinContent(15,0.003161597);
   hdeta->SetBinContent(16,0.003504153);
   hdeta->SetBinContent(17,0.003956066);
   hdeta->SetBinContent(18,0.004533361);
   hdeta->SetBinContent(19,0.005294626);
   hdeta->SetBinContent(20,0.006522419);
   hdeta->SetBinContent(21,0.008349302);
   hdeta->SetBinContent(22,0.01145962);
   hdeta->SetBinContent(23,0.01795024);
   hdeta->SetBinContent(24,0.03725661);
   hdeta->SetBinContent(25,0.2229392);
   hdeta->SetBinContent(26,0.22657);
   hdeta->SetBinContent(27,0.03819979);
   hdeta->SetBinContent(28,0.01819614);
   hdeta->SetBinContent(29,0.01157423);
   hdeta->SetBinContent(30,0.008372507);
   hdeta->SetBinContent(31,0.006547291);
   hdeta->SetBinContent(32,0.005354369);
   hdeta->SetBinContent(33,0.00453772);
   hdeta->SetBinContent(34,0.003944656);
   hdeta->SetBinContent(35,0.003467872);
   hdeta->SetBinContent(36,0.003108521);
   hdeta->SetBinContent(37,0.00284686);
   hdeta->SetBinContent(38,0.002635839);
   hdeta->SetBinContent(39,0.002429818);
   hdeta->SetBinContent(40,0.002286103);
   hdeta->SetBinContent(41,0.00212803);
   hdeta->SetBinContent(42,0.002017904);
   hdeta->SetBinContent(43,0.001914317);
   hdeta->SetBinContent(44,0.001838036);
   hdeta->SetBinContent(45,0.001747782);
   hdeta->SetBinContent(46,0.001692142);
   hdeta->SetBinContent(47,0.001646374);
   hdeta->SetBinContent(48,0.001564196);
   hdeta->SetBinContent(49,0.001502531);
   hdeta->SetBinContent(50,0.00146907);
   hdeta->SetBinContent(51,0.1428573);
   hdeta->SetBinError(0,0.0001371353);
   hdeta->SetBinError(1,1.374338e-05);
   hdeta->SetBinError(2,1.392574e-05);
   hdeta->SetBinError(3,1.424027e-05);
   hdeta->SetBinError(4,1.4505e-05);
   hdeta->SetBinError(5,1.479945e-05);
   hdeta->SetBinError(6,1.510177e-05);
   hdeta->SetBinError(7,1.535594e-05);
   hdeta->SetBinError(8,1.57595e-05);
   hdeta->SetBinError(9,1.610713e-05);
   hdeta->SetBinError(10,1.665545e-05);
   hdeta->SetBinError(11,1.709711e-05);
   hdeta->SetBinError(12,1.772672e-05);
   hdeta->SetBinError(13,1.837501e-05);
   hdeta->SetBinError(14,1.930711e-05);
   hdeta->SetBinError(15,2.013266e-05);
   hdeta->SetBinError(16,2.119529e-05);
   hdeta->SetBinError(17,2.252058e-05);
   hdeta->SetBinError(18,2.410783e-05);
   hdeta->SetBinError(19,2.605347e-05);
   hdeta->SetBinError(20,2.891693e-05);
   hdeta->SetBinError(21,3.271696e-05);
   hdeta->SetBinError(22,3.832948e-05);
   hdeta->SetBinError(23,4.797147e-05);
   hdeta->SetBinError(24,6.911138e-05);
   hdeta->SetBinError(25,0.0001690601);
   hdeta->SetBinError(26,0.0001704312);
   hdeta->SetBinError(27,6.998072e-05);
   hdeta->SetBinError(28,4.829892e-05);
   hdeta->SetBinError(29,3.852068e-05);
   hdeta->SetBinError(30,3.276239e-05);
   hdeta->SetBinError(31,2.897201e-05);
   hdeta->SetBinError(32,2.620004e-05);
   hdeta->SetBinError(33,2.411941e-05);
   hdeta->SetBinError(34,2.248808e-05);
   hdeta->SetBinError(35,2.108528e-05);
   hdeta->SetBinError(36,1.996295e-05);
   hdeta->SetBinError(37,1.910429e-05);
   hdeta->SetBinError(38,1.838262e-05);
   hdeta->SetBinError(39,1.76496e-05);
   hdeta->SetBinError(40,1.711969e-05);
   hdeta->SetBinError(41,1.651721e-05);
   hdeta->SetBinError(42,1.608415e-05);
   hdeta->SetBinError(43,1.566588e-05);
   hdeta->SetBinError(44,1.535058e-05);
   hdeta->SetBinError(45,1.496895e-05);
   hdeta->SetBinError(46,1.472876e-05);
   hdeta->SetBinError(47,1.452821e-05);
   hdeta->SetBinError(48,1.416099e-05);
   hdeta->SetBinError(49,1.387904e-05);
   hdeta->SetBinError(50,1.372363e-05);
   hdeta->SetBinError(51,0.0001353316);

   hdeta->SetMarkerStyle(20);
   hdeta->SetMarkerSize(msize);
   hdeta->SetMarkerColor(dataColor);
   hdeta->SetLineColor(dataColor);

   hdeta->GetXaxis()->SetTitle("#Delta#eta");
   hdeta->GetYaxis()->SetTitle("Fraction of tracklets");

   hdeta->GetXaxis()->CenterTitle();
   hdeta->GetYaxis()->CenterTitle();
   hdeta->GetXaxis()->SetNdivisions(505);

   //   hdeta->SetMaximum(1);
   hdeta->Draw("");


   /*
   hdeta->SetEntries(7800173);
   hdeta->SetFillColor(1);
   hdeta->SetFillStyle(0);
   hdeta->SetLineStyle(0);
   hdeta->SetMarkerStyle(20);
   hdeta->SetMarkerSize(0.7);
   hdeta->GetXaxis()->SetTitle("#Delta#eta^{Tracklet}_{1}^{1+2}");
   hdeta->GetXaxis()->SetLabelFont(42);
   hdeta->GetXaxis()->SetLabelOffset(0.01);
   hdeta->GetXaxis()->SetLabelSize(0.045);
   hdeta->GetXaxis()->SetTitleSize(0.055);
   hdeta->GetXaxis()->SetTitleFont(42);
   hdeta->GetYaxis()->SetTitle("Arbitrary normalization");
   hdeta->GetYaxis()->SetLabelFont(42);
   hdeta->GetYaxis()->SetLabelOffset(0.01);
   hdeta->GetYaxis()->SetLabelSize(0.045);
   hdeta->GetYaxis()->SetTitleSize(0.055);
   hdeta->GetYaxis()->SetTitleOffset(1.3);
   hdeta->GetYaxis()->SetTitleFont(42);
   hdeta->GetZaxis()->SetLabelFont(42);
   hdeta->GetZaxis()->SetLabelSize(0.045);
   hdeta->GetZaxis()->SetTitleFont(42);
   hdeta->Draw("");
   */

   
   TH1 *h2deta = new TH1F("h2deta","",50,-0.2,0.2);
   h2deta->SetBinContent(0,0.13936);
   h2deta->SetBinContent(1,0.001355331);
   h2deta->SetBinContent(2,0.001382065);
   h2deta->SetBinContent(3,0.001452559);
   h2deta->SetBinContent(4,0.001495625);
   h2deta->SetBinContent(5,0.001545087);
   h2deta->SetBinContent(6,0.001630218);
   h2deta->SetBinContent(7,0.00169894);
   h2deta->SetBinContent(8,0.001773826);
   h2deta->SetBinContent(9,0.001843164);
   h2deta->SetBinContent(10,0.001959421);
   h2deta->SetBinContent(11,0.002089392);
   h2deta->SetBinContent(12,0.002215741);
   h2deta->SetBinContent(13,0.002415589);
   h2deta->SetBinContent(14,0.002619752);
   h2deta->SetBinContent(15,0.002890556);
   h2deta->SetBinContent(16,0.003216138);
   h2deta->SetBinContent(17,0.003628623);
   h2deta->SetBinContent(18,0.004112295);
   h2deta->SetBinContent(19,0.004908298);
   h2deta->SetBinContent(20,0.005998141);
   h2deta->SetBinContent(21,0.007695233);
   h2deta->SetBinContent(22,0.01071938);
   h2deta->SetBinContent(23,0.01730351);
   h2deta->SetBinContent(24,0.03775296);
   h2deta->SetBinContent(25,0.235934);
   h2deta->SetBinContent(26,0.2400038);
   h2deta->SetBinContent(27,0.03876191);
   h2deta->SetBinContent(28,0.01762963);
   h2deta->SetBinContent(29,0.01082986);
   h2deta->SetBinContent(30,0.007768269);
   h2deta->SetBinContent(31,0.006008388);
   h2deta->SetBinContent(32,0.004886726);
   h2deta->SetBinContent(33,0.004135023);
   h2deta->SetBinContent(34,0.003587482);
   h2deta->SetBinContent(35,0.003182932);
   h2deta->SetBinContent(36,0.002852343);
   h2deta->SetBinContent(37,0.002586315);
   h2deta->SetBinContent(38,0.002378609);
   h2deta->SetBinContent(39,0.002203569);
   h2deta->SetBinContent(40,0.002075986);
   h2deta->SetBinContent(41,0.001984845);
   h2deta->SetBinContent(42,0.001841623);
   h2deta->SetBinContent(43,0.001742007);
   h2deta->SetBinContent(44,0.0016682);
   h2deta->SetBinContent(45,0.001607799);
   h2deta->SetBinContent(46,0.001559725);
   h2deta->SetBinContent(47,0.001487151);
   h2deta->SetBinContent(48,0.001433837);
   h2deta->SetBinContent(49,0.001396163);
   h2deta->SetBinContent(50,0.001353867);
   h2deta->SetBinContent(51,0.1360381);
   h2deta->SetBinError(0,0.0001036177);
   h2deta->SetBinError(1,1.021851e-05);
   h2deta->SetBinError(2,1.03188e-05);
   h2deta->SetBinError(3,1.057869e-05);
   h2deta->SetBinError(4,1.073437e-05);
   h2deta->SetBinError(5,1.091042e-05);
   h2deta->SetBinError(6,1.120696e-05);
   h2deta->SetBinError(7,1.144074e-05);
   h2deta->SetBinError(8,1.169016e-05);
   h2deta->SetBinError(9,1.191645e-05);
   h2deta->SetBinError(10,1.228652e-05);
   h2deta->SetBinError(11,1.268747e-05);
   h2deta->SetBinError(12,1.306546e-05);
   h2deta->SetBinError(13,1.364196e-05);
   h2deta->SetBinError(14,1.420676e-05);
   h2deta->SetBinError(15,1.492299e-05);
   h2deta->SetBinError(16,1.5741e-05);
   h2deta->SetBinError(17,1.671999e-05);
   h2deta->SetBinError(18,1.779948e-05);
   h2deta->SetBinError(19,1.944601e-05);
   h2deta->SetBinError(20,2.149678e-05);
   h2deta->SetBinError(21,2.434871e-05);
   h2deta->SetBinError(22,2.873756e-05);
   h2deta->SetBinError(23,3.651171e-05);
   h2deta->SetBinError(24,5.393127e-05);
   h2deta->SetBinError(25,0.0001348219);
   h2deta->SetBinError(26,0.0001359797);
   h2deta->SetBinError(27,5.464717e-05);
   h2deta->SetBinError(28,3.685417e-05);
   h2deta->SetBinError(29,2.888527e-05);
   h2deta->SetBinError(30,2.446398e-05);
   h2deta->SetBinError(31,2.151513e-05);
   h2deta->SetBinError(32,1.940323e-05);
   h2deta->SetBinError(33,1.78486e-05);
   h2deta->SetBinError(34,1.662494e-05);
   h2deta->SetBinError(35,1.565953e-05);
   h2deta->SetBinError(36,1.482402e-05);
   h2deta->SetBinError(37,1.411581e-05);
   h2deta->SetBinError(38,1.353713e-05);
   h2deta->SetBinError(39,1.302952e-05);
   h2deta->SetBinError(40,1.26467e-05);
   h2deta->SetBinError(41,1.236598e-05);
   h2deta->SetBinError(42,1.191147e-05);
   h2deta->SetBinError(43,1.158484e-05);
   h2deta->SetBinError(44,1.133677e-05);
   h2deta->SetBinError(45,1.112964e-05);
   h2deta->SetBinError(46,1.096198e-05);
   h2deta->SetBinError(47,1.070391e-05);
   h2deta->SetBinError(48,1.05103e-05);
   h2deta->SetBinError(49,1.03713e-05);
   h2deta->SetBinError(50,1.021299e-05);
   h2deta->SetBinError(51,0.0001023753);


   h2deta->SetLineWidth(2);
   h2deta->SetLineColor(mcColor);
   h2deta->SetMarkerColor(mcColor);
   h2deta->SetMarkerStyle(25);
   h2deta->SetMarkerSize(msize);

   h2deta->Draw("same hist");

   /*
   h2deta->SetEntries(1.297986e+07);
   h2deta->SetFillColor(1);
   h2deta->SetFillStyle(0);
   h2deta->SetLineColor(2);
   h2deta->SetLineStyle(0);
   h2deta->SetMarkerColor(2);
   h2deta->SetMarkerStyle(25);
   h2deta->SetMarkerSize(0.7);
   h2deta->GetXaxis()->SetTitle("#Delta#eta^{Tracklet}_{1}^{1+2}");
   h2deta->GetXaxis()->SetLabelFont(42);
   h2deta->GetXaxis()->SetLabelOffset(0.01);
   h2deta->GetXaxis()->SetLabelSize(0.045);
   h2deta->GetXaxis()->SetTitleSize(0.055);
   h2deta->GetXaxis()->SetTitleFont(42);
   h2deta->GetYaxis()->SetTitle("Arbitrary normalization");
   h2deta->GetYaxis()->SetLabelFont(42);
   h2deta->GetYaxis()->SetLabelOffset(0.01);
   h2deta->GetYaxis()->SetLabelSize(0.045);
   h2deta->GetYaxis()->SetTitleSize(0.055);
   h2deta->GetYaxis()->SetTitleOffset(1.3);
   h2deta->GetYaxis()->SetTitleFont(42);
   h2deta->GetZaxis()->SetLabelFont(42);
   h2deta->GetZaxis()->SetLabelSize(0.045);
   h2deta->GetZaxis()->SetTitleFont(42);
   h2deta->Draw("same");
   */
   

   /*
   TLegend *leg = new TLegend(0.57,0.7,0.97,0.91,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hdeta","Run132440","pl");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.7);
   entry=leg->AddEntry("h2deta","ATLAS-7TeV","pl");
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(0.7);
   leg->Draw();
   */
   TH1 *h = new TH1F("h","",50,-0.2,0.2);
   h->SetBinContent(0,13263);
   h->SetBinContent(1,127);
   h->SetBinContent(2,156);
   h->SetBinContent(3,155);
   h->SetBinContent(4,161);
   h->SetBinContent(5,126);
   h->SetBinContent(6,159);
   h->SetBinContent(7,161);
   h->SetBinContent(8,165);
   h->SetBinContent(9,171);
   h->SetBinContent(10,229);
   h->SetBinContent(11,190);
   h->SetBinContent(12,212);
   h->SetBinContent(13,196);
   h->SetBinContent(14,236);
   h->SetBinContent(15,261);
   h->SetBinContent(16,265);
   h->SetBinContent(17,294);
   h->SetBinContent(18,370);
   h->SetBinContent(19,439);
   h->SetBinContent(20,481);
   h->SetBinContent(21,666);
   h->SetBinContent(22,921);
   h->SetBinContent(23,1782);
   h->SetBinContent(24,5076);
   h->SetBinContent(25,77250);
   h->SetBinContent(26,78466);
   h->SetBinContent(27,5137);
   h->SetBinContent(28,1697);
   h->SetBinContent(29,974);
   h->SetBinContent(30,621);
   h->SetBinContent(31,500);
   h->SetBinContent(32,395);
   h->SetBinContent(33,338);
   h->SetBinContent(34,312);
   h->SetBinContent(35,267);
   h->SetBinContent(36,260);
   h->SetBinContent(37,269);
   h->SetBinContent(38,215);
   h->SetBinContent(39,201);
   h->SetBinContent(40,194);
   h->SetBinContent(41,200);
   h->SetBinContent(42,181);
   h->SetBinContent(43,211);
   h->SetBinContent(44,167);
   h->SetBinContent(45,175);
   h->SetBinContent(46,148);
   h->SetBinContent(47,160);
   h->SetBinContent(48,163);
   h->SetBinContent(49,124);
   h->SetBinContent(50,146);
   h->SetBinContent(51,13767);
   h->SetEntries(208800);
   h->SetFillColor(1);
   h->SetFillStyle(0);
   h->SetLineStyle(7);
   h->SetLineWidth(3);
   //
   h->SetLineColor(1);

   h->SetMarkerStyle(20);
   h->SetMarkerSize(1.25);
   h->GetXaxis()->SetTitle("|#Delta#eta|");
   h->GetXaxis()->SetLabelFont(42);
   h->GetXaxis()->SetLabelOffset(0.01);
   h->GetXaxis()->SetLabelSize(0.045);
   h->GetXaxis()->SetTitleSize(0.055);
   h->GetXaxis()->SetTitleFont(42);
   h->GetYaxis()->SetTitle("Fraction");
   h->GetYaxis()->SetLabelFont(42);
   h->GetYaxis()->SetLabelOffset(0.01);
   h->GetYaxis()->SetLabelSize(0.045);
   h->GetYaxis()->SetTitleSize(0.055);
   h->GetYaxis()->SetTitleOffset(1.3);
   h->GetYaxis()->SetTitleFont(42);
   h->GetZaxis()->SetLabelFont(42);
   h->GetZaxis()->SetLabelSize(0.045);
   h->GetZaxis()->SetTitleFont(42);
   h->Scale(1./1.6/208800.);
   h->GetXaxis()->SetRange(19,32);
   h->Draw("same hist");
   TLegend *leg = new TLegend(0.61,0.62,.91,0.87,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.035);
   leg->SetFillStyle(0);

   TLegendEntry *entry;

   entry=leg->AddEntry("hdeta","Data 7 TeV","p");
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2.0);
   
   
   entry=leg->AddEntry("h2deta","PYTHIA 7 TeV","l");
   entry->SetLineColor(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2.0);
   entry=leg->AddEntry("h","Primaries in MC","l");
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2.0);

   leg->Draw();

   printFinalCanvases(MyCanvas,"DeltaEta",1);


   /*/
   entry=leg->AddEntry("","PYTHIA 2.36 TeV","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(2);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2.0);
   */
   //   entry->SetTextFont(102);



   //c62->Modified();
   //c62->cd();
   //c62->SetSelected(c62);
}
