import FWCore.ParameterSet.Config as cms

selectHiCaloCompatibleTrack  = cms.EDProducer("HiCaloCompatibleTrackSelector",
              src = cms.InputTag("generalTracks"),
              srcTower = cms.InputTag(""),
              applyCaloComp = cms.untracked.bool(True),  # if false, every track is kept (better not to run the PF to begin with)
              applyPtDepCut = cms.untracked.bool(False), # apply pt denpedent (funcCaloComp) cut !
              trkPtMin = cms.untracked.double(20.0),                                              
              trkPtMax = cms.untracked.double(200.0),
              trkEtaMax = cms.untracked.double(2.4),
              towerPtMin = cms.untracked.double(5.0),
              matchConeRadius = cms.untracked.double(0.087),
              caloCut = cms.untracked.double(0.2), # (calo energy sum/track pt) > caloCut
              copyTrajectories = cms.untracked.bool(False), # true,  when doing retracking before
              copyExtras = cms.untracked.bool(True), ## set to false on AOD
              useQaulityStr=cms.untracked.bool(False),
              qualityString=cms.untracked.string("highPurity"),
              hasSimInfo =  cms.bool(False),
              funcCaloComp = cms.string("0.087/(1.0+exp(-0.28*(x-20.)))"), # root syntax, pt dependent calo-compatibility cut
              reverseSel=cms.untracked.bool(False) # reverse the selection!                                             
)
