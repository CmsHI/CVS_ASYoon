import FWCore.ParameterSet.Config as cms

hitrkMatchAnalyzer = cms.EDAnalyzer('HiTrackMatchingAnalyzer',
      trkFst = cms.untracked.InputTag('hiSelectedTracks'),
      trkSnd = cms.untracked.InputTag('hiSelectedTracks'),
      etaMax = cms.untracked.double(1.0),
      neededCentBins = cms.untracked.vint32(0,1,3,11,19,39)
)
                                   
