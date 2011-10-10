// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

// for jet,track,vertices correlation 
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

// sim <--> rec track association
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"

// Pixel hit information
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"
#include "DataFormats/SiPixelDetId/interface/PixelEndcapName.h"

// centrality
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"



// ROOT includes
#include <TNtuple.h>
#include <TH2.h>
#include <TMath.h>

class HiTrackMatchingAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HiTrackMatchingAnalyzer(const edm::ParameterSet&);
      ~HiTrackMatchingAnalyzer(){};

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      //bool hitDeadPXF(const reco::Track&);
      bool isMatched(const reco::Track&, const reco::Track&);
      typedef math::XYZPoint Point;

      // ----------member data ---------------------------
      edm::InputTag trkFst_;
      edm::InputTag trkSnd_;
      edm::InputTag jetTags_;

      double etaMax_;
      std::vector<double> jetEtCuts_;

      bool needTree_;
      double ptMinTree_;

      bool checkHitMat_; 
      double drMax_;
      double ptMinHitMat_;

      std::vector<int32_t> neededCentBins_;

      CentralityProvider * centrality_;

      std::vector<double> etaBins, ptBins, jetBins, centBins;

      edm::Service<TFileService> fs;

      std::vector<TH1F*> hTrk1Pt_Cent; // pt distribution 
      std::vector<TH1F*> hTrk2Pt_Cent;

      std::vector<TH1F*> hTrk1PtExcl_Cent;
      std::vector<TH1F*> hTrk2PtExcl_Cent;
      std::vector<TH1F*> hTrkPtMatch_Cent;

      //std::vector<TH2F*> hTrk1PtJetExcl_Cent;
      //std::vector<TH2F*> hTrk2PtJetExcl_Cent;
      //std::vector<TH2F*> hTrkPtJetMatch_Cent;


      std::vector<TH1F*> hTrk1FShare_Cent; // fraction of shared
      std::vector<TH1F*> hTrk2FShare_Cent; 

      //std::vector<TH2F*> hTrk1PtTrk2Pt_Cent;     
      //std::vector<TH2F*> hTrk1EtaTrk2Eta_Cent;
      //std::vector<TH2F*> hTrk1PhiTrk2Phi_Cent;

      // root objects
      TNtuple *nt_trk1, *nt_trk2;
      TNtuple *nt_trk_mat;
      TNtuple *nt_trk_cls; 

};
