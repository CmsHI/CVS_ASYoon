


from PbPbTrackingTools.HiCaloCompatibleTrackSelector.selectHiCaloCompatibleTrack_cfi import *

selectHiCaloCompOnly = selectHiCaloCompatibleTrack.clone(src = cms.InputTag("hiSelectedTracks"))
