import FWCore.ParameterSet.Config as cms

# clone event selection analyzer to run after successive steps

# clone vertex analyzer to run with various inputs

# track and jet spectra analyzer to run on HI samples
from edwenger.TrackSpectraAnalyzer.trackspectraanalyzer_cfi import *
trackAna.src = cms.untracked.InputTag("hiSelectedTracks")
trackAna.jsrc = cms.untracked.InputTag("patJets")
trackAna.vsrc = cms.untracked.InputTag("hiSelectedVertex")
trackAna.gjsrc = cms.untracked.InputTag("ak5HiGenJets")
trackAna.setQualityBit = cms.untracked.bool(False)

# tracking efficiency analyzer
from edwenger.TrkEffAnalyzer.trkEffAnalyzer_cff import *
trkEffAnalyzer.tracks = cms.untracked.InputTag("hiSelectedTracks")
trkEffAnalyzer.vertices = cms.untracked.InputTag("hiSelectedVertex")
trkEffAnalyzer.fillNtuples = cms.bool(False)
trkEffAnalyzer.constPtBins = cms.bool(False)

trackingParticleRecoTrackAsssociation.label_tr = cms.InputTag("hiSelectedTracks")

# sequences
