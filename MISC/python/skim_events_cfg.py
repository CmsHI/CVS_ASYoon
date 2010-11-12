import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import os

process = cms.Process("SKIMANA")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')


# =============== input file setting =====================
mylist = FileUtils.loadListFromFile ('run150431.txt')
mylist.extend ( FileUtils.loadListFromFile ('run150431.txt') )

# =============== 2.36 TeV MC Sample =====================
run_list = ['150431:834258-150431:834258',
            '150431:956113-150431:956113',
            '150431:1061046-150431:1061046',
            '150431:1130789-150431:1130789',
            '150431:1329205-150431:1329205',
            '150431:1450252-150431:1450252']

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring( *mylist),
   eventsToProcess = cms.untracked.VEventRange(run_list) 
)


# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'GR10_P_V12::All' 

# =============== Trigger selection ====================
from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel

process.whateverHLT = hltHighLevel.clone(
    #HLTPaths = cms.vstring('HLT_HIJet90U'), 
    HLTPaths = cms.vstring('HLT_HIMinBiasHF'),
    andOr = cms.bool(True)
)

from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
process.whateverL1 = hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('35')
    )

#process.eventFilter_step = cms.Path(process.whateverHLT)
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
    fileName = cms.untracked.string('file:/home/sungho/sctch100/data/hihlt/errored/raw/ErroredEvents_r150431_RAW.root')
)

process.output_step = cms.EndPath(process.output)


# =============== Schedule =====================
process.schedule = cms.Schedule(
    #process.eventFilter_step,
    #process.TriggerAnalyzerEndpath,
    process.output_step
)


