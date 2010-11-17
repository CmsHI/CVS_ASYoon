#ifndef PbPbTrackingTools_CaloCompatibleTrackSelector_h
#define PbPbTrackingTools_CaloCompatibleTrackSelector_h

/** \class CaloCompatibleTrackSelector
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


namespace reco { namespace modules {

    class CaloCompatibleTrackSelector : public edm::EDProducer {
        private:
        public:
            /// constructor 
            explicit CaloCompatibleTrackSelector( const edm::ParameterSet & cfg ) ;
            /// destructor
            virtual ~CaloCompatibleTrackSelector() ;

        private:
            typedef math::XYZPoint Point;
            /// process one event
            void produce( edm::Event& evt, const edm::EventSetup& es ) ;

            /// return class, or -1 if rejected
	    bool selectFakeOrReal(const reco::Track &trk);
	    bool isCaloCompatible(float pt, float et);

	    // a functional form of fake rejection in pt-calo space
	    float fCaloCompatibility(float pt);
	    
	    ///
            //void selectVertices ( const reco::VertexCollection &vtxs, std::vector<Point> &points);

            /// source collection label
            edm::InputTag src_;
	    edm::InputTag srcPFCand_;

	    //
	    double thePtMin_;

            /// copy only the tracks, not extras and rechits (for AOD)
            bool copyExtras_;
            /// copy also trajectories and trajectory->track associations
            bool copyTrajectories_;

	    /// when running on MC with "trackingParticles"
            bool hasSimInfo_;

            /// save all the tracks
            //bool keepAllTracks_;

            /// storage
            std::auto_ptr<reco::TrackCollection> selTracks_;
	    /*
            std::auto_ptr<reco::TrackExtraCollection> selTrackExtras_;
            std::auto_ptr< TrackingRecHitCollection>  selHits_;
            std::auto_ptr< std::vector<Trajectory> > selTrajs_;
            std::auto_ptr< std::vector<const Trajectory *> > selTrajPtrs_;
            std::auto_ptr< TrajTrackAssociationCollection >  selTTAss_;
            reco::TrackRefProd rTracks_;
            reco::TrackExtraRefProd rTrackExtras_;
            TrackingRecHitRefProd rHits_;
            edm::RefProd< std::vector<Trajectory> > rTrajectories_;
            std::vector<reco::TrackRef> trackRefs_;
	    */

	    float cand_type;
	    float cand_pt;
	    float cand_eta;

	    float trk_pt;

	    float sum_ecal;
	    float sum_hcal;
	    float sum_calo;



    };

} }

#endif
