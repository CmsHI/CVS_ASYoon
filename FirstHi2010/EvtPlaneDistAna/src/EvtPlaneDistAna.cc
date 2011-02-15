// -*- C++ -*-
//
// Package:    EvtPlaneDistAna
// Class:      EvtPlaneDistAna
// 
/**\class EvtPlaneDistAna EvtPlaneDistAna.cc FirstHi2010/EvtPlaneDistAna/src/EvtPlaneDistAna.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andre Yoon,32 4-A06,+41227676980,
//         Created:  Fri Feb 11 15:38:24 CET 2011
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
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

// ROOT include
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
using namespace std;


//
// class declaration
//

class EvtPlaneDistAna : public edm::EDAnalyzer {
   public:
      explicit EvtPlaneDistAna(const edm::ParameterSet&);
      ~EvtPlaneDistAna();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   edm::Service<TFileService> fs;
   string epLabel_;

   TH1F *hThetaDist;
   TH1F *hSumSinDist;
   TH1F *hSumCosDist;

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
EvtPlaneDistAna::EvtPlaneDistAna(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   epLabel_ = iConfig.getUntrackedParameter<std::string>("epLabel");
   
}


EvtPlaneDistAna::~EvtPlaneDistAna()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EvtPlaneDistAna::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   using reco::EvtPlaneCollection;
   Handle<reco::EvtPlaneCollection> evtPlaneCollectionHandle;
   iEvent.getByLabel("hiEvtPlane", "recoLevel", evtPlaneCollectionHandle);

   //Check if there was a problem accessing the EvtPlaneCollection

   if( !evtPlaneCollectionHandle.isValid() ){
      cout << "Error! Can't get hiEvtPlane!" << endl;
      return ;
   }

   double angle=0, sum_sin=0, sum_cos=0;

   //Loop over EvtPlane objects within collection
   for(reco::EvtPlaneCollection::const_iterator ep = evtPlaneCollectionHandle->begin(); ep != evtPlaneCollectionHandle->end(); ep++){

      string label  = ep->label();

      if(label.compare(epLabel_) != 0) continue;

      angle = ep->angle();
      sum_sin = ep->sumSin();
      sum_cos = ep->sumCos();

      hThetaDist->Fill(angle);
      hSumSinDist->Fill(sum_sin);
      hSumCosDist->Fill(sum_cos);
      //cout << "event plane method: " << label << " angle = " << angle 
      //<< " sum of sines of components " << sum_sin << " " << " sum of cosines of components " << sum_cos << endl;
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
EvtPlaneDistAna::beginJob()
{
   hThetaDist = fs->make<TH1F>("hThetaDist","event plane angle distribution; #Psi",100,-1.6,1.6);
   hSumSinDist = fs->make<TH1F>("hSumSinDist","sum sin dist; sum sin dist",250,-500,500);
   hSumCosDist = fs->make<TH1F>("hSumCosDist","sum cos dist; sum cos dist",250,-500,500);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EvtPlaneDistAna::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EvtPlaneDistAna);
