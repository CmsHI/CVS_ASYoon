import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("SKIM")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')


# =============== input file setting =====================

# =============== 2.36 TeV MC Sample =====================
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
     'rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HIAllPhysics/RECO/PromptReco-v1/000/150/066/2205E521-D5E8-DF11-B724-001617E30D52.root',
     'rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HIAllPhysics/RECO/PromptReco-v1/000/150/066/822BCD17-D5E8-DF11-9B93-001617DBD472.root',
     'rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HIAllPhysics/RECO/PromptReco-v1/000/150/066/823338D4-E6E8-DF11-B1C1-0030486730C6.root',
     'rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HIAllPhysics/RECO/PromptReco-v1/000/150/066/9A50D64F-D4E8-DF11-AE15-001D09F2910A.root'
    )
)


# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR10_P_V12::All' 

# =============== Trigger selection ====================
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel
process.hltbscHighMult = hltHighLevel.clone(
        HLTPaths = cms.vstring('HLT_HIL1Tech_BSC_HighMultiplicity'),
        andOr = cms.bool(True)
)

process.eventFilter_step = cms.Path(process.hltbscHighMult)

from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
process.bscHighMult = hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('35')
    )

process.eventFilter_step = cms.Path(process.bscHighMult)

# =============== Trigger summary =======================
process.load('L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi')
process.l1GtTrigReport.L1GtRecordInputTag = cms.InputTag( "gtDigis") # simGtDigis
process.L1AnalyzerEndpath = cms.EndPath( process.l1GtTrigReport )
process.MessageLogger.categories.append('L1GtTrigReport')
                    
# =============== Output ================================
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
    fileName = cms.untracked.string('file:/home/sungho/sctch101/data/evtdisplay/input/HIRun2010_run150066_HLT_HIL1Tech_BSC_HighMultiplicity.root')
)

process.output_step = cms.EndPath(process.output)


# =============== Schedule =====================
process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.L1AnalyzerEndpath,
    process.output_step
)


