import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("SKIM")

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
                 0, # by default
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Centrality binning scenario")


# get and parse the command line arguments
options.parseArguments()


# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/data/spectra/firsthi2010/test/328420FD-4FF0-DF11-B358-001D09F241B9.root')
  #fileNames = cms.untracked.vstring('/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/076/328420FD-4FF0-DF11-B358-001D09F241B9.root')
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
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
        version = cms.untracked.string('$Revision: 1.1 $'),
            name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiItrTrkRerecoAnaSkim_data_2760GeV_cfg.py,v $'),
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
    process.globalPrimTrackCollectionMerging * # hiGeneralGlobalPrimTracks
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
#process.load("FirstHi2010.PbPbSpectraAna.HiTrackSelection_cff")
#process.hiGeneralDerivedTracks = process.hiGoodTightTracks.clone(src = cms.InputTag("hiGeneralHybridTracks"))
#process.hiGeneralCaloTracks.src=cms.InputTag("hiGeneralHybridTracks") # everything is derived from Hybrid
#process.hiGeneralCaloHybridTracks = process.hiGeneralCaloTracks.clone()

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
process.reReco_step      = cms.Path(process.eventFilter * process.iterTracking_seq * process.HiParticleFlowRecoNoJets)
process.extraJets_step  = cms.Path(process.eventFilter  * process.dj_reco_extra)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)


# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
process = runOnCore(process) # to run on core, not needed if below is on
#process = enableHLTJet(process,"HLT_HIJet35U_Core")
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead 
process = disableLowPt(process) # disable low pt pixel
#process = usehiGoodMergedTracks(process) # use hiGoodMergedTracks instead
process = setAnaSeq(process,"AnaOnly") # EffOnly, AnaOnly, ALL
process = whichCentBinMode(process,options.centBins) # centrality binning
process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet
#process = setMinPtforPF(process,200) # min pt for PF reco/ana
process = runWithIterTrk(process,"hiGeneralCaloTracks") # use trk coll. from iterative trk
process = runWithLightCfg(process) # light cfg option

# =============== Output ================================
process.load("FirstHi2010.PbPbSpectraAna.hianalysisSkimContentIter_cff")

process.output = cms.OutputModule("PoolOutputModule",
    process.analysisSkimContent,
    #outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AODSIM'),
      filterName = cms.untracked.string('TrkAnaFilter')),
    fileName = cms.untracked.string('trkAnaSkimAODSIM.root')
)

process.output_step = cms.EndPath(process.output)

# =============== Schedule =====================

process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.reReco_step,  # re-reconstruction with PR setup
    process.extraJets_step
    )

process.schedule.append(process.output_step) 
