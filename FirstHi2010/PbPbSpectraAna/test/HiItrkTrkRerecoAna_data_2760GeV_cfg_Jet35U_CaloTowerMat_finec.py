import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("ANA")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration/EventContent/EventContent_cff')

# ============= pre-setting ============================
# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# my own variable
options.register('centBins',
                 1, # by default
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Centrality binning scenario")

centbins=[0,1,3,11,19,27,35] # make sure this is consistent with above

# get and parse the command line arguments
options.parseArguments()


# =============== 2.76 TeV MC Sample =====================
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/data/spectra/firsthi2010/test/328420FD-4FF0-DF11-B358-001D09F241B9.root')
)                            


# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(200))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR10_P_V12::All' # GR10_X_V12::All (X=E, P, H)

# Needed for Centrality Table
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
)
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.configurationMetadata = cms.untracked.PSet(
  version = cms.untracked.string('$Revision: 1.2 $'),
  name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiItrTrkRerecoAna_data_2760GeV_cfg_VAL_MB_CaloTowerMat.py,v $'),
  annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
  )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsDATA.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")


# Matt's iterative tracking and PF
process.load('CmsHi.JetAnalysis.ExtraPfReco_cff')
process.load('CmsHi.JetAnalysis.ExtraTrackReco_cff')
process.load("RecoHI.HiTracking.secondStep_cff")  # pair-seeded step
process.load("MNguyen.iterTracking.TrackSelections_cff")
process.hiGoodTightTracks.keepAllTracks = False
process.load("MNguyen.iterTracking.secondStep_triplet_cff")
process.load("MNguyen.iterTracking.thirdStep_pairs_cff")
process.load("MNguyen.iterTracking.MergeTrackCollectionsHI_cff")
process.hiNewClusters.Strip.maxSize = cms.uint32(2)

process.iterGlobalPrimTracks = process.iterTracks.clone(
        TrackProducer1 = 'hiScndGlobalPrimTracks',
        TrackProducer2 = 'hiThrdGlobalPrimTracks',
        )

process.hiGeneralGlobalPrimTracks = process.hiGeneralTracks.clone(
    TrackProducer1 = 'hiGlobalPrimTracks',
    TrackProducer2 = 'iterGlobalPrimTracks',
    )

process.hiGeneralHybridTracks = process.hiGeneralGlobalPrimTracks.clone(
    TrackProducer1 = 'hiGlobalPrimTracks',
    TrackProducer2 = 'iterTracks',
    )

process.globalPrimTrackCollectionMerging = cms.Sequence(
    process.iterGlobalPrimTracks*
    process.hiGeneralGlobalPrimTracks 
    )

# hiGlobalPrim (1st) + hiGeneral (2nd+3rd)
process.hybridTrackCollectionMerging = cms.Sequence(
    process.hiGeneralHybridTracks # hiGlobal
)   

process.iterTracking_seq = cms.Sequence(
    process.hiTrackReReco *
    process.hiGoodTightTracks *
    process.secondStep *
    process.thirdStep *
    #process.globalPrimTrackCollectionMerging * # hiGeneralGlobalPrimTracks
    process.trackCollectionMerging *  # hiGeneralTracks
    process.hybridTrackCollectionMerging # hiGeneral + hiGlobal
)

## Fixes to protect against large BS displacements (re-reco setup with PR)
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.fixedError = 0.5
process.hiSelectedProtoTracks.maxD0Significance = 100
process.hiPixelAdaptiveVertex.TkFilterParameters.maxD0Significance = 100
process.hiPixelAdaptiveVertex.useBeamConstraint = False
process.hiPixelAdaptiveVertex.PVSelParameters.maxDistanceToBeam = 1.0


# PF
process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiGeneralTracks")
process.trackerDrivenElectronSeeds.UseQuality = cms.bool(False)
process.HiParticleFlowRecoNoJets.remove(process.PFTowers) # not needed and in conflict


# Calo compatible tracks
process.load("FirstHi2010.PbPbSpectraAna.HiTrackSelection_cff")
process.hiOptCaloFst = process.hiLooseTracks.clone(src = cms.InputTag("hiOptCaloPreFst"))
process.hiOptCaloSnd = process.hiGoodTightTracks.clone(src = cms.InputTag("hiOptCaloPreSnd"))

process.hiOptimalTightTracks  = process.hiGeneralTracks.clone(
    ShareFrac = cms.double(999.0), # since two collections have no track in common
    TrackProducer1 = 'hiOptCaloFst',
    TrackProducer2 = 'hiOptCaloSnd',
)

# algo selection (algo = 0, i.e. only first iteration)
process.hiOptimalTightTracks1stIter = cms.EDFilter("TrackSelector",
     src = cms.InputTag("hiOptimalTightTracks"),
     cut = cms.string('algo==0')
)

process.ptDeptOptCalo_seq = cms.Sequence(
    process.hiOptCaloPreFst *
    process.hiOptCaloFst *
    process.hiOptCaloPreSnd *
    process.hiOptCaloSnd *
    process.hiOptimalTightTracks 
)

## Fixes to protect against large BS displacements (re-reco setup with PR)
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.fixedError = 0.5
process.hiSelectedProtoTracks.maxD0Significance = 100
process.hiPixelAdaptiveVertex.TkFilterParameters.maxD0Significance = 100
process.hiPixelAdaptiveVertex.useBeamConstraint = False
process.hiPixelAdaptiveVertex.PVSelParameters.maxDistanceToBeam = 1.0

# Track Matching Analyzer
process.load("PbPbTrackingTools.HiTrackMatchingAnalyzer.hitrkMatchAnalyzer_cfi")
process.hitrkMatchAnalyzer.trkFst = cms.untracked.InputTag('hiOptimalTightTracks')
process.hitrkMatchAnalyzer.trkSnd = cms.untracked.InputTag('hiGoodTightTracks')
process.hitrkMatchAnalyzer.needTree = cms.untracked.bool(True)
process.hitrkMatchAnalyzer.ptMinTree = cms.untracked.double(40) # only for pT>40  
process.hitrkMatchAnalyzer.checkHitMat = cms.untracked.bool(False)
process.hitrkMatchAnalyzer.needClusterAna = cms.untracked.bool(False)
process.hitrkMatchAnalyzer.neededCentBins = cms.untracked.vint32(centbins)

# =============== Pat jet in HI ========================
process.load("Saved.DiJetAna.ExtraReco_cff")
process.load("Saved.DiJetAna.dijetAna_cff")

from Saved.DiJetAna.customise_cfi import *
enableRECO(process,"Data","HI")
enableData(process)
process.djcalo.verbosity = 1
process.dj_reco_extra.remove(process.hiGoodTracksSelection) # this is unnecessary 

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.reReco_step      = cms.Path(process.eventFilter * process.iterTracking_seq)
process.extraTrks_step   = cms.Path(process.eventFilter * process.ptDeptOptCalo_seq)
process.extraJets_step  = cms.Path(process.eventFilter  * process.dj_reco_extra)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)

# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = runOnCore(process) # to run on core, not needed if below is on
process = enableHLTJet(process,"HLT_HIJet35U_Core")
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead 
process = disableLowPt(process) # disable low pt pixel
#process = usehiGoodMergedTracks(process) # use hiGoodMergedTracks instead
process = setAnaSeq(process,"AnaOnly") # EffOnly, AnaOnly, ALL
process = whichCentBinMode(process,options.centBins) # centrality binning
process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet
#process = setMinPtforPF(process,200) # min pt for PF reco/ana
process = runWithIterTrk(process,"hiOptimalTightTracks") # use trk coll. from iterative trk
process = runWithLightCfg(process) # light cfg option

# Additon of ana path (hiGoodTight)
process.hitrackAnaSnd = process.hitrackAna.clone(src = cms.untracked.InputTag("hiGoodTightTracks"),
                                                 src_evtCorr = cms.untracked.InputTag("hiGoodTightTracks"),
                                                 neededCentBins = cms.untracked.vint32(centbins))
process.hitrackAnaSnd_jetMode1 = process.hitrackAna_jetMode1.clone(src = cms.untracked.InputTag("hiGoodTightTracks"),
                                                                   src_evtCorr = cms.untracked.InputTag("hiGoodTightTracks"),
                                                                   neededCentBins = cms.untracked.vint32(centbins))
process.hitrackAnaSnd_jetMode2 = process.hitrackAna_jetMode2.clone(src = cms.untracked.InputTag("hiGoodTightTracks"),
                                                                   src_evtCorr = cms.untracked.InputTag("hiGoodTightTracks"),
                                                                   neededCentBins = cms.untracked.vint32(centbins))

process.ana_step_extra = cms.Path(process.eventFilter*
                                  (process.hitrackAnaSnd
                                   + process.hitrackAnaSnd_jetMode1
                                   + process.hitrackAnaSnd_jetMode2)* process.hitrkMatchAnalyzer)


# =============== Output ================================
#process.load("FirstHi2010.PbPbSpectraAna.hianalysisSkimContentIter_cff")

#process.output = cms.OutputModule("PoolOutputModule",
#    process.analysisSkimContent,
#    #outputCommands = cms.untracked.vstring('keep *'),
#    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
#    dataset = cms.untracked.PSet(
#      dataTier = cms.untracked.string('AODSIM'),
#      filterName = cms.untracked.string('TrkAnaFilter')),
#    fileName = cms.untracked.string(ivars.output)
#)

#process.output_step = cms.EndPath(process.output)

# =============== Schedule =====================

process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.reReco_step,  # re-reconstruction with PR setup
    process.extraTrks_step,
    process.extraJets_step,
    process.ana_step,
    process.ana_step_extra
    )

#process.schedule.append(process.output_step) 
