import FWCore.ParameterSet.Config as cms
process = cms.Process("ANASKIM")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('/store/user/davidlw/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RAWDEBUG_390/Hydjet_Quenched_MinBias_2760GeV_STARTUP39V2_GEN_SIM_RECODEBUG_390/e91272bc2b91d5f6eefc8e1f2c112a67/hiReco_RAW2DIGI_RECO_2_3_qyi.root')
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'START39_V2::All'

process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.3 $'),
            name = cms.untracked.string('$Source: /local/projects/CMSSW/rep/UserCode/edwenger/Skims/test/HiTrkAnaSkim_mc_2TeV_cfg.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsMC.root')
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")

from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
process = enableSIM(process)    # activate isGEN in analyzers

# =============== Pat jet in HI ========================
from Saved.DiJetAna.customise_cfi import *
enableRECO(process,"MC","HI")


# =============== Final Paths =====================
process.extraReco_step   = cms.Path(process.hiextraReco + process.reco_extra)
process.ana_step         = cms.Path(process.hiAnalysisSeq)

# =============== Customize =======================
process = disableLowPt(process) # disable low pt pixel
process = setAnaSeq(process,mode="ALL") # EffOnly, AnaOnly, ALL

# =============== Output ================================
#process.load("edwenger.Skims.analysisSkimContent_cff")
#process.output = cms.OutputModule("PoolOutputModule",
#    process.analysisSkimContent,
#    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
#    dataset = cms.untracked.PSet(
#      dataTier = cms.untracked.string('AODSIM'),
#      filterName = cms.untracked.string('TrkAnaFilter')),
#    fileName = cms.untracked.string('trkAnaSkimAODSIM.root')
#    )

#process.output_step = cms.EndPath(process.output)

# =============== Schedule =====================

process.schedule = cms.Schedule(
    process.extraReco_step,
    process.ana_step,
    #process.output_step
    )
