import FWCore.ParameterSet.Config as cms

centbindist = cms.EDAnalyzer('CentralityDistAna',
        jsrc = cms.untracked.InputTag("icPu5patJets"),
        neededCentBins = cms.untracked.vint32(0,1,3,11,19,39), # 0~5% (0,1), 5~10% (2,3), 10~30% (4,11) etc..
        useJetThreshold = cms.untracked.bool(False), # fill histogram for Jet ET> ET'
        produceTree = cms.untracked.bool(False), # fill ntuple for HFHits and HFTowers
        applyStrechFact = cms.untracked.double(-1)   # strech factor to compare 2010 and 2011 (-1 means no streching)                              
)
