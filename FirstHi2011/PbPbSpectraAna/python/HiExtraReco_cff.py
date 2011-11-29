import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiTrackSelection_cff import *


# Extra track selections/refit/etc..
hiextraTrack = cms.Sequence(hiGoodTightTracks)


# Below is the tracks with calo-compatibility cut based on calo-track matching in PF.
#hicaloTrack = cms.Sequence(hiGeneralCaloTracks)
