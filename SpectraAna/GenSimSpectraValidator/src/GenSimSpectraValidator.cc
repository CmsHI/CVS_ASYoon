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
// $Id: GenSimSpectraValidator.cc,v 1.4 2011/07/04 12:32:26 sungho Exp $
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

   // Get PDTable
   edm::ESHandle<ParticleDataTable> pdt_;
   iSetup.getData( pdt_);
   
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

      int parentId=0; 
      if(sim.parentVertex()->nSourceTracks() > 0) { 
	 parentId = (*(sim.parentVertex()->sourceTracks_begin()))->pdgId(); // PDG id of parent particle
      } 

      std::pair<bool,bool> acc = isAccepted(sim);
      int isAcc = (acc.first || acc.second) ? 1 : 0;

      const ParticleData * pd = pdt_->particle(abs(sim.pdgId()));
      double lifetime = pd->lifetime().value();
      //std::cout<<"lifetime = "<<lifetime<<" 2 = "<<pd->lifetime()<<" name = "<<pd->name()
      //<<" mass = "<<pd->mass()<<std::endl;

      nt_sim->Fill(sim.eta(),sim.phi(),sim.pt(),sim.pdgId(),sim.status(),fabs(sim.vertex().z()),sqrt(sim.vertex().perp2()),
		   sim.parentVertex()->nSourceTracks(),parentId,isAcc);
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


// ------------ method called at the beginning of each new run  ------------
void
GenSimSpectraValidator::beginRun(const edm::Run& r, const edm::EventSetup& es)
{

   // Get tracker geometry
   edm::ESHandle<TrackerGeometry> tracker;
   es.get<TrackerDigiGeometryRecord>().get(tracker);
   theTracker = tracker.product();

}

// ------------ method called once each job just before starting event loop  ------------
void 
GenSimSpectraValidator::beginJob()
{
   // tracks
   nt_gen = fs->make<TNtuple>("nt_gen","gen level information","geta:gphi:gpt:gpdgid");
   nt_sim = fs->make<TNtuple>("nt_sim","sim level information","seta:sphi:spt:spdgid:sstatus:sdz:sd0:snptrk:sptrkid:sacc");

   // vertices
   //nt_sim_vtx = fs->make<TNtuple>("nt_sim_vtx","sim level vtx information","vx:vy:vz:pdgid:status");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenSimSpectraValidator::endJob() {
}

// ------------
std::pair<bool,bool> 
GenSimSpectraValidator::isAccepted(const TrackingParticle & tp)
{
   std::vector<bool> f(nLayers, false);

   const std::vector<PSimHit> & simHits = tp.trackPSimHit(DetId::Tracker);
  
   for(std::vector<PSimHit>::const_iterator simHit = simHits.begin();
       simHit!= simHits.end(); simHit++)
      {
	 int id = getLayerId(*simHit);

	 if(id != -1)
	    f[id] = true;
      }

  bool canBeTriplet =
     ( (f[BPix1] && f[BPix2]     && f[BPix3]) ||
       (f[BPix1] && f[BPix2]     && f[FPix1_pos]) ||
       (f[BPix1] && f[BPix2]     && f[FPix1_neg]) ||
       (f[BPix1] && f[FPix1_pos] && f[FPix2_pos]) ||
       (f[BPix1] && f[FPix1_neg] && f[FPix2_neg]) );

  bool canBePair =
     ( (f[BPix1] && f[BPix2]) ||
       (f[BPix1] && f[BPix3]) ||
       (f[BPix2] && f[BPix3]) ||
       (f[BPix1] && f[FPix1_pos]) ||
       (f[BPix1] && f[FPix1_neg]) ||
       (f[BPix1] && f[FPix2_pos]) ||
       (f[BPix1] && f[FPix2_neg]) ||
       (f[BPix2] && f[FPix1_pos]) ||
       (f[BPix2] && f[FPix1_neg]) ||
       (f[BPix2] && f[FPix2_pos]) ||
       (f[BPix2] && f[FPix2_neg]) ||
       (f[FPix2_neg] && f[FPix2_neg]) ||
       (f[FPix2_pos] && f[FPix2_pos]) );

  return std::pair<bool,bool>(canBeTriplet, canBePair);
}


// ------------
int 
GenSimSpectraValidator::getLayerId(const PSimHit & simHit)
{

   unsigned int id = simHit.detUnitId();

   if(theTracker->idToDetUnit(id)->subDetector() ==
      GeomDetEnumerators::PixelBarrel)
      {
	 PXBDetId pid(id);
	 return pid.layer() - 1; // 0, 1, 2
      }

   if(theTracker->idToDetUnit(id)->subDetector() ==
      GeomDetEnumerators::PixelEndcap)
      {
	 PXFDetId pid(id);
	 return BPix3 + ((pid.side()-1) << 1) + pid.disk(); // 3 -
      }


   // strip
   return -1;
}


//define this as a plug-in
DEFINE_FWK_MODULE(GenSimSpectraValidator);
