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
hipfReReco = cms.Sequence(rereco_seq)


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
# It needs to be ran for every events while PF re-co is ran for events with pT>pT' only
hicaloTrack = cms.Sequence(hiGoodTightCaloTracks* 
                           hiGoodLooseCaloTracks* 
                           hiHighPtCaloTracks*    
                           hiPreDTGoodTightCaloTracks*
                           hiPreDZGoodTightCaloTracks*
                           hipfCandAnalyzer*
                           hipfCandAnalyzer_higtight*
                           hipfCandAnalyzer_higloose)
