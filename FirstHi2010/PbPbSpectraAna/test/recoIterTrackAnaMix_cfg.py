import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

#============= variable parsing ========================
ivars = VarParsing.VarParsing('standard')
ivars.register('initialEvent',mult=ivars.multiplicity.singleton,info="for testing")
#ivars.files = "file:/home/sungho/sctch101/data_mc_mix/pythia170_HICorePhysics_MinBiasSkim_440_test28_DBS_evt20_test01/MinBias_PreMix_202_1_skd_numEvent20.root"
ivars.files = "dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yetkin/mix/pythia170_HICorePhysics_MinBiasSkim_440_test28_DBS_evt5_test01/MinBias_PreMix_1652_5_EMZ_numEvent5.root"
ivars.output = 'trkhistsDM_mix.root'
ivars.maxEvents = 14
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
process = cms.Process('TRACKING')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

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
process.GlobalTag.globaltag = 'MC_44_V4::All'
process.GlobalTag.toGet.append(
        cms.PSet(record = cms.string("BeamSpotObjectsRcd"),
                 tag = cms.string("Realistic2.76ATeVCollisions_STARTUP_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_BEAMSPOT")
                 )
        )

process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string(""),
    centralitySrc = cms.InputTag("hiCentrality")
    )

from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.jec = cms.ESSource("PoolDBESSource",
                           DBParameters = cms.PSet(messageLevel = cms.untracked.int32(0)),
                           timetype = cms.string('runnumber'),
                           toGet = cms.VPSet(
    cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                      tag = cms.string("JetCorrectorParametersCollection_HI_Calo_hiGoodTightTracks_D6T_413_IC5Calo"),
                                      label = cms.untracked.string("IC5Calo")),

    cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                      tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK3PF'),
                                      label = cms.untracked.string("AK3PF")),

    cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                      tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK4PF'),
                                      label = cms.untracked.string("AK4PF")),

    cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                      tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK5PF'),
                                      label = cms.untracked.string("AK5PF")
                                      ),
    ),
                                                      connect = cms.string("sqlite_file:JEC_HI_PFTower_413patch2_2011_v3.db"),
                                                      )
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')


# Path and EndPath definitions

process.load('CmsHi.JetAnalysis.ExtraJetReco_cff')
process.load('CmsHi.JetAnalysis.PatAna_cff')
process.load('CmsHi.JetAnalysis.JetAnalyzers_cff')
from CmsHi.JetAnalysis.customise_cfi import *
enableDataPat(process)
enableDataAnalyzers(process)

process.load("SimGeneral.DataMixingModule.DigiToRawTracker_cff")
process.load("SimGeneral.DataMixingModule.RawToDigiTracker_cff")

process.load("SimGeneral.DataMixingModule.RecoTracks_cff")
process.load("SimGeneral.DataMixingModule.RecoIterTracks_cff")
process.load("SimGeneral.DataMixingModule.TrackAnalyzers_cff")

process.anamix = cms.EDAnalyzer("StripAnalyzer",
                                data = cms.InputTag("siStripDigis","VirginRaw","RAW2DIGI"),
                                mc = cms.InputTag("simSiStripDigis","ZeroSuppressed"),
                                mix = cms.InputTag("mixData","siStripDigisDM"),
                                zs = cms.InputTag("siStripZeroSuppression","VirginRaw"),
                                digi = cms.InputTag("siStripDigis","ZeroSuppressed"),
                                )


# Calo compatible tracks
process.load("FirstHi2010.PbPbSpectraAna.HiTrackSelection_cff")
process.hiOptCaloFst = process.hiLooseTracks.clone(src = cms.InputTag("hiOptCaloPreFst"))
process.hiOptCaloSnd = process.hiGoodTightTracks.clone(src = cms.InputTag("hiOptCaloPreSnd"))

process.hiOptimalTightTracks  = process.hiGeneralTracks.clone(
    ShareFrac = cms.double(999.0), # since two collections have no track in common
    TrackProducer1 = 'hiOptCaloFst',
    TrackProducer2 = 'hiOptCaloSnd',
    )

# algo selection (algo = 0, i.e. only first iteration)
process.hiOptimalTightTracks1stIter = cms.EDFilter("TrackSelector",
        src = cms.InputTag("hiOptimalTightTracks"),
        cut = cms.string('algo==0')
 )

process.ptDeptOptCalo_seq = cms.Sequence(
    process.hiOptCaloPreFst *
    process.hiOptCaloFst *
    process.hiOptCaloPreSnd *
    process.hiOptCaloSnd *
    process.hiOptimalTightTracks *
    process.hiOptimalTightTracks1stIter
 )


# Spectra Analyzers
process.load("edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff")
process.load("FirstHi2010.PbPbSpectraAna.HiAnalysis_cff")
process.hitrkEffAnalyzer.tracks = cms.untracked.InputTag('hiGeneralTracks')
process.hitrkEffAnalyzer.usePxlPair = cms.untracked.bool(True)
process.hitrackAna.src = cms.untracked.InputTag('hiGeneralTracks')
process.hitrackAna.src_evtCorr = cms.untracked.InputTag('hiGeneralTracks')
process.hitrackAna.triglabel=cms.untracked.InputTag('TriggerResults')

process.load('MitHig.PixelTrackletAnalyzer.trackAnalyzer_cff')
process.anaTrack.trackPtMin = cms.untracked.double(4)
process.anaTrack.simTrackPtMin = cms.untracked.double(4)
process.anaTrack.doSimTrack = cms.untracked.bool(True)
process.anaTrack.trackSrc = cms.InputTag('hiGeneralTracks')
process.anaTrack.tpFakeSrc = cms.untracked.InputTag('cutsTPForFak')
process.anaTrack.tpEffSrc = cms.untracked.InputTag('cutsTPForEff')
process.anaTrack.doPFMatching = cms.untracked.bool(False)

# =============== Customize =======================
from FirstHi2010.PbPbSpectraAna.hicustomise_cfi import *
process = setAnaSeq(process,"AnaOnly")
process = whichCentBinMode(process,options.centBins)
process = constraintOnLJetEta(process)

# =============== Final Paths =====================
process.extraTrks_step   = cms.Path(process.ptDeptOptCalo_seq)
process.ana_step = cms.Path(process.hitrkEffAna *process.anaTrack)
process.reco_step = cms.Path( 
    #process.icPu5patSequence_data *
    process.DigiToRawTracker *
    process.RawToDigiTracker *    
    process.reconstructIterTracks *
    process.genAnalyzer 
    #process.icPu5JetAnalyzer
)

process.endjob_step = cms.Path(process.endOfProcess)

process.schedule = cms.Schedule(
    process.reco_step,
    process.endjob_step,
    process.extraTrks_step,
    process.ana_step
)




