// -*- C++ -*-
//
// Package:    GenJetSpectraAnalyzer
// Class:      GenJetSpectraAnalyzer
// 
/**\class GenJetSpectraAnalyzer GenJetSpectraAnalyzer.cc SpectraAna/GenJetSpectraAnalyzer/src/GenJetSpectraAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Sungho Yoon
//         Created:  Sun Aug 23 10:50:33 EDT 2009
// $Id: GenJetSpectraAnalyzer.cc,v 1.1 2009/10/09 13:45:43 sungho Exp $
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

#include "SpectraAna/GenJetSpectraAnalyzer/interface/FoundJets.h" // class def

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/Common/interface/Association.h"


#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h" //for sorting                                      

//This to access HepMC
#include "HepMC/GenEvent.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"


#include "TNtuple.h"
//#include "TH1D.h"
//#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TClonesArray.h"

#include <fstream>

using namespace edm;
using namespace std;
using namespace reco;


//
// class decleration
//

class GenJetSpectraAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GenJetSpectraAnalyzer(const edm::ParameterSet&);
      ~GenJetSpectraAnalyzer();


private:
   virtual void beginJob() ;
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;
   edm::ESHandle<ParticleDataTable> pdt_;
   bool checkHeavyQuarkC(int it) const;
   bool checkHeavyQuarkB(int it) const;
   bool isFromHeavyQuark( const reco::Candidate & , bool bIniPartonOnly,  bool bIsCquark) const;

   Int_t iJets, iJIndex;
   Int_t iProcID;
   Float_t fJPt, fJPhi,fJRapid,fJEta,fJEt;
   Float_t fAlpha, fBeta, fBeta_check;
   string resultFileLabel;
   
   Int_t totEvt;

   TTree *spectraTree;
   TTree *spectraTree2;
   TFile * resultFile;
   TClonesArray *CAJetPart;
   TClonesArray *CAAllPart;

   //Service<TFileService> fs;
   bool pthatReject_;
   double pthatMax_;
   

      // ----------member data ---------------------------
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
GenJetSpectraAnalyzer::GenJetSpectraAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   resultFileLabel = iConfig.getParameter<string>("resultFile");
   pthatReject_ = iConfig.getUntrackedParameter<bool>("pthatReject",false);
   pthatMax_ = iConfig.getUntrackedParameter<double>("pthatMax", 5);
}


GenJetSpectraAnalyzer::~GenJetSpectraAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
bool
GenJetSpectraAnalyzer::checkHeavyQuarkC(int id) const {

   if(abs(id) == 4 ||
      abs(id) == 4201 || // diquarks system containing c                         
      abs(id) == 4203 ||
      abs(id) == 4301 ||
      abs(id) == 4303 ||
      abs(id) == 4301 ||
      abs(id) == 4303 ||
      abs(id) == 4403){
      return true;
   }else{
      return false;
   }
}

bool
GenJetSpectraAnalyzer::checkHeavyQuarkB(int id) const {

   if(abs(id) == 5 ||
      abs(id) == 5101 ||
      abs(id) == 5103 ||
      abs(id) == 5201 ||
      abs(id) == 5203 ||
      abs(id) == 5301 ||
      abs(id) == 5303 ||
      abs(id) == 5401 ||
      abs(id) == 5403 ||
      abs(id) == 5503) {
      return true;
   }else{
      return false;
   }
}



bool
GenJetSpectraAnalyzer::isFromHeavyQuark( const reco::Candidate & c, bool bIniPartonOnly, bool bIsCquark) const {

   for( size_t j= 0; j < c.numberOfMothers(); j++){
      const Candidate * mom = c.mother(j);
      const Candidate * grandMom;
      while ( (grandMom = mom->mother() )!=0){ // if mom's mom exists
         mom = grandMom;
	 const ParticleData * pd_mom = pdt_->particle(mom->pdgId());
         if(!bIniPartonOnly){// heavy quarks from anywhere along decay,shower,etc..   
	    if(bIsCquark){
	       if(checkHeavyQuarkC(mom->pdgId())) {
		  return true;
	       }
	    }else{
	       if(checkHeavyQuarkB(mom->pdgId())) {
                  return true;
               }
	    }
	 }
	 if(mom->numberOfMothers() == 2 &&
	    mom->status() == 3) break; // to pick up a parton produced in hard collision
      }

      const ParticleData * pd = pdt_->particle(mom->pdgId());
      if(bIsCquark){
	 if(checkHeavyQuarkC(mom->pdgId())){
	    return true;
	 }
      }else{
	 if(checkHeavyQuarkB(mom->pdgId())){
            return true;
         }
      }
   }
   return false;
}

void
GenJetSpectraAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   //using namespace edm;
   using namespace HepMC;

   //cout<<"[GenJetSpectraAnalyzer][analyze] BEGINS..."<<endl;

   // --- Particles                                                                                            
   iSetup.getData( pdt_);
   Handle<View<Candidate> > particles;
   iEvent.getByLabel("genParticles", particles);

   // --- HepMC to get event process id!
   Float_t pthat;
   //Int_t iSUB;
   Handle<HepMCProduct> mc;
   iEvent.getByLabel("generator",mc);
   const GenEvent* MCEvt = mc->GetEvent();
   // this rejects events with pthat > pthatMax!
   if(pthatReject_){
      pthat = MCEvt->event_scale();
      if(pthat>(Float_t)pthatMax_){
	 //cout<<"pT hat ="<<pthat<<endl;
	 return;
      }
   }

   // --- Gen Jets                                                                                     
   Handle<vector<GenJet> > genjets;
   iEvent.getByLabel("iterativeCone5GenJets",genjets);

   // --- Sort the particles according to thier status                                                 
   vector<const Candidate *> status1p;
   vector<const Candidate *> status2p;
   vector<const Candidate *> status3p; //mother parton candidates                                      

   TClonesArray &CAAllTemp = *((TClonesArray*)CAAllPart);
   Int_t iPartCount = -1;

   //iProcID = iEvent.id().event();
   //cout<<"Process ID? = "<<iProcID<<endl;

   for(View<Candidate>::const_iterator gen = particles->begin();
       gen != particles->end(); ++gen){
      
      if(gen->status() == 1){
	 iPartCount++;

	 FoundJets *AllTemp = new(CAAllTemp[iPartCount]) FoundJets(); 
	 AllTemp->fP = gen->p();
	 AllTemp->fPt = gen->pt();
	 AllTemp->fRapid = gen->rapidity();
	 AllTemp->fEta = gen->eta();
	 AllTemp->iCharge = gen->charge();
	 AllTemp->iStatus = gen->status(); // Status = 1 is guaranteed above
	 AllTemp->iPdgId = gen->pdgId();
	 AllTemp->iFromHQc = (isFromHeavyQuark( * gen, true, true)) ? 1 : 0;
         AllTemp->iFromAnyHQc = (isFromHeavyQuark( * gen, false, true)) ? 1 : 0;
	 AllTemp->iFromHQb = (isFromHeavyQuark( * gen, true, false)) ? 1 : 0;
	 AllTemp->iFromAnyHQb = (isFromHeavyQuark( * gen, false, false)) ? 1 : 0;
	 //AllTemp->bIsMortherPartonQuark = true;

	 status1p.push_back( & * gen);
      }
      if(gen->status() == 2){
         status2p.push_back( & * gen);
      }
      if(gen->status() == 3 && gen->numberOfMothers() != 0){ //exclude p,p_bar from beam               
         status3p.push_back( & * gen);
      }

   }

   spectraTree2->Fill(); //filled n times 
   CAAllPart->Clear();

   /*
   // ---- Analyze All particles !                                                                                       
   TClonesArray &CAAllTemp = *((TClonesArray*)CAAllPart);

   //FoundJets *AllTemp = new(CAAllTemp[0]) FoundJets();

   cout<<"Number of stutus 1 particle "<<status1p.size()<<endl;
   Int_t iPartCount = -1;

   for(size_t i = 0; i < status1p.size(); i++){

      iPartCount++;
   
      FoundJets *AllTemp = new(CAAllTemp[iPartCount]) FoundJets();

      AllTemp->fPt = status1p[i]->pt();
      AllTemp->fRapid = status1p[i]->rapidity();
      AllTemp->iCharge = status1p[i]->charge();
      AllTemp->iStatus = status1p[i]->status();
      AllTemp->iPdgId = status1p[i]->pdgId();
      AllTemp->bIsMortherPartonQuark = true;
   }
   
   spectraTree2->Fill(); //filled n times                                
   CAAllPart->Clear();
   */

   // ---- Analyze Jets!                                                                               
   iJets = genjets->size();

   //cout<<"[GenFragmentationExtractor][analyze] Number of jets : "<<iJets<<endl;

   vector<const GenJet *> jetsSorted;

   for(size_t j = 0; j < iJets; ++j){
      const GenJet* jet = &((*genjets)[j]);
      jetsSorted.push_back( & *jet);
   }

   sortByEtRef (&jetsSorted);

   //int highestNum = 2; // take only two highest Et jets in each event!                                 
   int highestNum = jetsSorted.size();

   /*
   if(jetsSorted.size() < 2) {
      cout<<"[GenFragmentationExtractor][analyze] Only one jet exists!"<<endl;
      highestNum = 1;
      return;
   }
   */

   TClonesArray &CAJetTemp = *((TClonesArray*)CAJetPart);

   for(size_t ij = 0; ij < highestNum; ij++){

      int  nChargedHadrons = 0;
      int  nAll = 0;
      bool isMotherPartonQuark = true;

      iJIndex = ij+1;
      fJPt = jetsSorted[ij]->pt();
      fJPhi = jetsSorted[ij]->phi();
      fJRapid = jetsSorted[ij]->rapidity();
      fJEt = jetsSorted[ij]->et();  

      //checkMotherParton(status3p,jPhi,jRapid,jEt);

      vector<const Candidate*> members = jetsSorted[ij]->getJetConstituentsQuick();

      //cout<<"Number of particles inside this jets "<<members.size()<<endl;

      for(size_t k = 0; k < members.size(); k++){

	 FoundJets *JetTemp = new(CAJetTemp[k]) FoundJets();

	 JetTemp->fP = members[k]->p();
	 JetTemp->fPt = members[k]->pt();
	 JetTemp->fRapid = members[k]->rapidity();
	 JetTemp->fEta = members[k]->eta();
	 JetTemp->iCharge = members[k]->charge();
	 JetTemp->iStatus = members[k]->status(); 
	 JetTemp->iPdgId = members[k]->pdgId(); 
	 JetTemp->iFromHQc = 0;
	 JetTemp->iFromAnyHQc = 0;
	 JetTemp->iFromHQb = 0;
         JetTemp->iFromAnyHQb = 0;
      }

      spectraTree->Fill(); //filled n times 
      CAJetPart->Clear();  
   }
   
   totEvt++;

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
GenJetSpectraAnalyzer::beginJob()
{
   resultFile = new TFile(resultFileLabel.c_str(),"recreate");
   resultFile->cd();

   CAJetPart = new TClonesArray("FoundJets",20000);
   CAAllPart = new TClonesArray("FoundJets",20000);

   spectraTree = new TTree("SpectraStudyTree","SpectraStudyTree");
   spectraTree->Branch("NumJets",&iJets,"NumJets/I");
   spectraTree->Branch("JetIndex",&iJIndex,"JetIndex/I");
   spectraTree->Branch("JetPt",&fJPt,"JetPt/F");
   spectraTree->Branch("JetPhi",&fJPhi,"JetPhi/F");
   spectraTree->Branch("JetRapidity",&fJRapid,"JetRapidity/F");
   spectraTree->Branch("JetEta",&fJEta,"JetEta/F");
   spectraTree->Branch("JetEt",&fJEt,"JetEt/F");
   spectraTree->Branch("Alpha",&fAlpha,"Alpha/F");

   spectraTree->Branch("JetParticles",&CAJetPart);

   spectraTree2 = new TTree("SpectraStudyTree2","SpectraStudyTree2");
   spectraTree2->Branch("AllParticles",&CAAllPart);

   totEvt = 0;

}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenJetSpectraAnalyzer::endJob() {
   resultFile->cd();
   spectraTree->Write();
   spectraTree2->Write();
   resultFile->Close();

   cout<<"Total number of events analyzed: "<<totEvt<<endl;

}

//define this as a plug-in
DEFINE_FWK_MODULE(GenJetSpectraAnalyzer);
