import FWCore.ParameterSet.Config as cms

# this is to enable or disable features as necessary for running over MC
def enableSIM(process):
    process.hipxltrackAna.isGEN=True
    process.hipxltrackAnaMult.isGEN=True
    process.hipxltrkEffAnalyzer.hasSimInfo=True
    process.hipxltrkEffAnalyzerMult.hasSimInfo=True
    process.hitrackAna.isGEN=True
    process.hitrackAnaMult.isGEN=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    process.hitrkEffAnalyzerMult.hasSimInfo=True
    return process

def disableLowPt(process):
    process.hiextraReco.remove(process.hiLowPtPixelTracks)
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrackAnaMult)
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    return process
