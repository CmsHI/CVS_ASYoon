import FWCore.ParameterSet.Config as cms


# =============== Trigger summary =======================
# L1
#import L1Trigger.GlobalTriggerAnalyzer.l1GtTrigReport_cfi import *
#process.l1GtTrigReport.L1GtRecordInputTag = cms.InputTag("gtDigis") # gtDigis

# HLT
#import HLTrigger.HLTanalyzers.hlTrigReport_cfi import *
#process.hlTrigReport.HLTriggerResults = cms.InputTag("TriggerResults","","REDIGI")

#process.TriggerAnalyzerEndpath = cms.EndPath(process.l1GtTrigReport*
#                                             process.hlTrigReport)

#process.MessageLogger.categories.append('L1GtTrigReport')
#process.MessageLogger.categories.append('HLTrigReport')
