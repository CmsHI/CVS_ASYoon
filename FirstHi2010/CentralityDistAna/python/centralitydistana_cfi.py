import FWCore.ParameterSet.Config as cms

centbindist = cms.EDAnalyzer('CentralityDistAna',
        neededCentBins = cms.untracked.vint32(0,1,3,11,19,39) # 0~5% (0,1), 5~10% (2,3), 10~30% (4,11) etc..
)
