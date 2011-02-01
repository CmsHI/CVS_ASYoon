import FWCore.ParameterSet.Config as cms

from FirstHi2010.PbPbSpectraAna.HiLowPtPxlRereco_cff import *
from FirstHi2010.PbPbSpectraAna.HiCentralityInfo_cff import *
from FirstHi2010.PbPbSpectraAna.HiTrackRefit_cff import *
from FirstHi2010.PbPbSpectraAna.HiTrackSelection_cff import *
from FirstHi2010.PbPbSpectraAna.HiPFRereco_cff import *
from edwenger.HiTrkEffAnalyzer.hipfCandAnalyzer_cff import *
from edwenger.HiTrkEffAnalyzer.TrackSelections_cff import *
from Appeltel.PixelTracksRun2010.HiLowPtPixelTracksFromReco_cff import *
from Appeltel.PixelTracksRun2010.HiMultipleMergedTracks_cff import *


# Extra reco 
hiextraReco = cms.Sequence(conformalPixelTrackReco)

# PF re-reco for events with pT>pT'
hipfReReco = cms.Sequence(rereco_seq*
                          hipfCandAnalyzer)


hiTightGlobalPrimTraks = cms.EDFilter("TrackSelector",
            src = cms.InputTag("hiGlobalPrimTracks"),
            cut = cms.string('(ptError/pt)<0.06 && numberOfValidHits>12')
)

from RecoHI.HiTracking.HISelectedTracks_cfi import hiSelectedTracks

hiHighPtTracks = hiSelectedTracks.clone(
    src="hiTightGlobalPrimTraks",
    copyTrajectories = False,
    d0_par2 = [9999, 1], # i.e. no compatibility cut
    dz_par2 = [9999, 1]
)


# Extra track selections/refit/etc..
hiextraTrack = cms.Sequence(hiTightGlobalPrimTraks
                            *hiHighPtTracks
                            *hiGoodTracksSelection
                            *hiCaloCompTracks)
                            #*hipfCandAnalyzer_test)
