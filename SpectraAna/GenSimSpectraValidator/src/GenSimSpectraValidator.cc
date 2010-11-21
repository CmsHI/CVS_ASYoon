// -*- C++ -*-
//
// Package:    GenSimSpectraValidator
// Class:      GenSimSpectraValidator
// 
/**\class GenSimSpectraValidator GenSimSpectraValidator.cc SpectraAna/GenSimSpectraValidator/src/GenSimSpectraValidator.cc

 Description: This is a simple ntuple producer for GEN/SIM level spectra 

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andre Yoon,32 4-A06,+41227676980,
//         Created:  Sun Nov 21 14:51:53 CET 2010
// $Id: GenSimSpectraValidator.cc,v 1.1 2010/11/21 16:52:06 sungho Exp $
//
//

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SpectraAna/GenSimSpectraValidator/interface/GenSimSpectraValidator.h"



GenSimSpectraValidator::GenSimSpectraValidator(const edm::ParameterSet& iConfig)

{
   gsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("gsrc",edm::InputTag("genParticles"));
   ssrc_ = iConfig.getUntrackedParameter<edm::InputTag>("ssrc",edm::InputTag("genParticles"));
   etaMax_ = iConfig.getUntrackedParameter<double>("etaMax", 2.4);


}


GenSimSpectraValidator::~GenSimSpectraValidator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GenSimSpectraValidator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   
   // Gen level ----------------------------------------------------------------
   Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel(gsrc_, genParticles);
   const GenParticleCollection *genCollect = genParticles.product();

   for(unsigned i=0; i<genCollect->size();i++){

      const GenParticle & gen = (*genCollect)[i];

      if(gen.status() != 1 || gen.charge() == 0) continue;

      if(fabs(gen.eta())>etaMax_) continue;
      
      nt_gen->Fill(gen.eta(),gen.phi(),gen.pt(),gen.pdgId());
   }


   // Sim level ----------------------------------------------------------------

   edm::Handle<TrackingParticleCollection>  simParticles;
   iEvent.getByLabel(ssrc_, simParticles);
   const TrackingParticleCollection *simCollect = simParticles.product();

   for(unsigned i=0; i<simCollect->size();i++){

      const TrackingParticle & sim = (*simCollect)[i];

      if(sim.status() < 0 || sim.charge()==0) continue; //only charged primaries

      if(fabs(sim.eta())>etaMax_) continue;

      nt_sim->Fill(sim.eta(),sim.phi(),sim.pt(),sim.pdgId(),sim.status());
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
GenSimSpectraValidator::beginJob()
{
   // tracks
   nt_gen = fs->make<TNtuple>("nt_gen","gen level information","geta:gphi:gpt:gpdgid");
   nt_sim = fs->make<TNtuple>("nt_sim","sim level information","seta:sphi:spt:spdgid:sstatus");

   // vertices
   nt_sim_vtx = fs->make<TNtuple>("nt_sim_vtx","sim level vtx information","vx:vy:vz:pdgid:status");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenSimSpectraValidator::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenSimSpectraValidator);
