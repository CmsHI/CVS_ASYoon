import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.ReconstructionHeavyIons_cff import *
from RecoHI.Configuration.Reconstruction_hiPF_cff import *

trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiSelectedTracks")
particleFlow.vertexCollection = cms.InputTag("hiSelectedVertex")

# Filter on reco::Track pt
trkfilter = cms.EDFilter("PtMinTrackSelector",
                         src = cms.InputTag("hiSelectedTracks"),
                         ptMin = cms.double(4.0),
                         filter = cms.bool(True),
                         )


# Filter on PF candidate pt
pftrkfilter = cms.EDFilter("PtMinCandViewCloneSelector",
                           src=cms.InputTag("particleFlow",""),
                           ptMin=cms.double(4.0),
                           filter=cms.bool(True)
                           )


rechits = cms.Sequence(siPixelRecHits * siStripMatchedRecHits)
pfreco = cms.Sequence(rechits * heavyIonTracking * HiParticleFlowReco)


# HI rereco with PF reco is only performed on events with high pt tracks
rereco_seq = cms.Sequence(trkfilter * pfreco * pftrkfilter)
