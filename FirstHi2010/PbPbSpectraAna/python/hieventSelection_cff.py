import FWCore.ParameterSet.Config as cms

# ================ Physics Declared Bit ================
physDeclFilter = cms.EDFilter("PhysDecl",
              applyfilter = cms.untracked.bool(False),
              HLTriggerResults = cms.InputTag("TriggerResults","","HLT")
              )

# ================ HLT Filters =========================
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel

hltMinBias = hltHighLevel.clone(
    HLTPaths = cms.vstring('HLT_HIMinBiasHfOrBSC'),
    andOr = cms.bool(True)
    )

hltJets = hltHighLevel.clone(
    HLTPaths = cms.vstring('HLT_L1Jet6U','HLT_Jet15U','HLT_Jet30U'),
    andOr = cms.bool(True)
    )


minBiasBscFilter = cms.Sequence(hltMinBias)

# ================ Spike Cleaning =========================
#ECAL cleaning
from CmsHi.PhotonAnalysis.hiEcalRecHitSpikeFilter_cfi import *
hiEcalRecHitSpikeFilter.minEt = 20.0

#HCAL cleaning
from JetMETAnalysis.HcalReflagging.hbherechitreflaggerJETMET_cfi import *

hbheReflagNewTimeEnv = hbherechitreflaggerJETMET.clone()
hbheReflagNewTimeEnv.timingshapedcutsParameters.hbheTimingFlagBit=cms.untracked.int32(8)

# HCAL Timing
hcalTimingFilter = cms.EDFilter("HcalTimingFilter",
                   hbheHits = cms.untracked.InputTag("hbheReflagNewTimeEnv")
                )

spikeCleaning = cms.Sequence(hiEcalRecHitSpikeFilter*
                             hbheReflagNewTimeEnv*
                             hcalTimingFilter)


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
