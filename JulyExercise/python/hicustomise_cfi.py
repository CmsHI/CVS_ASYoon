import FWCore.ParameterSet.Config as cms

# this is to enable or disable features as necessary for running over MC
def enableSIM(process):
    process.trackAna.isGEN=True
    process.trkEffAnalyzer.hasSimInfo=True
    return process


