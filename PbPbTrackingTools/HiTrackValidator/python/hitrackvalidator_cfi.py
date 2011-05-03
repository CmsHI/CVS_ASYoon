import FWCore.ParameterSet.Config as cms

hitrkvalidator = cms.EDAnalyzer('HiTrackValidator',
      bslabel=cms.untracked.InputTag("offlineBeamSpot"),
      vtxlabel=cms.untracked.InputTag("hiSelectedVertex"),
      trklabel=cms.untracked.InputTag("hiSelectedTracks"),
      jetlabel=cms.untracked.InputTag("patJets"),
      simtrklabel=cms.untracked.InputTag("mergedtruth","MergedTrackTruth"),
      associatorMap=cms.untracked.InputTag('trackingParticleRecoTrackAsssociation'),
      etaMax=cms.untracked.double(1.0),
      jetEtMin=cms.untracked.double(-1.0), # cut on leading jet ET of event (if -1.0, no cut)
      hasSimInfo=cms.untracked.bool(False),
      selectFake=cms.untracked.bool(False),
      useQaulityStr=cms.untracked.bool(True),
      qualityString=cms.untracked.string("highPurity"),
      fiducialCut = cms.untracked.bool(False), # fiducial cut for FPIX
      neededCentBins = cms.untracked.vint32(0,1,3,11,19,39)
)
