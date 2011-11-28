import FWCore.ParameterSet.Config as cms

#from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

#hiGeneralCaloTracks = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralTracks"))

#============================================================================
# This is for hiPtDepOptCaloTracks, which is the merged track collection of
# hiPtDeptOptCaloPreFst: calo compatible + loose selection
# hiPtDeptOptCaloPreSnd: calo incompatible + tight (hiGoodTight) selection
# (based on Energy Sum/track pT ratio with PF)
#============================================================================

#hiPtDeptOptCaloPreFst = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralGlobalPrimTracks"),
#                                                        applyPtDepCut = cms.untracked.bool(True))
#hiPtDeptOptCaloPreSnd = hiPtDeptOptCaloPreFst.clone(reverseSel = cms.untracked.bool(True))

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
