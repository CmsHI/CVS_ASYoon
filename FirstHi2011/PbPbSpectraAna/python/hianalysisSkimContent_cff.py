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
    
    # ecal/hcal rec hit (needed for spike cleaning)
    #'keep *_*_EcalRecHitsEB_*',
    #'keep *_hbhereco_*_*',
    
    # jet
    'keep *_towerMaker_*_*', # used for jet re-reco and calo-matching 
    'keep *_icPu5patJets_*_*',
    'keep *_iterativeConePu5CaloJets_*_*',
    
    # vertex
    'keep *_hiSelectedVertex_*_*',
    #'keep *_hiPixelAdaptiveVertex_*_*',
    #'keep *_hiPixelMedianVertex_*_*',
    
    # full tracks
    'keep recoTracks_hiGeneralHybridTracks_*_*', # 1st = hiGlobalPrimTracks (derivable by requring algo)
    'keep recoTracks_hiOptimalTightTracks_*_*',
    #'keep recoTrackExtras_hiGeneralHybridTracks_*_*', 
    
    # sim track matching
    #'keep *_trackingParticleRecoTrackAsssociation_*_*',
    #'keep *_mergedtruth_MergedTrackTruth_*'
    )
)
