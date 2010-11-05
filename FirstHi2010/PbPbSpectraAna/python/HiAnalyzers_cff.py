import FWCore.ParameterSet.Config as cms

# clone event selection analyzer to run after successive steps

# clone vertex analyzer to run with various inputs

# TrackSpectraAnalyzer -> HiTrackSpectraAnalyzer
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *

hitrackAnaMult = hitrackAna.clone(pixelMultMode=cms.untracked.bool(True)) # use pix mult as occupancy handle

hipxltrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiLowPtPixelTracks"),
                                 src_evtCorr=cms.untracked.InputTag("hiLowPtPixelTracks")
                                 )

hipxltrackAnaMult = hipxltrackAna.clone(pixelMultMode=cms.untracked.bool(True))
hirefitTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hirefitTracks")) #refitted track!

# tracking efficiency analyzer --------------------------
