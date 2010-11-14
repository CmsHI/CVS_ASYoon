import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os


process = cms.Process("RERECOSKIM")


process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration/StandardSequences/ReconstructionHeavyIons_cff')
process.load("RecoHI.Configuration.Reconstruction_hiPF_cff")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# ============= pre-setting ============================


# =============== 2.76 TeV MC Sample =====================
process.source = cms.Source ("PoolSource",
       skipEvents = cms.untracked.uint32(50),
       fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/mc/firsthi2010/hiReco_RAW2DIGI_RECODEBUG_55_1_txh.root'),
       secondaryFileNames = cms.untracked.vstring(),
       noEventSort = cms.untracked.bool(True),
       duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
)

# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.GlobalTag.globaltag = 'START39_V4HI::All'

#process.Timing = cms.Service("Timing")

# ntuple output
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string('trkcalohistMC.root')
                                   )


# =============== Import Sequences ===================== 
process.load("FirstHi2010.PbPbSpectraAna.HiPFRereco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("edwenger.HiTrkEffAnalyzer.hipfCandAnalyzer_cff")

# =============== Final Paths ==========================
process.eventFilter_step = cms.Path(process.eventFilter)
process.anaFilter_step = cms.Path(process.rereco_seq)
process.rereco_step = cms.Path(process.rereco_seq *
                               process.hipfCandAnalyzer)

# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
process = eventFilterRereco(process)
process = enableREDIGI(process) # to run on redigitized

# =============== Output ================================
process.load("FirstHi2010.PbPbSpectraAna.hiPFRerecoSkimContent_cff")

process.output = cms.OutputModule("PoolOutputModule",
    process.PFRerecoSkimContent,
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
    dataset = cms.untracked.PSet(
      dataTier = cms.untracked.string('AODSIM'),
      filterName = cms.untracked.string('TrkAnaFilter')),
    fileName = cms.untracked.string('trkAnaRerecoSkim.root')
)

process.output_step = cms.EndPath(process.output) 

# =============== Schedule =====================

process.schedule = cms.Schedule(process.eventFilter_step,
                                process.anaFilter_step,
                                process.rereco_step
                                )

#process.schedule.append(process.output_step)
