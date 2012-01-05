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
// $Id: CentralityDistAna.cc,v 1.14 2011/12/19 14:57:02 sungho Exp $
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

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"

#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

// ROOT includes
#include "TNtuple.h"
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
   TH1F *hHFhitValueAtCent;
   TH2F *hCentBinPxlHitDist;
   
   // With jet ET thresholds 
   TH1F *hCentBinDist_Jet35;
   TH1F *hCentBinDist_Jet50;
   TH1F *hCentBinDist_Jet60;
   TH1F *hCentBinDist_Jet80;
   TH1F *hCentBinDist_Jet100;
   
   TH1F *hHFhitSumDist_Jet35;
   TH1F *hHFhitSumDist_Jet50;
   TH1F *hHFhitSumDist_Jet60;
   TH1F *hHFhitSumDist_Jet80;
   TH1F *hHFhitSumDist_Jet100;

   TNtuple *nt_hfhits, *nt_hftowers;
   
   edm::InputTag jsrc_;

   std::vector<int32_t> neededCentBins_;

   bool useJetThreshold_;
   bool produceTree_;
   double applyStrechFact_;
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
   jsrc_ = iConfig.getUntrackedParameter<edm::InputTag>("jsrc",edm::InputTag("ak5CaloJets"));
   neededCentBins_ = iConfig.getUntrackedParameter<std::vector<int> >("neededCentBins");
   useJetThreshold_ = iConfig.getUntrackedParameter<bool>("useJetThreshold");
   produceTree_ = iConfig.getUntrackedParameter<bool>("produceTree");
   applyStrechFact_ = iConfig.getUntrackedParameter<double>("applyStrechFact_",-1);
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

   double jetet=0.0;

   // Get jet
   if(useJetThreshold_){

      edm::Handle<reco::CandidateView> jets;
      iEvent.getByLabel(jsrc_,jets);

      vector<const reco::Candidate *> sortedJets;

      for(unsigned it=0; it<jets->size(); ++it){
	 const reco::Candidate* jet = &((*jets)[it]);

	 sortedJets.push_back(jet);
	 sortByEtRef (&sortedJets);
      }

      if(sortedJets.size()!=0) jetet = sortedJets[0]->et(); // leading jet
   }


   // Get centrality information
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

   if(applyStrechFact_>0) hf = hf*applyStrechFact_; // apply strech factor (to compare 2011 and 201)

   hHFhitSumDist->Fill(hf/1000.);  // scaled it by 1000 GeV 
   hHFtowerSumDist->Fill(hft);

   if(produceTree_){
      nt_hfhits->Fill(hf,bin);
      nt_hftowers->Fill(hft,bin);
   }


   if(useJetThreshold_){
      if(jetet>=35)  hCentBinDist_Jet35->Fill(bin),  hHFhitSumDist_Jet35->Fill(hf/1000.);
      if(jetet>=50)  hCentBinDist_Jet50->Fill(bin),  hHFhitSumDist_Jet50->Fill(hf/1000.);
      if(jetet>=60)  hCentBinDist_Jet60->Fill(bin),  hHFhitSumDist_Jet60->Fill(hf/1000.);
      if(jetet>=80)  hCentBinDist_Jet80->Fill(bin),  hHFhitSumDist_Jet80->Fill(hf/1000.);
      if(jetet>=100) hCentBinDist_Jet100->Fill(bin), hHFhitSumDist_Jet100->Fill(hf/1000.);
   }

   // fill once to check Ncoll(cent. bin), HFhits(cent. bin) 
   int hbin = hNcollValueAtCent->GetXaxis()->FindBin(bin);
   if(hNcollValueAtCent->GetBinContent(hbin)==0) {
      hNcollValueAtCent->Fill(bin,ncollMean);
      hHFhitValueAtCent->Fill(bin,hf/1000.);
   } 

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
   hHFhitSumDist = fs->make<TH1F>("hHFhitSumDist","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
   hHFtowerSumDist = fs->make<TH1F>("hHFtowerSumDist","HF tower energy sum distribution; Total tower energy in HF",160,0.0,200);
   hNcollValueAtCent = fs->make<TH1F>("hNcollValueAtCent","N_{coll} value;centrality bin",40,-0.5,39.5);
   hHFhitValueAtCent = fs->make<TH1F>("hHFhitValueAtCent","HF hit energy value;centrality bin",40,-0.5,39.5);
   hCentBinPxlHitDist = fs->make<TH2F>("hCentBinPxlHitDist","Centrality bin vs pixel hit multiplicity;centrality bin;0.01*Nhit_{pixel}",
				       40,-0.5,39.5, 600,0,1200);

   if(useJetThreshold_){
      hCentBinDist_Jet35 = fs->make<TH1F>("hCentBinDist_Jet35","Centrality bin distribution; centrality bin",40,-0.5,39.5);
      hCentBinDist_Jet50 = fs->make<TH1F>("hCentBinDist_Jet50","Centrality bin distribution; centrality bin",40,-0.5,39.5);
      hCentBinDist_Jet60 = fs->make<TH1F>("hCentBinDist_Jet60","Centrality bin distribution; centrality bin",40,-0.5,39.5);
      hCentBinDist_Jet80 = fs->make<TH1F>("hCentBinDist_Jet80","Centrality bin distribution; centrality bin",40,-0.5,39.5);
      hCentBinDist_Jet100 = fs->make<TH1F>("hCentBinDist_Jet100","Centrality bin distribution; centrality bin",40,-0.5,39.5);

      hHFhitSumDist_Jet35 = fs->make<TH1F>("hHFhitSumDist_Jet35","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
      hHFhitSumDist_Jet50 = fs->make<TH1F>("hHFhitSumDist_Jet50","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
      hHFhitSumDist_Jet60 = fs->make<TH1F>("hHFhitSumDist_Jet60","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
      hHFhitSumDist_Jet80 = fs->make<TH1F>("hHFhitSumDist_Jet80","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
      hHFhitSumDist_Jet100 = fs->make<TH1F>("hHFhitSumDist_Jet100","HF hit energy sum distribution; Total energy in HF (TeV)",160,0.0,200);
   }

   if(produceTree_){
      nt_hfhits = fs->make<TNtuple>("nt_hfhits","HF hit distributions","hfhits:cbin");
      nt_hftowers = fs->make<TNtuple>("nt_hftowers","HF tower distributions","hftowers:cbin");
   }
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentralityDistAna::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentralityDistAna);
