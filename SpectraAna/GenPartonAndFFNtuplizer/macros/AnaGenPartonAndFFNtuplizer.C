
#include <iostream>

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TSystem.h"

#include "GenParticleInfo.h"
#include "SpectraStudyTreeClass.h"

// 0. dN/dET of jet for a given eta range (e.g. |eta|<1.0), given sample
// 1. dN/dpT of all tracks for a given eta range , given sample
// 2. FF(jet et, trk pt, parton flavor) for a given eta range, given sample
// 3. Commissioning Plots: pTHat distribution, 

// Histograms 
TH1F *dPtHat;
TH2F *dNJetdEtdPtHat;
TH2F *dNTrkdPtdPtHat;

// Variables
vector<double> etBins, ptBins, ptHatBins;

//const double ETBINS[19] ={0., 10., 20.,30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,200.,250.,300.,500.,825.};
//const int bins = sizeof(ETBINS)/sizeof(double) - 1;

//------------------------------------
void prepareHist();
void saveHistRoot();
//------------------------------------


void AnaGenPartonAndFFNtuplizer(bool save=false){

   // variables
   bool debug = false;


   TString infdir = "/net/hisrv0001/home/y_alive/scratch1/ana/jetquenching/pythia/proq20";
   TString infile = "spectAnaGEN_March26_PtAll_numEvents5000_proq20_Ext.root";

   TString outdir = "./root_output";
   TString outfile;
   outfile.Append(Form("%s/ANA_%s",outdir.Data(),infile.Data()));


   TFile *f1 = TFile::Open(Form("%s/%s",infdir.Data(),infile.Data()));

   if(!f1) {
      Error("<Input File Reading>","File is NULL");
      return;
   }
   

   f1->cd("genSpectAna");
   TTree *nt = (TTree*) f1->FindObjectAny("SpectraStudyTree");
   if(!nt) {
      Error("<Input Tree Reading>","Tree is NULL");
      return;
   }

   gSystem->Load("/net/hisrv0001/home/y_alive/cmssw_new/CMSSW_443_JetQuenchingAna/lib/slc5_amd64_gcc434/pluginSpectraAnaGenPartonAndFFNtuplizer.so");

   SpectraStudyTreeClass stree;

   TClonesArray *asstrk = new TClonesArray("GenParticleInfo");
   TClonesArray *alltrk = new TClonesArray("GenParticleInfo");

   nt->SetBranchAddress("fPthat",&stree.fPthat);
   nt->SetBranchAddress("fCrossx",&stree.fCrossx);

   nt->SetBranchAddress("nJets",&stree.nJets);
   nt->SetBranchAddress("nTrks",stree.nTrks);
   nt->SetBranchAddress("fJPt",stree.fJPt);
   nt->SetBranchAddress("fJEt",stree.fJEt);
   nt->SetBranchAddress("fJEta",stree.fJEta);
   nt->SetBranchAddress("fJPhi",stree.fJPhi);

   nt->SetBranchAddress("AssParticles",&asstrk);
   nt->SetBranchAddress("AllParticles",&alltrk);

   // prepare histograms
   prepareHist();

   for (int i=0;i<nt->GetEntries();i++){

      nt->GetEntry(i);
      if (i%5000==0) {
	 cout<<"Cross-section = "<<stree.fCrossx<<" pTHat = "<<stree.fPthat
	 <<" number of jets = "<<stree.nJets<<" number of total tracks = "<<asstrk->GetEntriesFast()<<endl;
      }

      int ntotTrk = 0;
      dPtHat->Fill(stree.fPthat);

      // 0. Parton/Jet and Associated Tracks ------------------------------------
      for (int j=0; j<stree.nJets; ++j) {

	 float jet  = stree.fJEt[j];
	 float jpt  = stree.fJPt[j];
	 float jeta = stree.fJEta[j];
	 float jphi = stree.fJPhi[j];
	 int ntrk = stree.nTrks[j];

	 if(debug) {
	    cout<<" Found Jet (et,pt,  eta,phi) = ("<<jet<<","<<jpt<<",  "<<jeta<<","<<jphi
		<<") with "<<ntrk<<" associated charged tracks"<<endl;
	 }

	 // HIST FILLING 
	 dNJetdEtdPtHat->Fill(jet,stree.fPthat,stree.fCrossx); 

	 // associated track loop 
	 for (int k=0; k<ntrk; ++k) {
	    GenParticleInfo *AssParticles = (GenParticleInfo*)asstrk->At(ntotTrk);
	    
	    float trkpt  = AssParticles->fPt;
	    float trketa = AssParticles->fEta;
	    float trkphi = AssParticles->fPhi;

	    if(debug) {
	       cout<<"    Associated Tracks (pt,eta,phi) = ("<<trkpt<<","<<trketa<<","<<trkphi
		   <<") and z = trkpt/jetet = "<<trkpt/jpt<<endl; 
	    }

	    // HIST FILLING
	    dNTrkdPtdPtHat->Fill(trkpt,stree.fPthat,stree.fCrossx);

	    ntotTrk++;
	 } // end of tracks

      } // end of nJets


      // 1. All Charged Tracks ----------------------------------------
      for (int l=0; l<alltrk->GetEntriesFast(); ++l) {
	 GenParticleInfo *AllParticles = (GenParticleInfo*)alltrk->At(l);

	 float alltrkpt  = AllParticles->fPt;
	 float alltrketa = AllParticles->fEta;
	 float alltrkphi = AllParticles->fPhi;
      }


   } // end of all entries

   if(save){
      cout<<"Output file = "<<outfile.Data()<<endl;
      TFile *outputFile = new TFile(outfile.Data(),"recreate");
      saveHistRoot();
   }

}


void prepareHist(){

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();

   const double small = 1e-3;

   // ptHat bins
   double pthb;
   for(pthb = 0; pthb < 1400-small; pthb += 5) ptHatBins.push_back(pthb);
   ptHatBins.push_back(1400);

   // et bins
   //for(int s=0;s<bins+1;s++) etBins.push_back(ETBINS[s]);
   double etb;
   for(etb = 0; etb < 1400-small; etb += 5) etBins.push_back(etb);
   etBins.push_back(1400);

   // pt bins
   double ptb;

   // simple rebinning possible with a rebinning facto n = 2, 3, 6 !
   for(ptb =   0  ; ptb <   1.2-small; ptb +=  0.05) ptBins.push_back(ptb); // 24 bins
   for(ptb =   1.2; ptb <   2.4-small; ptb +=  0.1 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =   2.4; ptb <   7.2-small; ptb +=  0.4 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =   7.2; ptb <  14.4-small; ptb +=  1.2 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  14.4; ptb <  28.8-small; ptb +=  2.4 ) ptBins.push_back(ptb); // 6 bins 
   for(ptb =  28.8; ptb <  48.0-small; ptb +=  3.2 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  48.0; ptb <  86.4-small; ptb +=  6.4 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  86.4; ptb < 189.6-small; ptb +=  8.6 ) ptBins.push_back(ptb); // 6 bins
   ptBins.push_back(189.6);

   dPtHat = new TH1F("dPtHat","#hat{q} with no weight", ptHatBins.size()-1, &ptHatBins[0]);   
   dNJetdEtdPtHat = new TH2F("dNJetdEtdPtHat","Parton/Jet E_{T} vs #hat{q}; E_{T} (GeV); #hat{q} (GeV)", 
			  etBins.size()-1, &etBins[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNTrkdPtdPtHat = new TH2F("dNTrkdPtdPtHat","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
			     ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);
}


void saveHistRoot(){

   dPtHat->Write();
   dNJetdEtdPtHat->Write();
   dNTrkdPtdPtHat->Write();

}
