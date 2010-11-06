


from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import *

selectCaloCompOnly = selectCaloCompatibleTrack.clone(selectFake = cms.untracked.bool(False))
