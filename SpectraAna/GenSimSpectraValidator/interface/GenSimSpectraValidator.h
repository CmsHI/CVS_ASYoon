// system include files 
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelEndcapName.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"

#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"


// ROOT includes
#include "TNtuple.h"
#include "TH1.h"
#include "TFile.h"

//                                                                                                                                             
// class declaration                                                                                                                           
//                                                                                                                                             

class GenSimSpectraValidator : public edm::EDAnalyzer {
 public:
   explicit GenSimSpectraValidator(const edm::ParameterSet&);
   ~GenSimSpectraValidator();


 private:
   virtual void beginJob() ;
   virtual void beginRun(const edm::Run&, const edm::EventSetup&);
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;

   std::pair<bool,bool> isAccepted(const TrackingParticle&);
   int getLayerId(const PSimHit&);

   // ----------member data --------------------------- 
   edm::InputTag gsrc_;
   edm::InputTag ssrc_;

   double  etaMax_;

   edm::Service<TFileService> fs;

   const TrackerGeometry * theTracker;
   
   // root objects
   TNtuple *nt_gen, *nt_sim;
   TNtuple *nt_sim_vtx;
   
   enum { BPix1=0, BPix2=1, BPix3=2,
	  FPix1_neg=3, FPix2_neg=4,
	  FPix1_pos=5, FPix2_pos=6,
	  nLayers=7};

   
};

