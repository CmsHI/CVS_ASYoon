import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiTrackSelection_cff import *
from RecoHI.HiTracking.HICaloCompatibleTracks_cfi import *


## hiGoodTightTracks
hiExtraTrack = cms.Sequence(hiGoodTightTracks)   # highPurity from hiSelectedTracks


## hiOptimalTightTracks
hiPreCaloCompTracks = hiCaloCompatibleTracks.clone(srcTracks = cms.InputTag("hiSelectedTracks"),
                                                   usePFCandMatching = cms.untracked.bool(True))

hiPreOptimalTightTracks = hiTracksWithLooseQuality.clone(src = cms.InputTag("hiGeneralTracks"),
                          keepAllTracks = cms.bool(False),
                          chi2n_no1Dmod_par = cms.double(0.15))

hiOptimalTightTracks = cms.EDFilter("TrackSelector",
                       src = cms.InputTag("hiPreOptimalTightTracks"),
                       cut = cms.string('quality("highPurity") || quality("tight")'))


hiOptTrack = cms.Sequence(hiPreCaloCompTracks*
                          hiPreOptimalTightTracks*
                          hiOptimalTightTracks) 
