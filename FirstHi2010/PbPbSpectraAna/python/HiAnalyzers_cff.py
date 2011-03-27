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

# clone hi track validator
#from SimTracker.TrackAssociation.TrackAssociatorByHits_cfi import *
#from SimTracker.TrackAssociation.trackingParticleRecoTrackAsssociation_cfi import *
#TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')

# clone hi event selection analyzer
from edwenger.HiEvtSelAnalyzer.hievtselanalyzer_cfi import *
preTrgAna = hievtselanalyzer.clone()
postTrgAna = hievtselanalyzer.clone()
postEvtAna = hievtselanalyzer.clone()

from PbPbTrackingTools.HiTrackValidator.hitrackvalidator_cfi import *
from edwenger.HiTrkEffAnalyzer.HiTPCuts_cff import *
hihightrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiHighPtTracks"))
hihightrkval_fake = hihightrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                     hasSimInfo=cms.untracked.bool(True),
                                     selectFake=cms.untracked.bool(True))
higoodtrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiGoodTracks"))
higoodtrkval_fake = higoodtrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                       hasSimInfo=cms.untracked.bool(True),
                                       selectFake=cms.untracked.bool(True))

hihightrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                     hihightrkval_fake)
higoodtrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                     higoodtrkval_fake)


# clone cent bin analyzer
from FirstHi2010.CentralityDistAna.centralitydistana_cfi import *
preTrigCentDist = centbindist.clone()
postTrigCentDist = centbindist.clone()
postEvtCentDist = centbindist.clone()

# clone hitrack spectra ana to run with pixel and global
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *
hitrackAna.doJet = cms.untracked.bool(True)
hitrackAna.triggerNeeded = cms.untracked.bool(True)
hitrackAna.pixelMultMode = cms.untracked.bool(False)
hitrackAna.neededTrigSpectra = cms.untracked.vint32(0,1,1,0,0) #Jet35U and 50U

hitrackAna_jetMode1 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,80)) # jet Et cut
hitrackAna_jetMode2 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,100))

hihightrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiHighPtTracks"),
                                  src_evtCorr=cms.untracked.InputTag("hiHighPtTracks")
                                  )
hihightrackAna_jetMode1 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,80))
hihightrackAna_jetMode2 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,100))

hicaloTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiCaloCompTracks"),
                                  src_evtCorr=cms.untracked.InputTag("hiCaloCompTracks")
                                  ) 

hipxltrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiConformalPixelTracks"),
                                 src_evtCorr=cms.untracked.InputTag("hiConformalPixelTracks")
                                 )

hirefitTrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hirefitTracks")
                                   ) #refitted track!


## tracking efficiency analyzer --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hitrkEffAnalyzer_cff.py

## particle flow rereco and ana --------------------------------------
# defined in edwenger/HiTrkEffAnalyzer/python/hipfCandAnalyzer_cff.py


# Sequences
preTrgTest = cms.Sequence(preTrgAna*
                          (preAdpVtxAna+preMedVtxAna+preSelVtxAna)*
                          preTrigCentDist)

postTrgTest = cms.Sequence(postTrgAna*
                           postTrigCentDist)

postEvtSelTest = cms.Sequence(postEvtAna*
                              (postAdpVtxAna+postMedVtxAna+postSelVtxAna)*
                              postEvtCentDist)



