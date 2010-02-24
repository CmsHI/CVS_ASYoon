// SpectraExtractor_v1.C simple spectra extractor
// # CDF bins and proper error handeling?
// v2 - sorting based on the existence of b/c quark from mother quark/any along line 
// v3 - inclusion of eta in addition to y/ different processes/ includsions
// v3_TEST - separate dn/dpt with an weight at histogram level
// v4 - separate histograms for different pt_hat bins!
// v5 - differentiation between b and c
//Float_t fJPtBins[] = {62, 72, 83, 96,  110, 127, 146, 169, 195, 224, 259, 298, 344, 396, 457, 527, 700};
Float_t fJPtBins[] = {0, 62, 72, 83, 96,  110, 127, 146, 169, 195, 224, 259, 298, 344, 396, 457, 527, 700};


void Extract(Char_t *input)
{

   Float_t p_cutOff = 10.0;

   Bool_t inclusive = true;
   Bool_t tau_included = false;

   gSystem->Load("/net/hisrv0001/home/y_alive/cmssw/CMSSW_331_SpectraPPBar/lib/slc4_ia32_gcc345/pluginGenJetSpectraAnalyzerPlugins.so");
   
   // in fact, this should be dsig not dn @!
   // change it to TH1F!

   // Normal jet and hadron spectra
   TH1D *dsigdjpt = new TH1D("dsigdjpt","dsigdjpt",17,fJPtBins); // dn/djptdy ?  divide by bin size (2*y)

   dsigdjpt->Sumw2();

   TH1D *dsigdp1  = new TH1D("dsigdp1","dsigdp3",2000,0.0,500);
   TH1D *dsigdp2  = new TH1D("dsigdp2","dsigdp3",2000,0.0,500);
   TH1D *dsigdp3  = new TH1D("dsigdp3","dsigdp3",2000,0.0,500);

   dsigdp1->Sumw2();
   dsigdp2->Sumw2();
   dsigdp3->Sumw2();

   TH1D *dsigdpt  = new TH1D("dsigdpt","dsigdpt",2000,0.0,500); 
   TH1D *dsigdpt_hadronic  = new TH1D("dsigdpt_hadronic","dsigdpt_hadronic",2000,0.0,500);
   TH1D *dsigdpt_leptonic  = new TH1D("dsigdpt_leptonic","dsigdpt_leptonic",2000,0.0,500);
   
   dsigdpt->Sumw2();
   dsigdpt_hadronic->Sumw2();
   dsigdpt_leptonic->Sumw2();


   TH1D *dsigdpt1  = new TH1D("dsigdpt1","dsigdpt1",2000,0.0,500);
   TH1D *dsigdpt2  = new TH1D("dsigdpt2","dsigdpt2",2000,0.0,500);
   TH1D *dsigdpt3  = new TH1D("dsigdpt3","dsigdpt3",2000,0.0,500);
   TH1D *dsigdpt4  = new TH1D("dsigdpt4","dsigdpt4",2000,0.0,500);
   TH1D *dsigdpt5  = new TH1D("dsigdpt5","dsigdpt5",2000,0.0,500);
   TH1D *dsigdpt6  = new TH1D("dsigdpt6","dsigdpt6",2000,0.0,500);
   TH1D *dsigdpt7  = new TH1D("dsigdpt7","dsigdpt7",2000,0.0,500);
   TH1D *dsigdpt8  = new TH1D("dsigdpt8","dsigdpt8",2000,0.0,500);
   TH1D *dsigdpt9  = new TH1D("dsigdpt9","dsigdpt9",2000,0.0,500);


   TH1D *dsigdpt_LQ  = new TH1D("dsigdpt_LQ","dsigdpt_LQ",2000,0.0,500);
   TH1D *dsigdpt_LQ_hadronic  = new TH1D("dsigdpt_LQ_hadronic","dsigdpt_LQ_hadronic",2000,0.0,500);
   TH1D *dsigdpt_LQ_leptonic  = new TH1D("dsigdpt_LQ_leptonic","dsigdpt_LQ_leptonic",2000,0.0,500);

   dsigdpt_LQ->Sumw2();
   dsigdpt_LQ_hadronic->Sumw2();
   dsigdpt_LQ_leptonic->Sumw2();

   // HQ
   TH1D *dsigdpt_HQc  = new TH1D("dsigdpt_HQc","dsigdpt_HQc",2000,0.0,500);
   TH1D *dsigdpt_HQc_hadronic  = new TH1D("dsigdpt_HQc_hadronic","dsigdpt_HQc_hadronic",2000,0.0,500);
   TH1D *dsigdpt_HQc_leptonic  = new TH1D("dsigdpt_HQc_leptonic","dsigdpt_HQc_leptonic",2000,0.0,500);

   dsigdpt_HQc->Sumw2();
   dsigdpt_HQc_hadronic->Sumw2();
   dsigdpt_HQc_leptonic->Sumw2();

   TH1D *dsigdpt_HQb  = new TH1D("dsigdpt_HQb","dsigdpt_HQb",2000,0.0,500);
   TH1D *dsigdpt_HQb_hadronic  = new TH1D("dsigdpt_HQb_hadronic","dsigdpt_HQb_hadronic",2000,0.0,500);
   TH1D *dsigdpt_HQb_leptonic  = new TH1D("dsigdpt_HQb_leptonic","dsigdpt_HQb_leptonic",2000,0.0,500);

   dsigdpt_HQb->Sumw2();
   dsigdpt_HQb_hadronic->Sumw2();
   dsigdpt_HQb_leptonic->Sumw2();

   //any HQ
   TH1D *dsigdpt_anyHQc  = new TH1D("dsigdpt_anyHQc","dsigdpt_anyHQc",2000,0.0,500);
   TH1D *dsigdpt_anyHQc_hadronic  = new TH1D("dsigdpt_anyHQc_hadronic","dsigdpt_anyHQc_hadronic",2000,0.0,500);
   TH1D *dsigdpt_anyHQc_leptonic  = new TH1D("dsigdpt_anyHQc_leptonic","dsigdpt_anyHQc_leptonic",2000,0.0,500);

   dsigdpt_anyHQc->Sumw2();
   dsigdpt_anyHQc_hadronic->Sumw2();
   dsigdpt_anyHQc_leptonic->Sumw2();

   TH1D *dsigdpt_anyHQb  = new TH1D("dsigdpt_anyHQb","dsigdpt_anyHQb",2000,0.0,500);
   TH1D *dsigdpt_anyHQb_hadronic  = new TH1D("dsigdpt_anyHQb_hadronic","dsigdpt_anyHQb_hadronic",2000,0.0,500);
   TH1D *dsigdpt_anyHQb_leptonic  = new TH1D("dsigdpt_anyHQb_leptonic","dsigdpt_anyHQb_leptonic",2000,0.0,500);

   dsigdpt_anyHQb->Sumw2();
   dsigdpt_anyHQb_hadronic->Sumw2();
   dsigdpt_anyHQb_leptonic->Sumw2();


   /*
   TH1D* hp;
   TH1D* hp2;
   TH1D* hp3;
   TH1D* hj;
   
   Int_t NumBins = 18;
   Char_t cName[400];
   Char_t cName2[400];
   Char_t cName3[400];

   TObjArray Jlist(0);
   TObjArray Plist(0);
   TObjArray Plist2(0);
   TObjArray Plist3(0);
   
   cout<<"[BEG] List of historgrams to be created and added"<<endl;

   for(Int_t i = 0; i < (NumBins-1); i++){

      sprintf(cName,"hpart_jpt%dto%d",fJPtBins[i],fJPtBins[i+1]);
      hp = new TH1D(cName,cName,1000,0.0,1000);
      hp->Sumw2();

      sprintf(cName2,"hpartZ_jpt%dto%d",fJPtBins[i],fJPtBins[i+1]);
      hp2 = new TH1D(cName2,cName2,1000,0.0,10.0);
      hp2->Sumw2();
      
      sprintf(cName3,"hpartX_jpt%dto%d",fJPtBins[i],fJPtBins[i+1]);
      hp3 = new TH1D(cName3,cName3,1000,0.0,10.0);
      hp3->Sumw2();

      Plist.Add(hp);
      Plist2.Add(hp2);
      Plist3.Add(hp3);

      cout<<cName<<" and "<<cName2<<" and "<<cName3<<endl;

      sprintf(cName,"hjet_jpt%dto%d",fJPtBins[i],fJPtBins[i+1]);
      hj = new TH1D(cName,cName,1000,0.0,1000);
      hj->Sumw2();

      Jlist.Add(hj);
      cout<<cName<<endl;

   }

   cout<<"[END] List of historgrams to be created and added"<<endl;
   */

   Int_t iJIndex;
   Float_t fJPt, fJPhi, fJRapid;

   TClonesArray *CAJetPart;
   CAJetPart = new TClonesArray("FoundJets");

   TClonesArray *CAAllPart;
   CAAllPart = new TClonesArray("FoundJets");

   Char_t cFileList[200];
   cout<<"Input file name is "<<input<<endl;
   sprintf(cFileList,input);

   Char_t cFileName[256];
   ifstream fNames;
   
   Int_t ind = 1;

   Float_t NumEvents;
   Float_t MinJetPt = 0.0;
   Float_t MinJetRapid = 0.0;
   Float_t MaxJetRapid = 0.7;

   Float_t cross;
   Float_t totLum;
   
   fNames.open(cFileList);

   while(!fNames.eof()){
      fNames>>cFileName;
      cout<<cFileName<<endl;
      
      TChain *chain = new TChain("SpectraStudyTree");
      chain->Add(cFileName);

      TChain *chain2 = new TChain("SpectraStudyTree2");
      chain2->Add(cFileName);

      //--------------------------------------------------------
      // for luminosity calculation !  
      //--------------------------------------------------------

      /*
      NumEvents = 100000;
      if(ind==1) {
	 //NumEvents = 500000;
	 NumEvents = 496734;//after subtracting those with p>pt_hat with 5
	 //NumEvents = 497907;// with 6
	 cross=3.903E+01;                
      }
      if(ind==2) {
         cross = 7.367E+00;
         NumEvents = 500000;
      }
      if(ind==3) {
         cross = 4.756E-01;
         NumEvents = 500000;
      }
      if(ind==4) {
         cross = 7.946E-02;
         NumEvents = 2000000;
      }
      if(ind==5) {
         cross = 2.740E-02;
         NumEvents = 1000000;
      }
      if(ind==6) {
         cross = 4.808E-03;
         NumEvents = 1000000;
      }
      if(ind==7) {
         cross = 4.085E-04;
         NumEvents = 500000;
      }
      if(ind==8) cross = 3.429E-05;
      if(ind==9) cross = 3.331E-06;
      if(ind==10) cross = 3.679E-07;
      if(ind==11) cross = 4.375E-08;
      if(ind==12) cross = 5.098E-09;
      if(ind==13) cross = 5.602E-10;
      */


      NumEvents = 100000;
      if(ind==1) {
         NumEvents = 999604; // 396 is ruled out
         cross=3.903E+01;
      }
      if(ind==2) {
         cross = 4.759E-01;
         NumEvents = 1000000;
      }
      if(ind==3) {
         cross = 7.946E-02;
         NumEvents = 2000000;
      }
      if(ind==4) {
         cross = 2.740E-02;
         NumEvents = 1000000;
      }
      if(ind==5) {
         cross = 4.808E-03;
         NumEvents = 1000000;
      }
      if(ind==6) {
         cross = 4.085E-04;
         NumEvents = 500000;
      }
      if(ind==7) cross = 3.429E-05;   
      if(ind==8) cross = 3.331E-06; 
      if(ind==9) cross = 3.679E-07; 
      if(ind==10) cross = 4.375E-08; 
      if(ind==11) cross = 5.098E-09; 
      if(ind==12) cross = 5.602E-10;  

      totLum = NumEvents/cross;

      cout<<"Total Luminosity is "<<totLum<<" based on "<<NumEvents<<" events"<<endl;
      
      //--------------------------------------------------------        
      // Jet pt spectrum
      //--------------------------------------------------------        

      chain->SetBranchAddress("JetIndex",&iJIndex);
      chain->SetBranchAddress("JetPt",&fJPt);
      chain->SetBranchAddress("JetPhi",&fJPhi);
      chain->SetBranchAddress("JetRapidity",&fJRapid);
      chain->SetBranchAddress("JetParticles",&CAJetPart);

      cout<<"[jet spectrum] entries in this chain "<<chain->GetEntries()<<endl; 

      dsigdjpt->Sumw2();

      for(Long_t j=0;j<chain->GetEntries();j++){

	 chain->GetEntry(j);

	 Int_t iNumPart = CAJetPart->GetEntriesFast();

	 if(fJPt>MinJetPt &&
	    fabs(fJRapid)>=MinJetRapid &&
	    fabs(fJRapid)<MaxJetRapid) {

	    dsigdjpt->Fill(fJPt,1./totLum); 

	 }
      }   
      
      //--------------------------------------------------------
      // charged hadron pt spectrum  
      //--------------------------------------------------------

      chain2->SetBranchAddress("AllParticles",&CAAllPart);

      cout<<"[hadron spectrum] entries in this chain "<<chain2->GetEntries()<<endl;
      
      dsigdp1->Sumw2();
      dsigdp2->Sumw2();
      dsigdp3->Sumw2();
                     
      dsigdpt->Sumw2();
      dsigdpt_hadronic->Sumw2();
      dsigdpt_leptonic->Sumw2();
      
      dsigdpt_LQ->Sumw2();
      dsigdpt_LQ_hadronic->Sumw2();
      dsigdpt_LQ_leptonic->Sumw2();

      dsigdpt_HQc->Sumw2();
      dsigdpt_HQc_hadronic->Sumw2();
      dsigdpt_HQc_leptonic->Sumw2();

      dsigdpt_HQb->Sumw2();
      dsigdpt_HQb_hadronic->Sumw2();
      dsigdpt_HQb_leptonic->Sumw2();

      dsigdpt_anyHQb->Sumw2();
      dsigdpt_anyHQb_hadronic->Sumw2();
      dsigdpt_anyHQb_leptonic->Sumw2();

      dsigdpt_anyHQc->Sumw2();
      dsigdpt_anyHQc_hadronic->Sumw2();
      dsigdpt_anyHQc_leptonic->Sumw2();

      
      Int_t nEviolated = 0; 

      for(Long_t l=0;l<chain2->GetEntries();l++){
	 
	 chain2->GetEntry(l);

	 Int_t iNumPart2 = CAAllPart->GetEntriesFast();
	 Bool_t pEviolated = false;
	 if(ind==1){
	    for(Int_t ml = 0; ml<iNumPart2;ml++){

	       FoundJets *pTempAllPart = (FoundJets*)CAAllPart->At(ml);
	       /*
	       if((pTempAllPart->iCharge!=0) &&
		  (pTempAllPart->iStatus==1) &&
		  (fabs(pTempAllPart->fEta)<1.0)){
		  if(pTempAllPart->fP>p_cutOff) pEviolated = true;//based on the mag. of momentum
	       }
	       */
	       if((pTempAllPart->iStatus==1) &&
                  (fabs(pTempAllPart->fEta)<1.0)){
		  dsigdp1->Fill(pTempAllPart->fP,1./totLum);
                  if(pTempAllPart->fP>p_cutOff) pEviolated = true;//based on the mag. of momentum 
               }
	    }
	    if(pEviolated) {
	       nEviolated++;
	       continue;
	    }
	 }

	 for(Int_t m=0;m<iNumPart2;m++){
	    
	    FoundJets *TempAllPart = (FoundJets*)CAAllPart->At(m);
	    
	    if((TempAllPart->iCharge!=0) &&
	       (TempAllPart->iStatus==1) &&
	       (fabs(TempAllPart->fEta)<1.0)) {
	       
	       // QCD inclusive 
	       dsigdpt->Fill(TempAllPart->fPt,1./totLum);
	       if(ind==1) dsigdpt1->Fill(TempAllPart->fPt);
	       if(ind==2) dsigdpt2->Fill(TempAllPart->fPt);
	       if(ind==3) dsigdpt3->Fill(TempAllPart->fPt);
	       if(ind==4) dsigdpt4->Fill(TempAllPart->fPt);
	       if(ind==5) dsigdpt5->Fill(TempAllPart->fPt);
	       if(ind==6) dsigdpt6->Fill(TempAllPart->fPt);
	       if(ind==7) dsigdpt7->Fill(TempAllPart->fPt);
	       if(ind==8) dsigdpt8->Fill(TempAllPart->fPt);
	       if(ind==9) dsigdpt9->Fill(TempAllPart->fPt);
	       
	       // QCD hadronic
	       if((fabs(TempAllPart->iPdgId)!=11) &&
		  (fabs(TempAllPart->iPdgId)!=13)) { 
		  dsigdpt_hadronic->Fill(TempAllPart->fPt,1./totLum);
	       }
	       // QCD leptonic 
	       if((fabs(TempAllPart->iPdgId)==11) ||
		  (fabs(TempAllPart->iPdgId)==13)) {
		  dsigdpt_leptonic->Fill(TempAllPart->fPt,1./totLum);
	       }
	       
	       // LF
	       if((TempAllPart->iFromHQc!=1)&&(TempAllPart->iFromHQb!=1)){
		  // LF inclusive 
		  dsigdpt_LQ->Fill(TempAllPart->fPt,1./totLum);
		  // LF hadronic 
		  if((fabs(TempAllPart->iPdgId)!=11) &&
		     (fabs(TempAllPart->iPdgId)!=13)) {
		     dsigdpt_LQ_hadronic->Fill(TempAllPart->fPt,1./totLum);
		  }
		  // LF leptonic 
		  if((fabs(TempAllPart->iPdgId)==11) ||
		     (fabs(TempAllPart->iPdgId)==13)) {
		     dsigdpt_LQ_leptonic->Fill(TempAllPart->fPt,1./totLum);
		  }
	       }
	       
	       // HF c
	       if(TempAllPart->iFromHQc == 1){
		  // HF inclusive 
		  dsigdpt_HQc->Fill(TempAllPart->fPt,1./totLum);
		  // HF hadronic 
		  if((fabs(TempAllPart->iPdgId)!=11) &&
		     (fabs(TempAllPart->iPdgId)!=13)) {
		     dsigdpt_HQc_hadronic->Fill(TempAllPart->fPt,1./totLum);
		  }
		  // HF leptonic 
		  if((fabs(TempAllPart->iPdgId)==11) ||
		     (fabs(TempAllPart->iPdgId)==13)) {
		     dsigdpt_HQc_leptonic->Fill(TempAllPart->fPt,1./totLum);
		  }
	       }
	       
	       // HF b
	       if(TempAllPart->iFromHQb == 1){
		  // HF inclusive 
		  dsigdpt_HQb->Fill(TempAllPart->fPt,1./totLum);
		  // HF hadronic
		  if((fabs(TempAllPart->iPdgId)!=11) &&
		     (fabs(TempAllPart->iPdgId)!=13)) {
		     dsigdpt_HQb_hadronic->Fill(TempAllPart->fPt,1./totLum);
		  }
		  // HF leptonic 
		  if((fabs(TempAllPart->iPdgId)==11) ||
		     (fabs(TempAllPart->iPdgId)==13)) {
		     dsigdpt_HQb_leptonic->Fill(TempAllPart->fPt,1./totLum);
		  }
	       }
	       
	       // any HF c
	       if(TempAllPart->iFromAnyHQc == 1){
		  // HF inclusive 
		  dsigdpt_anyHQc->Fill(TempAllPart->fPt,1./totLum);
		  // HF hadronic 
		  if((fabs(TempAllPart->iPdgId)!=11) &&
		     (fabs(TempAllPart->iPdgId)!=13)) {
		     dsigdpt_anyHQc_hadronic->Fill(TempAllPart->fPt,1./totLum);
		  }
		  // HF leptonic 
		  if((fabs(TempAllPart->iPdgId)==11) ||
		     (fabs(TempAllPart->iPdgId)==13)) {
		     dsigdpt_anyHQc_leptonic->Fill(TempAllPart->fPt,1./totLum);
		  }
	       }
	       // any HF b
	       if(TempAllPart->iFromAnyHQb == 1){
		  // HF inclusive 
                     dsigdpt_anyHQb->Fill(TempAllPart->fPt,1./totLum);
                     // HF hadronic 
                     if((fabs(TempAllPart->iPdgId)!=11) &&
                        (fabs(TempAllPart->iPdgId)!=13)) {
                        dsigdpt_anyHQb_hadronic->Fill(TempAllPart->fPt,1./totLum);
                     }
                     // HF leptonic 
                     if((fabs(TempAllPart->iPdgId)==11) ||
                        (fabs(TempAllPart->iPdgId)==13)) {
                        dsigdpt_anyHQb_leptonic->Fill(TempAllPart->fPt,1./totLum);
                     }
	       }


	    }
	 }
      }
      
      if(ind==1) dsigdpt1->Sumw2(), dsigdpt1->Scale(1./totLum);
      if(ind==2) dsigdpt2->Sumw2(), dsigdpt2->Scale(1./totLum);
      if(ind==3) dsigdpt3->Sumw2(), dsigdpt3->Scale(1./totLum);
      if(ind==4) dsigdpt4->Sumw2(), dsigdpt4->Scale(1./totLum);
      if(ind==5) dsigdpt5->Sumw2(), dsigdpt5->Scale(1./totLum);
      if(ind==6) dsigdpt6->Sumw2(), dsigdpt6->Scale(1./totLum);
      if(ind==7) dsigdpt7->Sumw2(), dsigdpt7->Scale(1./totLum);
      if(ind==8) dsigdpt8->Sumw2(), dsigdpt8->Scale(1./totLum);
      if(ind==9) dsigdpt9->Sumw2(), dsigdpt9->Scale(1./totLum);
      
      if(ind==1) cout<<"Number of events with p>pt_hat = "<<nEviolated<<endl;
      ind++; //move on to the next file in file list
   }
   
   cout<<"Number of events with p>pt_hat = "<<nEviolated<<endl;
   
   Char_t cTemp[300];
   
   sprintf(cTemp,"SPECTRAv5_TEST_%s_pCutOff%.2f.root",cFileList,p_cutOff);
   
   TFile *fExtracted=new TFile(cTemp,"recreate");
   
   TDirectory *dSpectra = fExtracted->mkdir("spectra");
   
   dSpectra->cd();                                                                                                                                       
   dsigdjpt->Write();

   dsigdp1->Write();
   dsigdp2->Write();
   dsigdp3->Write();

   dsigdpt->Write();

   dsigdpt1->Write();
   dsigdpt2->Write();
   dsigdpt3->Write();
   dsigdpt4->Write();
   dsigdpt5->Write();
   dsigdpt6->Write();
   dsigdpt7->Write();
   dsigdpt8->Write();
   dsigdpt9->Write();
   
   dsigdpt_hadronic->Write();
   dsigdpt_leptonic->Write();

   dsigdpt_LQ->Write();
   dsigdpt_LQ_hadronic->Write();
   dsigdpt_LQ_leptonic->Write();

   dsigdpt_HQc->Write();
   dsigdpt_HQc_hadronic->Write();
   dsigdpt_HQc_leptonic->Write();
   
   dsigdpt_HQb->Write();
   dsigdpt_HQb_hadronic->Write();
   dsigdpt_HQb_leptonic->Write();

   dsigdpt_anyHQb->Write();
   dsigdpt_anyHQb_hadronic->Write();
   dsigdpt_anyHQb_leptonic->Write();

   dsigdpt_anyHQc->Write();
   dsigdpt_anyHQc_hadronic->Write();
   dsigdpt_anyHQc_leptonic->Write();

   fExtracted->Close();
   cout<<cTemp<<" is created"<<endl;
}


void FillHist(TObjArray list,Char_t *type,Float_t jpt,Float_t fpt,Float_t norm){



   Bool_t found = false;

   Char_t cMName[400];

   //cout<<"Number of objects in the list "<<list.GetEntries()<<endl;

   for(Int_t m = 0 ; m < 18; m++){

      if(fJPtBins[m]<jpt && fJPtBins[m+1]>=jpt){
	 sprintf(cMName,"h%s_jpt%dto%d",type,fJPtBins[m],fJPtBins[m+1]);
	 //cout<<cMName<<endl;
	 if((list.FindObject(cMName))){
	    //cout<<"Got cha"<<endl;
	    ((TH1D*) list.FindObject(cMName))->Fill(fpt,norm); //type casting
	    found = true;
	 }
      }
   }

   //if(!found) cout<<"This jet doens't belong to any of the histrograms ( jpt = "<<jpt<<" )"<<endl;
}


Float_t weight_function(Float_t x0, Float_t x1, Float_t x, Float_t exp){

   // return a weight (minimum of 1! not 0)
   Float_t fx = 1 + x1*pow((x-x0),exp);
   return fx;

}


