import FWCore.ParameterSet.Config as cms

process = cms.Process('HiTEST')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

# message logger
process.MessageLogger.categories = ['HiTrackMatchingAnalyzer']
process.MessageLogger.debugModules = ['*']
process.MessageLogger.cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),
    DEBUG = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
    ),
    INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(0)
    ),
    HiTrackMatchingAnalyzer = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
    )
)

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.3 $'),
    annotation = cms.untracked.string('step2 nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
    )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(30)
    )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Input source
process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring(
    'file:/home/sungho/sctch101/mc/firsthi2010/hiReco_RAW2DIGI_RECO_UQ_Dijet80_395.root'
    )
)

# Track efficiency analyzer
process.load("PbPbTrackingTools.HiTrackMatchingAnalyzer.hitrkMatchAnalyzer_cfi")
process.hitrkMatchAnalyzer.trkFst = cms.untracked.InputTag('hiGlobalPrimTracks')
#process.hitrkMatchAnalyzer.trkSnd = cms.untracked.InputTag('hiGlobalPrimTracks')
process.hitrkMatchAnalyzer.trkSnd = cms.untracked.InputTag('hiSelectedTracks') 

# Additional output definition
process.TFileService = cms.Service("TFileService",
        fileName = cms.string('hists.root')
        )

# Other statements
#process.GlobalTag.globaltag = 'MC_38Y_V8::All' #38X
process.GlobalTag.globaltag = 'START39_V7HI::All' 

# Needed for Centrality Table
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("Hydjet_2760GeV")  # use AMPT_2760GeV for AMPT
    )

from CmsHi.Analysis2010.CommonFunctions_cff import *
#overrideCentrality(process)

# Path and EndPath definitions
process.ana_step  = cms.Path(process.hitrkMatchAnalyzer)

#process.out_step = cms.EndPath(process.output)
