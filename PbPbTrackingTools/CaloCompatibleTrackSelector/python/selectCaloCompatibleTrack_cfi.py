import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
              src = cms.InputTag("generalTracks"),
              srcPFCand = cms.InputTag("particleFlow",""),
              ptMin = cms.untracked.double(10),
              hasSimInfo =  cms.bool(False),
              funcCaloComp = cms.string("(x>10) * (1.2*pow(TMath::Abs(x-10),6.6/9)) * (2+1.4/(exp(-10*(x-9))-1))"), # a function that defines track-calo (in)compatible region
              copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
              copyExtras = cms.untracked.bool(True) ## set to false on AOD
)
