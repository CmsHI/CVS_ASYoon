import FWCore.ParameterSet.Config as cms

# clone event selection analyzer to run after successive steps


# clone vertex analyzer to run with various inputs
from edwenger.HiVertexAnalyzer.hivertexanalyzer_cfi import *
preAdpVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiPixelAdaptiveVertex"))
preMedVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiPixelMedianVertex"))
preSelVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiSelectedVertex"))

postAdpVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiPixelAdaptiveVertex"))
postMedVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiPixelMedianVertex"))
postSelVtxAna = hivertexanalyzer.clone(vtxlabel=cms.untracked.InputTag("hiSelectedVertex"))

# clone hitrack spectra ana to run with pixel and global
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *

hitrackAnaMult = hitrackAna.clone(pixelMultMode=cms.untracked.bool(True)) # use pix mult as occupancy handle
hicompTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("caloCompatibleTracks"))

hipxltrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiLowPtPixelTracks"),
                                 src_evtCorr=cms.untracked.InputTag("hiLowPtPixelTracks")
                                 )

hipxltrackAnaMult = hipxltrackAna.clone(pixelMultMode=cms.untracked.bool(True))
hirefitTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hirefitTracks")) #refitted track!


## tracking efficiency analyzer --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hitrkEffAnalyzer_cff.py

## particle flow rereco and ana --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hipfCandAnalyzer_cff.py


# Sequences
preEvtSelVtxAna = cms.Sequence(preAdpVtxAna*
                               preMedVtxAna*
                               preSelVtxAna)

postEvtSelVtxAna = cms.Sequence(postAdpVtxAna*
                                postMedVtxAna*
                                postSelVtxAna)
                              



