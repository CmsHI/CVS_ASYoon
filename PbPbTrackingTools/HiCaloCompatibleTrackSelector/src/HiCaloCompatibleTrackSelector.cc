/*
 
 Based on analytical track selector   
 
 - This is track selector that rejects tracks lie in the incompatible calo-track region.
 - No selection is done other then rejecting those tracks.
 
 */


// Basic inclusion
#include "PbPbTrackingTools/HiCaloCompatibleTrackSelector/interface/HiCaloCompatibleTrackSelector.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Math/interface/deltaR.h"
#include <Math/DistFunc.h>
#include "TMath.h"


using reco::modules::HiCaloCompatibleTrackSelector;

HiCaloCompatibleTrackSelector::HiCaloCompatibleTrackSelector( const edm::ParameterSet & cfg ) :
src_(cfg.getParameter<edm::InputTag>("src")),
srcTower_(cfg.getParameter<edm::InputTag>("srcTower")),
applyCaloComp_(cfg.getUntrackedParameter<bool>("applyCaloComp")),
applyPtDepCut_(cfg.getUntrackedParameter<bool>("applyPtDepCut")),
trkPtMin_(cfg.getUntrackedParameter<double>("trkPtMin",20.0)),
trkPtMax_(cfg.getUntrackedParameter<double>("trkPtMax",20.0)),
trkEtaMax_(cfg.getUntrackedParameter<double>("trkEtaMax",2.4)),
towerPtMin_(cfg.getUntrackedParameter<double>("towerPtMin",5.0)),
matchConeRadius_(cfg.getUntrackedParameter<double>("matchConeRadius",0.087)),
caloCut_(cfg.getUntrackedParameter<double>("caloCut",0.2)),
copyExtras_(cfg.getUntrackedParameter<bool>("copyExtras", false)),
copyTrajectories_(cfg.getUntrackedParameter<bool>("copyTrajectories", false)),
useQaulityStr_(cfg.getUntrackedParameter<bool>("useQaulityStr")),
qualityString_(cfg.getUntrackedParameter<std::string>("qualityString")),
hasSimInfo_(cfg.getUntrackedParameter<bool>("hasSimInfo_", false)),
funcCaloComp_(cfg.getParameter<std::string>("funcCaloComp")),
reverseSel_(cfg.getUntrackedParameter<bool>("reverseSel"))
{
  std::string alias( cfg.getParameter<std::string>( "@module_label" ) );
  produces<reco::TrackCollection>().setBranchAlias( alias + "Tracks");
  if (copyExtras_) {
    produces<reco::TrackExtraCollection>().setBranchAlias( alias + "TrackExtras");
    produces<TrackingRecHitCollection>().setBranchAlias( alias + "RecHits");
  }
  if (copyTrajectories_) {
    produces< std::vector<Trajectory> >().setBranchAlias( alias + "Trajectories");
    produces< TrajTrackAssociationCollection >().setBranchAlias( alias + "TrajectoryTrackAssociations");
  }
  
  fCaloComp = new TF1("fCaloComp",funcCaloComp_.c_str(),0,200); // a parameterization of pt dependent cut
}

HiCaloCompatibleTrackSelector::~HiCaloCompatibleTrackSelector() {
}


void HiCaloCompatibleTrackSelector::matchByDrAllowReuse(const reco::Track & trk, const edm::Handle<CaloTowerCollection> & towers, float & bestdr, int & ibest)
{
  // loop over towers
  bestdr=1e10;
  ibest=-1;
  for(unsigned int i = 0; i < towers->size(); ++i){
    const CaloTower & tower= (*towers)[i];
    if (tower.pt()<towerPtMin_) continue;
    if (fabs(tower.eta())>trkEtaMax_) continue;
    float dr = reco::deltaR(tower,trk);
    if (dr<bestdr) {
      bestdr = dr;
      ibest = i;
    }
  }
}

void HiCaloCompatibleTrackSelector::matchByConeAllowReuse(const reco::Track & trk, const edm::Handle<CaloTowerCollection> & towers, float & bestpt, int & ibest)
{
  // loop over towers
  bestpt=-1;
  ibest=-1;
  for(unsigned int i = 0; i < towers->size(); ++i){
    const CaloTower & tower= (*towers)[i];
    if (tower.pt()<towerPtMin_) continue;
    if (fabs(tower.eta())>trkEtaMax_) continue;
    float dr = reco::deltaR(tower,trk);
    if (dr>matchConeRadius_) continue;
    // choose highest pt in cone
    if (tower.pt()>bestpt) {
      bestpt = tower.pt();
      ibest = i;
    }
  }
}

void HiCaloCompatibleTrackSelector::produce( edm::Event& evt, const edm::EventSetup& es ) 
{
  using namespace std; 
  using namespace edm;
  using namespace reco;
  
  LogDebug("HiCaloCompatibleTrackSelector")<<"min pt for selection = "<< trkPtMin_<<endl;
  
  
  Handle<TrackCollection> hSrcTrack;
  Handle< vector<Trajectory> > hTraj;
  Handle< vector<Trajectory> > hTrajP;
  Handle< TrajTrackAssociationCollection > hTTAss;
  
  // get track collection
  Handle<edm::View<reco::Track> > trackCollectionH;
  evt.getByLabel(src_,trackCollectionH);
  const edm::View<reco::Track>  tC = *(trackCollectionH.product());
  
  // get track collection (new collection to be created)
  evt.getByLabel(src_,hSrcTrack);
  
  selTracks_ = auto_ptr<TrackCollection>(new TrackCollection());
  
  // get PFCandidates
  edm::Handle<CaloTowerCollection> towers;
  bool isTowerThere = evt.getByLabel(srcTower_, towers);
  
  
  for(edm::View<reco::Track>::size_type i=0; i<tC.size(); ++i) {
    edm::RefToBase<reco::Track> track(trackCollectionH, i);
    const reco::Track & trk = (*hSrcTrack)[i];
    
    if(!isTowerThere || !applyCaloComp_){   // if no PFCand or no compatibility check,  no selection 
      
      selTracks_->push_back(trk);
      
    }else{
      
      float matchDr;
      int matchIndex;
      float matchPt=0;
      matchByDrAllowReuse(trk,towers,matchDr,matchIndex);
      if (matchIndex>=0) {
        matchPt=(*towers)[i].pt();
      }
      
      bool keepIt = false;
      
      //if (matchDr<matchConeRadius_&&(matchPt/trk.pt()>caloCut_)) keepIt = true;
        
      if(applyPtDepCut_){
	 float matchConeRadius_pt = (fCaloComp->Eval(trk.pt())!=fCaloComp->Eval(trk.pt())) ? 0 : fCaloComp->Eval(trk.pt()); // protect agains NaN
	 if (matchDr<matchConeRadius_pt && (matchPt/trk.pt()>caloCut_)) keepIt = true; // keep it calo-compatible 
      }else{
	 if(trk.pt() < trkPtMin_) keepIt = true; // if pt< min pt, keep it
	 else if(matchDr<matchConeRadius_&& (matchPt/trk.pt()>caloCut_)) keepIt = true;
      }
      
      if(reverseSel_) keepIt = (!keepIt); // reverse the selection 
      
      if(keepIt) selTracks_->push_back(trk); // save selected tracks 
      
      
    }
  }
  
  LogDebug("HiCaloCompatibleTrackSelector")<<" number of tracks: (1) before selection = "<<tC.size()
  <<" (2) after selection = "<<selTracks_->size()<<endl;
  
  evt.put(selTracks_);
  
}


