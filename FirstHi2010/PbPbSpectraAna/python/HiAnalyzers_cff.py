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

# clone hi event selection analyzer
from edwenger.HiEvtSelAnalyzer.hievtselanalyzer_cfi import *
preTrgAna = hievtselanalyzer.clone()
postTrgAna = hievtselanalyzer.clone()
postEvtAna = hievtselanalyzer.clone()

from PbPbTrackingTools.HiTrackValidator.hitrackvalidator_cfi import *
from edwenger.HiTrkEffAnalyzer.HiTPCuts_cff import *
hihightrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiHighPtCaloTracks"))
hihightrkval_pt80 = hihightrkval.clone(jetEtMin=cms.untracked.double(80.0))
hihightrkval_fake = hihightrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                     hasSimInfo=cms.untracked.bool(True),
                                     selectFake=cms.untracked.bool(True))
hihightrkval_fake_pt80 = hihightrkval_fake.clone(jetEtMin=cms.untracked.double(80.0))

higloosetrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiGoodLooseCaloTracks"))
higloosetrkval_pt80 = higloosetrkval.clone(jetEtMin=cms.untracked.double(80.0))
higloosetrkval_fake = higloosetrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                           hasSimInfo=cms.untracked.bool(True),
                                           selectFake=cms.untracked.bool(True))
higloosetrkval_fake_pt80 = higloosetrkval_fake.clone(jetEtMin=cms.untracked.double(80.0))

higoodtrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiGoodTightCaloTracks"))
higoodtrkval_pt80 = higoodtrkval.clone(jetEtMin=cms.untracked.double(80.0))
higoodtrkval_fake = higoodtrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                       hasSimInfo=cms.untracked.bool(True),
                                       selectFake=cms.untracked.bool(True))
higoodtrkval_fake_pt80 = higoodtrkval_fake.clone(jetEtMin=cms.untracked.double(80.0))

# d0, dz open for systematic studies
hipredttrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiPreDTGoodTightCaloTracks"))
hipredttrkval_pt80 = hipredttrkval.clone(jetEtMin=cms.untracked.double(80.0))
hipredttrkval_fake = hipredttrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                         hasSimInfo=cms.untracked.bool(True),
                                         selectFake=cms.untracked.bool(True))
hipredttrkval_fake_pt80 = hipredttrkval_fake.clone(jetEtMin=cms.untracked.double(80.0))

hipredztrkval = hitrkvalidator.clone(trklabel=cms.untracked.InputTag("hiPreDZGoodTightCaloTracks"))
hipredztrkval_pt80 = hipredztrkval.clone(jetEtMin=cms.untracked.double(80.0))
hipredztrkval_fake = hipredztrkval.clone(simtrklabel = cms.untracked.InputTag("cutsTPForFak"),
                                         hasSimInfo=cms.untracked.bool(True),
                                         selectFake=cms.untracked.bool(True))
hipredztrkval_fake_pt80 = hipredztrkval_fake.clone(jetEtMin=cms.untracked.double(80.0))


## Sequence 
hihightrkval_all = cms.Sequence(hihightrkval*
                                hihightrkval_pt80)
higloosetrkval_all = cms.Sequence(higloosetrkval*
                                  higloosetrkval_pt80)
higoodtrkval_all = cms.Sequence(higoodtrkval*
                                higoodtrkval_pt80)

hipredttrkval_all = cms.Sequence(hipredttrkval*
                                 hipredttrkval_pt80)

hipredztrkval_all = cms.Sequence(hipredztrkval*
                                 hipredztrkval_pt80)

hihightrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                     hihightrkval_fake*
                                     hihightrkval_fake_pt80)
higloosetrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                       higloosetrkval_fake*
                                       higloosetrkval_fake_pt80)
higoodtrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                     higoodtrkval_fake*
                                     higoodtrkval_fake_pt80)

hipredttrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                      hipredttrkval_fake*
                                      hipredttrkval_fake_pt80)

hipredztrkval_fakeOnly = cms.Sequence(cutsTPForFak*
                                      hipredztrkval_fake*
                                      hipredztrkval_fake_pt80)

                                       
# clone cent bin analyzer
from FirstHi2010.CentralityDistAna.centralitydistana_cfi import *
preTrigCentDist = centbindist.clone()
postTrigCentDist = centbindist.clone()
postEvtCentDist = centbindist.clone()
extraCentDist = centbindist.clone(useJetThreshold = cms.untracked.bool(True)) # jet required

# clone hitrack spectra ana to run with pixel and global
from edwenger.HiTrackSpectraAnalyzer.hitrackspectraanalyzer_cfi import *

# HiGoodTight
hitrackAna.src = cms.untracked.InputTag("hiGoodTightCaloTracks")
hitrackAna.src_evtCorr = cms.untracked.InputTag("hiGoodTightCaloTracks")
hitrackAna.doJet = cms.untracked.bool(True)
hitrackAna.triggerNeeded = cms.untracked.bool(True)
hitrackAna.pixelMultMode = cms.untracked.bool(False)
hitrackAna.neededTrigSpectra = cms.untracked.vint32(0,1,1,0,0) #Jet35U and 50U

hitrackAna_jetMode1 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,80)) # jet Et cut
hitrackAna_jetMode2 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,100))
hitrackAna_jetMode3 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(80,9000)) # jet Et cut
hitrackAna_jetMode4 = hitrackAna.clone(jetEtCuts=cms.untracked.vdouble(100,9000))

# HiGoodLoose
higoodlooseAna = hitrackAna.clone(src=cms.untracked.InputTag("hiGoodLooseCaloTracks"),
                                  src_evtCorr=cms.untracked.InputTag("hiGoodLooseCaloTracks")
                                  )
higoodlooseAna_jetMode1 = higoodlooseAna.clone(jetEtCuts=cms.untracked.vdouble(0,80))
higoodlooseAna_jetMode2 = higoodlooseAna.clone(jetEtCuts=cms.untracked.vdouble(0,100))
higoodlooseAna_jetMode3 = higoodlooseAna.clone(jetEtCuts=cms.untracked.vdouble(80,9000))
higoodlooseAna_jetMode4 = higoodlooseAna.clone(jetEtCuts=cms.untracked.vdouble(100,9000))

# HiHighPt
hihightrackAna = hitrackAna.clone(src=cms.untracked.InputTag("hiHighPtCaloTracks"),
                                  src_evtCorr=cms.untracked.InputTag("hiHighPtCaloTracks")
                                  )
hihightrackAna_jetMode1 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,80))
hihightrackAna_jetMode2 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(0,100))
hihightrackAna_jetMode3 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(80,9000))
hihightrackAna_jetMode4 = hihightrackAna.clone(jetEtCuts=cms.untracked.vdouble(100,9000))



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
                          preSelVtxAna*
                          preTrigCentDist)

postTrgTest = cms.Sequence(postTrgAna*
                           postTrigCentDist)

postEvtSelTest = cms.Sequence(postEvtAna*
                              postSelVtxAna*
                              postEvtCentDist)



