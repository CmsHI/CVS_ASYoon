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
options.register('centRange',
                 "ALL", # 0To10, 50To100, and etc 
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Centrality bin range")

# get and parse the command line arguments
options.parseArguments()


# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/data/spectra/firsthi2010/test/r150476_443DCAFD-33EC-DF11-9F03-003048D2C0F2.root')
  fileNames = cms.untracked.vstring('/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/076/328420FD-4FF0-DF11-B358-001D09F241B9.root')
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
        version = cms.untracked.string('$Revision: 1.5 $'),
            name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkAnaSkim_data_2760GeV_cfg.py,v $'),
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
process.load("Saved.DiJetAna.ExtraReco_cff")
process.load("Saved.DiJetAna.dijetAna_cff")

from Saved.DiJetAna.customise_cfi import *
enableRECO(process,"Data","HI")
enableData(process)
process.hiAnalysisSeq *= process.djcalo

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraReco_step   = cms.Path(process.eventFilter * (process.hiextraReco + process.hipfReReco))
process.extraJets_step  = cms.Path(process.eventFilter * process.dj_reco_extra)
process.extraTrks_step   = cms.Path(process.eventFilter * process.hiextraTrack)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)


# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead 
process = disableLowPt(process) # disable low pt pixel
process = setAnaSeq(process,"AnaOnly") # EffOnly, AnaOnly, ALL
process = whichCentBins(process,options.centRange) # centrality range
process = setMinPtforPF(process,100) # min pt for PF reco/ana

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
    process.ana_step
    )

#process.schedule.append(process.output_step) 
