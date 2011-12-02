import FWCore.ParameterSet.Config as cms

from RecoLocalTracker.Configuration.RecoLocalTracker_cff import *
from RecoHI.Configuration.Reconstruction_HI_cff import *
from RecoHI.HiTracking.hiIterTracking_cff import *

## Heavy Ion Tracking 
rechits = cms.Sequence(siPixelRecHits * siStripMatchedRecHits)
hiTrackReReco = cms.Sequence(rechits * heavyIonTracking)

## Iterative Tracking (customize to skip mixed step) 
hiThirdStepFilter.recTracks = cms.InputTag("hiSecondPixelTripletSelectedTracks")
hiPixelPairClusters.oldClusterRemovalInfo = cms.InputTag("hiSecondPixelTripletClusters")
trackCollectionMerging.remove(thirdAndFourthSteps) # skip merging thirdAndFourthSteps
iterTracks.TrackProducer2 = cms.string('hiPixelPairSelectedTracks')

## Full Re-tracking with Iterative tracking 
iterTracking_seq = cms.Sequence(
    hiTrackReReco 
    *hiSecondPixelTripletStep
    #*hiMixedTripletStep  # skipped 
    *hiPixelPairStep
    *trackCollectionMerging
    )
