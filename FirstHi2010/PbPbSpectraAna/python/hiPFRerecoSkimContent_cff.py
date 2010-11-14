import FWCore.ParameterSet.Config as cms

PFRerecoSkimContent = cms.PSet(
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
              'keep recoTracks_hiGlobalPrimTracks_*_*',
              'keep recoTracks_hiSelectedTracks_*_*',
              'keep recoTracks_hirefitTracks_*_*',
              'keep recoTracks_caloCompatibleTracks*_*_*',
              'keep recoTrackExtras_hiGlobalPrimTracks_*_*',
              'keep recoTrackExtras_hiSelectedTracks_*_*',
              'keep recoTracks_hirefitTracks_*_*',
              'keep recoTracks_caloCompatibleTracks*_*_*',
                                           

               # PF candidate
               'keep recoPFClusters_*CAL_*_*',
               'keep recoPFBlocks_*_*_*',
               'keep recoPFCandidates_*__*',
                                                                                      
               # sim track matching
               'keep *_trackingParticleRecoTrackAsssociation_*_*',
               'keep TrackingParticles_mergedtruth_MergedTrackTruth_*'
     )
)
