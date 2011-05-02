import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

hiHighPtCaloTracks  = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiHighPtTracks"),
                                                      srcPFCand = cms.InputTag("particleFlow","","ANASKIM"),
                                                      vertices = cms.InputTag("hiSelectedVertex"),
                                                      ptMin = cms.untracked.double(10),
                                                      selectFake = cms.untracked.bool(False),
                                                      qualityString=cms.untracked.string("tight"))


hiGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiGoodTightTracks"),
                                                 qualityString=cms.untracked.string("highPurity"))
hiGoodLooseCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiGoodLooseTracks"),
                                                 qualityString=cms.untracked.string("loose"))
hiPreDTGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiPreDTGoodTightTracks"),
                                                      useQaulityStr=cms.untracked.bool(False))
hiPreDZGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiPreDZGoodTightTracks"),
                                                      useQaulityStr=cms.untracked.bool(False))
