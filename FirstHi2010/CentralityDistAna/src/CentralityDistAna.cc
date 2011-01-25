// -*- C++ -*-
//
// Package:    CentralityDistAna
// Class:      CentralityDistAna
// 
/**\class CentralityDistAna CentralityDistAna.cc FirstHi2010/CentralityDistAna/src/CentralityDistAna.cc

 Description: simple centrality distribution analyzer

 Implementation:
    see /CMSSW/RecoHI/HiCentralityAlgos/test/AnalyzerWithCentrality.cc
*/
//
// Original Author:  Andre Yoon,32 4-A06,+41227676980,
//         Created:  Mon Nov 22 11:37:43 CET 2010
// $Id: CentralityDistAna.cc,v 1.8 2011/01/20 20:34:25 sungho Exp $
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
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
using namespace std;

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
   TH1F *hCentBinDistNcollWeighted;
   TH1F *hCentBinDistNpartWeighted;
   TH1F *hHFhitSumDist;
   TH1F *hHFtowerSumDist;

   TH1F *hNcollValueAtCent;
   TH2F *hCentBinPxlHitDist;
   

   std::vector<int32_t> neededCentBins_;

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
CentralityDistAna::CentralityDistAna(const edm::ParameterSet& iConfig) :
   centrality_(0)
{
   //now do what ever initialization is needed
   neededCentBins_ = iConfig.getUntrackedParameter<std::vector<int> >("neededCentBins");


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

   float hf = centrality_->raw()->EtHFhitSum();
   float hft = centrality_->raw()->EtHFtowerSum();

   float npartMean = centrality_->NpartMean();
   float ncollMean = centrality_->NcollMean();

   // centrality variable distribution
   hCentBinDist->Fill(bin);
   hCentBinDistNpartWeighted->Fill(bin,npartMean);
   hCentBinDistNcollWeighted->Fill(bin,ncollMean);

   hHFhitSumDist->Fill(hf);
   hHFtowerSumDist->Fill(hft);

   // fill once to check Ncoll(cent. bin) 
   int hbin = hNcollValueAtCent->GetXaxis()->FindBin(bin);
   if(hNcollValueAtCent->GetBinContent(hbin)==0) hNcollValueAtCent->Fill(bin,ncollMean);
   
   // correlation variable
   float pixelhit = centrality_->raw()->multiplicityPixel();
   pixelhit = pixelhit/100.; // renormaliztion so that 120K -> 1200     

   hCentBinPxlHitDist->Fill(bin,pixelhit);


   

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
   hCentBinDist = fs->make<TH1F>("hCentBinDist","Centrality bin distribution; centrality bin",40,-0.5,39.5);
   hCentBinDistNcollWeighted = fs->make<TH1F>("hCentBinDistNcollWeighted",
					      "Centrality bin distribution weighted by N_{coll};centrality bin",40,-0.5,39.5);
   hCentBinDistNpartWeighted = fs->make<TH1F>("hCentBinDistNpartWeighted",
					      "Centrality bin distribution weighted by N_{part};centrality bin",40,-0.5,39.5);
   hHFhitSumDist = fs->make<TH1F>("hHFhitSumDist","HF hit energy sum distribution; Total energy in HF",160,0.0,200);
   hHFtowerSumDist = fs->make<TH1F>("hHFtowerSumDist","HF tower energy sum distribution; Total tower energy in HF",160,0.0,200);
   hNcollValueAtCent = fs->make<TH1F>("hNcollValueAtCent","N_{coll} value;centrality bin",40,-0.5,39.5);
   hCentBinPxlHitDist = fs->make<TH2F>("hCentBinPxlHitDist","Centrality bin vs pixel hit multiplicity;centrality bin;0.01*Nhit_{pixel}",
				       40,-0.5,39.5, 600,0,1200);
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralityDistAna::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralityDistAna);
