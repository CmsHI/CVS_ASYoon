import FWCore.ParameterSet.Config as cms

analysisSkimContent = cms.PSet(
        outputCommands = cms.untracked.vstring(
        'drop *',
        # event
        'keep *_offlineBeamSpot_*_*',
        'keep *_TriggerResults_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*RECO',
        
        # centrality
        'keep *_hiCentrality_*_*',
        
        # jet
        #'keep *_towerMaker_*_*',
        'keep *_*patJets_*_*',
        'keep *_iterativeConePu5CaloJets_*_*',

        # vertex
        'keep *_hiSelectedVertex_*_*',
        
        # full tracks
        'keep recoTracks_hiGeneralHybridTracks_*_*',
        'keep recoTracks_hiOptimalTightTracks_*_*',
        )
)
