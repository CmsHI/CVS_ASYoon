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

# tracking efficiency analyzer
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *
trackingParticleRecoTrackAsssociation.label_tr = cms.InputTag("hiSelectedTracks")
hitrkEffAnalyzer.doAssociation = cms.untracked.bool(False)
hitrkEffAnalyzerMult = hitrkEffAnalyzer.clone(pixelMultMode=cms.untracked.bool(True))


pxltrackingParticleRecoTrackAsssociation = trackingParticleRecoTrackAsssociation.clone(label_tr = cms.InputTag("hiLowPtPixelTracks"))
hipxltrkEffAnalyzer = hitrkEffAnalyzer.clone(tracks = cms.untracked.InputTag('hiLowPtPixelTracks'),
                                             associatormap = cms.untracked.InputTag('pxltrackingParticleRecoTrackAsssociation'),
                                             fillNtuples = cms.bool(True),
                                             doAssociation = cms.untracked.bool(False))

hipxltrkEffAnalyzerMult = hipxltrkEffAnalyzer.clone(pixelMultMode=cms.untracked.bool(True))


# sequence
hitrkEffAna = cms.Sequence(trackingParticleRecoTrackAsssociation*
                           (hitrkEffAnalyzer + hitrkEffAnalyzerMult))

hipxltrkEffAna = cms.Sequence(pxltrackingParticleRecoTrackAsssociation*
                              (hipxltrkEffAnalyzer + hipxltrkEffAnalyzerMult))
