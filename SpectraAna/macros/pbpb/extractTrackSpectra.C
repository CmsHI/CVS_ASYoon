#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>


// Histograms
TH1F *hNevt;
TH1F *hCentBinDist;
TH1F *hVx=0, *hVy=0, *hVz=0;
TH2F *hVzCent;

TH1F *hQual=0, *hMQual=0;

TH1F *hPt=0, *hEta=0, *hPhi=0;
TH1F *hSPt=0, *hSEta=0, *hSPhi=0;
TH1F *hAPt=0, *hAEta=0, *hAPhi=0;
TH1F *hMPt=0, *hMEta=0, *hMPhi=0;

TH1F *hVzPt1D=0, *hVzSPt1D=0, *hVzMPt1D=0; 


// Global Variables
bool doSim=true;
bool vzcut=true;
bool ccut=false;
bool useQual=false;
double maxEta=2.4;

std::vector<double> etaBins, ptBins, jetBins, centBins;

//--------------------------------------------------
void prepareHist();
//--------------------------------------------------

void extractTrackSpectra(int maxEvt = -1){

   // Define the input file and HiForest
   HiForest *c;

   //TString inf = "merged_trackAnalysis_withSim_39X";
   TString inf = "merged_trackAna_withSim_44X";

   //TString inf = "merged_trackAna_all_mb_39x";
   //TString inf = "merged_trackAna_all_mb_44x";

   TString ind = "/d01/y_alive/spectra/mc/matt_ntuples/";
   c = new HiForest(Form("%s%s.root",ind.Data(),inf.Data()));

   Long_t maxevt = (c->GetEntries()<maxEvt || maxEvt<0) ? c->GetEntries() : maxEvt;
   
   // Output file 
   TString outf = "output";
   outf.Append(Form("_%d",maxevt));
   if(vzcut) outf.Append("_vzcut");
   if(ccut) outf.Append("_ccut");
   outf.Append(Form("_qual%d",useQual));
   outf.Append(Form("_eta%1.1f",maxEta));

   // Prepare histogram =============================
   prepareHist();

   // Event loop ===================================
   int nrejected = 0;
   int ntotal = 0;

   for (int i=0;i<maxevt;i++){

      c->GetEntry(i);
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;

      if(vzcut && fabs(c->track.vz[1])>10.0) continue;
      if(ccut && c->track.cbin>32) continue;

      ntotal++;  // after all selection

      hCentBinDist->Fill(c->track.cbin); // centrality distribution for MB 
      hVx->Fill(c->track.vx[1]), hVy->Fill(c->track.vy[1]), hVz->Fill(c->track.vz[1]);
      hVzCent->Fill(c->track.vz[1],c->track.cbin);

      // rec track loop 
      int ntrk1200Mev=0, nstrk1200Mev=0, nmtrk1200Mev=0;

      for(int j = 0; j < c->track.nTrk; ++j){

	 int quality = c->track.trkQual[j];
	 
	 float pt=0.0, phi=0.0, eta=0.0;
	 pt = c->track.trkPt[j];
	 eta = c->track.trkEta[j];
	 phi = c->track.trkPhi[j];

	 float nhits = c->track.trkNHit[j];

	 hQual->Fill(quality);

	 if(useQual && quality!=1) continue;
	 if(fabs(eta)>maxEta) continue;
	 if(pt>1.2) ntrk1200Mev++;
	 
	 hPt->Fill(pt);
	 hEta->Fill(eta);
	 hPhi->Fill(phi);
      }

      hVzPt1D->Fill(c->track.vz[1],ntrk1200Mev);

      // sim tracks
      if(doSim){
	 // all sim track loop
	 for(int k = 0; k < c->track.nParticle; ++k){

	    float spt=0.0, sphi=0.0, seta=0.0;
	    spt = c->track.pPt[k];
	    seta = c->track.pEta[k];
	    sphi = c->track.pPhi[k];
	    
	    int status = c->track.pStatus[k];
	    float isAcc = c->track.pAcc[k];
	    
	    if(status!=1) continue; // only primary 
	    if(fabs(seta)>maxEta) continue; // within |eta|<etaMax
	    if(spt>1.2) nstrk1200Mev++;

	    hSPt->Fill(spt);
	    hSEta->Fill(seta);
	    hSPhi->Fill(sphi);
	    
	    // accepted sim only 
	    if(isAcc==1) hAPt->Fill(spt), hAEta->Fill(seta), hAPhi->Fill(sphi);

	    float nMatch = c->track.pNRec[k]; // float
	    int mquality = c->track.mtrkQual[k];
	    float nshits = c->track.mtrkNHit[k];

	    if(nMatch<1.) continue; // only matched
	    hMQual->Fill(mquality);

	    if(useQual && mquality!=1) continue; // with same quality 
	    if(spt>1.2) nmtrk1200Mev++;
	    
	    hMPt->Fill(spt); // use sim track pt
	    hMEta->Fill(seta);
	    hMPhi->Fill(sphi);


	 }
	 
	 hVzSPt1D->Fill(c->track.vz[1],nstrk1200Mev);
	 hVzMPt1D->Fill(c->track.vz[1],nmtrk1200Mev);

      } // end - doSim
      

   } // event loop
   
   // Event Statistics ======================
   cout<<"Total number of events processed = "<<ntotal<<endl;
   hNevt->Fill(0.5,ntotal);


   // Save output ===========================
   TFile *outputFile = new TFile(Form("/home/sungho/ana/hi2011/tracking/outputFiles/%s_%s.root",outf.Data(),inf.Data()),"recreate");

   hNevt->Write();
   hCentBinDist->Write();
   hVx->Write(), hVy->Write(), hVz->Write();
   hVzCent->Write();

   hQual->Write(), hMQual->Write();

   //hPt->Write(), hSPt->Write(), hAPt->Write(), hMPt->Write();
   hPt->Write();
   hEta->Write(), hSEta->Write(), hAEta->Write(), hMEta->Write();
   hPhi->Write(), hSPhi->Write(), hAPhi->Write(), hMPhi->Write();

   hVzPt1D->Write(), hVzSPt1D->Write(), hVzMPt1D->Write();
      
   cout<<"Output file = "<<Form("outputFiles/%s_%s.root",outf.Data(),inf.Data())<<endl;
   delete c;


}


void prepareHist(){

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();

   // pt bins
   const double small = 1e-3;
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


   hNevt = new TH1F("hNevt","Number of events",2,0,2);
   hCentBinDist = new TH1F("hCentBinDist","Centrality bin distribution; centrality bin",40,-0.5,39.5);

   hVx = new TH1F("hVx","Vertex Distribution in X; vx (cm)",200,-20,20);
   hVy = new TH1F("hVy","Vertex Distribution in Y; vy (cm)",200,-20,20);
   hVz = new TH1F("hVz","Vertex Distribution in Z; vz (cm)",200,-20,20);

   hVzCent = new TH2F("hVzCent","vz vs centrality; vz (cm); centrality bin",200,-20,20, 40,-0.5,39.5);

   hQual = new TH1F("hQual","Quality bit of rec tracks; Quality",5,0,5);
   hMQual = new TH1F("hMQual","Quality bit of matched sim tracks; Quality",5,0,5);

   hPt = new TH1F("hPt","Rec track transverse momentum ;p_{T} (GeV/c)", ptBins.size()-1, &ptBins[0]);
   hSPt = new TH1F("hSPt","Sim track transverse momentum ;p_{T} (GeV/c)", ptBins.size()-1, &ptBins[0]);
   hAPt = new TH1F("hAPt","Accepted sim track transverse momentum ;p_{T} (GeV/c)", ptBins.size()-1, &ptBins[0]);
   hMPt = new TH1F("hMPt","Matched sim track transverse momentum ;p_{T} (GeV/c)", ptBins.size()-1, &ptBins[0]);

   hVzPt1D = new TH1F("hVzPt1D","Vertex Distribution in Z weighted by N_{rec tracks}; vz (cm)",40,-20,20);
   hVzSPt1D = new TH1F("hVzSPt1D","Vertex Distribution in Z weighted by N_{sim tracks}; vz (cm)",40,-20,20);
   hVzMPt1D = new TH1F("hVzMPt1D","Vertex Distribution in Z weighted by N_{matched simtracks}; vz (cm)",40,-20,20);


   hEta = new TH1F("hEta","Rec track eta ;#eta", 100, -2.6, 2.6);
   hSEta= new TH1F("hSEta","Sim track eta ;#eta", 100, -2.6, 2.6);
   hAEta= new TH1F("hAEta","Accepted sim track eta ;#eta", 100, -2.6, 2.6);
   hMEta= new TH1F("hMEta","Matched sim track eta ;#eta", 100, -2.6, 2.6);
   
   hPhi = new TH1F("hPhi","Rec track phi; #phi", 200, -3.42, 3.42);
   hSPhi= new TH1F("hSPhi","Sim track phi; #phi", 200, -3.42, 3.42);
   hAPhi= new TH1F("hAPhi","Accepted sim track phi; #phi", 200, -3.42, 3.42);
   hMPhi= new TH1F("hMPhi","Matched sim track phi; #phi", 200, -3.42, 3.42);

}
