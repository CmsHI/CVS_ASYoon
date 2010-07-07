import FWCore.ParameterSet.Config as cms

# clone event selection analyzer to run after successive steps

# clone vertex analyzer to run with various inputs

# TrackSpectraAnalyzer -> HiTrackSpectraAnalyzer
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *
#hitrackAna.src = cms.untracked.InputTag("selectTracks")


# tracking efficiency analyzer
from edwenger.TrkEffAnalyzer.trkEffAnalyzer_cff import *
trkEffAnalyzer.tracks = cms.untracked.InputTag("hiSelectedTracks")
trkEffAnalyzer.jets = cms.untracked.InputTag('patJets')
trkEffAnalyzer.vertices = cms.untracked.InputTag("hiSelectedVertex")
trkEffAnalyzer.fillNtuples = cms.bool(False)
trkEffAnalyzer.constPtBins = cms.bool(False)

trackingParticleRecoTrackAsssociation.label_tr = cms.InputTag("hiSelectedTracks")

# sequences
