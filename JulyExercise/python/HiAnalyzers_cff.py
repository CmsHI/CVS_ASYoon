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
from edwenger.Skims.HiTPCuts_cff import *
from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

# full tracking 
fulltrackingParticleRecoTrackAsssociation = trackingParticleRecoTrackAsssociation.clone(label_tr=cms.InputTag("hiSelectedTracks"),
                                                                                        label_tp_effic  = cms.InputTag("cutsFullTracks"),
                                                                                        label_tp_fake = cms.InputTag("cutsFullTracks"))

hitrkEffAnalyzer.label_tp_effic = cms.untracked.InputTag("cutsFullTracks")
hitrkEffAnalyzer.label_tp_fake = cms.untracked.InputTag("cutsFullTracks")
hitrkEffAnalyzer.associatormap = cms.untracked.InputTag('fulltrackingParticleRecoTrackAsssociation')
hitrkEffAnalyzer.doAssociation = cms.untracked.bool(False)
hitrkEffAnalyzerMult = hitrkEffAnalyzer.clone(pixelMultMode=cms.untracked.bool(True))

# pixel tracking
pxltrackingParticleRecoTrackAsssociation = trackingParticleRecoTrackAsssociation.clone(label_tr = cms.InputTag("hiLowPtPixelTracks"))
hipxltrkEffAnalyzer = hitrkEffAnalyzer.clone(tracks = cms.untracked.InputTag('hiLowPtPixelTracks'),
                                             label_tp_effic = cms.untracked.InputTag('mergedtruth','MergedTrackTruth'),
                                             label_tp_fake = cms.untracked.InputTag('mergedtruth','MergedTrackTruth'),
                                             associatormap = cms.untracked.InputTag('pxltrackingParticleRecoTrackAsssociation'),
                                             fillNtuples = cms.bool(True),
                                             doAssociation = cms.untracked.bool(False))

hipxltrkEffAnalyzerMult = hipxltrkEffAnalyzer.clone(pixelMultMode=cms.untracked.bool(True))


# sequence ------------------------------------------
hitrkEffAna = cms.Sequence(cutsFullTracks*
                           fulltrackingParticleRecoTrackAsssociation*
                           (hitrkEffAnalyzer + hitrkEffAnalyzerMult))

hipxltrkEffAna = cms.Sequence(pxltrackingParticleRecoTrackAsssociation*
                              (hipxltrkEffAnalyzer + hipxltrkEffAnalyzerMult))
