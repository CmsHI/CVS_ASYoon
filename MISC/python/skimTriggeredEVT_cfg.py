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
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/308/FEEBDF87-19EA-DF11-8472-001D09F23944.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/308/FE732182-19EA-DF11-BFA8-001D09F2447F.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/308/E4EECE82-19EA-DF11-B887-001D09F2441B.root'
    )
)


# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR10_P_V12::All' 

# =============== Trigger selection ====================
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel

process.whateverHLT = hltHighLevel.clone(
    HLTPaths = cms.vstring('HLT_HIJet90U'), 
    andOr = cms.bool(True)
)

from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
process.whateverL1 = hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('35')
    )

process.eventFilter_step = cms.Path(process.whateverHLT)
#process.eventFilter_step = cms.Path(process.whateverL1)

# =============== Trigger summary =======================
# L1
process.load('L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi')
process.l1GtTrigReport.L1GtRecordInputTag = cms.InputTag( "gtDigis") # simGtDigis

# HLT
process.load('HLTrigger.HLTanalyzers.hlTrigReport_cfi')
process.TriggerAnalyzerEndpath = cms.EndPath(process.l1GtTrigReport*
                                             process.hlTrigReport)

process.MessageLogger.categories.append('L1GtTrigReport')
process.MessageLogger.categories.append('HLTrigReport')
                    
# =============== Output ================================
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('eventFilter_step')),
    fileName = cms.untracked.string('file:/home/sungho/sctch101/data/evtdisplay/input/HIRun2010_run150308_HLT_HIJet90U_test.root')
)

process.output_step = cms.EndPath(process.output)


# =============== Schedule =====================
process.schedule = cms.Schedule(
    process.eventFilter_step,
    process.TriggerAnalyzerEndpath,
    process.output_step
)


