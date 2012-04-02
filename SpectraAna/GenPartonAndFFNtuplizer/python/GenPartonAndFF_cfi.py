import FWCore.ParameterSet.Config as cms

genSpectAna = cms.EDAnalyzer('GenPartonAndFFNtuplizer',
              gsrc = cms.untracked.InputTag("genParticles"),
              gjsrc = cms.untracked.InputTag("ak5GenJets"),
              pthatCut = cms.untracked.double(0.0),
              crossX = cms.untracked.double(0.0), # cross section in mb
              numEvt = cms.untracked.int32(100) # number of events                             
)
