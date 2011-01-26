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

// centrality
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"



// ROOT includes
#include <TH2.h>
#include <TMath.h>

class HiTrackValidator : public edm::EDAnalyzer {
   public:
      explicit HiTrackValidator(const edm::ParameterSet&);
      ~HiTrackValidator(){};

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      typedef math::XYZPoint Point;

      // ----------member data ---------------------------
      edm::Service<TFileService> f;

      edm::InputTag bslabel_;
      edm::InputTag vtxlabel_;
      edm::InputTag trklabel_;
      edm::InputTag simtrklabel_;
      edm::InputTag associatorMap_;

      CentralityProvider * centrality_;

      double etaMax_;

      bool hasSimInfo_;
      bool selectFake_;
      bool useQaulityStr_;

      // quality cuts distribution 
      TH1D *hVtxSize;
      TH1D *hNlayers;
      TH1D *hNlayers3D;
      TH1D *hNlayersLost;
      TH1D *hNvalidHits;
      TH1D *hChi2n;
      TH1D *hRelPtErr;
      TH1D *hdzPV, *hd0PV;
      TH1D *hdzErr, *hd0Err;
      TH1D *hdzErrPV, *hd0ErrPV;
      TH1D *hvzErr, *hvtErr;
      TH1D *hdzOverdzErr, *hd0Overd0Err;
      TH1D *hdzOverdzErrPV, *hd0Overd0ErrPV;

      std::vector<TH1D*> hNvalidHits_Cent;
      std::vector<TH1D*> hChi2n_Cent;
      std::vector<TH1D*> hRelPtErr_Cent;
      std::vector<TH1D*> hdzPV_Cent;
      std::vector<TH1D*> hd0PV_Cent;
      std::vector<TH1D*> hdzErrPV_Cent;
      std::vector<TH1D*> hd0ErrPV_Cent;
      std::vector<TH1D*> hdzOverdzErrPV_Cent;
      std::vector<TH1D*> hd0Overd0ErrPV_Cent;

      // as a function of pt
      TH2D *hNlayersdPt;
      TH2D *hNlayers3DdPt;
      TH2D *hNlayersLostdPt;
      TH2D *hNvalidHitsdPt;
      TH2D *hChi2ndPt;
      TH2D *hRelPtErrdPt;
      TH2D *hdzPVdPt, *hd0PVdPt;
      TH2D *hdzErrdPt, *hd0ErrdPt;
      TH2D *hdzErrPVdPt, *hd0ErrPVdPt;
      TH2D *hvzErrdPt, *hvtErrdPt;
      TH2D *hdzOverdzErrdPt, *hd0Overd0ErrdPt;
      TH2D *hdzOverdzErrPVdPt, *hd0Overd0ErrPVdPt;

      std::vector<TH2D*> hNvalidHitsdPt_Cent;
      std::vector<TH2D*> hChi2ndPt_Cent;
      std::vector<TH2D*> hRelPtErrdPt_Cent;
      std::vector<TH2D*> hdzPVdPt_Cent;
      std::vector<TH2D*> hd0PVdPt_Cent;
      std::vector<TH2D*> hdzErrPVdPt_Cent;
      std::vector<TH2D*> hd0ErrPVdPt_Cent;
      std::vector<TH2D*> hdzOverdzErrPVdPt_Cent;
      std::vector<TH2D*> hd0Overd0ErrPVdPt_Cent;

      // correlations
      TH2D *hdzErrd0Err;
      TH2D *hdzErrd0ErrPV;
      TH2D *hdzOverdzErrd0Err;
      TH2D *hdzOverdzErrd0ErrPV;

      std::vector<TH2D*> hdzOverdzErrd0Err_Cent;
      std::vector<TH2D*> hdzOverdzErrd0ErrPV_Cent;
      
      // kinematic distributions
      TH2D *hEtaPhi;
      std::vector<TH2D*> hEtaPhi_Cent;

      std::vector<double> ptBins;
      std::vector<int32_t> neededCentBins_;


};
