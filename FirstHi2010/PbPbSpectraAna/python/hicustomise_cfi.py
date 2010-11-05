import FWCore.ParameterSet.Config as cms

# this is to enable or disable features as necessary for running over MC


def enableSIM(process):
    process.hipxltrackAna.isGEN=True
    process.hipxltrackAnaMult.isGEN=True
    process.hitrackAna.isGEN=True
    process.hitrackAnaMult.isGEN=True
    process.hipxltrkEffAnalyzer.hasSimInfo=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    return process

def enableEffOnly(process):
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrackAnaMult)
    process.hiAnalysisSeq.remove(process.hitrackAna)
    process.hiAnalysisSeq.remove(process.hirefitTrackAna)
    process.hiAnalysisSeq.remove(process.hitrackAnaMult)
    return process

def disableLowPt(process):
    process.hiextraReco.remove(process.hiLowPtPixelTracks)
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrackAnaMult)
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    return process

def disableEff(process):
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    process.hiAnalysisSeq.remove(process.hitrkEffAna)
    return process

def setAnaSeq(process,mode="AnaOnly"):
    if mode=="AnaOnly":
        process = disableEff(process)
    if mode=="EffOnly":
        process = enableEffOnly(process)
    if mode=="ALL":
        print "Ana and Eff both run"
    return process

def conditionalTest(process):
    listOfHiAnaSeq = str(process.hiAnalysisSeq)
    if listOfHiAnaSeq.find("") == 0:
        print "test"
    return process
