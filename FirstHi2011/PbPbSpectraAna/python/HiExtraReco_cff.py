import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiTrackSelection_cff import *
from RecoHI.HiTracking.HICaloCompatibleTracks_cfi import *


## hiGoodTightTracks
hiExtraTrack = cms.Sequence(hiGoodTightTracks)   # highPurity from hiSelectedTracks


## hiOptimalTightTracks
hiPreCaloCompTracks = hiCaloCompatibleTracks.clone(srcTracks = cms.InputTag("hiGeneralTracks"),
                                                   usePFCandMatching = cms.untracked.bool(False), # use CaloTower
                                                   trkPtMin = cms.untracked.double(0.0))

hiPreOptimalTightTracks = hiTracksWithLooseQuality.clone(src = cms.InputTag("hiPreCaloCompTracks"),
                          keepAllTracks = cms.bool(False),
                          chi2n_no1Dmod_par = cms.double(0.15))

hiOptimalTightTracks = cms.EDFilter("TrackSelector",
                       src = cms.InputTag("hiPreOptimalTightTracks"),
                       cut = cms.string('quality("tight") || quality("highPurity")'))

hiOptTrack = cms.Sequence(hiPreCaloCompTracks*
                          hiPreOptimalTightTracks*
                          hiOptimalTightTracks) 
