// -*- C++ -*-
//
// Package:    GenAnalyzer
// Class:      GenAnalyzer
// 
/**\class GenAnalyzer GenAnalyzer.cc Spectra/GenAnalyzer/src/GenAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Sungho Yoon
//         Created:  Wed Mar 18 15:10:26 EDT 2009
// $Id: GenAnalyzer.cc,v 1.3 2009/03/19 17:37:47 edwenger Exp $
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
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TNtuple.h"
#include "TH1D.h"
#include "TFile.h"


//
// class decleration
//

class GenAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GenAnalyzer(const edm::ParameterSet&);
      ~GenAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   TH1D *hpt_all;
   TH1D *hpt_central;
   TH1D *hpt_pip;
   TH1D *hpt_pim;
   TH1D *hpt_kp;
   TH1D *hpt_km;
   TH1D *hpt_p;
   TH1D *hpt_pbar;
   TH1D *hpt_lambda;
   TH1D *hpt_lambdabar;
   TH1D *hpt_k0s;
   TH1D *hpt_d0;

   TNtuple *nt_auxiliary; 

   edm::Service<TFileService> fs;

   bool auxiliaryInfo_; 

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
GenAnalyzer::GenAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   auxiliaryInfo_ = iConfig.getUntrackedParameter<bool>("auxiliaryInfo",false);

}


GenAnalyzer::~GenAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GenAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   // Get generated events;
   Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel("genParticles", genParticles);
   const GenParticleCollection *genCollect = genParticles.product();
   if(genCollect == 0){
      cout<<"No GenParticleCollection found"<<endl;
      return;
   }

   int nCollect = genCollect->size();
   for(int i = 0; i < nCollect; i++){
      const GenParticle & gen = (*genCollect)[i];
      
      int nMom = gen.numberOfMothers();
      int nDau = gen.numberOfDaughters();
      int status = gen.status();
      int pdgId = gen.pdgId();
      int charge = gen.charge();

      if(auxiliaryInfo_){
	 float var[10];
	 var[0]=nMom;
	 var[1]=nDau;
	 var[2]=status;
	 var[3]=pdgId;
	 var[4]=charge;
	 nt_auxiliary->Fill(var);
      }

      //if(gen.mother(0) == 0){
      if(gen.status() == 1) {	
          if(abs(gen.eta())<2.5){

            if(charge!=0 && abs(pdgId)!=11 && abs(pdgId)!=13 && abs(pdgId)!=15) //charged hadrons
	      hpt_all->Fill(gen.pt());

	    if(pdgId ==   211) hpt_pip->Fill(gen.pt());
	    if(pdgId ==  -211) hpt_pim->Fill(gen.pt());
	    if(pdgId ==   321) hpt_kp->Fill(gen.pt());
	    if(pdgId ==  -321) hpt_km->Fill(gen.pt());
	    if(pdgId ==  2212) hpt_p->Fill(gen.pt());
	    if(pdgId == -2212) hpt_pbar->Fill(gen.pt());
	    if(pdgId ==  3122) hpt_lambda->Fill(gen.pt());
	    if(pdgId == -3122) hpt_lambdabar->Fill(gen.pt());
	    if(pdgId ==   310) hpt_k0s->Fill(gen.pt());
	    if(pdgId ==   421) hpt_d0->Fill(gen.pt());
	 }
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
GenAnalyzer::beginJob(const edm::EventSetup&)
{
   if(auxiliaryInfo_){
      nt_auxiliary = fs->make<TNtuple>("nt_auxiliary","","nMom:nDau:status:pdgId:charge");
   }

   hpt_all       = fs->make<TH1D>("hpt_all",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_pip       = fs->make<TH1D>("hpt_pip",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_pim       = fs->make<TH1D>("hpt_pim",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_kp        = fs->make<TH1D>("hpt_kp",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_km        = fs->make<TH1D>("hpt_km",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_p         = fs->make<TH1D>("hpt_p",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_pbar      = fs->make<TH1D>("hpt_pbar",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_lambda    = fs->make<TH1D>("hpt_lambda",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_lambdabar = fs->make<TH1D>("hpt_lambdabar",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_k0s       = fs->make<TH1D>("hpt_k0s",";p_{T} (GeV/c);",100,0.0,100.);
   hpt_d0        = fs->make<TH1D>("hpt_d0",";p_{T} (GeV/c);",100,0.0,100.);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenAnalyzer);
