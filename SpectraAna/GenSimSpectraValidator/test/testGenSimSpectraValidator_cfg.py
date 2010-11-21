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

# =============== 2.76 TeV MC Sample =====================
process.source = cms.Source("PoolSource",
       fileNames = cms.untracked.vstring('file:/home/sungho/sctch101/mc/firsthi2010/hiReco_RAW2DIGI_RECO_55_1_txh.root')
       )


# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'START39_V4HI::All'

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('gensimval.root')
                                   )

# =============== Import Sequences =====================
process.load("SpectraAna.GenSimSpectraValidator.gensimspectravalidator_cfi")

# =============== Final Paths ==========================
process.ana_step = cms.Path(process.gensimSpectraValidator)


# =============== Schedule =============================
process.schedule = cms.Schedule(process.ana_step)
