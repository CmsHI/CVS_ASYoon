// -*- C++ -*-
//
// Package:    TrackSpectraAnalyzer
// Class:      TrackSpectraAnalyzer
// 
/**\class TrackSpectraAnalyzer TrackSpectraAnalyzer.cc SpectraAna/TrackSpectraAnalyzer/src/TrackSpectraAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andre Yoon,32 4-A06,+41227676980,
//         Created:  Wed Apr 28 16:18:39 CEST 2010
// $Id$
//
//


// system include files
#include <memory>
#include <string>
//#include <vector>
//#include <iostream>


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/CaloJet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//#include "DataFormats/Common/interface/Handle.h"
//#include "DataFormats/HLTReco/interface/TriggerObject.h"


#include "TNtuple.h"
#include "TH1D.h"
#include "TFile.h"


//
// class declaration
//

class TrackSpectraAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TrackSpectraAnalyzer(const edm::ParameterSet&);
      ~TrackSpectraAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

   // ----------member data ---------------------------
   
   TNtuple *nt_dndptdeta; 
   TNtuple *nt_gen_dndptdeta;
   TNtuple *nt_jet;
   TNtuple *nt_jettrack;

   TH1D *hTrkPtMB;
   TH1D *hVtxZ;

   edm::Service<TFileService> fs;
   
   bool doOutput_;
   bool isGEN_, doJet_;
   double  etaMax_;
   int32_t nVtxTrkCut_;
   edm::InputTag src_;
   edm::InputTag vsrc_;
   edm::InputTag jsrc_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TrackSpectraAnalyzer::TrackSpectraAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   src_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("generalTracks"));
   vsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("vsrc",edm::InputTag("offlinePrimaryVertices"));
   jsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("jsrc",edm::InputTag("ak5CaloJets"));
   doOutput_ = iConfig.getUntrackedParameter<bool>("doOutput", true);
   isGEN_ = iConfig.getUntrackedParameter<bool>("isGEN", true);
   doJet_ = iConfig.getUntrackedParameter<bool>("doJet", true);
   etaMax_ = iConfig.getUntrackedParameter<double>("etaMax", 5.0);
   nVtxTrkCut_ = iConfig.getUntrackedParameter<int>("nVtxTrkCut", 3);

}


TrackSpectraAnalyzer::~TrackSpectraAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TrackSpectraAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   const int nTrigs = 5;

   const string qualityString = "highPurity";

   //-----------------------   (This part will be in an EDFilter later)  
   // get vtx collection 
   Handle<vector<Vertex> > vertices;
   iEvent.getByLabel(vsrc_, vertices);
   if(vertices->size()!=1) return; // one and only one vertex
   int numFake=0, numVtxTrk=0;
   double bestvz=-999.9;
   for(unsigned it=0; it<vertices->size(); ++it) {
      const reco::Vertex & vtx = (*vertices)[it];
      if(vtx.isFake()) numFake++;
      numVtxTrk = vtx.tracksSize();
      bestvz = vtx.z();
   }
   if(numVtxTrk<nVtxTrkCut_) return;
   if(numFake>=1) return;
   hVtxZ->Fill(bestvz);
   //-----------------------   (This part will be in an EDFilter later)    
   
   // get hlt bit
   Handle<edm::TriggerResults> triggerResults;
   iEvent.getByLabel(edm::InputTag("TriggerResults","","HLT"), triggerResults);
   //iEvent.getByLabel("TriggerResults","","HLT",triggerResults);
   const edm::TriggerNames triggerNames = iEvent.triggerNames(*triggerResults); 
   bool accept[nTrigs];
   
   accept[0] = triggerResults->accept(triggerNames.triggerIndex("HLT_MinBiasBSC"));
   accept[1] = triggerResults->accept(triggerNames.triggerIndex("HLT_L1Jet6U"));
   accept[2] = triggerResults->accept(triggerNames.triggerIndex("HLT_Jet15U"));
   accept[3] = triggerResults->accept(triggerNames.triggerIndex("HLT_Jet30U"));
   accept[4] = triggerResults->accept(triggerNames.triggerIndex("HLT_Jet50U"));

   for(int i=0; i<nTrigs; i++) { 
      //cout<<triggerResults->accept(triggerNames.triggerIndex("HLT_MinBiasBSC"))<<endl;
      //accept[i] = triggerResults->accept(triggerNames.triggerIndex(hltNames[i])); 
      //if(accept[i]) hHLTPaths->Fill(hltNames[i],1); 
    } 

   //----- loop over jets and store in a vector -----
   Handle<vector<reco::CaloJet> > jets;
   iEvent.getByLabel(jsrc_, jets);

   vector<const reco::CaloJet *> sortedJets;

   for(unsigned it=0; it<jets->size(); ++it){
      const reco::CaloJet* jts = &((*jets)[it]);
      sortedJets.push_back( & *jts);
      sortByEtRef (&sortedJets);
   }

   for(unsigned it=0; it<sortedJets.size(); ++it){
      nt_jet->Fill(sortedJets[it]->et(),sortedJets[it]->eta(),sortedJets[it]->phi(),
		  accept[0],accept[1],accept[2],accept[3],accept[4]);
      break;
   }


   // get track collection 
   Handle<vector<Track> > tracks;
   iEvent.getByLabel(src_, tracks);

   for(unsigned it=0; it<tracks->size(); ++it){
      const reco::Track & trk = (*tracks)[it];
      if(!trk.quality(reco::TrackBase::qualityByName(qualityString))) continue;

      if(accept[0]==1) hTrkPtMB->Fill(trk.pt());
      nt_dndptdeta->Fill(trk.pt(),trk.eta());


      // (leading jet)-track
      // even if there's no jet track info saved (needed for MB)
      double jet_et = 0, jet_eta = 0;
      unsigned index = 0; 
      if(sortedJets.size()==0) jet_et = 0,jet_eta = 0;
      else jet_et = sortedJets[index]->et(), jet_eta = sortedJets[index]->eta();

      nt_jettrack->Fill(trk.pt(),trk.eta(),sortedJets[it]->eta(),
			accept[0],accept[1],accept[2],accept[3],accept[4]);
      

   }

   if(isGEN_){
      Handle<GenParticleCollection> genParticles;
      iEvent.getByLabel("genParticles", genParticles);
      const GenParticleCollection *genCollect = genParticles.product();

      for(unsigned i=0; i<genCollect->size();i++){
	 const GenParticle & gen = (*genCollect)[i];
	 if(gen.status() != 1) continue;
	 if(gen.collisionId() != 0) continue;
	 if(gen.charge() == 0) continue;
	 if(fabs(gen.eta())>etaMax_) continue;
	 nt_gen_dndptdeta->Fill(gen.pt(),gen.eta());
      }
   }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TrackSpectraAnalyzer::beginJob()
{
   if(doOutput_){
      nt_dndptdeta = fs->make<TNtuple>("nt_dndptdeta","eta vs pt","pt:eta");
      hTrkPtMB = fs->make<TH1D>("hTrkPtMB","track p_{T}; p_{T} [GeV/c]", 1000, 0.0, 200.0);
      hVtxZ = fs->make<TH1D>("hVtxZ","z position of best reconstructed pixel vertex", 80,-20,20);
      if(isGEN_) nt_gen_dndptdeta = fs->make<TNtuple>("nt_gen_dndptdeta","eta vs pt","pt:eta");
      if(doJet_) {
	 nt_jet = fs->make<TNtuple>("nt_jet","jet spectra ntuple","jet:jeta:jphi:mb:jet6:jet15:jet30:jet50");
	 nt_jettrack = fs->make<TNtuple>("nt_jettrack","jet tracks correlation ntuple","pt:eta:jet:mb:jet6:jet15:jet30:jet50");
      }
   }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackSpectraAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackSpectraAnalyzer);
