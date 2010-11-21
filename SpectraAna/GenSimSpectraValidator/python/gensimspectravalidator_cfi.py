import FWCore.ParameterSet.Config as cms

gensimSpectraValidator = cms.EDAnalyzer('GenSimSpectraValidator',
                        gsrc = cms.untracked.InputTag('hiGenParticles'),
                        ssrc = cms.untracked.InputTag('mergedtruth','MergedTrackTruth'),
                        etaMax = cms.untracked.double(2.4)
                        )
