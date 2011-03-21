import FWCore.ParameterSet.Config as cms


def enableSIM(process):
    process.preTrgAna.isGEN=True
    process.postTrgAna.isGEN=True
    process.postEvtAna.isGEN=True
    process.hipxltrackAna.isGEN=True
    process.hitrackAna.isGEN=True
    process.hihightrackAna.isGEN=True
    process.hipxltrkEffAnalyzer.hasSimInfo=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    process.hihightrkEffAnalyzer.hasSimInfo=True
    process.hiAnalysisSeq.replace(process.hihightrkval,process.hihightrkval+process.hihightrkval_fakeOnly)
    process.hiAnalysisSeq.replace(process.higoodtrkval,process.higoodtrkval+process.higoodtrkval_fakeOnly)
    process.pfCandidateAnalyzer.isData=False
    process.pfCandidateAnalyzer.hasSimInfo=True
    process.pfCandidateAnalyzer_test.isData=False
    process.pfCandidateAnalyzer_test.hasSimInfo=True
    process.minBiasBscFilter.remove(process.hltMinBias) # assuming MC is 100% MB
    #process.hltMinBias.HLTPaths=cms.vstring('HLT_HIMinBiasBSC')  # default HLTPath is not available for MC
    print "hltMinBias is removed from minBiasBscFilter check what's left:", process.minBiasBscFilter 
    return process

def enableEffOnly(process):
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hitrackAna)
    process.hiAnalysisSeq.remove(process.hihightrackAna)
    process.hiAnalysisSeq.remove(process.hirefitTrackAna)
    return process

def disableLowPt(process):
    print "No low pt ana (no low pt re-reco as well unlesss hiGoodMergedTracks is used)!"
    process.hiextraReco.remove(process.conformalPixelTrackReco)
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    return process

def disableLowPtAna(process):
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    return process

def disableEff(process):
    process.hiAnalysisSeq.remove(process.hipxltrkEffAna)
    process.hiAnalysisSeq.remove(process.hihightrkEffAna)
    process.hiAnalysisSeq.remove(process.hitrkEffAna)
    process.hiAnalysisSeq.remove(process.hicalotrkEffAna)
    return process

def enableREDIGI(process):
    print "enableREDIGI option is enabled (REDIGI)!"
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    return process

def runOnCore(process):
    # hmm.. do we need similar list as in runOn384p2"
    print "runOnCore option is enabled (HLT_HIMinBiasHfOrBSC_Core)!"
    process.hltMinBias.HLTPaths=cms.vstring('HLT_HIMinBiasHfOrBSC_Core')
    return process

def runOn384p2(process):
    list = ['HLT_HIMinBiasCalo','HLT_HIJet35U']
    print "runOn384p2 option is enabled (HLT_HIMinBiasCalo and HISIGNAL)!"
    print "hlt list for track analyzer = ",list
    process.hltMinBias.HLTPaths=cms.vstring('HLT_HIMinBiasCalo')  # HLT_HIMinBiasBSC is not available
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','HISIGNAL')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna.hltNames = cms.untracked.vstring(list)
    process.hicaloTrackAna.hltNames = cms.untracked.vstring(list)
    process.hipxltrackAna.hltNames = cms.untracked.vstring(list)
    process.hirefitTrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrkval.useQaulityStr = cms.untracked.bool(False)
    process.hihightrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.higoodtrkval.useQaulityStr =cms.untracked.bool(False)
    process.higoodtrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.preTrgAna.trignames = cms.untracked.vstring(list)
    process.postTrgAna.trignames = cms.untracked.vstring(list)
    process.postEvtAna.trignames = cms.untracked.vstring(list)
    return process

def runOn395(process):
    list = ['HLT_HIMinBiasHF','HLT_HIJet35U','HLT_HIJet50U']
    print "runOn395 option is enabled (minBiasBscFilter removed)!"
    print "hlt list for track analyzer = ",list
    process.eventFilter.remove(process.minBiasBscFilter)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','HLT')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','HLT')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna.hltNames = cms.untracked.vstring(list)
    process.hicaloTrackAna.hltNames = cms.untracked.vstring(list)
    process.hipxltrackAna.hltNames = cms.untracked.vstring(list)
    process.hirefitTrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrkval.useQaulityStr = cms.untracked.bool(False)
    process.hihightrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.higoodtrkval.useQaulityStr =cms.untracked.bool(False)
    process.higoodtrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.preTrgAna.trignames = cms.untracked.vstring(list)
    process.postTrgAna.trignames = cms.untracked.vstring(list)
    process.postEvtAna.trignames = cms.untracked.vstring(list)
    return process

def runOn393(process):
    print "runOn393 option is enabled (minBiasBscFilter removed)!"
    process.eventFilter.remove(process.minBiasBscFilter)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    return process

def runOn393DataMixMC(process):
    print "runOn393DataMixMC option is enabled (the whole event filtering removed)!"
    process.eventFilter.remove(process.minBiasBscFilter)
    process.eventFilter.remove(process.collisionEventSelection)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hicaloTrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hicaloTrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hipxltrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hipxltrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hirefitTrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hirefitTrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    return process

def runOn393NewDataMixMC(process):
    print "runOn393NewDataMixMC option is enabled (the whole event filtering removed)!"
    process.eventFilter.remove(process.minBiasBscFilter)
    process.eventFilter.remove(process.collisionEventSelection)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECOMIX')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hicaloTrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hicaloTrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hipxltrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hipxltrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hirefitTrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hirefitTrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    return process

    
def usehiSelectedTracks(process):
    print "hiSelectedTracks is used!"
    process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiSelectedTracks")
    process.hiCaloCompTracks.src = cms.InputTag("hiSelectedTracks")
    process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag('hiSelectedTracks')
    process.pfCandidateAnalyzer.Tracks = cms.InputTag("hiSelectedTracks")
    process.hitrackAna.src = cms.untracked.InputTag("hiSelectedTracks")
    process.hitrackAna.src_evtCorr = cms.untracked.InputTag("hiSelectedTracks")
    #process.hihightrackAna.src = cms.untracked.InputTag("hiSelectedTracks")
    #process.hihightrackAna.src_evtCorr = cms.untracked.InputTag("hiSelectedTracks")
    process.hiextraTrack.remove(process.hiGoodTracksSelection)
    process.heavyIonTracking.remove(process.hiGoodTracksSelection)
    return process


### this is for selecting jet events instead of prescaled MB
def enableHLTJet(process,hltname='HLT_HIJet50U'):
    process.hltJets.HLTPaths = [hltname]
    process.minBiasBscFilter.replace(process.hltMinBias,process.hltJets)
    print "Skim jet HLT path: ", process.hltJets.HLTPaths, "and minBiasBscFilter: ", process.minBiasBscFilter
    process.eventFilter*=process.hiEcalRecHitSpikeFilter
    return process
                            

def usehiGoodMergedTracks(process):
    print "hiGoodMergedTracks is used (except PF re-reco)! --> re-reco of conformalPixelTrackReco!"
    print "make sure disableLowPt comes before usehiGoodMergedTracks"
    #process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiSelectedTracks")
    process.hiCaloCompTracks.src = cms.InputTag("hiGoodMergedTracks")
    process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag('hiGoodMergedTracks')
    process.pfCandidateAnalyzer.Tracks = cms.InputTag("hiGoodMergedTracks")
    process.hitrackAna.src = cms.untracked.InputTag("hiGoodMergedTracks")
    process.hitrackAna.src_evtCorr = cms.untracked.InputTag("hiGoodMergedTracks")
    #process.hihightrackAna.src = cms.untracked.InputTag("hiGoodMergedTracks")
    #process.hihightrackAna.src_evtCorr = cms.untracked.InputTag("hiGoodMergedTracks")
    process.hiextraReco *= process.conformalPixelTrackReco
    process.hiGoodTracksSelection *= process.hiGoodMergedTracks
    return process

def setMinPtforPF(process,minpt=10):
    print "Particle Flow reconstruction/ana with min pT = ", minpt
    process.trkfilter.ptMin = cms.double(minpt)
    process.pftrkfilter.ptMin = cms.double(minpt)
    process.pfCandidateAnalyzer.ptMin = cms.untracked.double(minpt)
    process.pfCandidateAnalyzer_test.ptMin = cms.untracked.double(minpt)
    process.hiCaloCompTracks.ptMin = cms.untracked.double(minpt)
    return process

def whichCentBinMode(process,cbinMode=0):
    if cbinMode==0 :
        # 0~5,5~10,10~30,30~50,50~90
        cbins=[0,1,3,11,19,35] # cut off 90~100% bin
        print "Centrality bins = ", cbins
    if cbinMode==1 :
        # 0~5,5~10,10~30,30~50,50~70,70~90
        cbins=[0,1,3,11,19,27,35] # cut off 90~100% bin
        print "Centrality bins = ", cbins
    if cbinMode==3 :
        cbins=[0,1,3,11,19,39] 
        print "Centrality bins = ", cbins
    if cbinMode==4 :
        cbins=[0,1,3,11,19,27,39]
        print "Centrality bins = ", cbins
    process.hitrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hicaloTrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hipxltrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hirefitTrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrkEffAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrkEffAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
    process.preTrigCentDist.neededCentBins = cms.untracked.vint32(cbins)
    process.postTrigCentDist.neededCentBins = cms.untracked.vint32(cbins)
    process.postEvtCentDist.neededCentBins = cms.untracked.vint32(cbins)
    process.preAdpVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.preMedVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.preSelVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.postAdpVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.postMedVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.postSelVtxAna.neededCentBins = cms.untracked.vint32(cbins)
    process.preTrgAna.neededCentBins = cms.untracked.vint32(cbins)
    process.preTrgAna.neededCentBins = cms.untracked.vint32(cbins)
    process.postEvtAna.neededCentBins = cms.untracked.vint32(cbins)
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
    elif centRange=="0To30":
        setCentBins(process,0,11)
    elif centRange=="0To50":
        setCentBins(process,0,19)
    elif centRange=="5To10":
        setCentBins(process,2,3)
    elif centRange=="10To30":
        setCentBins(process,4,11)
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
        setCentBins(process,45,39)
    elif centRange=="30To100":
        setCentBins(process,12,39)
    elif centRange=="ALL":
        setCentBins(process,0,0)
    return process

def constraintOnLJetEta(process):
    # contraint jet eta acceptance within tracker acceptance 
    print "Constraint on the leading jet eta !"
    process.hitrkEffAnalyzer.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrkEffAnalyzer.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hicaloTrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hipxltrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hirefitTrackAna.trkAcceptedJet = cms.untracked.bool(True)
    return process

def useSubLeadingJet(process):
    print "Sub-leading jet is used in event classificaiton !"
    process.hitrkEffAnalyzer.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrkEffAnalyzer.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hicaloTrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hipxltrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hirefitTrackAna.useSubLeadingJet = cms.untracked.bool(True)
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
