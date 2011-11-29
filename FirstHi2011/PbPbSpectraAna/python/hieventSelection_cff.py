import FWCore.ParameterSet.Config as cms

# ================ Physics Declared Bit ================
physDeclFilter = cms.EDFilter("PhysDecl",
              applyfilter = cms.untracked.bool(False),
              HLTriggerResults = cms.InputTag("TriggerResults","","HLT")
              )

# ================ HLT Filters =========================
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel

hltMinBias = hltHighLevel.clone(
    HLTPaths = cms.vstring('HLT_HIMinBiasHfOrBSC_v1'),
    andOr = cms.bool(True)
    )

hltJets = hltHighLevel.clone(
    HLTPaths = cms.vstring('HLT_L1Jet6U','HLT_Jet15U','HLT_Jet30U'),
    andOr = cms.bool(True)
    )


minBiasBscFilter = cms.Sequence(hltMinBias)

# ================ Spike Cleaning =========================
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
HBHENoiseFilter.minRatio = cms.double(-99999.0) # see CmsHi.JetAnalysis.EventSelection_cff
HBHENoiseFilter.maxRatio = cms.double(99999.0)
HBHENoiseFilter.minZeros = cms.int32(100)
spikeCleaning = cms.Sequence(HBHENoiseFilter)

# =========== Jet Eta selector ===================
barrelJets = cms.EDFilter("EtaPtMinCandViewSelector",
                          src = cms.InputTag("iterativeConePu5CaloJets"),
                          ptMin   = cms.double(0),
                          etaMin = cms.double(-2),
                          etaMax = cms.double(2)
                          )

jetFilter = cms.EDFilter("CandCountFilter",
                         src = cms.InputTag("barrelJets"),
                         minNumber = cms.uint32(1)
                         )

jetEtaSel = cms.Sequence(barrelJets *
                         jetFilter)
