import FWCore.ParameterSet.Config as cms

from FirstHi2010.PbPbSpectraAna.HiLowPtPxlRereco_cff import *
from FirstHi2010.PbPbSpectraAna.HiCentralityInfo_cff import *
from FirstHi2010.PbPbSpectraAna.HiTrackRefit_cff import *
from FirstHi2010.PbPbSpectraAna.HiTrackSelection_cff import *
from FirstHi2010.PbPbSpectraAna.HiPFRereco_cff import *
from edwenger.HiTrkEffAnalyzer.hipfCandAnalyzer_cff import *
from edwenger.HiTrkEffAnalyzer.TrackSelections_cff import *


# Extra reco 
hiextraReco = cms.Sequence(hiLowPtPixelTracks)

# PF re-reco for events with pT>pT'
hipfReReco = cms.Sequence(rereco_seq*
                          hipfCandAnalyzer)


# Extra track selections/refit/etc..
hiextraTrack = cms.Sequence(hiGoodTracksSelection
                            *hiCaloCompTracks
                            *hipfCandAnalyzer_test)
