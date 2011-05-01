import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

hiHighPtCaloTracks  = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiHighPtTracks"),
                                                      srcPFCand = cms.InputTag("particleFlow","","ANASKIM"),
                                                      vertices = cms.InputTag("hiSelectedVertex"),
                                                      ptMin = cms.untracked.double(10),
                                                      selectFake = cms.untracked.bool(False))

hiGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiGoodTightTracks"))
hiGoodLooseCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiGoodLooseTracks"))
hiPreDTGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiPreDTGoodTightTracks"))
hiPreDZGoodTightCaloTracks = hiHighPtCaloTracks.clone(src = cms.InputTag("hiPreDZGoodTightTracks"))
