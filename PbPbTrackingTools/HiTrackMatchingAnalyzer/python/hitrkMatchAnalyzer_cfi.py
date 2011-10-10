import FWCore.ParameterSet.Config as cms

hitrkMatchAnalyzer = cms.EDAnalyzer('HiTrackMatchingAnalyzer',
      trkFst = cms.untracked.InputTag('hiSelectedTracks'),
      trkSnd = cms.untracked.InputTag('hiSelectedTracks'),
      jetTags = cms.untracked.InputTag('patJets'),
      siStripClst = cms.untracked.InputTag('siStripClst'),
      jetEtCuts = cms.untracked.vdouble(110,9000), # select events with leading jet E within range
      etaMax = cms.untracked.double(1.0),
      needTree = cms.untracked.bool(False), # fill tree
      ptMinTree = cms.untracked.double(35.0), # fill tree only if pT>ptMinTree
      checkHitMat = cms.untracked.bool(False), # check hit level infor between tracks
      drMax = cms.untracked.double(0.005), # for  dr(trk1,trk2) < drMax
      ptMinHitMat =  cms.untracked.double(35.0), #  for trk1 pt and trk2 pt > ptMin
      needClusterAna = cms.untracked.bool(False), # analyze cluster size
      neededCentBins = cms.untracked.vint32(0,1,3,11,19,39)
)
                                   
