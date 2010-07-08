import FWCore.ParameterSet.Config as cms

# this is to enable or disable features as necessary for running over MC
def enableSIM(process):
    process.hitrackAna.isGEN=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    return process


