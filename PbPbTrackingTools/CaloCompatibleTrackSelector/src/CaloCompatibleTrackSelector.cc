/*

Based on analytical track selector   

- This is track selector that rejects tracks lie in the incompatible calo-track region.
- No selection is done other then rejecting those tracks.

*/


// Basic inclusion
#include "PbPbTrackingTools/CaloCompatibleTrackSelector/interface/CaloCompatibleTrackSelector.h"
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

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include <Math/DistFunc.h>
#include "TMath.h"
#include <TF1.h>


using reco::modules::CaloCompatibleTrackSelector;

CaloCompatibleTrackSelector::CaloCompatibleTrackSelector( const edm::ParameterSet & cfg ) :
    src_(cfg.getParameter<edm::InputTag>("src")),
    srcPFCand_(cfg.getParameter<edm::InputTag>("srcPFCand")),
    thePtMin_(cfg.getUntrackedParameter<double>("ptMin",10.0)),
    copyExtras_(cfg.getUntrackedParameter<bool>("copyExtras", false)),
    copyTrajectories_(cfg.getUntrackedParameter<bool>("copyTrajectories", false)),
    hasSimInfo_(cfg.getUntrackedParameter<bool>("hasSimInfo_", false)),
    funcCaloComp_(cfg.getParameter<std::string>("funcCaloComp"))
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
   
   fCaloComp = new TF1("fCaloComp",funcCaloComp_.c_str(),0,200); // a function that defines track-calo (in)compatible region 

}

CaloCompatibleTrackSelector::~CaloCompatibleTrackSelector() {
}

void CaloCompatibleTrackSelector::produce( edm::Event& evt, const edm::EventSetup& es ) 
{
    using namespace std; 
    using namespace edm;
    using namespace reco;

    LogDebug("CaloCompatibleTrackSelector")<<"min pt for selection = "<<thePtMin_<<endl;

    
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
    Handle<PFCandidateCollection> pfCandidates;
    bool isPFThere = evt.getByLabel(srcPFCand_, pfCandidates);


    for(edm::View<reco::Track>::size_type i=0; i<tC.size(); ++i) {
       edm::RefToBase<reco::Track> track(trackCollectionH, i);
       const reco::Track & trk = (*hSrcTrack)[i];

       if(!isPFThere){   // if no PFCand, no selection 

	  selTracks_->push_back(trk);

       }else{

	  // loop over PF candidates
	  for( unsigned j=0; j<pfCandidates->size(); j++ ) {
	     const reco::PFCandidate& cand = (*pfCandidates)[j];
	     cand_type = cand.particleId();
	     
	     if(!(cand_type == PFCandidate::h)) continue; // charged hadron only
	     reco::TrackRef pftrackRef = cand.trackRef();
	     
	     if(i!=pftrackRef.key()) continue; // matched track (Track <--> PF Cand) only
	     
	     trk_pt = trk.pt();
	     
	     // loop over PF cand's element
	     sum_ecal=0.0, sum_hcal=0.0, sum_calo=0.0;
	     
	     for(unsigned k=0; k<cand.elementsInBlocks().size(); k++) {
		
		PFBlockRef blockRef = cand.elementsInBlocks()[k].first;
		
		unsigned indexInBlock = cand.elementsInBlocks()[k].second;
		const edm::OwnVector<  reco::PFBlockElement>&  elements = (*blockRef).elements();
		
		switch (elements[indexInBlock].type()) {
		   
		case PFBlockElement::ECAL: {
		   reco::PFClusterRef clusterRef = elements[indexInBlock].clusterRef();
		   double eet = clusterRef->energy()/cosh(clusterRef->eta());
		   sum_ecal+=eet;
		   break;
		}
		   
		case PFBlockElement::HCAL: {
		   reco::PFClusterRef clusterRef = elements[indexInBlock].clusterRef();
		   double eet = clusterRef->energy()/cosh(clusterRef->eta());
		   sum_hcal+=eet;
		   break; 
		}       
		case PFBlockElement::TRACK: {
		   //This is just the reference to the track itself, since tracks can never be linked to other tracks
		   break; 
		}       
		default:
		   break;
		}
		
	     } // end of elementsInBlocks()
	     
	     sum_calo = sum_ecal + sum_hcal; // add HCAL and ECAL cal sum
	     
	  }
	  if(trk_pt < thePtMin_) selTracks_->push_back(trk); // if pt< min pt, keep it
	  else if(fCaloComp->Eval(trk_pt)<sum_calo) selTracks_->push_back(trk); // if calo sum > function(pt), keep it
	  else LogDebug("CaloCompatibleTrackSelector")<<" rejected track pt = "<<trk_pt<<endl;
       }
    }
    
    LogDebug("CaloCompatibleTrackSelector")<<" number of tracks: (1) before selection = "<<tC.size()
					   <<" (2) after selection = "<<selTracks_->size()<<endl;

    evt.put(selTracks_);

}


/*
bool CaloCompatibleTrackSelector::isCaloCompatible(float pt, float et){

   //return (fCaloCompatibility(pt)<et);
   return (fCaloComp->Eval(x)<et);
}
*/

/*
float CaloCompatibleTrackSelector::fCaloCompatibility(float x){
   return fCaloComp->Eval(x);
}
*/
/*
float CaloCompatibleTrackSelector::fCaloCompatibility(float x){
   
   float a, b, c;
   a = 1.0, b = 1.0, c = 1.0;

   float y = 0;

   if(x<14)
      y = 0;
   else 
      y = 1.2*pow(x-10,8.7/9)*(2+1./(exp(-1.*(x-14))-1));

   return y;
}
*/
