import FWCore.ParameterSet.Config as cms


def enableSIM(process):
    process.preTrgAna.isGEN=True
    process.postTrgAna.isGEN=True
    process.postEvtAna.isGEN=True
    process.hipxltrackAna.isGEN=True
    process.hitrackAna.isGEN=True
    process.hitrackAna_jetMode1.isGEN=True
    process.hitrackAna_jetMode2.isGEN=True
    process.hitrackAna_jetMode3.isGEN=True
    process.hitrackAna_jetMode4.isGEN=True
    process.higoodlooseAna.isGEN=True
    process.higoodlooseAna_jetMode1.isGEN=True
    process.higoodlooseAna_jetMode2.isGEN=True
    process.higoodlooseAna_jetMode3.isGEN=True
    process.higoodlooseAna_jetMode4.isGEN=True
    process.hihightrackAna.isGEN=True
    process.hihightrackAna_jetMode1.isGEN=True
    process.hihightrackAna_jetMode2.isGEN=True
    process.hihightrackAna_jetMode3.isGEN=True
    process.hihightrackAna_jetMode4.isGEN=True
    process.hipxltrkEffAnalyzer.hasSimInfo=True
    process.hitrkEffAnalyzer.hasSimInfo=True
    process.hihightrkEffAnalyzer.hasSimInfo=True
    process.higloosetrkEffAnalyzer.hasSimInfo=True
    process.hiAnalysisSeq.replace(process.hihightrkval_all,process.hihightrkval_all+process.hihightrkval_fakeOnly)
    process.hiAnalysisSeq.replace(process.higloosetrkval_all,process.higloosetrkval_all+process.higloosetrkval_fakeOnly)
    process.hiAnalysisSeq.replace(process.higoodtrkval_all,process.higoodtrkval_all+process.higoodtrkval_fakeOnly)
    process.hiAnalysisSeq.replace(process.hipredttrkval_all,process.hipredttrkval_all+process.hipredttrkval_fakeOnly)
    process.hiAnalysisSeq.replace(process.hipredztrkval_all,process.hipredztrkval_all+process.hipredztrkval_fakeOnly)
    process.pfCandidateAnalyzer.isData=False
    process.pfCandidateAnalyzer.hasSimInfo=True
    process.pfCandidateAnalyzer_test.isData=False
    process.pfCandidateAnalyzer_test.hasSimInfo=True
    process.hipfCandAnalyzer.replace(process.pfCandidateAnalyzer,process.cutsTPForFak*process.pfCandidateAnalyzer)
    process.hipfCandAnalyzer_test.replace(process.pfCandidateAnalyzer_test,process.cutsTPForFak*process.pfCandidateAnalyzer_test)
    process.minBiasBscFilter.remove(process.hltMinBias) # assuming MC is 100% MB
    process.higoodtrkval.fiducialCut=True
    process.higoodtrkval_pt80.fiducialCut=True
    process.higoodtrkval_fake.fiducialCut=True
    process.higoodtrkval_fake_pt80.fiducialCut=True
    process.higloosetrkval.fiducialCut=True
    process.higloosetrkval_fake.fiducialCut=True
    process.higloosetrkval_pt80.fiducialCut=True
    process.higloosetrkval_fake_pt80.fiducialCut=True
    process.hihightrkval.fiducialCut=True
    process.hihightrkval_fake.fiducialCut=True
    process.hihightrkval_pt80.fiducialCut=True
    process.hihightrkval_fake_pt80.fiducialCut=True
    process.hipredttrkval.fiducialCut=True
    process.hipredttrkval_fake.fiducialCut=True
    process.hipredttrkval_pt80.fiducialCut=True
    process.hipredttrkval_fake_pt80.fiducialCut=True
    process.hipredztrkval.fiducialCut=True
    process.hipredztrkval_fake.fiducialCut=True
    process.hipredztrkval_pt80.fiducialCut=True
    process.hipredztrkval_fake_pt80.fiducialCut=True
    #process.hltMinBias.HLTPaths=cms.vstring('HLT_HIMinBiasBSC')  # default HLTPath is not available for MC
    print "hltMinBias is removed from minBiasBscFilter check what's left:", process.minBiasBscFilter 
    return process


def runWithLightCfg(process):
    print "Light cfg: following modules are removed"
    print "higoodtrkval*, hihightrkval*, higloosetrkval*, hipredttrkval*"
    print "hihightrackAna*, higoodlooseAna*"
    #process.hiAnalysisSeq.remove(process.higoodtrkval)
    #process.hiAnalysisSeq.remove(process.higoodtrkval_pt80)
    process.hiAnalysisSeq.remove(process.hihightrkval)
    process.hiAnalysisSeq.remove(process.hihightrkval_pt80)
    process.hiAnalysisSeq.remove(process.higloosetrkval)
    process.hiAnalysisSeq.remove(process.higloosetrkval_pt80)
    process.hiAnalysisSeq.remove(process.hipredttrkval)
    process.hiAnalysisSeq.remove(process.hipredttrkval_pt80)
    process.hiAnalysisSeq.remove(process.hihightrackAna)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode1)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode2)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode3)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode4)
    process.hiAnalysisSeq.remove(process.higoodlooseAna)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode1)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode2)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode3)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode4)
    return process
    
def enableEffOnly(process):
    process.hiAnalysisSeq.remove(process.hipxltrackAna)
    process.hiAnalysisSeq.remove(process.hitrackAna)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode1)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode2)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode3)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode4)
    process.hiAnalysisSeq.remove(process.higoodlooseAna)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode1)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode2)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode3)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode4)
    process.hiAnalysisSeq.remove(process.hihightrackAna)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode1)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode2)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode3)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode4)
    process.hiAnalysisSeq.remove(process.hirefitTrackAna)
    return process

def disableValidatorForFake(process):
    print "track validator for fake only removed"
    process.hiAnalysisSeq.remove(process.hihightrkval_fakeOnly)
    process.hiAnalysisSeq.remove(process.higloosetrkval_fakeOnly)
    process.hiAnalysisSeq.remove(process.higoodtrkval_fakeOnly)
    return process

def disableValidator(process):
    print "track validator for fake only removed"
    process.hiAnalysisSeq.remove(process.hihightrkval)
    process.hiAnalysisSeq.remove(process.hihightrkval_pt80)
    process.hiAnalysisSeq.remove(process.higloosetrkval)
    process.hiAnalysisSeq.remove(process.higloosetrkval_pt80)
    process.hiAnalysisSeq.remove(process.higoodtrkval)
    process.hiAnalysisSeq.remove(process.higoodtrkval_pt80)
    process.hiAnalysisSeq.remove(process.hipredttrkval)
    process.hiAnalysisSeq.remove(process.hipredttrkval_pt80)
    return process


def disableJetEtCutOnAna(process):
    print "*_jetMode* analzyers are removed!"
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode1)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode2)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode3)
    process.hiAnalysisSeq.remove(process.hitrackAna_jetMode4)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode1)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode2)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode3)
    process.hiAnalysisSeq.remove(process.higoodlooseAna_jetMode4)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode1)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode2)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode3)
    process.hiAnalysisSeq.remove(process.hihightrackAna_jetMode4)
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
    process.hiAnalysisSeq.remove(process.higloosetrkEffAna)
    process.hiAnalysisSeq.remove(process.hitrkEffAna)
    process.hiAnalysisSeq.remove(process.hicalotrkEffAna)
    return process

def enableREDIGI(process):
    print "enableREDIGI option is enabled (REDIGI)!"
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.higoodlooseAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','REDIGI')
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

def runWithCaloTracks(process):
    print "run with calo-compatible tracks! (*CaloTracks for validator, analyzers)"
    # also add the whole calo-track seq
    process.hihightrkval.trklabel=cms.untracked.InputTag("hiHighPtCaloTracks")
    process.higloosetrkval.trklabel=cms.untracked.InputTag("hiGoodLooseCaloTracks")
    process.higoodtrkval.trklabel=cms.untracked.InputTag("hiGoodTightCaloTracks")
    process.hipredttrkval.trklabel=cms.untracked.InputTag("hiPreDTGoodTightCaloTracks")
    process.hipredztrkval.trklabel=cms.untracked.InputTag("hiPreDZGoodTightCaloTracks")
    process.hitrackAna.src = cms.untracked.InputTag("hiGoodTightCaloTracks")
    process.hitrackAna.src_evtCorr = cms.untracked.InputTag("hiGoodTightCaloTracks")
    process.higoodlooseAna.src = cms.untracked.InputTag("hiGoodLooseCaloTracks")
    process.higoodlooseAna.src_evtCorr = cms.untracked.InputTag("hiGoodLooseCaloTracks")
    process.hihightrackAna.src = cms.untracked.InputTag("hiHighPtCaloTracks")
    process.hihightrackAna.src_evtCorr = cms.untracked.InputTag("hiHighPtCaloTracks")
    process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag('hiGoodTightCaloTracks')
    process.higloosetrkEffAnalyzer.tracks = cms.untracked.InputTag('hiGoodLooseCaloTracks')
    process.hihightrkEffAnalyzer.tracks = cms.untracked.InputTag('hiHighPtCaloTracks')
    return process

def runWithIterTrk(process,trkcoll='hiGeneralTracks'):
    print "use the following tracking collections [",trkcoll,"] from iterative tracking"
    print "quality bit is removed"
    process.higoodtrkval.trklabel=cms.untracked.InputTag(trkcoll)
    process.hipredttrkval.trklabel=cms.untracked.InputTag(trkcoll)
    process.hipredztrkval.trklabel=cms.untracked.InputTag(trkcoll)
    process.hitrackAna.src = cms.untracked.InputTag(trkcoll)  # trkAna
    process.hitrackAna_jetMode1.src = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode2.src = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode3.src = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode4.src = cms.untracked.InputTag(trkcoll)
    process.hitrackAna.src_evtCorr = cms.untracked.InputTag(trkcoll) # event correction
    process.hitrackAna_jetMode1.src_evtCorr = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode2.src_evtCorr = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode3.src_evtCorr = cms.untracked.InputTag(trkcoll)
    process.hitrackAna_jetMode4.src_evtCorr = cms.untracked.InputTag(trkcoll)
    process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag(trkcoll)
    process.higoodtrkval.useQaulityStr = cms.untracked.bool(False) # quality bit
    process.higoodtrkval_pt80.useQaulityStr = cms.untracked.bool(False)
    process.higoodtrkval_fake.useQaulityStr = cms.untracked.bool(False)
    process.higoodtrkval_fake_pt80.useQaulityStr = cms.untracked.bool(False)
    process.hitrkEffAnalyzer.useQaulityStr = cms.untracked.bool(False) 
    process.hitrackAna.setQualityBit = cms.untracked.bool(False) 
    process.hitrackAna_jetMode1.setQualityBit = cms.untracked.bool(False)
    process.hitrackAna_jetMode2.setQualityBit = cms.untracked.bool(False)
    process.hitrackAna_jetMode3.setQualityBit = cms.untracked.bool(False)
    process.hitrackAna_jetMode4.setQualityBit = cms.untracked.bool(False)
    process.hitrkEffAnalyzer.usePxlPair= cms.untracked.bool(True) # use pixel pair as accepted
    return process
    

def runHiTrkRecoForPF(process):
    print "HI tracking reconstruction added in the PF reco sequence"
    print "Also hiPostGlobalPrimDumTracks is added at the beginning" 
    process.rechits *= process.heavyIonTracking
    process.heavyIonTracking *= process.hiextraTrack
    process.trkfilter.src=cms.InputTag("hiPostGlobalPrimDumTracks")
    process.hipfReReco.replace(process.rereco_seq,process.hiPostGlobalPrimDumTracksSelection*process.rereco_seq)
    return process

def runOn384p2(process):
    list = ['HLT_HIMinBiasCalo','HLT_HIJet35U']
    print "runOn384p2 option is enabled (HLT_HIMinBiasCalo and HISIGNAL + spike cleaning removed)!"
    print "hlt list for track analyzer = ",list
    process.eventFilter.remove(process.spikeCleaning)
    process.hltMinBias.HLTPaths=cms.vstring('HLT_HIMinBiasCalo')  # HLT_HIMinBiasBSC is not available
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','HISIGNAL')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','HISIGNAL')
    process.hitrackAna.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.hicaloTrackAna.hltNames = cms.untracked.vstring(list)
    process.hipxltrackAna.hltNames = cms.untracked.vstring(list)
    process.hirefitTrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrkval.useQaulityStr = cms.untracked.bool(True)
    process.hihightrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.hihightrkval_pt80.useQaulityStr = cms.untracked.bool(True)
    process.hihightrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higloosetrkval.useQaulityStr = cms.untracked.bool(True)
    process.higloosetrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.higloosetrkval_pt80.useQaulityStr = cms.untracked.bool(True)
    process.higloosetrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.hipredttrkval.useQaulityStr =cms.untracked.bool(False) # these two tracks do not need quality
    process.hipredttrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.hipredttrkval_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredttrkval_fake_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_fake_pt80.useQaulityStr =cms.untracked.bool(False)
    process.preTrgAna.trignames = cms.untracked.vstring(list)
    process.postTrgAna.trignames = cms.untracked.vstring(list)
    process.postEvtAna.trignames = cms.untracked.vstring(list)
    return process

def runOn395(process):
    list = ['HLT_HIMinBiasHF','HLT_HIJet35U','HLT_HIJet50U']
    print "runOn395 option is enabled (minBiasBscFilter and spike cleaning removed)!"
    print "hlt list for track analyzer = ",list
    process.eventFilter.remove(process.minBiasBscFilter)
    process.eventFilter.remove(process.spikeCleaning)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','HLT')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','HLT')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.higoodlooseAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','HLT')
    process.hitrackAna.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.hitrackAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.higoodlooseAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode1.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode2.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode3.hltNames = cms.untracked.vstring(list)
    process.hihightrackAna_jetMode4.hltNames = cms.untracked.vstring(list)
    process.hicaloTrackAna.hltNames = cms.untracked.vstring(list)
    process.hipxltrackAna.hltNames = cms.untracked.vstring(list)
    process.hirefitTrackAna.hltNames = cms.untracked.vstring(list)
    process.hihightrkval.useQaulityStr = cms.untracked.bool(True)
    process.hihightrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.hihightrkval_pt80.useQaulityStr = cms.untracked.bool(True)
    process.hihightrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higloosetrkval.useQaulityStr = cms.untracked.bool(True)
    process.higloosetrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.higloosetrkval_pt80.useQaulityStr = cms.untracked.bool(True)
    process.higloosetrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_fake.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_pt80.useQaulityStr =cms.untracked.bool(True)
    process.higoodtrkval_fake_pt80.useQaulityStr =cms.untracked.bool(True)
    process.hipredttrkval.useQaulityStr =cms.untracked.bool(False) # these two don't need quality
    process.hipredttrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.hipredttrkval_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredttrkval_fake_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_fake.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_pt80.useQaulityStr =cms.untracked.bool(False)
    process.hipredztrkval_fake_pt80.useQaulityStr =cms.untracked.bool(False)
    process.preTrgAna.trignames = cms.untracked.vstring(list)
    process.postTrgAna.trignames = cms.untracked.vstring(list)
    process.postEvtAna.trignames = cms.untracked.vstring(list)
    return process

def runOn393(process):
    print "runOn393 option is enabled (minBiasBscFilter and spike cleaning removed)!"
    process.eventFilter.remove(process.minBiasBscFilter)
    process.eventFilter.remove(process.spikeCleaning)
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
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
    process.eventFilter.remove(process.spikeCleaning)
    process.eventFilter.remove(process.collisionEventSelection)
    process.primaryVertexFilter.cut=cms.string("!isFake && abs(z) <= 15 && position.Rho <= 2")
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECO')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECO')
    process.preTrgAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.postTrgAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.postEvtAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
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
    process.eventFilter.remove(process.spikeCleaning)
    process.eventFilter.remove(process.collisionEventSelection)
    process.primaryVertexFilter.cut=cms.string("!isFake && abs(z) <= 15 && position.Rho <= 2")
    process.hltMinBias.TriggerResultsTag=cms.InputTag('TriggerResults','','RECOMIX')
    process.hltJets.TriggerResultsTag=cms.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hitrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.higoodlooseAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.higoodlooseAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.higoodlooseAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.higoodlooseAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.higoodlooseAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna_jetMode1.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna_jetMode2.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna_jetMode3.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hihightrackAna_jetMode4.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hicaloTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hipxltrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.hirefitTrackAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.preTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.postTrgAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.postEvtAna.triglabel=cms.untracked.InputTag('TriggerResults','','RECOMIX')
    process.preTrgAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.postTrgAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.postEvtAna.gtrklabel=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hitrackAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.hitrackAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.higoodlooseAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.higoodlooseAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode1.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode1.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode2.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode2.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode3.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode3.gjsrc=cms.untracked.InputTag("ak5GenJets")
    process.hihightrackAna_jetMode4.gsrc=cms.untracked.InputTag("genParticles")
    process.hihightrackAna_jetMode4.gjsrc=cms.untracked.InputTag("ak5GenJets")
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
    process.hiHighPtCaloTracks.src = cms.InputTag("hiSelectedTracks")
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
    process.spikeCleaning *= process.jetEvtFilter
    print "Jet eta cut cleaning added!"
    print "Skim jet HLT path: ", process.hltJets.HLTPaths, "and minBiasBscFilter: ", process.minBiasBscFilter
    #print "Spike cleaning added"
    if hltname.find('Jet35U') >= 0:
        jetcut1=[80,100]
        jetcut2=[100,120]
        print "Jet Et cuts on spectra analyzer: cut 1 = ", jetcut1, " cut 2 = ", jetcut2
        #print "Also added: cut 3 = ",process.hitrackAna_jetMode3.jetEtCuts
        process.hitrackAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.hitrackAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
        process.higoodlooseAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.higoodlooseAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
        process.hihightrackAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.hihightrackAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
        process.hiAnalysisSeq.replace(process.hitrackAna_jetMode2,process.hitrackAna_jetMode2
                                      +process.hitrackAna_jetMode3+process.hitrackAna_jetMode4)
        process.hiAnalysisSeq.replace(process.higoodlooseAna_jetMode2,process.higoodlooseAna_jetMode2
                                      +process.higoodlooseAna_jetMode3+process.higoodlooseAna_jetMode4)
        process.hiAnalysisSeq.replace(process.hihightrackAna_jetMode2,process.hihightrackAna_jetMode2
                                      +process.hihightrackAna_jetMode3+process.hihightrackAna_jetMode4)
    if hltname.find('Jet50U') >= 0:
        jetcut1=[100,9000]
        jetcut2=[120,9000]
        print "Jet Et cuts on spectra analyzer: cut 1 = ", jetcut1, " cut 2 = ", jetcut2
        process.hitrackAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.hitrackAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
        process.higoodlooseAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.higoodlooseAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
        process.hihightrackAna_jetMode1.jetEtCuts=cms.untracked.vdouble(jetcut1)
        process.hihightrackAna_jetMode2.jetEtCuts=cms.untracked.vdouble(jetcut2)
    return process
                            

def usehiGoodMergedTracks(process):
    print "hiGoodMergedTracks is used (except PF re-reco)! --> re-reco of conformalPixelTrackReco!"
    print "make sure disableLowPt comes before usehiGoodMergedTracks"
    #process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiSelectedTracks")
    process.hiHighPtCaloTracks.src = cms.InputTag("hiGoodMergedTracks")
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
    #process.pfCandidateAnalyzer.ptMin = cms.untracked.double(minpt)
    #process.pfCandidateAnalyzer_test.ptMin = cms.untracked.double(minpt)
    process.hiHighPtCaloTracks.ptMin = cms.untracked.double(minpt)
    process.hiGoodTightCaloTracks.ptMin = cms.untracked.double(minpt)
    process.hiGoodLooseCaloTracks.ptMin= cms.untracked.double(minpt)
    process.hiPreDTGoodTightCaloTracks.ptMin= cms.untracked.double(minpt)
    process.hiPreDZGoodTightCaloTracks.ptMin= cms.untracked.double(minpt)
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
        # 0~5,5~10,10~30,30~50,50~60,60~70,70~80,80~90
        cbins=[0,1,3,11,19,23,27,31,35]
        print "Centrality bins = ", cbins
    if cbinMode==4 :
        cbins=[0,1,3,11,19,27,39]
        print "Centrality bins = ", cbins
    process.hitrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrackAna_jetMode1.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrackAna_jetMode2.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrackAna_jetMode3.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrackAna_jetMode4.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodlooseAna.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodlooseAna_jetMode1.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodlooseAna_jetMode2.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodlooseAna_jetMode3.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodlooseAna_jetMode4.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna_jetMode1.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna_jetMode2.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna_jetMode3.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrackAna_jetMode4.neededCentBins = cms.untracked.vint32(cbins)
    process.hicaloTrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hipxltrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hirefitTrackAna.neededCentBins = cms.untracked.vint32(cbins)
    process.hitrkEffAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrkEffAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
    process.higloosetrkEffAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
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
    process.hihightrkval.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrkval_fake.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrkval_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.hihightrkval_fake_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.higloosetrkval.neededCentBins = cms.untracked.vint32(cbins)
    process.higloosetrkval_fake.neededCentBins = cms.untracked.vint32(cbins)
    process.higloosetrkval_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.higloosetrkval_fake_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodtrkval.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodtrkval_fake.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodtrkval_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.higoodtrkval_fake_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredttrkval.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredttrkval_fake.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredttrkval_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredttrkval_fake_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredztrkval.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredztrkval_fake.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredztrkval_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.hipredztrkval_fake_pt80.neededCentBins = cms.untracked.vint32(cbins)
    process.pfCandidateAnalyzer.neededCentBins = cms.untracked.vint32(cbins)
    process.pfCandidateAnalyzer_test.neededCentBins = cms.untracked.vint32(cbins)
    process.pfCandidateAnalyzer_higtight.neededCentBins = cms.untracked.vint32(cbins)
    process.pfCandidateAnalyzer_higloose.neededCentBins = cms.untracked.vint32(cbins)
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
    process.higloosetrkEffAnalyzer.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode1.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode2.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode3.trkAcceptedJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode4.trkAcceptedJet = cms.untracked.bool(True)
    process.higoodlooseAna.trkAcceptedJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode1.trkAcceptedJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode2.trkAcceptedJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode3.trkAcceptedJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode4.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode1.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode2.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode3.trkAcceptedJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode4.trkAcceptedJet = cms.untracked.bool(True)
    process.hicaloTrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hipxltrackAna.trkAcceptedJet = cms.untracked.bool(True)
    process.hirefitTrackAna.trkAcceptedJet = cms.untracked.bool(True)
    return process

def useSubLeadingJet(process):
    print "Sub-leading jet is used in event classificaiton !"
    process.hitrkEffAnalyzer.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrkEffAnalyzer.useSubLeadingJet = cms.untracked.bool(True)
    process.higloosetrkEffAnalyzer.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode1.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode2.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode3.useSubLeadingJet = cms.untracked.bool(True)
    process.hitrackAna_jetMode4.useSubLeadingJet = cms.untracked.bool(True)
    process.higoodlooseAna.useSubLeadingJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode1.useSubLeadingJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode2.useSubLeadingJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode3.useSubLeadingJet = cms.untracked.bool(True)
    process.higoodlooseAna_jetMode4.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode1.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode2.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode3.useSubLeadingJet = cms.untracked.bool(True)
    process.hihightrackAna_jetMode4.useSubLeadingJet = cms.untracked.bool(True)
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
