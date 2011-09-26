#include "PbPbTrackingTools/HiTrackMatchingAnalyzer/interface/HiTrackMatchingAnalyzer.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

HiTrackMatchingAnalyzer::HiTrackMatchingAnalyzer(const edm::ParameterSet& iConfig)
   :
   trkFst_(iConfig.getUntrackedParameter<edm::InputTag>("trkFst")),
   trkSnd_(iConfig.getUntrackedParameter<edm::InputTag>("trkSnd")),
   etaMax_(iConfig.getUntrackedParameter<double>("etaMax")),
   neededCentBins_(iConfig.getUntrackedParameter<std::vector<int> >("neededCentBins")),
   centrality_(0)
{

}


// ------------ method called to for each event  ------------
void
HiTrackMatchingAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;
   using namespace std;
   using namespace reco;


   //----- centrality information ----------------------
   centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup);
   int cbin = centrality_->getBin();

   // --------- Track 1 -------------------------------
   edm::Handle<std::vector<reco::Track> > trk1st;
   iEvent.getByLabel(trkFst_, trk1st);
   
   // --------- Track 2 -------------------------------
   edm::Handle<std::vector<reco::Track> > trk2nd;
   iEvent.getByLabel(trkSnd_, trk2nd);


   int ntrk1_eta = 0; // number of tracks within kinematic region
   int ntrk2_eta = 0;

   int nmatched = 0;

   float  fmatch1 = 0.0; // fraction of matched
   float  fmatch2 = 0.0;


   // pre-loop to count and fill full pt spectra

   for(unsigned it=0; it<trk1st->size(); ++it){
      const reco::Track & ptrk1 = (*trk1st)[it];
      if(fabs(ptrk1.eta())>=etaMax_) continue;
      ntrk1_eta++;

      for(unsigned i=0;i<neededCentBins_.size()-1;i++){
	 if(i==0){
	    if(cbin<=neededCentBins_[i+1]){
	       hTrk1Pt_Cent[i]->Fill(ptrk1.pt());
	    }
	 }else{
	    if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1]){
	       hTrk1Pt_Cent[i]->Fill(ptrk1.pt());
	    }
	 }
      } // end of centrality binned histogram  

   }

   for(unsigned it2=0; it2<trk2nd->size(); ++it2){
      const reco::Track & ptrk2 = (*trk2nd)[it2];
      if(fabs(ptrk2.eta())>=etaMax_) continue;
      ntrk2_eta++;

      for(unsigned i=0;i<neededCentBins_.size()-1;i++){
         if(i==0){
            if(cbin<=neededCentBins_[i+1]){
               hTrk2Pt_Cent[i]->Fill(ptrk2.pt());
            }
         }else{
            if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1]){
               hTrk2Pt_Cent[i]->Fill(ptrk2.pt());
            }
         }
      } // end of centrality binned histogram 
   }
   

   // track 1 
   for(unsigned it=0; it<trk1st->size(); ++it){
      const reco::Track & trk1 = (*trk1st)[it];
      
      if(fabs(trk1.eta())>=etaMax_) continue;

      double pt1 = trk1.pt();
      double pt2 = 0.0;

      bool matched = false;

      // track 2 
      for(unsigned it2=0; it2<trk2nd->size(); ++it2){
	 const reco::Track & trk2 = (*trk2nd)[it2];
	 if(fabs(trk2.eta())>=etaMax_) continue;
	 matched = isMatched(trk1,trk2);
	 pt2 = trk2.pt();
	 if (matched) break;
      }   // track 2 


      // ----------------- matched tracks ---------------------------------
      if(matched){ 
	 nmatched ++;  // increase counter
	 for(unsigned i=0;i<neededCentBins_.size()-1;i++){
	    if(i==0){
	       if(cbin<=neededCentBins_[i+1]){
		  hTrkPtMatch_Cent[i]->Fill(pt1); // doesn't matter pt1 and pt2
	       }
	    }else{
	       if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1]){
		  hTrkPtMatch_Cent[i]->Fill(pt1);
	       }
	    }
	 } // end of centrality binned histogram
      }
      // ----------------- matched tracks ---------------------------------

   } // track 1   

   // Summary -----------------------------------------

   fmatch1 = (ntrk1_eta==0) ? 999 : ((float) nmatched)/((float) ntrk1_eta);
   fmatch2 = (ntrk2_eta==0) ? 999 : ((float) nmatched)/((float) ntrk2_eta);

   for(unsigned i=0;i<neededCentBins_.size()-1;i++){
      if(i==0){
	 if(cbin<=neededCentBins_[i+1]){
	    hTrk1FShare_Cent[i]->Fill(fmatch1); 
	    hTrk2FShare_Cent[i]->Fill(fmatch2);
	 }
      }else{
	 if(cbin>neededCentBins_[i] && cbin<=neededCentBins_[i+1]){
	    hTrk1FShare_Cent[i]->Fill(fmatch1);
            hTrk2FShare_Cent[i]->Fill(fmatch2);
	 }
      }
   }

   LogDebug("HiTrackMatchingAnalyzer")<<" Number of tracks in TC1 = "<<ntrk1_eta<<endl;
   LogDebug("HiTrackMatchingAnalyzer")<<" Number of tracks in TC2 = "<<ntrk2_eta<<endl;
   LogDebug("HiTrackMatchingAnalyzer")<<" Number of matched tracks = "<<nmatched<<endl;

   LogDebug("HiTrackMatchingAnalyzer")<<" Fraction of matched track 1 = "<<fmatch1<<endl;
   LogDebug("HiTrackMatchingAnalyzer")<<" Fraction of matched track 2 = "<<fmatch2<<endl;

}

// ------------ method called once each job just before starting event loop  ------------
void
HiTrackMatchingAnalyzer::beginJob()
{

   // eta bins
   static double etaMin   = -2.6;
   static double etaMax   =  2.6;
   static double etaWidth =  0.4;

   for(double eta = etaMin; eta < etaMax + etaWidth/2; eta += etaWidth)
      etaBins.push_back(eta);

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

   
   //TFileDirectory subDir = fs->mkdir( "histColl" );

   for(unsigned i=0;i<neededCentBins_.size()-1;i++){

      hTrk1Pt_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));
      hTrk2Pt_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));

      //hTrk1PtExcl_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));
      //hTrk2PtExcl_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));
      hTrkPtMatch_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));

      hTrk1FShare_Cent.push_back( fs->make<TH1F>("","f_{shared};shared fraction",100, 0.0, 1.2));
      hTrk2FShare_Cent.push_back( fs->make<TH1F>("","f_{shared};shared fraction",100, 0.0, 1.2));
      

      if(i==0){
	 hTrk1Pt_Cent[i]->SetName(Form("hTrk1Pt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));  
	 hTrk2Pt_Cent[i]->SetName(Form("hTrk2Pt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 
	 //hTrk1PtExcl_Cent[i]->SetName(Form("hTrk1PtExcl_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 //hTrk2PtExcl_Cent[i]->SetName(Form("hTrk2PtExcl_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hTrkPtMatch_Cent[i]->SetName(Form("hTrkPtMatch_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 
	 hTrk1FShare_Cent[i]->SetName(Form("hTrk1FShare_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hTrk2FShare_Cent[i]->SetName(Form("hTrk2FShare_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
      }else{
	 hTrk1Pt_Cent[i]->SetName(Form("hTrk1Pt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrk2Pt_Cent[i]->SetName(Form("hTrk2Pt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 
	 //hTrk1PtExcl_Cent[i]->SetName(Form("hTrk1PtExcl_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
         //hTrk2PtExcl_Cent[i]->SetName(Form("hTrk2PtExcl_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrkPtMatch_Cent[i]->SetName(Form("hTrkPtMatch_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 
	 hTrk1FShare_Cent[i]->SetName(Form("hTrk1FShare_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrk2FShare_Cent[i]->SetName(Form("hTrk2FShare_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
      }
   }


}


// ------------ method called once each job just after ending the event loop  ------------
void
HiTrackMatchingAnalyzer::endJob() {
}


//  ------------ check track matching based on various criteria --------------
bool 
HiTrackMatchingAnalyzer::isMatched(const reco::Track& tr1, const reco::Track& tr2) {

   
   // hit level checks
   uint32_t tr1_nlayers     = tr1.hitPattern().trackerLayersWithMeasurement();
   uint32_t tr2_nlayers     = tr2.hitPattern().trackerLayersWithMeasurement();

   uint32_t tr1_nlayersLost = tr1.hitPattern().trackerLayersWithoutMeasurement();
   uint32_t tr2_nlayersLost = tr2.hitPattern().trackerLayersWithoutMeasurement();

   uint32_t tr1_nhits = tr1.numberOfValidHits();
   uint32_t tr2_nhits = tr2.numberOfValidHits();

   // kinematics
   double tr1_pt = tr1.pt();
   double tr2_pt = tr2.pt();

   double tr1_eta = tr1.eta();
   double tr2_eta = tr2.eta();

   double tr1_phi = tr1.phi();
   double tr2_phi = tr2.phi();

   // qualities
   double tr1_chi2n =  tr1.normalizedChi2();
   double tr2_chi2n =  tr2.normalizedChi2();


   return (
	   tr1_nlayers == tr2_nlayers &&
	   tr1_nlayersLost == tr2_nlayersLost &&
	   tr1_nhits == tr2_nhits &&
	   fabs(tr1_pt-tr2_pt) < 0.000001  &&
	   fabs(tr1_eta-tr2_eta) < 0.000001 &&
	   fabs(tr1_phi-tr2_phi) < 0.000001 &&
	   fabs(tr1_chi2n-tr2_chi2n) < 0.000001
	   );

}


//define this as a plug-in 
DEFINE_FWK_MODULE(HiTrackMatchingAnalyzer);
