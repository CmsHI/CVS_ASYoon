// -*- C++ -*-
//
// Package:    CentralityDistAna
// Class:      CentralityDistAna
// 
/**\class CentralityDistAna CentralityDistAna.cc FirstHi2010/CentralityDistAna/src/CentralityDistAna.cc

 Description: simple centrality distribution analyzer

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andre Yoon,32 4-A06,+41227676980,
//         Created:  Mon Nov 22 11:37:43 CET 2010
// $Id$
//
//


// system include files
#include <memory>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

// ROOT includes
#include "TH1.h"
#include "TFile.h"


//
// class declaration
//

class CentralityDistAna : public edm::EDAnalyzer {
   public:
      explicit CentralityDistAna(const edm::ParameterSet&);
      ~CentralityDistAna();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
   CentralityProvider * centrality_;

   edm::Service<TFileService> fs;

   TH1F *hCentBinDist;
   
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
CentralityDistAna::CentralityDistAna(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


CentralityDistAna::~CentralityDistAna()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
CentralityDistAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   if(!centrality_) centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup);

   int bin = centrality_->getBin();
   hCentBinDist->Fill(bin);
   


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
CentralityDistAna::beginJob()
{
   hCentBinDist = fs->make<TH1F>("hCentBinDist","Centrality bin distribution",40,0,40);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralityDistAna::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralityDistAna);
