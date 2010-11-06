#include "PbPbTrackingTools/CaloCompatibleTrackSelector/interface/CaloCompatibleTrackSelector.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorByHits.h"
#include <Math/DistFunc.h>
#include "TMath.h"

using reco::modules::CaloCompatibleTrackSelector;

CaloCompatibleTrackSelector::CaloCompatibleTrackSelector( const edm::ParameterSet & cfg ) :
    src_( cfg.getParameter<edm::InputTag>( "src" ) ),
    beamspot_( cfg.getParameter<edm::InputTag>( "beamspot" ) ),
    vertices_( cfg.getParameter<edm::InputTag>( "vertices" ) ),
    qualityString_(cfg.getParameter<std::string>("qualityString")),
    setQualityBit_( false ),
    qualityToSet_(TrackBase::qualityByName(cfg.getParameter<std::string>("qualityString"))),

    copyExtras_(cfg.getUntrackedParameter<bool>("copyExtras", false)),
    copyTrajectories_(cfg.getUntrackedParameter<bool>("copyTrajectories", false)),
    keepAllTracks_( cfg.exists("keepAllTracks") ?
		    cfg.getParameter<bool>("keepAllTracks") :
		    false )  // as this is what you expect from a well behaved selector
{
   /*
    if (cfg.exists("qualityBit")) {
        std::string qualityStr = cfg.getParameter<std::string>("qualityBit");
        if (qualityStr != "") {
            setQualityBit_ = true;
            //qualityToSet_  = TrackBase::qualityByName(cfg.getParameter<std::string>("qualityBit"));
        }
    }
   */
   
   if (keepAllTracks_ && !setQualityBit_) throw cms::Exception("Configuration") << 
      "If you set 'keepAllTracks' to true, you must specify which qualityBit to set.\n";
   if (setQualityBit_ && (qualityToSet_ == TrackBase::undefQuality)) throw cms::Exception("Configuration") <<
      "You can't set the quality bit " << cfg.getParameter<std::string>("qualityBit") << " as it is 'undefQuality' or unknown.\n";
   
   
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
   
}

CaloCompatibleTrackSelector::~CaloCompatibleTrackSelector() {
}

void CaloCompatibleTrackSelector::produce( edm::Event& evt, const edm::EventSetup& es ) 
{
    using namespace std; 
    using namespace edm;
    using namespace reco;

    const string qualityString = "highPurity";

    Handle<TrackCollection> hSrcTrack;
    Handle< vector<Trajectory> > hTraj;
    Handle< vector<Trajectory> > hTrajP;
    Handle< TrajTrackAssociationCollection > hTTAss;

    // looking for the beam spot
    edm::Handle<reco::BeamSpot> hBsp;
    evt.getByLabel(beamspot_, hBsp);
    reco::BeamSpot vertexBeamSpot;
    vertexBeamSpot = *hBsp;
    
    // Select good primary vertices for use in subsequent track selection
    edm::Handle<reco::VertexCollection> hVtx;
    evt.getByLabel(vertices_, hVtx);
    std::vector<Point> points;
    selectVertices(*hVtx, points);
    
    // get association map
    //Handle<reco::RecoToSimCollection > rectosimCollection;
    //evt.getByLabel("trackingParticleRecoTrackAsssociation", rectosimCollection);
    //const RecoToSimCollection p = *(rectosimCollection.product());

    // get track collection
    Handle<edm::View<reco::Track> > trackCollectionH;
    evt.getByLabel(src_,trackCollectionH);
    const edm::View<reco::Track>  tC = *(trackCollectionH.product());

    // get track collection
    evt.getByLabel( src_, hSrcTrack );

    selTracks_ = auto_ptr<TrackCollection>(new TrackCollection());
    //rTracks_ = evt.getRefBeforePut<TrackCollection>();      

    for(edm::View<reco::Track>::size_type i=0; i<tC.size(); ++i) {
       edm::RefToBase<reco::Track> track(trackCollectionH, i);
       const reco::Track & trk = (*hSrcTrack)[i];

       //if(!trk.quality(reco::TrackBase::qualityByName(qualityString_))) continue;
       selTracks_->push_back(trk);
    }
    evt.put(selTracks_);

}

bool CaloCompatibleTrackSelector::selectFakeOrReal(const reco::Track &trk) {
   using namespace std;
   //cout<<"Hey"<<endl;
   return true;
}

void CaloCompatibleTrackSelector::selectVertices(const reco::VertexCollection &vtxs, std::vector<Point> &points) {
   // Select good primary vertices
   using namespace reco;
   int32_t toTake = vtxNumber_; 
   for (VertexCollection::const_iterator it = vtxs.begin(), ed = vtxs.end(); it != ed; ++it) {
      if ((it->tracksSize() >= vtxTracks_)  && 
	  ( (it->chi2() == 0.0) || (TMath::Prob(it->chi2(), static_cast<int32_t>(it->ndof()) ) >= vtxChi2Prob_) ) ) {
	 points.push_back(it->position()); 
	 toTake--; if (toTake == 0) break;
      }
   }
}


