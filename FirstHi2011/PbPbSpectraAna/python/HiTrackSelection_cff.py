import FWCore.ParameterSet.Config as cms

from FirstHi2011.PbPbSpectraAna.HiTrackQualitySel_cfi import *
hiGoodTightTracks = hiQualitySelTracks.clone()

#============================================================================                                                      
# This is for hiPtDepOptCaloTracks, which is the merged track collection of
# hiOptCaloPreFst: calo compatible + loose selection
# hiOptCaloPreSnd: calo incompatible + tight (hiGoodTight) selection
# (based on dR matchin with CaloTower)
#===========================================================================

from PbPbTrackingTools.HiCaloCompatibleTrackSelector.selectHiCaloCompatibleTrack_cfi import *

hiOptCaloPreFst = selectHiCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralHybridTracks"), 
                                                    applyPtDepCut = cms.untracked.bool(True))
hiOptCaloPreSnd = hiOptCaloPreFst.clone(reverseSel = cms.untracked.bool(True))

# loose selection
hiOptCaloPreFstLoose = hiOptCaloPreFst.clone(funcCaloComp = cms.string("0.087")) # float dR cut
hiOptCaloPreSndLoose = hiOptCaloPreFstLoose.clone(reverseSel = cms.untracked.bool(True))
