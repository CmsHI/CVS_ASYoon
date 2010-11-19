import FWCore.ParameterSet.Config as cms


def enableSIM(process):
    process.hipxltrackAna.isGEN=True
    process.hitrackAna.isGEN=True
    process.hipxltrkEffAnalyzer.hasSimInfo=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    process.pfCandidateAnalyzer.isData=False
    process.pfCandidateAnalyzer.hasSimInfo=True
    process.pfCandidateAnalyzer_test.isData=False
    process.pfCandidateAnalyzer_test.hasSimInfo=True
    return process

def enableEffOnly(process):
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hitrackAna)
    process.hiAnalysisSeq.remove(process.hirefitTrackAna)
    return process

def disableLowPt(process):
    process.hiextraReco.remove(process.hiLowPtPixelTracks)
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    return process

def disableEff(process):
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    process.hiAnalysisSeq.remove(process.hitrkEffAna)
    process.hiAnalysisSeq.remove(process.hicalotrkEffAna)
    return process

def enableREDIGI(process):
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    return process

def usehiSelectedTracks(process):
    print "hiSelectedTracks is used!"
    process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiSelectedTracks")
    process.hiCaloCompTracks.src = cms.InputTag("hiSelectedTracks")
    process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag('hiSelectedTracks')
    process.pfCandidateAnalyzer.Tracks = cms.InputTag("hiSelectedTracks")
    return process

def setMinPtforPF(process,minpt=10):
    print "Particle Flow reconstruction/ana with min pT = ", minpt
    process.trkfilter.ptMin = cms.double(minpt)
    process.pftrkfilter.ptMin = cms.double(minpt)
    process.pfCandidateAnalyzer.ptMin = cms.untracked.double(minpt)
    process.hiCaloCompTracks.ptMin = cms.untracked.double(minpt)
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

# low -> low edge, up -> up edge
def whichCentBins(process,centRange):
    if centRange=="0To5":
        setCentBins(process,0,1)
    elif centRange=="0To10":
        setCentBins(process,0,3)
    elif centRange=="0To20":
        setCentBins(process,0,7)
    elif centRange=="20To40":
        setCentBins(process,8,15)
    elif centRange=="30To50":
        setCentBins(process,12,19)
    elif centRange=="50To100":
        setCentBins(process,20,39)
    elif centRange=="50To60":
        setCentBins(process,20,23)
    elif centRange=="60To80":
        setCentBins(process,24,31)
    elif centRange=="80To100":
        setCentBins(process,32,39)
    elif centRange=="60To100":
        setCentBins(process,25,39)
    elif centRange=="ALL":
        setCentBins(process,0,0)
    return process
            

def setAnaSeq(process,mode="AnaOnly"):
    if mode=="AnaOnly":
        process = disableEff(process)
        print "Ana only (no Eff)"
    if mode=="EffOnly":
        process = enableEffOnly(process)
        print "Eff only (no Ana)"
    if mode=="ALL":
        print "Ana and Eff both run"
    return process

def customiseLooseCuts(process):
    process.pfCandidateAnalyzer.minHits=0
    process.pfCandidateAnalyzer.maxPtErr=1.0
    process.pfCandidateAnalyzer.maxD0=10.0
    process.pfCandidateAnalyzer.maxDZ=10.0
    process.pfCandidateAnalyzer.maxD0Norm=100.0
    process.pfCandidateAnalyzer.maxDZNorm=100.0
    process.pfCandidateAnalyzer.pixelSeedOnly=False
    return process
                                

def eventFilterRereco(process):
    process.eventFilter.remove(process.centFilter)
    process.eventFilter.remove(process.preEvtSelVtxAna)
    process.eventFilter.remove(process.postEvtSelVtxAna)
    return process

#def conditionalTest(process):
#    listOfHiAnaSeq = str(process.hiAnalysisSeq)
#    if listOfHiAnaSeq.find("") == 0:
#        print "test"
#    if 'hipxltrackAnaMult' in listOfHiAnaSeq:
#        print "test"
#    return process
