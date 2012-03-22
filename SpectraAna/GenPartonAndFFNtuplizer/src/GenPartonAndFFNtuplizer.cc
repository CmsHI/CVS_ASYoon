// -*- C++ -*-
//
// Package:    GenPartonAndFFNtuplizer
// Class:      GenPartonAndFFNtuplizer
// 
/**\class GenPartonAndFFNtuplizer GenPartonAndFFNtuplizer.cc SpectraAna/GenPartonAndFFNtuplizer/src/GenPartonAndFFNtuplizer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sungho Yoon
//         Created:  Thu Mar 22 13:42:33 EDT 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h" //for sorting 

#include "SpectraAna/GenPartonAndFFNtuplizer/interface/GenParticleInfo.h"

#include "TNtuple.h"
#include "TClonesArray.h"

using namespace std;

//
// class declaration
//

class GenPartonAndFFNtuplizer : public edm::EDAnalyzer {
   public:
      explicit GenPartonAndFFNtuplizer(const edm::ParameterSet&);
      ~GenPartonAndFFNtuplizer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

   // inputs
   edm::InputTag gsrc_;
   edm::InputTag gjsrc_;

   // root objects
   edm::Service<TFileService> fs;

   TTree *tSpect;

   TClonesArray *tCAPartons;  // parton/jet + associated hadrons
   TClonesArray *tCAHadrons;  // all hadrons 

   static const int MAXJETS = 50000;
   
   struct PJ{
      int   nJets;
      float fJPt[MAXJETS];
      float fJEt[MAXJETS];
      float fJEta[MAXJETS];
      float fJPhi[MAXJETS];
   };
      
   PJ jets_;

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
GenPartonAndFFNtuplizer::GenPartonAndFFNtuplizer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   gsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("gsrc",edm::InputTag("genParticles"));
   gjsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("gjsrc",edm::InputTag("ak5GenJets"));
}


GenPartonAndFFNtuplizer::~GenPartonAndFFNtuplizer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenPartonAndFFNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;

   // Event Info

   // Get GenParticles
   edm::Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel(gsrc_, genParticles);
   const GenParticleCollection *genCollect = genParticles.product();


   // Get "GenParton"/"GenJet"
   Handle<vector<GenJet> > genjets;
   iEvent.getByLabel(gjsrc_,genjets);


   // Analyze Parton/Jet + Associated Hadrons ---------------------------
   TClonesArray &tCAPartonsTemp = *((TClonesArray*)tCAPartons);

   int totJet = genjets->size();
   jets_.nJets = 0;   // jets that pass cuts and saved

   vector<const GenJet *> sortedJets;
      
   for(int j = 0; j < totJet; ++j){
      const GenJet* jet = &((*genjets)[j]);
      sortedJets.push_back( & *jet);
   }
      
   sortByEtRef (&sortedJets);

   for(int ij = 0; ij < totJet; ij++){

      int  nChargedHadrons = 0;

      jets_.fJEt[jets_.nJets]   = sortedJets[ij]->et();
      jets_.fJPt[jets_.nJets]   = sortedJets[ij]->pt();
      jets_.fJPhi[jets_.nJets]  = sortedJets[ij]->phi();
      jets_.fJEta[jets_.nJets]  = sortedJets[ij]->eta();
      
      jets_.nJets++;
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
GenPartonAndFFNtuplizer::beginJob()
{
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenPartonAndFFNtuplizer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
GenPartonAndFFNtuplizer::beginRun(edm::Run const&, edm::EventSetup const&)
{
   tSpect = fs->make<TTree>("SpectraStudyTree","Tree for Spectra/JetQuenching");
   tCAPartons = fs->make<TClonesArray>("TCAPartons",20000);

   tSpect->Branch("nJets",&jets_.nJets,"nJets/I");
   tSpect->Branch("fJPt",jets_.fJPt,"fJPt[nJets]/F");
   tSpect->Branch("fJEt",jets_.fJEt,"fJEt[nJets]/F");
   tSpect->Branch("fJEta",jets_.fJEta,"fJEta[nJets]/F");
   tSpect->Branch("fJPhi",jets_.fJPhi,"fJPhi[nJets]/F");
   tSpect->Branch("AllPartons",&tCAPartons);
   
}

// ------------ method called when ending the processing of a run  ------------
void 
GenPartonAndFFNtuplizer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
GenPartonAndFFNtuplizer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
GenPartonAndFFNtuplizer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenPartonAndFFNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenPartonAndFFNtuplizer);
