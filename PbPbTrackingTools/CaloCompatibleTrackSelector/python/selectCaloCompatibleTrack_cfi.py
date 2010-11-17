import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
                                   src = cms.InputTag("generalTracks"),
                                   srcPFCand = cms.InputTag("particleFlow",""),
                                   ptMin = cms.untracked.double(10),
                                   hasSimInfo =  cms.bool(False), 
                                   copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
                                   copyExtras = cms.untracked.bool(True) ## set to false on AOD
                                   )
