import FWCore.ParameterSet.Config as cms

hitrkvalidator = cms.EDAnalyzer('HiTrackValidator',
      bslabel=cms.untracked.InputTag("offlineBeamSpot"),
      vtxlabel=cms.untracked.InputTag("hiSelectedVertex"),
      trklabel=cms.untracked.InputTag("hiSelectedTracks"),
      simtrklabel=cms.untracked.InputTag("mergedtruth","MergedTrackTruth"),
      associatorMap=cms.untracked.InputTag('trackingParticleRecoTrackAsssociation'),
      etaMax=cms.untracked.double(1.0),
      hasSimInfo=cms.untracked.bool(False),
      selectFake=cms.untracked.bool(False),
      useQaulityStr=cms.untracked.bool(True)
)
