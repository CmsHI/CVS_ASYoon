import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("ANASKIM")

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

# =============== debugging if needed ===================

# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
   #fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/mc/firsthi2010/hydjet_393_start39_v7hi_D42A5DEB.root')
   fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/mc/firsthi2010/hiReco_RAW2DIGI_RECO_UQ_Dijet80_395.root')
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(20))
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
        version = cms.untracked.string('$Revision: 1.3 $'),
            name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkRePFRecoAnaSkim_mc_2760GeV_cfg_399.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsMC.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")


## Fixes to protect against large BS displacements (re-reco setup with PR)
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.fixedError = 0.5
process.hiSelectedProtoTracks.maxD0Significance = 100
process.hiPixelAdaptiveVertex.TkFilterParameters.maxD0Significance = 100
process.hiPixelAdaptiveVertex.useBeamConstraint = False
process.hiPixelAdaptiveVertex.PVSelParameters.maxDistanceToBeam = 1.0


# =============== Pat jet in HI ========================
process.load("Saved.QM11Ana.PatAna_cff")
process.load("Saved.QM11Ana.Analyzers_cff")

# =============== Final Paths =====================
process.reReco_step      = cms.Path(process.siPixelRecHits * process.hiPixelVertices * process.heavyIonTracking)
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraTrks_step   = cms.Path(process.eventFilter * process.hiextraTrack)
process.extraReco_step   = cms.Path(process.eventFilter * process.hipfReReco)
process.extraCalo_step   = cms.Path(process.eventFilter * process.hicaloTrack)
process.extraJets_step   = cms.Path(process.eventFilter * process.genPartons * process.hiPartons * process.icPu5patSequence)
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
process = runOn393(process)
process = whichCentBinMode(process,options.centBins) # centrality binning
#process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet
process = setMinPtforPF(process,10) # min pt for PF reco/ana
process = disableValidator(process) # remove validator for fake tracks

# as these are not needed
process.heavyIonTracking.remove(process.hiConformalPixelTracks)
process.heavyIonTracking.remove(process.hiGoodMergedTracks)


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
    process.extraTrks_step, # extra track collections
    process.extraReco_step, # PF + calo-compatible tracks
    process.extraCalo_step, # extrak track with calo-trk compatibility
    process.extraJets_step,
    process.ana_step
    )

#process.schedule.append(process.output_step)

