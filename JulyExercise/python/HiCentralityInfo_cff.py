import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.ReconstructionHeavyIons_cff import *
from RecoHI.HiCentralityAlgos.HiCentrality_cfi import *
from CondCore.DBCommon.CondDBCommon_cfi import *

CondDBCommon.connect = 'sqlite_file:/net/hisrv0001/home/y_alive/cmssw/CMSSW_370p4_SpectraPbPb_TEST5/src/CmsHi/JulyExercise/data/CentralityTables.db'

PoolDBESSource = cms.ESSource("PoolDBESSource",
             CondDBCommon,
            DumpStat=cms.untracked.bool(True),
              toGet = cms.VPSet(cms.PSet(
                 record = cms.string('HeavyIonRcd'),
                 #tag = cms.string('HFhits40_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_NZS_v0')
                 tag = cms.string('HFhits40_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0')
                 )),
)

hicentProd = cms.Sequence(siPixelRecHits*hiCentrality)
