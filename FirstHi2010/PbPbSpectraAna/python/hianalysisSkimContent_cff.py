import FWCore.ParameterSet.Config as cms

analysisSkimContent = cms.PSet(
        outputCommands = cms.untracked.vstring('drop *',
                                               # event
                                               'keep *_hiSelectedVertex_*_*',
                                               'keep *_hiPixelAdaptiveVertex_*_*',
                                               'keep *_hiPixelMedianVertex_*_*',
                                               'keep *_offlineBeamSpot_*_*',
                                               'keep *_TriggerResults_*_HLT',
                                               'keep *_TriggerResults_*_REDIGI',
                                               'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*RECO',
                                               
                                               # mc gen info
                                               'keep *_*GenJet*_*_*',
                                               'keep *_hiGenParticles_*_*',
                                               'keep GenEventInfoProduct_*_*_*',
                                               
                                               # jet
                                               'keep *_towerMaker_*_*',
                                               'keep *_patJets_*_*',

                                               # low pt tracks
                                               'keep recoTracks_hiLowPtPixelTracks_*_*',
                                               
                                               # full tracks
                                               'keep recoTracks_generalTracks_*_*RECO',
                                               'keep recoTracks_refitTracks_*_*',
                                               'keep recoRecoChargedCandidates_allTracks_*_*',
                                               'keep recoTracks_caloCompatibleTracks*_*_*',
                                               
                                               # sim track matching
                                               'keep *_trackingParticleRecoTrackAsssociation_*_*',
                                               'keep TrackingParticles_mergedtruth_MergedTrackTruth_*'
                                               )
        )
