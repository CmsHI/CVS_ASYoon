//------------------------------------------------------------------------------------------ 
// October 08 2010, Andre S. Yoon 
// 
// Simple (non-compilable) macro that caculates the number of events for a given jet ET
// range and illustrates in histograms. 
//
// 
//* to use the color scheme of the histogram, turn off the force style in rootlogon.C
//------------------------------------------------------------------------------------------

void CountNForJetEtRange(TString input, float ji, float jf, bool xcheck){

  
  gStyle->SetHistFillColor(2);

  TFile *f1 = new TFile(input.Data());
  if(f1->IsOpen()==false) Error("[FileLoading]","could not open hist file [%s].",input.Data());

  cout<<"\n"<<endl;
  cout<<" ===================== This is from hJet0Pt =================================== "<<endl;
  TH1F *hJetPt = (TH1F*) f1->Get("trackAna_STD/hJet0Pt");
  hJetPt->Draw("");
  c1->SetLogy();
  float dbin = hJetPt->GetXaxis()->GetBinWidth(1);
  cout<<" Bin width = "<<dbin<<endl;

  float nevt = hJetPt->Integral("dbin");
  cout<<" >>>> Total number of events in the full range = "<<nevt<<endl;

  int bi1=0, bf=0;

  bi = hJetPt->GetXaxis()->FindBin(ji);
  if(jf==-1) bf = hJetPt->GetXaxis()->GetLast();
  else bf = hJetPt->GetXaxis()->FindBin(jf)-1;
  
  cout<<" Jet ET range: "<<ji<<" to "<<jf<<endl;
  cout<<" Corresponding bin range: "<<bi<<" to "<<bf<<endl;
  cout<<" From the found bins >> \n lower edge of the initial bin = "
      <<hJetPt->GetXaxis()->GetBinLowEdge(bi)
      <<" \n upper edge of the final bin = "
      <<hJetPt->GetXaxis()->GetBinUpEdge(bf)<<endl;

  TH1F *hJetPtReRange = (TH1F*) hJetPt->Clone("hJetPtReRange");
  hJetPtReRange->GetXaxis()->SetRange(bi,bf);
  hJetPtReRange->UseCurrentStyle();
  hJetPtReRange->Draw("same");

  float nevt_re = hJetPtReRange->Integral("dbin");
  cout<<" >>>> Total number of events in the selected range = "<<nevt_re<<endl;
  cout<<" >>>> Ratio of the selected to the full = "<<nevt_re/nevt<<endl;

  if(xcheck){
  cout<<"\n"<<endl;
  cout<<" ===================== This is from hRecJetET_STD_corr ========================= "<<endl;
  TH1F *hJetPtCorr = (TH1F*) f1->Get("trackAna_STD/hRecJetEt_STD_corr");
  TCanvas *c2 = new TCanvas("c2","c2",700,500);
  c2->cd();
  hJetPtCorr->GetXaxis()->SetRange(1,20);
  hJetPtCorr->Draw("");
  c2->SetLogy();
  float dbin2 = hJetPtCorr->GetXaxis()->GetBinWidth(1);
  cout<<" Bin width = "<<dbin2<<endl;
  
  float nevt2 = hJetPtCorr->Integral("dbin");
  cout<<" >>>> Total number of events in the full range = "<<nevt2<<endl;

  int bi2=0, bf2=0;

  bi2 = hJetPtCorr->GetXaxis()->FindBin(ji);
  if(jf==-1) bf = hJetPtCorr->GetXaxis()->GetLast();
  else bf2 = hJetPtCorr->GetXaxis()->FindBin(jf)-1;

  cout<<" Jet ET range: "<<ji<<" to "<<jf<<endl;
  cout<<" Corresponding bin range: "<<bi2<<" to "<<bf2<<endl;
  cout<<" From the found bins >> \n lower edge of the initial bin = "
      <<hJetPtCorr->GetXaxis()->GetBinLowEdge(bi2)
      <<" \n upper edge of the final bin = "
      <<hJetPtCorr->GetXaxis()->GetBinUpEdge(bf2)<<endl;

  TH1F *hJetPtReRangeCorr = (TH1F*) hJetPtCorr->Clone("hJetPtReRangeCorr");
  hJetPtReRangeCorr->GetXaxis()->SetRange(bi2,bf2);
  hJetPtReRangeCorr->UseCurrentStyle();
  hJetPtReRangeCorr->Draw("same");

  float nevt_re2 = hJetPtReRangeCorr->Integral("dbin");
  cout<<" >>>> Total number of events in the selected range = "<<nevt_re2<<endl;
  cout<<" >>>> Ratio of the selected to the full = "<<nevt_re2/nevt2<<endl;
  cout<<"\n"<<endl;

  
  }
}

