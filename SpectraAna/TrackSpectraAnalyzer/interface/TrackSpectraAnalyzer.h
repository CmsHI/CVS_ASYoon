
// user include files                                                                                                                                                  
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"

//#include "FWCore/Common/interface/TriggerNames.h"
//#include "DataFormats/Common/interface/TriggerResults.h"

//#include "DataFormats/TrackReco/interface/Track.h"
//#include "DataFormats/VertexReco/interface/Vertex.h"
//#include "DataFormats/JetReco/interface/CaloJet.h"

//#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
//#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//#include "DataFormats/PatCandidates/interface/Jet.h"

#include "SpectraAna/TrackSpectraAnalyzer/interface/TrackSpectraAnalyzerHist.h"


//                                                                                                                                                                     
// class declaration                                                                                                                                                   
//                                                                                                                                                                     

class TrackSpectraAnalyzer : public edm::EDAnalyzer {
 public:
   explicit TrackSpectraAnalyzer(const edm::ParameterSet&);
   ~TrackSpectraAnalyzer();


 private:
   virtual void beginJob() ;
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;

   // ----------member data ---------------------------                                                                                                                

   /*
   TNtuple *nt_dndptdeta;
   TNtuple *nt_gen_dndptdeta;
   TNtuple *nt_jet;
   //TNtuple *nt_jettrack;                                                                                                                                             

   TH1D *hTrkPtMB;
   TH1D *hVtxZ;

   TH2D *hTrkPtEta;
   //TH2D *hJetEtEtaMB, *hJetEtEta6U, *hJetEtEta15U, *hJetEtEta30U, *hJetEtEta50U;                                                                                     
   TH3D *hTrkPtEtaMB, *hTrkPtEta6U, *hTrkPtEta15U, *hTrkPtEta30U, *hTrkPtEta50U;
   */
   TrackSpectraAnalyzerHist *histograms;
   
   edm::Service<TFileService> fs;

   edm::InputTag src_;
   edm::InputTag vsrc_;
   edm::InputTag jsrc_;

   bool wantNtuple_;
   bool isGEN_, doJet_;
   
   //int32_t  etaBins_;
   double  etaCut_;

   int32_t ptBins_;
   double  ptMin_, ptMax_;

   int32_t jetaBins_;
   double jetaMax_;

   int32_t jetBins_;
   double  jetMin_, jetMax_;

   int32_t nVtxTrkCut_;

};

