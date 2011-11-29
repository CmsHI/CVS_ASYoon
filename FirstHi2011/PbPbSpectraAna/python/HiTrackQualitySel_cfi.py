import FWCore.ParameterSet.Config as cms

hiQualitySelTracks = cms.EDFilter("TrackSelector",
               src = cms.InputTag("hiSelectedTracks"),
               cut = cms.string('quality("highPurity")')
               )

