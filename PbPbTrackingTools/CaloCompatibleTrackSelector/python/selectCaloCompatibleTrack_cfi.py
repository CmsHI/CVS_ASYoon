import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
                                   src = cms.InputTag("generalTracks"),
                                   keepAllTracks = cms.bool(False), ## if set to true tracks failing this filter are kept in the output
                                   beamspot = cms.InputTag("offlineBeamSpot"),
                                   selectFake = cms.untracked.bool(False),
                                   qualityString = cms.string('highPurity'),
                                   
                                   #untracked bool copyTrajectories = true // when doing retracking before
                                   copyTrajectories = cms.untracked.bool(False),
                                   copyExtras = cms.untracked.bool(True), ## set to false on AOD
                                   qualityBit = cms.string('highPurity'), ## set to '' or comment out if you don't want to set the bit
                                   )
