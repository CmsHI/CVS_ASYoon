import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
                                   src = cms.InputTag("generalTracks"),
                                   srcPFCand = cms.InputTag("particleFlow",""),
                                   ptMin = cms.untracked.double(10),
                                   hasSimInfo =  cms.bool(False), 
                                   funcCaloComp = cms.string("(x>14)*1.2*pow(x-10,8.7/9)*(2+1./(exp(-1.*(x-14))-1))"), # this is a function that defines track-calo (in)compatible region
                                   copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
                                   copyExtras = cms.untracked.bool(True) ## set to false on AOD
                                   )
