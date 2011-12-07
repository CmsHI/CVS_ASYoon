import FWCore.ParameterSet.Config as cms

from RecoLocalTracker.Configuration.RecoLocalTracker_cff import *
from RecoHI.Configuration.Reconstruction_HI_cff import *
from MNguyen.iterTracking.TrackSelections_cff import *
hiGoodTightTracks.keepAllTracks = False # put here so that it's propagated in secondStep and thirdStep
from MNguyen.iterTracking.secondStep_triplet_cff import *
from MNguyen.iterTracking.thirdStep_pairs_cff import *
from MNguyen.iterTracking.MergeTrackCollectionsHI_cff import *


## Heavy Ion Tracking 
rechits = cms.Sequence(siPixelRecHits * siStripMatchedRecHits)
hiTrackReReco = cms.Sequence(rechits * heavyIonTracking)
heavyIonTracking.remove(hiTracksWithLooseQuality) # not needed
heavyIonTracking.remove(hiTracksWithTightQuality) # not needed

## Customizations 
hiGoodTightTracks.src = cms.InputTag("hiGlobalPrimTracks") # 
#hiGoodTightTracks.keepAllTracks = False # see above
#hiNewClusters.Strip.maxSize = cms.uint32(2)

hiGeneralHybridTracks = hiGeneralTracks.clone(
    TrackProducer1 = 'hiGlobalPrimTracks', 
    TrackProducer2 = 'iterTracks',
    )

## Merging of hiGlobalPrim (1st) + hiGeneral (2nd+3rd)
hybridTrackCollectionMerging = cms.Sequence(
    hiGeneralHybridTracks # hiGlobal
    )

iterTracking39X_seq = cms.Sequence(
    hiTrackReReco *
    hiGoodTightTracks *
    secondStep *
    thirdStep *
    #trackCollectionMerging *
    hybridTrackCollectionMerging # hiGeneral + hiGlobal
    )

