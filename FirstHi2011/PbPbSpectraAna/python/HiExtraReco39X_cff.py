import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.HiCaloCompatibleTrackSelector.selectHiCaloCompatibleTrack_cfi import *
from MNguyen.iterTracking.TrackSelections_cff import *
hiGoodTightTracks.keepAllTracks = False # to make sure not all tracks are kept
from MNguyen.iterTracking.MergeTrackCollectionsHI_cff import *

#============================================================================
# This is for hiPtDepOptCaloTracks, which is the merged track collection of
# hiOptCaloPreFst: calo compatible + loose selection
# hiOptCaloPreSnd: calo incompatible + tight (hiGoodTight) selection
# (based on dR matching and energy fraction with CaloTower)
#============================================================================

hiOptCaloPreFst = selectHiCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralHybridTracks"),
                                                    applyPtDepCut = cms.untracked.bool(True))
hiOptCaloPreSnd = hiOptCaloPreFst.clone(reverseSel = cms.untracked.bool(True))

# loose selection (not used!)
hiOptCaloPreFstLoose = hiOptCaloPreFst.clone(funcCaloComp = cms.string("0.087")) # flaat dR cut
hiOptCaloPreSndLoose = hiOptCaloPreFstLoose.clone(reverseSel = cms.untracked.bool(True))

hiOptCaloFst = hiLooseTracks.clone(src = cms.InputTag("hiOptCaloPreFst"))
hiOptCaloSnd = hiGoodTightTracks.clone(src = cms.InputTag("hiOptCaloPreSnd"))

hiOptimalTightTracks  = hiGeneralTracks.clone(
    ShareFrac = cms.double(999.0), # since two collections have no track in common
    TrackProducer1 = 'hiOptCaloFst',
    TrackProducer2 = 'hiOptCaloSnd',
)

# algo selection (algo = 4, i.e. only first iteration) - not really needed
hiOptimalTightTracks1stIter = cms.EDFilter("TrackSelector",
     src = cms.InputTag("hiOptimalTightTracks"),
     cut = cms.string('algo==4')
)

hiOptTrack39X = cms.Sequence(
    hiOptCaloPreFst *
    hiOptCaloFst *
    hiOptCaloPreSnd *
    hiOptCaloSnd *
    hiOptimalTightTracks 
    #process.hiOptimalTightTracks1stIter
)

