import FWCore.ParameterSet.Config as cms

from PbPbTrackingTools.CaloCompatibleTrackSelector.selectCaloCompatibleTrack_cfi import * 

hiGeneralCaloTracks = selectCaloCompatibleTrack.clone(src = cms.InputTag("hiGeneralTracks"))
                                                      
