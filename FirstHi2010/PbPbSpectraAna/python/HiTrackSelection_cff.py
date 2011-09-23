import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

hiGeneralCaloTracks = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralTracks"))



# This is for hiPtDepOptCaloTracks, which is the merged track collection of
# hiPtDeptOptCaloPreFst: calo compatible + loose selection
# hiPtDeptOptCaloPreSnd: calo incompatible + tight (hiGoodTight) selection

hiPtDeptOptCaloPreFst = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralGlobalPrimTracks"),
                                                        applyPtDepCut = cms.untracked.bool(True))
hiPtDeptOptCaloPreSnd = hiPtDeptOptCaloPreFst.clone(reverseSel = cms.untracked.bool(True))
                                                      
