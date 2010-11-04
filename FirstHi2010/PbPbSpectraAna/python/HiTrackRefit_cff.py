import FWCore.ParameterSet.Config as cms

# vertex constraint
doConstraint = cms.EDProducer("VertexConstraintProducer")

# refit tracks
from RecoTracker.TrackProducer.TrackRefitter_cfi import TrackRefitter
hirefitTracks = TrackRefitter.clone(
    constraint = 'vertex',
    srcConstr = 'doConstraint'
    )

# sequence
hitrackRefit = cms.Sequence(doConstraint * hirefitTracks)
