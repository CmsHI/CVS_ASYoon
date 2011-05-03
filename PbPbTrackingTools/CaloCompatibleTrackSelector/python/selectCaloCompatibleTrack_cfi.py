import FWCore.ParameterSet.Config as cms

selectCaloCompatibleTrack  = cms.EDProducer("CaloCompatibleTrackSelector",
              src = cms.InputTag("generalTracks"),
              srcPFCand = cms.InputTag("particleFlow",""),
              applyCaloComp = cms.untracked.bool(True),  # if false, every track is kept (better not to run the PF to begin with)
              ptMin = cms.untracked.double(10),
              hasSimInfo =  cms.bool(False),
              #funcCaloComp = cms.string("(x>14) * (1.2*pow(TMath::Abs(x-10),8.5/9)) * (2+1./(exp(-1*(x-13))-1))"), # tighter
              funcCaloComp = cms.string("(x>10) * (1.2*pow(TMath::Abs(x-10),6.0/9)) * (2+1.4/(exp(-10*(x-9))-1))"), # looser
              copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
              copyExtras = cms.untracked.bool(True), ## set to false on AOD
              useQaulityStr=cms.untracked.bool(True),
              qualityString=cms.untracked.string("highPurity")
)
