import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiTrackSelection_cff import *
from edwenger.HiTrkEffAnalyzer.hipfCandAnalyzer_cff import *
from edwenger.HiTrkEffAnalyzer.TrackSelections_cff import *


# PF re-reco for events with pT>pT'
#hipfReReco = cms.Sequence(rereco_seq)


# Extra track selections/refit/etc..
hiextraTrack = cms.Sequence(hiPostGlobalPrimTracksSelection
                            *hiGoodTracksSelection
                            *hiGoodLooseTracksSelection
                            *hiGoodTightTracksSelection
                            *hiHighPtTrackSelection
                            *hiPreDTGoodTightTracksSelection # for systematics only
                            *hiPreDZGoodTightTracksSelection # for systematics only
                            )

# Below is the tracks with calo-compatibility cut based on calo-track matching in PF.
#hicaloTrack = cms.Sequence(hiGeneralCaloTracks)
