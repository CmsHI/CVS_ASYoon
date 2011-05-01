import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.ReconstructionHeavyIons_cff import *
from RecoHI.Configuration.Reconstruction_hiPF_cff import *
from edwenger.HiTrkEffAnalyzer.TrackSelections_cff import *
from Appeltel.PixelTracksRun2010.HiLowPtPixelTracksFromReco_cff import *
from Appeltel.PixelTracksRun2010.HiMultipleMergedTracks_cff import *


trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiHighPtTracks")
trackerDrivenElectronSeeds.UseQuality = cms.bool(False)
particleFlow.vertexCollection = cms.InputTag("hiSelectedVertex")


# Filter on reco::Track pt
trkfilter = cms.EDFilter("PtMinTrackSelector",
                         src = cms.InputTag("hiHighPtTracks"), # hiGoodTracks are not produced yet
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
pfreco = cms.Sequence(rechits * HiParticleFlowReco) 

HiParticleFlowReco.remove(recoPFJets) # PF jets are not needed

# HI rereco with PF reco is only performed on events with high pt tracks
rereco_seq = cms.Sequence(trkfilter * pfreco * pftrkfilter)
