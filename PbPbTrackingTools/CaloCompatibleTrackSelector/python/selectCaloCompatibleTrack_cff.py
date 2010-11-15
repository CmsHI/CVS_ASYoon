


from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import *

selectCaloCompOnly = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiSelectedTracks"))
