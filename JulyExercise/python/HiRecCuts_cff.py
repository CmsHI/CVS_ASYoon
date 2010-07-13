import FWCore.ParameterSet.Config as cms

import PhysicsTools.RecoAlgos.recoTrackSelector_cfi

cutsRecoTracks = PhysicsTools.RecoAlgos.recoTrackSelector_cfi.recoTrackSelector.clone(src = cms.InputTag("hiSelectedTracks"),
                                                                                      minRapidity = cms.double(-2.5),
                                                                                      ptMin = cms.double(1.0),
                                                                                      maxRapidity = cms.double(2.5),
                                                                                      quality = cms.vstring(''))

