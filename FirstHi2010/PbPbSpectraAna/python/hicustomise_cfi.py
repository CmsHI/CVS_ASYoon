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

def enableREDIGI(process):
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    return process
    

def setCentBins(process,ci=0,cf=10):
    if ci==cf:
        print "No centrality selection"
        process.eventFilter.remove(process.centFilter)
    else: 
        for i in range(ci,cf+1):
            process.centFilter.selectedBins.append(i)
        print "Centrality bins = ", process.centFilter.selectedBins
    return process

def whichCentBins(process,centRange):
    if centRange=="0To10":
        setCentBins(process,0,3)
    elif centRange=="0To20":
        setCentBins(process,0,7)
    elif centRange=="20To40":
        setCentBins(process,9,15)
    elif centRange=="60To100":
        setCentBins(process,25,39)
    elif centRange=="ALL":
        setCentBins(process,0,0)
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
