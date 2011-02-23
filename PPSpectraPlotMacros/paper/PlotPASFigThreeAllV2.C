//-----------------------------------------------------------------
// July 06 2010    Andre S. Yoon 
//-----------------------------------------------------------------

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "CorrectType.h"

#include "utilities.h"
#include "commonStyle.h"

#include "TLine.h"
#include "TLegend.h"
#endif


TFile *all_fullF=0;
TFile *mb_fullF=0;
TFile *mb_mergedF=0;
TFile *mb_partF=0;

TFile *jmt_partF=0;
TFile *jmt_fullF=0;
TFile *jmt_sec_partF=0;

TH1D *hdndpt_all_full=0;
TH1D *hdndpt_all_full_test=0;
TH1D *hdndpt_mb_full=0;
TH1D *hdndpt_mb_merged=0;
TH1D *hdndpt_mb_part=0;
TH1D *hdndpt_jmt_full=0;
TH1D *hdndpt_jmt_part=0;
TH1D *hdndpt_jmt_sec_part=0;

TGraphErrors *tdndpt_mb_merged=0;

TH1D *hdndpt_all_full_dum=0;
TH1D *hdndpt_all_full_dum2=0;
TH1D *hdndpt_mb_full_dum=0;
TH1D *hdndpt_mb_merged_dum=0;
TH1D *hdndpt_mb_part_dum=0;
TH1D *hdndpt_jmt_full_dum=0;
TH1D *hdndpt_jmt_part_dum=0;
TH1D *hdndpt_jmt_sec_part_dum=0;


TF1 *fitF=0;

TPad *pp1=0, *pp1_1=0;
TH1D *dum1=0, *dum1_1=0;

TCanvas *can2=0, *can3=0, *can4=0, *can5=0, *can6=0, *can7=0;
TH1D *dum2=0, *dum3=0, *dum4=0, *dum5=0, *dum6=0, *dum7=0;

TLegend *leg1=0, *leg2=0, *leg3=0;

TString fitFormula;

TLatex *tex=0, *tex2=0;

//-------------------------------------------------
void setPad(TCanvas *can);
void setLowerPad(TH1D *dum_low);
void fitRatio(float ix, float fx);
void putCMSPrel();
void putIntLum();
void putB();
//------------------------------------------------- 

void PlotPASFigThreeAllV2(bool save=false){

   bool lowpT = false;

   float pt_min, pt_max;
   float ymin, ymax;
   float ymin_r, ymax_r;

   if(lowpT){
      pt_min = 0.5, pt_max = 12;
      ymin = 6E-4, ymax = 3E+2;
      ymin_r = 0.97, ymax_r = 1.03;
   }else{
      pt_min = 0.5, pt_max = 390;
      ymin = 2E-13, ymax = 3E+4;
      ymin_r = 0.65, ymax_r = 1.35;
   }
   
   
   // file loading -----------------------------------------
   // All merged
   all_fullF = (TFile*) loadFile(all_fullF,
				 //"../rootOutput_postApp_2nd/jan032011_v2/MergedAll_MBproc0710_Jet15Uproc0710_Jet50Uproc1022_eta2.4_jan032011_v2_v4.root");
				 //"../rootOutput_postApp_2nd/jan032011/MergedAll_MBproc0710_Jet15Uproc0710_Jet50Uproc1022_eta2.4_jan032011_v2.root");
	    //"../rootOutput_postApp_2nd/data/dec222010/MergedAll_MBproc0710_Jet15Uproc0710_Jet50Uproc1022_eta2.4_dec222010.root");
	    //"../rootOutput_postApp_2nd_dec142010/MergedAll_MBproc0710_Jet15Uproc0710_Jet50Uproc1022_SeparateCorr_dec142010_SeparateMerging.root");
				 //"../rootOutput_postApp_2nd/dec142010/MergedAll_MBproc0710_Jet15Uproc0710_Jet50Uproc1022_SeparateCorr_dec142010.root");
				 //"./../rootOutput_postApp_2nd/jan122011/MergedAll_MBproc0710_Jet15Uproc0111_Jet50Uproc0111_eta2.4_jan122011.root");				 
				 "./../rootOutput_postApp_3rd/feb072011/MergedAll_MBproc0710_Jet15Uproc0111_Jet50Uproc0111_eta2.4_feb07011_V2.root");

   hdndpt_all_full = (TH1D*) all_fullF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_all_full==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   // MB: no ET cut
   mb_fullF = (TFile*) loadFile(mb_fullF,
				//"../rootOutput_postApp_2nd/jan032011/Merged_MBproc0710_0To2400_eta2.4_jan032011.root");
				//"../rootOutput_postApp_2nd/dec142010/Merged_MBproc0710_0To2400_SeparateCorr_dec142010.root");
				//"../rootOutput_postApp_2nd/jan122011/Merged_MBproc0710_0To2400_jan122011.root");
				"./../rootOutput_postApp_3rd/feb072011/MergedAll_MBproc0710_eta2.4_jet0to2400feb07011_V2.root");

   hdndpt_mb_full = (TH1D*) mb_fullF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_mb_full==0) {
      Error("[HistLoading]","could not get histogram");
      return;
   }
   
   // MB: 0~60
   mb_partF = (TFile*) loadFile(mb_partF,
				//"../rootOutput_postApp_2nd/jan032011/Merged_MBproc0710_0To60_eta2.4_jan032011.root");
				//"../rootOutput_postApp_2nd/dec142010/Merged_MBproc0710_0To60_SeparateCorr_dec142010.root");
				//"../rootOutput_postApp_2nd/jan122011/Merged_MBproc0710_0To60_jan122011.root");
				"./../rootOutput_postApp_3rd/feb072011/MergedAll_MBproc0710_eta2.4_jet0to60_feb07011_V2.root");

   hdndpt_mb_part = (TH1D*) mb_partF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_mb_part==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   // JMT 15: full (60~2400)
   jmt_fullF = (TFile*) loadFile(jmt_fullF,
				 //"../rootOutput_postApp_2nd/jan032011/Merged_Jet15Uproc0710_60To2400_jan032011.root");
                                 //"../rootOutput_postApp_2nd/dec142010/Merged_Jet15Uproc0710_60To2400_SeparateCorr_dec142010.root");
				 //"../rootOutput_postApp_2nd/jan122011/Merged_Jet15Uproc0111_60To2400.root");
				 "./../rootOutput_postApp_3rd/feb072011/Merged_Jet15Uproc0111_eta2.4_60To2400_feb07011_V2.root");

   hdndpt_jmt_full  = (TH1D*) jmt_fullF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_jmt_full==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   
   // JMT 15 : 60~120
   jmt_partF = (TFile*) loadFile(jmt_partF,
				 //"../rootOutput_postApp_2nd/jan032011/Merged_Jet15Uproc0710_60To120_jan032011.root");
				 //"../rootOutput_postApp_2nd/dec142010/Merged_Jet15Uproc0710_60To120_SeparateCorr_dec142010.root");
				 //"../rootOutput_postApp_2nd/jan122011/Merged_Jet15Uproc0111_60To120.root");
				 "./../rootOutput_postApp_3rd/feb072011/Merged_Jet15Uproc0111_eta2.4_60To120_feb07011_V2.root");

   hdndpt_jmt_part = (TH1D*) jmt_partF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_jmt_part==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }

   // JMT 50 : 120~INF 
   jmt_sec_partF = (TFile*) loadFile(jmt_sec_partF,
				     //"../rootOutput_postApp_2nd/jan032011_v2/CORR_JM-R10A-PR4-Jet50Uskim-v0_proc1022_final_v2_eta_0.0to2.4_jet_120.0to2400.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0_tmplt1_pu1.root");
				     //"../rootOutput_postApp_2nd/dec142010/CORR_JM-R10A-PR4-Jet50Uskim-v0_proc1022_final_v2_eta_0.0to2.4_jet_120.0to2400.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0_tmplt1.root");
				     //"../rootOutput_postApp_2nd/jan122011/CORR_JM-R10A-PR4-Jet50Uskim-v0_proc0111_JetVtx_proc0111_2011_eta_0.0to2.4_jet_120.0to2400.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0_tmplt1_pu0.root");
				     "./../rootOutput_postApp_3rd/feb072011/CORR_JM-R10A-PR4-Jet50Uskim-v0_proc0111_JetVtx_proc0111_2011_eta_0.0to2.4_jet_120.0to2400.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0_tmplt1_pu0.root");


   hdndpt_jmt_sec_part = (TH1D*) jmt_sec_partF->Get("corrTypeOne/hdndpt_full");
   if(hdndpt_jmt_sec_part==0) {
     Error("[HistLoading]","could not get histogram");
     return;
   }


   // Rebin
   int rebinF = 4;
   hdndpt_all_full->Rebin(rebinF);
   hdndpt_mb_full->Rebin(rebinF);
   hdndpt_mb_part->Rebin(rebinF);
   hdndpt_jmt_part->Rebin(rebinF);
   hdndpt_jmt_full->Rebin(rebinF);
   hdndpt_jmt_sec_part->Rebin(rebinF);

   // Basic canvas and dummy histogram
   TCanvas *call = new TCanvas("call","call",510,670);
   setPad(call);

   // ----- pad 1 
   pp1->cd();
   pp1->SetLogy();
   pp1->SetLogx();

   dum1 = GetDummyHist(0,pt_max,ymin,ymax,"p_{T}","(1/N_{evt}) dN/dp_{T}",false);
   dum1->GetYaxis()->SetNdivisions(908);
   dum1->Draw("");

   
   hdndpt_mb_part->SetFillStyle(3001);
   hdndpt_mb_part->SetFillColor(kAzure-2);
   hdndpt_mb_part->SetLineColor(kAzure-2);

   hdndpt_jmt_part->SetFillStyle(3001);
   hdndpt_jmt_part->SetLineColor(kPink-2);
   hdndpt_jmt_part->SetFillColor(kPink-2);
     
   hdndpt_jmt_sec_part->SetFillStyle(3001);
   hdndpt_jmt_sec_part->SetLineColor(kSpring-2);
   hdndpt_jmt_sec_part->SetFillColor(kSpring-2);

   hdndpt_jmt_part->Add(hdndpt_jmt_sec_part);
   hdndpt_mb_part->Add(hdndpt_jmt_part);
   
   //hdndpt_jmt_sec_part->Draw("histsame");
   //hdndpt_jmt_part->Draw("histsame");
   hdndpt_mb_part->Draw("histsame");
   hdndpt_jmt_part->Draw("histsame");
   hdndpt_jmt_sec_part->Draw("histsame"); 


   // Adding test
   /*
   hdndpt_all_full_test = (TH1D*) hdndpt_mb_part->Clone("hdndpt_all_full_test");
   hdndpt_all_full_test->Add(hdndpt_jmt_part);
   hdndpt_all_full_test->Add(hdndpt_jmt_sec_part);
   th1Style1(hdndpt_all_full_test,1,20,1.0,1,1.0,1,1);
   */

   hdndpt_jmt_full->GetXaxis()->SetRange(hdndpt_jmt_full->GetXaxis()->FindBin(40),
			     hdndpt_jmt_full->GetXaxis()->GetLast());
   
   th1Style1(hdndpt_mb_full,1,25,1.2,1,1.5,1,1);
   th1Style1(hdndpt_jmt_full,1,26,1.2,1,1.5,1,1);
   th1Style1(hdndpt_all_full,1,20,1.0,1,1.0,1,1);


   leg1 = new TLegend(0.20,0.055,0.65,0.26);
   leg1->SetMargin(0.3), leg1->SetBorderSize(1);
   leg1->SetFillColor(kWhite);
   leg1->SetTextSize(0.025), leg1->SetMargin(0.2);
   leg1->AddEntry(hdndpt_mb_part,"HLT MB (E_{T} < 60 GeV)","lf");
   leg1->AddEntry(hdndpt_jmt_part,"HLT, E_{T}^{un} > 15 GeV (60 #leq E_{T} < 120 GeV)","lf");
   leg1->AddEntry(hdndpt_jmt_sec_part,"HLT, E_{T}^{un} > 50 GeV (120 #leq E_{T})","lf");
   leg1->Draw();

   leg2 = new TLegend(0.50,0.6,0.94,0.83);
   leg2->SetMargin(0.3), leg2->SetBorderSize(0);
   leg2->SetFillColor(kWhite), leg2->SetFillStyle(0);
   leg2->SetTextSize(0.030), leg1->SetMargin(0.2);
   leg2->SetHeader("   #sqrt{s} = 7 TeV  |#eta|<2.4  #scale[0.7]{#int}Ldt = 2.96 pb^{-1}");
   leg2->AddEntry(hdndpt_all_full,"Combined samples","pl");
   leg2->AddEntry(hdndpt_mb_full,"HLT MB (all E_{T})","pl");
   leg2->AddEntry(hdndpt_jmt_full,"HLT, E_{T}^{un} > 15 GeV (E_{T} #geq 60)","pl");
   leg2->Draw();


   putCMSPrel();
   //putIntLum();

   putB();

   // ----- pad 2 
   pp1_1->cd();
   pp1_1->SetLogx();
   
   dum1_1 = GetDummyHist(0,pt_max,ymin_r,ymax_r,"p_{T} [GeV/c]","Ratio",false);
   //dum1_1 = GetDummyHist(0,pt_max,ymin_r,ymax_r,"p_{T}","MB / Combined",false); 
   setLowerPad(dum1_1);
   dum1_1->Draw("");

   TLine *line = new TLine(0,1,pt_max,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();

   hdndpt_all_full_dum = (TH1D*) hdndpt_all_full->Clone("hdndpt_all_full_dum");
   hdndpt_mb_full_dum = (TH1D*) hdndpt_mb_full->Clone("hdndpt_mb_full_dum"); 
   hdndpt_all_full_dum->Divide(hdndpt_mb_full_dum);
   //th1Style1(hdndpt_all_full_dum,1,20,1.0,1,1.5,1,1); 

   hdndpt_all_full_dum2 = (TH1D*) hdndpt_all_full->Clone("hdndpt_all_full_dum2");
   hdndpt_jmt_full_dum = (TH1D*) hdndpt_jmt_full->Clone("hdndpt_jmt_full_dum");
   hdndpt_all_full_dum2->Divide(hdndpt_jmt_full_dum);
   th1Style1(hdndpt_all_full_dum2,1,26,1.1,1,1.5,1,1);

   leg3 = new TLegend(0.19,0.44,0.53,0.64);
   leg3->SetMargin(0.3), leg3->SetBorderSize(0);
   leg3->SetFillColor(kWhite);
   leg3->SetFillStyle(0);
   leg3->SetTextSize(0.05), leg3->SetMargin(0.2);
   leg3->AddEntry(hdndpt_all_full_dum,"Combined/MB","pl");
   leg3->AddEntry(hdndpt_all_full_dum2,"Combined/HLT, E_{T}^{un} > 15 GeV (E_{T} #geq 60)","pl");
   leg3->Draw();


   // fit ratio
   //fitRatio(14,42);
   
   //Save canvase
   if(save){
     printCanvases(call,"dndpt_comparison_full_vs_merged_all_v2",0,1);
   }

}

void fitRatio(float ix, float fx){

   can2 = new TCanvas("can2","can2",550,410);
   can2->cd();
   //can2->SetLogy();
   
   dum2 = (TH1D*) dum1_1->Clone("dum2");
   dum2->Draw();

   //fitFormula = "[0]*x+[1]";
   fitFormula = "[0]";

   cout<<"\n"<<"[fitdNdpT] fitting function = "<<fitFormula.Data()<<"\n"<<endl;

   fitF = new TF1("fitFunction",fitFormula.Data(),ix,fx);

   fitF->SetParameters(1.0,0.0);

   fitF->SetLineColor(4);
   fitF->SetLineWidth(3);

   hdndpt_mb_full_dum->Fit(fitF,"RO");

   hdndpt_mb_full_dum->SetMarkerSize(1), hdndpt_mb_full_dum->Draw("pzsame");
   fitF->Draw("same");
}



void setLowerPad(TH1D *dum_low){

   //Just to make lower pannel lable appearing as similar size as upper one                                                                                                  
   dum_low->GetYaxis()->SetLabelSize(0.07);
   dum_low->GetYaxis()->SetTitleSize(0.08);
   dum_low->GetYaxis()->SetTitleOffset(1.0);

   dum_low->GetXaxis()->SetLabelSize(0.09);
   dum_low->GetXaxis()->SetLabelOffset(0.05);
   dum_low->GetXaxis()->SetTitleSize(0.11);
   dum_low->GetXaxis()->SetTitleOffset(1.47);

   dum_low->GetYaxis()->SetNdivisions(405);
   dum_low->GetYaxis()-> SetDecimals(true);
   dum_low->Draw();

}



void setPad(TCanvas *can){

   can->cd();

   pp1 = new TPad("p1","p1",0,0.34,1,1,0,0,0);
   pp1->SetBottomMargin(0.0);
   pp1->SetTopMargin(0.05*(1/0.72));

   pp1->Draw();
   pp1->cd();
   pp1->SetNumber(1);

   can->cd();

   pp1_1 = new TPad("p1_1","p1_1",0,0.0,1,0.34,0,0,0);
   pp1_1->SetTopMargin(0);
   pp1_1->SetBottomMargin(0.14*(1/0.34));
   pp1_1->Draw();
   pp1_1->cd();
   pp1_1->SetNumber(2);
}

void putB(){
  TLatex * texB;
  texB= new TLatex(0.2,0.86,"(b)");
  texB->SetTextSize(0.04);
  texB->SetLineWidth(2);
  texB->SetNDC();
  texB->Draw();
}

void putCMSPrel(){
  tex = new TLatex(0.66,0.86,"CMS Preliminary");
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}


void putIntLum(){
  //tex2 = new TLatex(0.67,0.77,"#intLdt = 10.2 nb^{-1}");                                                                                                                         
  //tex2 = new TLatex(0.43,0.85,"#intLdt = 10.2 nb^{-1}");                                                                                                                         
  tex2 = new TLatex(0.68,0.78,"#intLdt = 10.2 nb^{-1}");
  tex2->SetTextSize(0.034);
  tex2->SetLineWidth(2);
  tex2->SetNDC();
  tex2->Draw();
}
