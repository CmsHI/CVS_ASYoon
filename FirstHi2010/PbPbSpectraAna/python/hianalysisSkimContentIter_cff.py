import FWCore.ParameterSet.Config as cms

analysisSkimContent = cms.PSet(
        outputCommands = cms.untracked.vstring(
        'drop *',
        # event
        'keep *_offlineBeamSpot_*_*',
        'keep *_TriggerResults_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*RECO',
        
        # mc gen info
        'keep *_*GenJet*_*_*',
        'keep *_hiGenParticles_*_*',
        'keep GenEventInfoProduct_*_*_*',
        
        # centrality
        'keep *_hiCentrality_*_*',
        
        # pixel and strip
        #'keep *_siPixelClusters_*_*',
        #'keep *_siStripClusters_*_*',
        #'keep *_simSiPixelDigis_*_*',
        #'keep *_simSiStripDigis_*_*',
        
        # ecal/hcal rec hit (needed for spike cleaning)
        #'keep *_*_EcalRecHitsEB_*',
        #'keep *_hbhereco_*_*',
        
        # jet
        #'keep *_towerMaker_*_*',
        'keep *_patJets_*_*',
        'keep *_iterativeConePu5CaloJets_*_*',

        # PF candidate
        'keep recoPFClusters_*CAL_*_*',
        'keep recoPFBlocks_*_*_*',
        'keep recoPFCandidates_*__*',

        # vertex
        'keep *_hiSelectedVertex_*_*',
        'keep *_hiPixelAdaptiveVertex_*_*',
        'keep *_hiPixelMedianVertex_*_*',
        
        # full tracks
        'keep recoTracks_hiGlobalPrimTracks_*_*',
        'keep recoTracks_hiGeneralGlobalPrimTracks_*_*',
        'keep recoTracks_hiGeneralTracks_*_*',
        'keep recoTracks_hiSelectedTracks_*_*',
        #'keep recoTrackExtras_hiGlobalPrimTracks_*_*',
        #'keep recoTrackExtras_hiGeneralGlobalPrimTracks_*_*',
        'keep recoTrackExtras_hiGeneralTracks_*_*',
        'keep recoTrackExtras_hiSelectedTracks_*_*',
        
        # sim track matching
        'keep *_trackingParticleRecoTrackAsssociation_*_*',
        'keep *_mergedtruth_MergedTrackTruth_*'
        )
)
