#include "PbPbTrackingTools/HiTrackMatchingAnalyzer/interface/HiTrackMatchingAnalyzer.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

HiTrackMatchingAnalyzer::HiTrackMatchingAnalyzer(const edm::ParameterSet& iConfig)
   :
   trkFst_(iConfig.getUntrackedParameter<edm::InputTag>("trkFst")),
   trkSnd_(iConfig.getUntrackedParameter<edm::InputTag>("trkSnd")),
   jetTags_(iConfig.getUntrackedParameter<edm::InputTag>("jetTags")),
   etaMax_(iConfig.getUntrackedParameter<double>("etaMax")),
   jetEtCuts_(iConfig.getUntrackedParameter<std::vector<double> >("jetEtCuts")),
   needTree_(iConfig.getUntrackedParameter<bool>("needTree")),
   ptMinTree_(iConfig.getUntrackedParameter<double>("ptMinTree")),
   checkHitMat_(iConfig.getUntrackedParameter<bool>("checkHitMat")),
   drMax_(iConfig.getUntrackedParameter<double>("drMax")),
   ptMinHitMat_(iConfig.getUntrackedParameter<double>("ptMinHitMat")),
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

   //-------- jet --------------------------------
   float leadJetEt_ = 0.0, leadJetEta_=-999.0;

   edm::Handle<std::vector<pat::Jet> > jets;
   iEvent.getByLabel(jetTags_, jets);

   vector<const reco::Candidate *> sortedJets;     
         
   for(unsigned it=0; it<jets->size(); ++it){
      const reco::Candidate* jet = &((*jets)[it]);
      sortedJets.push_back(jet);
      sortByEtRef (&sortedJets);
   }

   for(unsigned it=0; it<sortedJets.size(); ++it){
      if(fabs(sortedJets[it]->eta())>2.0) continue;
      leadJetEt_  = sortedJets[it]->et(), leadJetEta_ = sortedJets[it]->eta();
      break;
   }

   // Placing jet Et cuts such that the events are reqiured to have jet ET:[low,high]
   if(jetEtCuts_.size()!=0 && (leadJetEt_<jetEtCuts_[0] || leadJetEt_>=jetEtCuts_[1])) return;

   // --------- Track 1 -------------------------------
   edm::Handle<std::vector<reco::Track> > trk1st;
   iEvent.getByLabel(trkFst_, trk1st);

   const reco::TrackCollection *TC1 = 0; 
   TC1 = trk1st.product();
   const reco::TrackCollection tC1 = *TC1;

   // --------- Track 2 -------------------------------
   edm::Handle<std::vector<reco::Track> > trk2nd;
   iEvent.getByLabel(trkSnd_, trk2nd);

   const reco::TrackCollection *TC2 = 0;
   TC2 = trk2nd.product();
   const reco::TrackCollection tC2 = *TC2;



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

      // fill tree
      if(needTree_ && ptrk1.pt()>ptMinTree_){
	 nt_trk1->Fill(iEvent.id().run(),iEvent.id().event(),cbin,ptrk1.eta(),ptrk1.phi(),ptrk1.pt(),ptrk1.numberOfValidHits(),
		       ptrk1.normalizedChi2(),ptrk1.ptError()/ptrk1.pt(),ptrk1.dzError(),ptrk1.d0Error(),ptrk1.algo());
      }

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

      if(needTree_ && ptrk2.pt()>ptMinTree_){
         nt_trk2->Fill(iEvent.id().run(),iEvent.id().event(),cbin,ptrk2.eta(),ptrk2.phi(),ptrk2.pt(),ptrk2.numberOfValidHits(),
                       ptrk2.normalizedChi2(),ptrk2.ptError()/ptrk2.pt(),ptrk2.dzError(),ptrk2.d0Error(),ptrk2.algo());
      }

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

	 // fill tree
	 if(needTree_ && trk1.pt()>ptMinTree_){  // trk1 or trk 2 doesn't matter as there are identical
	    nt_trk_mat->Fill(iEvent.id().run(),iEvent.id().event(),cbin,trk1.eta(),trk1.phi(),trk1.pt(),trk1.numberOfValidHits(),
			     trk1.normalizedChi2(),trk1.ptError()/trk1.pt(),trk1.dzError(),trk1.d0Error(),trk1.algo());
	 }

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

   

   // Hit level track matchin -------------------------------------
   // -------------------------------------------------------------
   // since track matcing is time cosuming, look at tracks with 
   // certain kinematic range i.e. pT>40 GeV/c, |eta|<1.0, dR<0.005 
   // and etc
   // -------------------------------------------------------------
   if(checkHitMat_){

      // obtain rec hits
      std::map<reco::TrackCollection::const_iterator, std::vector<const TrackingRecHit*> > rh1;
      std::map<reco::TrackCollection::const_iterator, std::vector<const TrackingRecHit*> > rh2;
      for (reco::TrackCollection::const_iterator track=tC1.begin(); track!=tC1.end(); ++track){
	 trackingRecHit_iterator itB = track->recHitsBegin();
	 trackingRecHit_iterator itE = track->recHitsEnd();
	 for (trackingRecHit_iterator it = itB;  it != itE; ++it) { 
	    const TrackingRecHit* hit = &(**it);
	    rh1[track].push_back(hit);
	 }
      }

      for (reco::TrackCollection::const_iterator track=tC2.begin(); track!=tC2.end(); ++track){
	 trackingRecHit_iterator jtB = track->recHitsBegin();
	 trackingRecHit_iterator jtE = track->recHitsEnd();
	 for (trackingRecHit_iterator jt = jtB;  jt != jtE; ++jt) { 
	    const TrackingRecHit* hit = &(**jt);
	    rh2[track].push_back(hit);
	 }
      }

      // track 1
      for (reco::TrackCollection::const_iterator track=tC1.begin(); track!=tC1.end(); ++track){

	 // kinematic cut
	 if(fabs(track->eta())>=etaMax_ || track->pt()<ptMinHitMat_) continue;

	 std::vector<const TrackingRecHit*>& iHits = rh1[track]; 
	 unsigned nh1 = iHits.size();
	 
	 int counter=0;
	 
	 // track 2
	 for (reco::TrackCollection::const_iterator track2=tC2.begin(); track2!=tC2.end(); ++track2){

	    // kinematic cut
	    if(fabs(track2->eta())>=etaMax_ || track2->pt()<ptMinHitMat_) continue;

	    // dR requirement 
	    float dphi = track->phi() - track2->phi();
	    if(fabs(dphi)>(TMath::Pi()) && dphi>0) dphi = dphi - (float) 2.*TMath::Pi();
	    if(fabs(dphi)>(TMath::Pi()) && dphi<0) dphi = dphi + (float) 2.*TMath::Pi();
	    float deta = track->eta() - track2->eta();;
	    float dr = TMath::Sqrt(dphi*dphi + deta*deta);

	    //cout<<" pt1 = "<<track->pt()<<" pt 2 = "<<track2->pt()
	    //<<" deta = "<<deta<<" dphi = "<<dphi<<" dr = "<<dr<<endl;

	    if(dr>drMax_ || dr<0.00000000001) continue; // exclude self-matching
	    counter++;

	    std::vector<const TrackingRecHit*>& jHits = rh2[track2]; 
	    unsigned nh2 = jHits.size();
	    
	    int noverlap=0; // number of overlap layers
	    
	    // check shared hits! 
	    for ( unsigned ih=0; ih<nh1; ++ih ) {              // hits from trk1
	       const TrackingRecHit* it = iHits[ih];
	       if (it->isValid()){
		  for ( unsigned jh=0; jh<nh2; ++jh ) {        // hits from trk2
		     const TrackingRecHit* jt = jHits[jh];
		     if (jt->isValid()){
			if ( it->sharesInput(jt,TrackingRecHit::some) ) {
			   noverlap++;
			}
		     }
		  }
	       }
	    } // check shared hits
	    
	    //if(noverlap>2){
	    //cout<<" dr = "<<dr<<" nhits1 = "<<track->numberOfValidHits()<<" nhits2 = "
	    //<<track2->numberOfValidHits()<<" shared hits = "<<noverlap
	    //<<" pt1 = "<<track->pt()<<" pt 2 = "<<track2->pt()<<endl;
	    //}

	    // ntuple filling
	    if(needTree_) {
	       nt_trk_cls->Fill(cbin, counter, track->eta(), track->phi(), track->pt(),
				track2->eta(), track2->phi(), track2->pt(), dr, 
				track->numberOfValidHits(), track2->numberOfValidHits(), noverlap,
				track->normalizedChi2(), track2->normalizedChi2(),
				std::max(track->ptError()/track->pt(),track2->ptError()/track2->pt()));
	    }

	 } // track 2 
      } // track 1


   } // checkHit


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

   //LogDebug("HiTrackMatchingAnalyzer")<<" Number of tracks in TC1 = "<<ntrk1_eta<<endl;
   //LogDebug("HiTrackMatchingAnalyzer")<<" Number of tracks in TC2 = "<<ntrk2_eta<<endl;
   //LogDebug("HiTrackMatchingAnalyzer")<<" Number of matched tracks = "<<nmatched<<endl;

   //LogDebug("HiTrackMatchingAnalyzer")<<" Fraction of matched track 1 = "<<fmatch1<<endl;
   //LogDebug("HiTrackMatchingAnalyzer")<<" Fraction of matched track 2 = "<<fmatch2<<endl;

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

   

   for(unsigned i=0;i<neededCentBins_.size()-1;i++){

      hTrk1Pt_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));
      hTrk2Pt_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));
      hTrkPtMatch_Cent.push_back( fs->make<TH1F>("","pt;p_{T} (GeV/c)",ptBins.size()-1, &ptBins[0]));

      hTrk1FShare_Cent.push_back( fs->make<TH1F>("","f_{shared};shared fraction",100, 0.0, 1.2));
      hTrk2FShare_Cent.push_back( fs->make<TH1F>("","f_{shared};shared fraction",100, 0.0, 1.2));
      

      if(i==0){
	 hTrk1Pt_Cent[i]->SetName(Form("hTrk1Pt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));  
	 hTrk2Pt_Cent[i]->SetName(Form("hTrk2Pt_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hTrkPtMatch_Cent[i]->SetName(Form("hTrkPtMatch_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 
	 hTrk1FShare_Cent[i]->SetName(Form("hTrk1FShare_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
	 hTrk2FShare_Cent[i]->SetName(Form("hTrk2FShare_cbin%dto%d",neededCentBins_[i],neededCentBins_[i+1]));
      }else{
	 hTrk1Pt_Cent[i]->SetName(Form("hTrk1Pt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrk2Pt_Cent[i]->SetName(Form("hTrk2Pt_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrkPtMatch_Cent[i]->SetName(Form("hTrkPtMatch_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 
	 hTrk1FShare_Cent[i]->SetName(Form("hTrk1FShare_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
	 hTrk2FShare_Cent[i]->SetName(Form("hTrk2FShare_cbin%dto%d",neededCentBins_[i]+1,neededCentBins_[i+1]));
      }
   }

   if(needTree_){
      nt_trk1    = fs->make<TNtuple>("nt_trk1","track 1 profile","run:evt:cent:eta:phi:pt:nhits:chi2n:pterr:dzE:d0E:algo");
      nt_trk2    = fs->make<TNtuple>("nt_trk2","track 2 profile","run:evt:cent:eta:phi:pt:nhits:chi2n:pterr:dzE:d0E:algo");
      nt_trk_mat = fs->make<TNtuple>("nt_trk_mat","matched track profile","run:evt:cent:eta:phi:pt:nhits:chi2n:pterr:dzE:d0E:algo");
      nt_trk_cls = fs->make<TNtuple>("nt_trk_cls","closest track profile",
				     "cent:counter:eta1:phi1:pt1:eta2:phi2:pt2:dr:nhits1:nhits2:nshared:chi2n1:chi2n2:pterr");
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
