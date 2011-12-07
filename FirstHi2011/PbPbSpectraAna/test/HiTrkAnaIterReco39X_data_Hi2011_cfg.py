#-----------------------------------------------------------------
# cfg- to produce hiOptimalTightTracks in old way (i.e 39X)
# and run the analyzers on this track - Andre Yoon (Dec 06 2011)
#-----------------------------------------------------------------

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
                 1, # finer bin by default
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Centrality binning scenario")

# get and parse the command line arguments
options.parseArguments()

# =============== debugging if needed ===================

# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('file:/d01/y_alive/spectra/data/test/HIRun2011_hiHighPt_PromptSkim_v1_5842602B.root') # high pt skim
  #fileNames = cms.untracked.vstring('file:/d01/y_alive/spectra/data/test/hirun2011_hihighpt_prv1_r181950_fc02.root') # high pt prv1
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(120))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR_R_44_V10::All'

# Centrality 
from CmsHi.Analysis2010.CommonFunctions_cff import *
#overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFtowers"),
    nonDefaultGlauberModel = cms.string(""),
    centralitySrc = cms.InputTag("hiCentrality")
    )

process.configurationMetadata = cms.untracked.PSet(
 version = cms.untracked.string('$Revision: 1.2 $'),
 name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2011/PbPbSpectraAna/test/HiTrkAnaIterReco39X_mc_Hi2011_cfg.py,v $'),
 annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsDATA.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2011.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2011.PbPbSpectraAna.HiExtraReco39X_cff")
process.load("FirstHi2011.PbPbSpectraAna.HiAnalysis_cff")
process.load("FirstHi2011.PbPbSpectraAna.HiIterTracking39X_cff")

# =============== Pat Jet ==========================
process.load('CmsHi.JetAnalysis.PatAna_cff')

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraJets_step   = cms.Path(process.eventFilter * process.icPu5patSequence_data)
process.iterTrack_step   = cms.Path(process.eventFilter * process.iterTracking39X_seq)
process.extraTrks_step   = cms.Path(process.eventFilter * process.hiOptTrack39X) 
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)

# =============== Customization =======================
from FirstHi2011.PbPbSpectraAna.hicustomise_cfi import *
from CmsHi.JetAnalysis.customise_cfi import *
enableDataPat(process) # Pat jet for Data
enableHLTJet(process,"HLT_HIJet80_v1") # HLT and jet ET range customize
setAnaSeq(process,"AnaOnly")   # EffOnly, AnaOnly, ALL
constraintOnLJetEta(process)               # constraint on leading jet eta
whichCentBinMode(process,options.centBins) # centrality binning
whichTrackCollection(process,"hiOptimalTightTracks") # input track collection for main ana


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
    process.extraJets_step,
    process.iterTrack_step,
    process.extraTrks_step,
    process.ana_step
    )

#process.schedule.append(process.output_step)

