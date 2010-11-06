import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

caloCompatibleTracks  = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiSelectedTracks"),
                                                        vertices = cms.InputTag("hiSelectedVertex"),
                                                        selectFake = cms.untracked.bool(False))
