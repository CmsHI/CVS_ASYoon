import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

#============= variable parsing ========================
ivars = VarParsing.VarParsing('standard')
ivars.register('initialEvent',mult=ivars.multiplicity.singleton,info="for testing")

ivars.files = "dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/krajczar/mix/MinBias_DijetUnquenched80_d20101126_Offset_30_RECO/Mixed_30_RECO_Mixed_30_DIGI_FE622F66-EBF0-DF11-8447-003048F118D4.root"

ivars.register('outputNtuple',
               "Ntuple.root",
               VarParsing.VarParsing.multiplicity.singleton,
               VarParsing.VarParsing.varType.string,
               "Ntuples for Jet Analysis")

ivars.outputNtuple = 'Ntuple.root'

ivars.output = 'trkhistsMC.root'
ivars.maxEvents = 10
ivars.initialEvent = 1

ivars.parseArguments()


#============= actual configuration ====================
process = cms.Process("ANASKIM")

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
options.register('centRange',
                 "ALL", # 0To10, 50To100, and etc 
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Centrality bin range")

# get and parse the command line arguments
options.parseArguments()

# =============== debugging if needed ===================

# =============== 2.76 TeV MC Sample =====================

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(ivars.files)
)

# =============== Other Statements =====================

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(ivars.maxEvents))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.GlobalTag.globaltag = 'START39_V4HI::All' 

# Needed for Centrality Table
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
)
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.4 $'),
            name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/ASYoon/FirstHi2010/PbPbSpectraAna/test/HiTrkAnaSkim_mc_2760GeV_cfg_393DataMixMC_VAR.py,v $'),
            annotation = cms.untracked.string('BPTX_AND + BSC_OR + !BSCHALO')
        )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(ivars.output)
                                   )

# =============== Import Sequences =====================
process.load("FirstHi2010.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiExtraReco_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")

# =============== Pat jet in HI ========================
process.load("Saved.DiJetAna.ExtraReco_cff")
process.load("Saved.DiJetAna.dijetAna_cff")

from Saved.DiJetAna.customise_cfi import *
enableRECO(process,"MC","HI")
enableDataMixMC(process)  # to run on DataMixMC

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
#process.extraReco_step   = cms.Path(process.eventFilter * (process.hiextraReco + process.hipfReReco))
process.extraReco_step   = cms.Path(process.eventFilter * process.hiextraReco)
process.extraJets_step  = cms.Path(process.eventFilter  * process.dj_reco_extra)
process.extraTrks_step   = cms.Path(process.eventFilter * process.hiextraTrack)
process.ana_step         = cms.Path(process.eventFilter * process.hiAnalysisSeq)


# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
#process = enableHLTJet(process,"HLT_HIJet50U")
#process = usehiSelectedTracks(process) # use hiSelectedTracks instead
process = enableSIM(process)    # activate isGEN in analyzers
process = disableLowPt(process) # disable low pt pixel
process = disableJetEtCutOnAna(process) # remove trackAna with jet Et cuts
#process = usehiGoodMergedTracks(process) # use hiGoodMergedTracks instead 
process = setAnaSeq(process,"ALL") # EffOnly, AnaOnly, ALL
#process = enableREDIGI(process) # to run on redigitized 
process = runOn393DataMixMC(process)
process = whichCentBinMode(process,options.centBins) # centrality binning
#process = constraintOnLJetEta(process) # constraint on leading jet eta
#process = useSubLeadingJet(process) # use sub leading jet  
#process = setMinPtforPF(process,200) # min pt for PF reco/ana

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
    process.extraReco_step,
    process.extraJets_step,
    process.extraTrks_step,
    process.ana_step
    )

#process.schedule.append(process.output_step)

