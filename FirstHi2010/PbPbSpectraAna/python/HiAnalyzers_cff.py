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

# clone cent bin analyzer
from FirstHi2010.CentralityDistAna.centralitydistana_cfi import *
preCentDist = centbindist.clone()
postCentDist = centbindist.clone()

# clone hitrack spectra ana to run with pixel and global
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *
hitrackAna.doJet = cms.untracked.bool(True)
hitrackAna.triggerNeeded = cms.untracked.bool(True)
hitrackAna.pixelMultMode = cms.untracked.bool(True)
hitrackAna.neededTrigSpectra = cms.untracked.vint32(0,1,1,0,0) #Jet35U and 50U

hicaloTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiCaloCompTracks"),
                                  src_evtCorr=cms.untracked.InputTag("hiCaloCompTracks"),
                                  ) 

hipxltrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiLowPtPixelTracks"),
                                 src_evtCorr=cms.untracked.InputTag("hiLowPtPixelTracks"),
                                 )

hirefitTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hirefitTracks"),
                                   doJet = cms.untracked.bool(True),
                                   pixelMultMode = cms.untracked.bool(True)
                                   ) #refitted track!


## tracking efficiency analyzer --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hitrkEffAnalyzer_cff.py

## particle flow rereco and ana --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hipfCandAnalyzer_cff.py


# Sequences
preEvtSelVtxAna = cms.Sequence(preAdpVtxAna*
                               preMedVtxAna*
                               preSelVtxAna*
                               preCentDist)
                               
postEvtSelVtxAna = cms.Sequence(postAdpVtxAna*
                                postMedVtxAna*
                                postSelVtxAna*
                                postCentDist)
                              



