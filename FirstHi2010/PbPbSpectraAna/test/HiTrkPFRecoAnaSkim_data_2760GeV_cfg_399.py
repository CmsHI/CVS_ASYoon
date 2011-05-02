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


# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/data/spectra/firsthi2010/test/r150476_443DCAFD-33EC-DF11-9F03-003048D2C0F2.root')
  fileNames = cms.untracked.vstring('/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/076/328420FD-4FF0-DF11-B358-001D09F241B9.root')
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(50))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.GlobalTag.globaltag = 'GR10_P_V12::All' # CorePhysics prompt reco: GR10_X_V12::All (X=E, P, H)
process.GlobalTag.globaltag = 'GR_R_39X_V6B::All' # AllPhysics rereco

# Needed for Centrality Table
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
)
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.4 $'),
            name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkAnaSkim_data_2760GeV_cfg_399.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsDATA.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")

## Fixes to protect against large BS displacements (re-reco setup with PR)
## (this is needed since PF reco requires HI tracking on the floy)
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2
process.hiPixel3ProtoTracks.RegionFactoryPSet.RegionPSet.fixedError = 0.5
process.hiSelectedProtoTracks.maxD0Significance = 100
process.hiPixelAdaptiveVertex.TkFilterParameters.maxD0Significance = 100
process.hiPixelAdaptiveVertex.useBeamConstraint = False
process.hiPixelAdaptiveVertex.PVSelParameters.maxDistanceToBeam = 1.0


# =============== Pat jet in HI ========================
process.load("Saved.QM11Ana.PatAna_cff")
process.load("Saved.QM11Ana.Analyzers_cff")
process.inclusiveJetAnalyzer.isMC = False
process.inclusiveJetAnalyzer.hltTrgNames = ['HLT_HIMinBiasHfOrBSC','HLT_HIJet35U', 'HLT_HIJet35U','HLT_HIJet50U'] # for allphysics
#process.hiAnalysisSeq *= process.inclusiveJetAnalyzer

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraReco_step   = cms.Path(process.eventFilter * process.hipfReReco)
process.extraTrks_step   = cms.Path(process.eventFilter * process.hiextraTrack)
process.extraCalo_step   = cms.Path(process.eventFilter * process.hicaloTrack)
process.extraJets_step  = cms.Path(process.eventFilter  * process.icPu5patSequence_data)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)


# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = runOnCore(process) # to run on core, not needed if below is on
#process = enableHLTJet(process,"HLT_HIJet35U")
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead 
process = disableLowPt(process) # disable low pt pixel
#process = usehiGoodMergedTracks(process) # use hiGoodMergedTracks instead
process = setAnaSeq(process,"AnaOnly") # EffOnly, AnaOnly, ALL
process = whichCentBinMode(process,options.centBins) # centrality binning
process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet
process = setMinPtforPF(process,10) # min pt for PF reco/ana
process = disableValidator(process) # remove validator for faketracks
process = runHiTrkRecoForPF(process) # HI Trk reco added for PF

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
#      dataTier = cms.untracked.string('AODSIM'),
#      filterName = cms.untracked.string('TrkAnaFilter')),
#    fileName = cms.untracked.string('trkAnaSkimAODSIM_test.root')
#)

#process.output_step = cms.EndPath(process.output)

# =============== Schedule =====================

process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.extraReco_step,
    process.extraJets_step,
    process.extraTrks_step,
    process.extraCalo_step,
    process.ana_step
    )

#process.schedule.append(process.output_step) 
