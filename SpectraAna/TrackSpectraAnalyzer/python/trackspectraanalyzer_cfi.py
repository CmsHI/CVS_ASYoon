import FWCore.ParameterSet.Config as cms

trackAna = cms.EDAnalyzer('TrackSpectraAnalyzer',
        src = cms.untracked.InputTag("generalTracks"),
        vsrc = cms.untracked.InputTag("offlinePrimaryVertices"),
        jsrc = cms.untracked.InputTag("ak5CaloJets"),
        doOutput = cms.untracked.bool(True),
        isGEN = cms.untracked.bool(True),
        doJet = cms.untracked.bool(True),
        etaMax = cms.untracked.double(5.0),
        nVtxTrkCut = cms.untracked.int32(3)
)