#ifndef PbPbTrackingTools_HiCaloCompatibleTrackSelector_h
#define PbPbTrackingTools_HiCaloCompatibleTrackSelector_h

/** \class HiCaloCompatibleTrackSelector
 *
 *  It selects tracks based on a cut imposed on track-calo compatibility, 
 *  and saves tracks in event. 
 * 
 *
 */

#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"

// ROOT includes
#include "TF1.h"

namespace reco { namespace modules {
  
  class HiCaloCompatibleTrackSelector : public edm::EDProducer {
  private:
  public:
    /// constructor 
    explicit HiCaloCompatibleTrackSelector( const edm::ParameterSet & cfg ) ;
    /// destructor
    virtual ~HiCaloCompatibleTrackSelector() ;
    
  private:
    typedef math::XYZPoint Point;
    /// process one event
    void produce( edm::Event& evt, const edm::EventSetup& es ) ;
    
    /// return class, or -1 if rejected
    //bool isCaloCompatible(float pt, float et);
    
    // a functional form of fake rejection in pt-calo space
    //float fCaloCompatibility(float pt);
    
    ///
    //void selectVertices ( const reco::VertexCollection &vtxs, std::vector<Point> &points);
    
    /// source collection label
    edm::InputTag src_;
    edm::InputTag srcTower_;

    //
    bool applyCaloComp_;
    bool applyPtDepCut_;
    double trkPtMin_;
    double trkPtMax_;
    double trkEtaMax_;
    double towerPtMin_;
    double matchDR_;
    double caloCut_;
    
    /// copy only the tracks, not extras and rechits (for AOD)
    bool copyExtras_;
    /// copy also trajectories and trajectory->track associations
    bool copyTrajectories_;
    
    bool useQaulityStr_;
    std::string qualityString_;
    
    /// when running on MC with "trackingParticles"
    bool hasSimInfo_;
    
    // string of functional form
    std::string funcCaloComp_;
    
    /// reverse selection criteria
    bool reverseSel_;
    
    /// storage
    std::auto_ptr<reco::TrackCollection> selTracks_;
    
    // TF1         
    TF1 *fCaloComp;
    
  };
  
} }

#endif
