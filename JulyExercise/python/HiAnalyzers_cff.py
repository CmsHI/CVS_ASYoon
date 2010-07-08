import FWCore.ParameterSet.Config as cms

# clone event selection analyzer to run after successive steps

# clone vertex analyzer to run with various inputs

# TrackSpectraAnalyzer -> HiTrackSpectraAnalyzer
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *

hitrackAnaMult = hitrackAna.clone(pixelMultMode=cms.untracked.bool(True)) # use pix mult as occupancy handle



# tracking efficiency analyzer
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *
trackingParticleRecoTrackAsssociation.label_tr = cms.InputTag("hiSelectedTracks")

hitrkEffAnalyzerMult = hitrkEffAnalyzer.clone(pixelMultMode= cms.untracked.bool(True))

# sequences
