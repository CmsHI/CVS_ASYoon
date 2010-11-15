import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
                                   src = cms.InputTag("generalTracks"),
                                   srcPFCand = cms.InputTag("particleFlow",""),
                                   keepAllTracks = cms.bool(False), ## if set to true tracks failing this filter are kept in the output
                                   hasSimInfo =  cms.bool(False), 
                                   copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
                                   copyExtras = cms.untracked.bool(True) ## set to false on AOD
                                   )
