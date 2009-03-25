// -*- C++ -*-
//
// Package:    EmbedderAnalyzer
// Class:      EmbedderAnalyzer
// 
/**\class EmbedderAnalyzer EmbedderAnalyzer.cc HIProdAlgos/EmbedderAnalyzer/src/EmbedderAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Sungho Yoon
//         Created:  Thu Mar  5 08:46:59 EST 2009
// $Id$
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"


#include "HepMC/GenEvent.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"

#include "TFile.h"
#include "TNtuple.h"

using namespace std;


//
// class decleration
//

class EmbedderAnalyzer : public edm::EDAnalyzer {
   public:
      explicit EmbedderAnalyzer(const edm::ParameterSet&);
      ~EmbedderAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
   TTree* anaTree;
   TNtuple *nt_bkgMC;
   TNtuple *nt_sigMC;
   TNtuple *nt_mixMC;

   TNtuple *nt_bkgMC_vtx;
   TNtuple *nt_sigMC_vtx;
   TNtuple *nt_mixMC_vtx;

   TNtuple *nt_bkgSIM;
   TNtuple *nt_sigSIM;
   TNtuple *nt_mixSIM;

   TNtuple *nt_bkgSIM_vtx;
   TNtuple *nt_sigSIM_vtx;
   TNtuple *nt_mixSIM_vtx;

   bool isMixed_;
   
   edm::Service<TFileService> fs; 

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
EmbedderAnalyzer::EmbedderAnalyzer(const edm::ParameterSet& iConfig) 

{
   //now do what ever initialization is needed
   isMixed_ = iConfig.getUntrackedParameter<bool>("isMixed",false);
}


EmbedderAnalyzer::~EmbedderAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EmbedderAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   cout<<"=================================================================================================="<<endl;

   using namespace edm;
   using namespace HepMC;


   //------------------------------------------------------------------
   // Getting MC level info
   //------------------------------------------------------------------
   cout<<"[EmbedderAnalyzer] Analyze MC level info ..."<<endl;

   const GenEvent* bgEvt; 
   const GenEvent* sigEvt; 

   //------ 1.source (existing data) 
   Handle<HepMCProduct> mc;
   iEvent.getByLabel("source",mc);
   bgEvt = mc->GetEvent();

   HepMC::GenEvent::particle_const_iterator mcbg = bgEvt->particles_begin();
   HepMC::GenEvent::particle_const_iterator mced = bgEvt->particles_end();

   for(HepMC::GenEvent::particle_const_iterator it = mcbg; it != mced; ++it){

	 float var[10];
	
	 int pdgId = (*it)->pdg_id();
	 int status = (*it)->status();
	 double eta = (*it)->momentum().eta();
	 double phi = (*it)->momentum().phi();
	 double pt = (*it)->momentum().perp();
	 
	 var[0] = pdgId;
	 var[1] = status;
	 var[2] = eta;
	 var[3] = phi;
	 var[4] = pt;
	 
	 nt_bkgMC->Fill(var);
   }
   
   HepMC::GenEvent::vertex_const_iterator vbg = bgEvt->vertices_begin();
   HepMC::GenEvent::vertex_const_iterator ved = bgEvt->vertices_end();

   for(HepMC::GenEvent::vertex_const_iterator bgMVtx = vbg; bgMVtx != ved; ++bgMVtx){

      float var[10];

      int vId = (*bgMVtx)->id();
      bool bcode = (*bgMVtx)->barcode();
      double vx = (*bgMVtx)->position().x();
      double vy = (*bgMVtx)->position().y();
      double vz = (*bgMVtx)->position().z();

      var[0] = vId;
      var[1] = bcode;
      var[2] = vx;
      var[3] = vy;
      var[4] = vz;

      nt_bkgMC_vtx->Fill(var);
   }

   //------ 2.signal (generated data on the fly) 
   if(isMixed_){

      Handle<HepMCProduct> mc2;
      iEvent.getByLabel("signal",mc2);
      sigEvt = mc2->GetEvent();

      HepMC::GenEvent::particle_const_iterator mcbg2 = sigEvt->particles_begin();
      HepMC::GenEvent::particle_const_iterator mced2 = sigEvt->particles_end();

      for(HepMC::GenEvent::particle_const_iterator it = mcbg2; it != mced2; ++it){

	    float var[10];
	    
	    int pdgId = (*it)->pdg_id();
	    int status = (*it)->status();
	    double eta = (*it)->momentum().eta();
	    double phi = (*it)->momentum().phi();
	    double pt = (*it)->momentum().perp();

	    var[0] = pdgId;
	    var[1] = status;
	    var[2] = eta;
	    var[3] = phi;
	    var[4] = pt;

	    nt_sigMC->Fill(var);
      }
 
      HepMC::GenEvent::vertex_const_iterator vbg2 = sigEvt->vertices_begin();
      HepMC::GenEvent::vertex_const_iterator ved2 = sigEvt->vertices_end();
      
      for(HepMC::GenEvent::vertex_const_iterator sigMVtx = vbg2; sigMVtx != ved2; ++sigMVtx){
	 
	 float var[10];
	 
	 int vId = (*sigMVtx)->id();
	 int bcode = (*sigMVtx)->barcode();
	 double vx = (*sigMVtx)->position().x();
	 double vy = (*sigMVtx)->position().y();
	 double vz = (*sigMVtx)->position().z();
	 
	 var[0] = vId;
	 var[1] = bcode;
	 var[2] = vx;
	 var[3] = vy;
	 var[4] = vz;
	 
	 nt_sigMC_vtx->Fill(var);
      }
   }
   
   //------ 3. mixed (singal+source)  

   if(isMixed_){

      cout<<"[EmbedderAnalyzer] Mixed event!"<<endl;

      int nmix; 
      int nsig;
      int nbkg; 
      /*
      int nbcx;
      int trig;
      int src;
      */

      Handle<CrossingFrame<HepMCProduct> > mixed;
      iEvent.getByLabel(InputTag("mix","source"),mixed);

      MixCollection<HepMCProduct> mix(mixed.product());

      nmix = mix.size();
      nsig = mix.sizeSignal();
      nbkg = mix.sizePileup();

      cout<<"[EmbedderAnalyzer] Number of objects is "<<nmix<<" (nsig = "<<nsig<<" and nbkg = "<<nbkg<<")"<<endl; 

      //MixCollection<HepMCProduct>::iterator mixit;
      MixCollection<HepMCProduct>::iterator mbegin = mix.begin();
      MixCollection<HepMCProduct>::iterator mend = mix.end();

      for(MixCollection<HepMCProduct>::iterator mixit = mbegin; mixit != mend; ++mixit) {
	 /*
	 nbcx = mixit.bunch();
	 trig = mixit.getTrigger();
	 src = mixit.getSourceType();
	 */

	 const GenEvent* mixEvt = (*mixit).GetEvent();

	 cout<<"[EmbedderAnalyzer] >>>Event number =  "<<mixEvt->event_number()<<"<<<"<<endl;
	 cout<<"[EmbedderAnalyzer] There are "<<mixEvt->particles_size()<<" particles"<<endl;
	 cout<<"[EmbedderAnalyzer] There are "<<mixEvt->vertices_size()<<" vertices"<<endl;
	 /*
	 cout<<"[EmbedderAnalyzer] There are "<<nbcx<<" bunch crossing"<<endl;
	 cout<<"[EmbedderAnalyzer] Trigger =  "<<trig<<endl;
	 cout<<"[EmbedderAnalyzer] Source type =  "<<src<<endl;
	 */
	 HepMC::GenEvent::particle_const_iterator begin = mixEvt->particles_begin();
	 HepMC::GenEvent::particle_const_iterator end = mixEvt->particles_end();
	 
	 for(HepMC::GenEvent::particle_const_iterator it = begin; it != end; ++it){

	       float var[10];
	       
	       int pdgId = (*it)->pdg_id();
	       int status = (*it)->status();
	       double eta = (*it)->momentum().eta();
	       double phi = (*it)->momentum().phi();
	       double pt = (*it)->momentum().perp();

	       var[0] = pdgId;
	       var[1] = status;
	       var[2] = eta;
	       var[3] = phi;
	       var[4] = pt;
	       
	       nt_mixMC->Fill(var);
         }

	 HepMC::GenEvent::vertex_const_iterator vbg3 = mixEvt->vertices_begin();
	 HepMC::GenEvent::vertex_const_iterator ved3 = mixEvt->vertices_end();

	 for(HepMC::GenEvent::vertex_const_iterator mixMVtx = vbg3; mixMVtx != ved3; ++mixMVtx){

	    float var[10];

	    int vId = (*mixMVtx)->id();
	    bool bcode = (*mixMVtx)->barcode();
	    double vx = (*mixMVtx)->position().x();
	    double vy = (*mixMVtx)->position().y();
	    double vz = (*mixMVtx)->position().z();

	    var[0] = vId;
	    var[1] = bcode;
	    var[2] = vx;
	    var[3] = vy;
	    var[4] = vz;

	    nt_mixMC_vtx->Fill(var);
	 }

      }
   }
   
   
   //----------------------------------------------------------------------
   // Getting SIM level info
   //----------------------------------------------------------------------

   cout<<"[EmbedderAnalyzer] Analyze SIM level info ..."<<endl;

   //------ 1. source (existing data)  "g4SimHits"

   Handle<SimTrackContainer> bkgSTrk;
   iEvent.getByLabel("g4SimHits",bkgSTrk);
   cout<<"[EmbedderAnalyzer] Number of background SIM tracks:  "<<bkgSTrk->size()<<endl;

   SimTrackContainer::const_iterator stbg =  bkgSTrk->begin(); 
   SimTrackContainer::const_iterator sted = bkgSTrk->end();

   for(SimTrackContainer::const_iterator strkit = stbg; strkit != sted; ++strkit){

      float var[10];
      
      int pID = strkit->type();
      int vtxInd = strkit->vertIndex();
      int mcInd = strkit->genpartIndex();
      double eta = strkit->momentum().eta();
      double phi = strkit->momentum().phi();
      double pt = strkit->momentum().pt();

      var[0] = pID;
      var[1] = vtxInd;
      var[2] = mcInd;
      var[3] = eta;
      var[4] = phi;
      var[5] = pt;

      nt_bkgSIM->Fill(var);
   }

   Handle<SimVertexContainer> bkgSVtx;
   iEvent.getByLabel("g4SimHits",bkgSVtx);
   cout<<"[EmbedderAnalyzer] Number of background SIM vertices:  "<<bkgSVtx->size()<<endl;

   SimVertexContainer::const_iterator svbg = bkgSVtx->begin();
   SimVertexContainer::const_iterator sved = bkgSVtx->end();

   for(SimVertexContainer::const_iterator svtxit = svbg; svtxit != sved; ++svtxit){

      float var[10];
  
      int pInd = svtxit->parentIndex();
      bool noParent = svtxit->noParent();
      double vx = svtxit->position().x();
      double vy = svtxit->position().y();
      double vz = svtxit->position().z();

      var[0] = pInd;
      var[1] = noParent;
      var[2] = vx;
      var[3] = vy;
      var[4] = vz;
      
      nt_bkgSIM_vtx->Fill(var);

   }


   //------ 1. signal? (generated on the fly)  "SuperSIM"    
   if(isMixed_){

      Handle<SimTrackContainer> sigSTrk;
      iEvent.getByLabel("superSIM",sigSTrk);
      cout<<"[EmbedderAnalyzer] Number of signal SIM tracks:  "<<sigSTrk->size()<<endl;
      
      SimTrackContainer::const_iterator stbg2 =  sigSTrk->begin();
      SimTrackContainer::const_iterator sted2 = sigSTrk->end();
      
      for(SimTrackContainer::const_iterator strkit2 = stbg2; strkit2 != sted2; ++strkit2){
	 
	 float var[10];
	 
	 int pID = strkit2->type();
	 int vtxInd = strkit2->vertIndex();
	 int mcInd = strkit2->genpartIndex();
	 double eta = strkit2->momentum().eta();
	 double phi = strkit2->momentum().phi();
	 double pt = strkit2->momentum().pt();
	 
	 var[0] = pID;
	 var[1] = vtxInd;
	 var[2] = mcInd;
	 var[3] = eta;
	 var[4] = phi;
	 var[5] = pt;
	 
	 nt_sigSIM->Fill(var);
      }
   } 
   
   if(isMixed_){
      
      Handle<SimVertexContainer> sigSVtx;
      iEvent.getByLabel("superSIM",sigSVtx);
      cout<<"[EmbedderAnalyzer] Number of signal SIM vertices:  "<<sigSVtx->size()<<endl;
      
      SimVertexContainer::const_iterator svbg2 = sigSVtx->begin();
      SimVertexContainer::const_iterator sved2 = sigSVtx->end();
      
      for(SimVertexContainer::const_iterator svtxit2 = svbg2; svtxit2 != sved2; ++svtxit2){
	 
	 float var[10];
	 
	 int pInd = svtxit2->parentIndex();
	 bool noParent = svtxit2->noParent();
	 double vx = svtxit2->position().x();
	 double vy = svtxit2->position().y();
	 double vz = svtxit2->position().z();
	 
	 var[0] = pInd;
	 var[1] = noParent;
	 var[2] = vx;
	 var[3] = vy;
	 var[4] = vz;
	 
	 nt_sigSIM_vtx->Fill(var);
	 
      }
   }


   //------ mixed 
   if(isMixed_){

      cout<<"[EmbedderAnalyzer] Mixed event!"<<endl;

      Handle<CrossingFrame<SimTrack> > mixedSTrk;
      iEvent.getByLabel(InputTag("mix","g4SimHits"),mixedSTrk);


      MixCollection<SimTrack> mixSTrk(mixedSTrk.product());

      cout<<"[EmbedderAnalyzer] Number of mixed SIM tracks:  "<<mixSTrk.size()<<endl;
      
      MixCollection<SimTrack>::iterator stbg3 =  mixSTrk.begin();
      MixCollection<SimTrack>::iterator sted3 = mixSTrk.end();
    
      for(MixCollection<SimTrack>::iterator strkit3 = stbg3; strkit3 != sted3; ++strkit3){
	 
	 float var[10];

	 int pID = strkit3->type();
	 int vtxInd = strkit3->vertIndex();
         int mcInd = strkit3->genpartIndex();
	 double eta = strkit3->momentum().eta();
	 double phi = strkit3->momentum().phi();
	 double pt = strkit3->momentum().pt();

	 var[0] = pID;
	 var[1] = vtxInd;
	 var[2] = mcInd;
	 var[3] = eta;
	 var[4] = phi;
	 var[5] = pt;

	 nt_mixSIM->Fill(var);

      }
   } 


   if(isMixed_){
      
      Handle<CrossingFrame<SimVertex> > mixedSVtx;
      iEvent.getByLabel(InputTag("mix","g4SimHits"),mixedSVtx);

      MixCollection<SimVertex> mixSVtx(mixedSVtx.product());

      cout<<"[EmbedderAnalyzer] Number of mixed SIM vertices:  "<<mixSVtx.size()<<endl;

      MixCollection<SimVertex>::iterator svbg3 =  mixSVtx.begin();
      MixCollection<SimVertex>::iterator sved3 = mixSVtx.end();

      for(MixCollection<SimVertex>::iterator svtxit3 = svbg3; svtxit3 != sved3; ++svtxit3){

         float var[10];

         int pInd = svtxit3->parentIndex();
	 bool noParent = svtxit3->noParent();
         double vx = svtxit3->position().x();
         double vy = svtxit3->position().y();
         double vz = svtxit3->position().z();

	 var[0] = pInd;
	 var[1] = noParent;
	 var[2] = vx;
	 var[3] = vy;
	 var[4] = vz;

         nt_mixSIM_vtx->Fill(var);

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
EmbedderAnalyzer::beginJob(const edm::EventSetup&)
{

   //MC
   nt_bkgMC = fs->make<TNtuple>("nt_bkgMC","MC level analysis ntuple (source)","id:status:eta:phi:pt");
   nt_bkgMC_vtx = fs->make<TNtuple>("nt_bkgMC_vtx","MC level analysis ntuple (source)","vid:bcode:vx:vy:vz");
   if(isMixed_){
      nt_sigMC = fs->make<TNtuple>("nt_sigMC","MC level analysis ntuple (signal)","id:status:eta:phi:pt");
      nt_sigMC_vtx = fs->make<TNtuple>("nt_sigMC_vtx","MC level analysis ntuple (source)","vid:bcode:vx:vy:vz");
      nt_mixMC = fs->make<TNtuple>("nt_mixMC","MC level analysis ntuple (mixed)","id:status:eta:phi:pt");
      nt_mixMC_vtx = fs->make<TNtuple>("nt_mixMC_vtx","MC level analysis ntuple (source)","vid:bcode:vx:vy:vz");
   }

   //SIM
   nt_bkgSIM = fs->make<TNtuple>("nt_bkgSIM","SIM level analysis ntuple (source)","id:vtxid:mcid:eta:phi:pt");
   nt_bkgSIM_vtx = fs->make<TNtuple>("nt_bkgSIM_vtx","SIM level analysis ntuple (source)","pind:parent:vx:vy:vz");
   if(isMixed_){
      nt_sigSIM = fs->make<TNtuple>("nt_sigSIM","SIM level analysis ntuple (source)","id:vtxid:mcid:eta:phi:pt");
      nt_sigSIM_vtx = fs->make<TNtuple>("nt_sigSIM_vtx","SIM level analysis ntuple (source)","pind:parent:vx:vy:vz");
      nt_mixSIM = fs->make<TNtuple>("nt_mixSIM","SIM level analysis ntuple (mixed)","id:vtxid:mcid:eta:phi:pt");
      nt_mixSIM_vtx = fs->make<TNtuple>("nt_mixSIM_vtx","SIM level analysis ntuple (source)","pind:parent:vx:vy:vz");
   }

   //nt_sim = tf->make<TNtuple>("nt_sim","SIM level analysis ntuple","a:b:c:d");
   //anaTree = tf->make<TTree>("ANA_MC","MC level analysis tree");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
EmbedderAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EmbedderAnalyzer);
