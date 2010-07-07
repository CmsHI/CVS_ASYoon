import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

# =============== 7 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
    '/store/mc/Spring10/Hydjet_Quenched_MinBias_2760GeV/GEN-SIM-RECO/MC_36Y_V7A-v1/0005/E82E5989-BE70-DF11-9952-001EC9AA9FCC.root'))

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.GlobalTag.globaltag = 'START3X_V26A::All'
process.GlobalTag.globaltag = 'MC_37Y_V4::All'

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.14 $'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/UserCode/edwenger/Skims/test/TrkAnaSkim_mc_7TeV_cfg.py,v $'),
    annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
)

process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string('trkhistsMC.root')
                                   )

# =============== Import Sequences =====================

process.load("edwenger.Skims.EventFilter_cff")
process.load("edwenger.Skims.ExtraReco_cff")
process.load("edwenger.Skims.Analysis_cff")

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJECSet( process, "Summer09_7TeV_ReReco332") # get the 7 TeV jet corrections

from edwenger.Skims.customise_cfi import *
process = enableSIM(process)    # activate isGEN in analyzers
#process = enableREDIGI(process) # set proper HLT process name for REDIGI samples

# =============== Final Paths =====================

process.eventFilter_step = cms.Path(process.eventFilterHi)
#process.extraReco_step   = cms.Path(process.eventFilterHi * process.extraReco)
process.ana_step         = cms.Path(process.eventFilterHi * process.analysisSeqHi)

# Re-make genjets for 35x reprocessing of 31x MC

#process.load("RecoJets.Configuration.GenJetParticles_cff")
#process.load("RecoJets.Configuration.RecoGenJets_cff")

#process.gen_step = cms.Path(process.genJetParticles *
#                            process.ak5GenJets *
#                            process.ak7GenJets)

# =============== Output ================================
process.load("edwenger.Skims.analysisSkimContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
    process.analysisSkimContent,
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
    #process.extraReco_step,
    process.ana_step,
    #process.output_step
    )