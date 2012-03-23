import FWCore.ParameterSet.Config as cms

genSpectAna = cms.EDAnalyzer('GenPartonAndFFNtuplizer',
              gsrc = cms.untracked.InputTag("genParticles"),
              gjsrc = cms.untracked.InputTag("ak5GenJets"),
              pthatCut = cms.untracked.double(0.0) # 
)
