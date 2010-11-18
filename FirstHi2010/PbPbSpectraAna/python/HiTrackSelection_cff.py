import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

hiCaloCompTracks  = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiSelectedTracks"),
                                                    srcPFCand = cms.InputTag("particleFlow","","ANASKIM"),
                                                    vertices = cms.InputTag("hiSelectedVertex"),
                                                    ptMin = cms.untracked.double(10),
                                                    selectFake = cms.untracked.bool(False))
