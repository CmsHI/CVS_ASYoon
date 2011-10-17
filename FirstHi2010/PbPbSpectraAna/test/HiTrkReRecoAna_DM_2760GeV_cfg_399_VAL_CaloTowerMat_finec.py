import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

#============= variable parsing ========================
ivars = VarParsing.VarParsing('standard')
ivars.register('initialEvent',mult=ivars.multiplicity.singleton,info="for testing")
#ivars.files ="dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Bass_MinBias_2760GeV/Pyquen_UnquenchedDiJet_Pt80_GEN-SIM-RECO_393_set1/fae6fe9048513d9ac8f476dd10ba6ba7/hiReco_RAW2DIGI_RECO_99_1_UX4.root"
ivars.files = "dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yetkin/mix/pythia170_HICorePhysics_MinBiasSkim_440_test28_DBS_evt20_test01/MinBias_PreMix_202_1_skd_numEvent20.root"
ivars.output = 'trkhists.root'
ivars.maxEvents = 3
ivars.initialEvent = 1

ivars.parseArguments()


#============= actual configuration ====================   
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

# get and parse the command line arguments
options.parseArguments()

# =============== debugging if needed ===================

# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring(ivars.files)
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(ivars.maxEvents))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'START39_V7HI::All' 

# Needed for Centrality Table
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("Hydjet_2760GeV")  # use AMPT_2760GeV for AMPT
)
from CmsHi.Analysis2010.CommonFunctions_cff import *
#overrideCentrality(process)

process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.5 $'),
            name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkReRecoAna_mc_2760GeV_cfg_399_CaloTowerMat.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(ivars.output)
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
    process.trackCollectionMerging *
    #process.globalPrimTrackCollectionMerging * # not needed
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
process.trackerDrivenElectronSeeds.TkColList = cms.VInputTag("hiGeneralGlobalPrimTracks")
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

# algo selection (algo = 4, i.e. only first iteration)
process.hiOptimalTightTracks1stIter = cms.EDFilter("TrackSelector",
        src = cms.InputTag("hiOptimalTightTracks"),
        cut = cms.string('algo==4')
)

process.ptDeptOptCalo_seq = cms.Sequence(
    process.hiOptCaloPreFst *
    process.hiOptCaloFst *
    process.hiOptCaloPreSnd *
    process.hiOptCaloSnd *
    process.hiOptimalTightTracks *
    process.hiOptimalTightTracks1stIter
    )

# =============== Pat jet in HI ========================
process.load("Saved.QM11Ana.PatAna_cff") # something overlap with PF reco
process.load("Saved.QM11Ana.Analyzers_cff")

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.reReco_step      = cms.Path(process.eventFilter * process.iterTracking_seq)
process.extraTrks_step   = cms.Path(process.eventFilter * process.ptDeptOptCalo_seq)
process.extraJets_step  = cms.Path(process.eventFilter * process.genPartons * process.hiPartons * process.icPu5patSequence)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq )


# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = enableHLTJet(process,"HLT_HIJet50U")
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead
process = enableSIM(process)    # activate isGEN in analyzers
process = disableLowPt(process) # disable low pt pixel
process = disableJetEtCutOnAna(process) # remove trackAna with jet Et cuts
#process = usehiGoodMergedTracks(process) # use hiGoodMergedTracks instead 
process = setAnaSeq(process,"ALL") # EffOnly, AnaOnly, ALL
#process = enableREDIGI(process) # to run on redigitized 
#process = runOn393(process)
process = runOn440DataMixMC(process)
process = whichCentBinMode(process,options.centBins) # centrality binning
#process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet
#process = runWithIterTrk(process,"hiGeneralCaloTracks") # use trk coll. from iterative trk
#process = runWithIterTrk(process,"hiOptCaloFst")
#process = runWithIterTrk(process,"hiOptCaloSnd")
process = runWithIterTrk(process,"hiOptimalTightTracks") 
process = runWithLightCfg(process)

# ============== Customization ==========================
process.hiAnalysisSeq.remove(process.higoodtrkval_fakeOnly)
process.hiAnalysisSeq.remove(process.higloosetrkval_fakeOnly)
process.hiAnalysisSeq.remove(process.hihightrkval_fakeOnly)
process.hiAnalysisSeq.remove(process.hipredttrkval_fakeOnly)
process.hiAnalysisSeq.remove(process.higloosetrkEffAna)

# to run hihightrkEffAnalyzer with 1st iteration of hiOptimalTightTracks
process.hihightrkEffAnalyzer.tracks = cms.untracked.InputTag("hiOptimalTightTracks1stIter")
process.hihightrkEffAnalyzer.usePxlPair= cms.untracked.bool(True)
process.hihightrkEffAnalyzer.useQaulityStr = cms.untracked.bool(False)

# =============== Output ================================
#process.load("FirstHi2010.PbPbSpectraAna.hianalysisSkimContent_cff")

#process.output = cms.OutputModule("PoolOutputModule",
#    #process.analysisSkimContent,
#    outputCommands = cms.untracked.vstring('keep *'),
#    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
#    dataset = cms.untracked.PSet(
#    dataTier = cms.untracked.string('AODSIM'),
#    filterName = cms.untracked.string('TrkAnaFilter')),
#    fileName = cms.untracked.string('trkAnaSkimAODSIM.root')
#)

#process.output_step = cms.EndPath(process.output)

# =============== Schedule =====================

process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.reReco_step,  # re-reconstruction with PR setup
    process.extraTrks_step,
    process.extraJets_step,
    process.ana_step
    )

#process.schedule.append(process.output_step)

