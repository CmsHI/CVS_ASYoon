#-----------------------------------------------------------------
# cfg - to do tracking reconstruction on DM sample and 
#       to produce hiOptimalTightTracks in old way (i.e 39X)
#       and finally run the analyzers on this track
#-----------------------------------------------------------------

import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

#============= variable parsing ========================
ivars = VarParsing.VarParsing('standard')
ivars.register('initialEvent',mult=ivars.multiplicity.singleton,info="for testing")
ivars.files = "file:/d01/y_alive/spectra/data_mc_mix/MinBias_PreMix_1289_6_SH6_numEvent5.root"
ivars.output = 'trkhistsDM_mix.root'
ivars.maxEvents = 5
ivars.initialEvent = 1

ivars.parseArguments()

# my own variable
options = VarParsing.VarParsing ('standard')
options.register('centBins',
                 1, # by default
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Centrality binning scenario")


#============= actual configuration ====================  
process = cms.Process("RECOANA")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration/EventContent/EventContent_cff')


process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(ivars.maxEvents)
            )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Input Sample  =====================
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( ivars.files )
                            )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(ivars.output))


# =============== Other Statements =====================
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(120))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#process.GlobalTag.globaltag = 'GR_R_44_V10::All'
#process.GlobalTag.globaltag = 'STARTHI44_V7::All'  # use MC GT
process.GlobalTag.globaltag = 'MC_44_V4::All' # for 2010 DM sample
process.GlobalTag.toGet.append(
    cms.PSet(record = cms.string("BeamSpotObjectsRcd"),
             tag = cms.string("Realistic2.76ATeVCollisions_STARTUP_v0_mc"),
             connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_BEAMSPOT")
             )
)
    
# Centrality (use data centrality table)
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"), # use HFtowers for 2011 data!
    nonDefaultGlauberModel = cms.string(""),
    centralitySrc = cms.InputTag("hiCentrality")
)


# =============== Import Sequences =====================
process.load("FirstHi2011.PbPbSpectraAna.HiEventFilter_cff")
process.load("FirstHi2011.PbPbSpectraAna.HiExtraReco39X_cff")
process.load("FirstHi2011.PbPbSpectraAna.HiAnalysis_cff")
#process.load("FirstHi2011.PbPbSpectraAna.HiIterTracking39X_cff") # not needed

# =============== Pat Jet ==========================
process.load('CmsHi.JetAnalysis.PatAna_cff')

# =============== DM Specifi-Reco ========================
process.load("SimGeneral.DataMixingModule.DigiToRawTracker_cff")
process.load("SimGeneral.DataMixingModule.RawToDigiTracker_cff")
process.load("SimGeneral.DataMixingModule.RecoTracks_cff")
process.load("SimGeneral.DataMixingModule.RecoIterTracks_cff")

# =============== Final Paths =====================
process.eventFilter_step = cms.Path(process.eventFilter)
process.extraJets_step   = cms.Path(process.icPu5patSequence_data)
process.iterTrack_step   = cms.Path(process.DigiToRawTracker *
                                    process.RawToDigiTracker *
                                    process.reconstructIterTracks) # not iterTracking39X_seq !
process.extraTrks_step   = cms.Path(process.hiOptTrack39X)
process.ana_step         = cms.Path(process.hiAnalysisSeq)

# =============== Customization =======================
from FirstHi2011.PbPbSpectraAna.hicustomise_cfi import *
from CmsHi.JetAnalysis.customise_cfi import *
enableDataPat(process) # Pat jet for Data
enableSIM(process)     # activate isGEN in analyzers
setAnaSeq(process,"ALL")   # EffOnly, AnaOnly, ALL
constraintOnLJetEta(process)               # constraint on leading jet eta
whichCentBinMode(process,options.centBins) # centrality binning
whichTrackCollection(process,"hiOptimalTightTracks") # input track collection for main ana

# =============== Extra customization ================
# only track val and track eff ana left!
process.ana_step.remove(process.extraCentDist) #
process.ana_step.remove(process.higoodtrkval_pt80) # no jet, no et cut
process.ana_step.remove(process.higoodtrkval_pt100)
process.ana_step.remove(process.higoodtrkval_pt120)
process.ana_step.remove(process.higoodtrkval_fake_pt80)
process.ana_step.remove(process.hitrackAna)
process.ana_step.remove(process.hitrackAna_jetMode1)
process.ana_step.remove(process.hitrackAna_jetMode2)
process.hitrkEffAnalyzer.usePxlPair = cms.untracked.bool(True)
process.hitrkEffAnalyzer.useJetEtMode = cms.int32(0) # 0 = no jet, 1 = leading jet, 2 = closest jets

# =============== Schedule ===========================
process.endjob_step = cms.Path(process.endOfProcess)

process.schedule = cms.Schedule(
    process.iterTrack_step,
    process.endjob_step,
    process.extraTrks_step,
    process.ana_step
    )
