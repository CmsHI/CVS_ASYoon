import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("ANASKIM")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

# ============= pre-setting ============================
# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# my own variable
options.register('centRange',
                 "0To10", 
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Centrality bin range")

# get and parse the command line arguments
options.parseArguments()


# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v2/000/150/436/E076DB87-BEEB-DF11-BAA0-0019B9F70468.root')
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
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
            name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkAnaSkim_mc_2760GeV_cfg.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsDATA.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")


# =============== Pat jet in HI ========================
from Saved.DiJetAna.customise_cfi import *
enableRECO(process,"Data","HI")

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraReco_step   = cms.Path(process.eventFilter*(process.hiextraReco + process.reco_extra))
process.ana_step         = cms.Path(process.eventFilter*process.hiAnalysisSeq)

# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = enableSIM(process)    # activate isGEN in analyzers
process = disableLowPt(process) # disable low pt pixel
process = setAnaSeq(process,"AnaOnly") # EffOnly, AnaOnly, ALL
#process = enableREDIGI(process) # to run on redigitized 
process = whichCentBins(process,options.centRange)

# =============== Output ================================
process.load("FirstHi2010.PbPbSpectraAna.hianalysisSkimContent_cff")

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
    process.ana_step,
    #process.output_step,
    )
