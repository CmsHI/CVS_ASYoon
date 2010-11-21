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

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

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
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;

   // ----------member data --------------------------- 
   edm::InputTag gsrc_;
   edm::InputTag ssrc_;

   double  etaMax_;

   edm::Service<TFileService> fs;
   
   // root objects
   TNtuple *nt_gen, *nt_sim;
   TNtuple *nt_sim_vtx;
   
   
   
};

