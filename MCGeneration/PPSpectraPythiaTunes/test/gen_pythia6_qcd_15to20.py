import FWCore.ParameterSet.Config as cms

process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('100'),
    name = cms.untracked.string('PyReleaseValidation')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("EmptySource")


# ============= Pythia setting  ================================
from Configuration.Generator.PythiaUED6TSettings_cfi import *
#from Configuration.Generator.PythiaUEP0Settings_cfi import *
#from Configuration.Generator.PythiaUEProPT0Settings_cfi import *
#from Configuration.Generator.PythiaUEX1Settings_cfi import *
#from Configuration.Generator.PythiaUEX2Settings_cfi import *

process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(7000.0),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
         pythiaUESettingsBlock,
         processParameters = cms.vstring(
                 'MSEL=1         ! High Pt QCD',
                 'CKIN(3)=15     ! Pt hat lower cut',
                 'CKIN(4)=20     ! Pt hat upper cut'
                 ),
         parameterSets = cms.vstring('pythiaUESettings',
                                     'processParameters')
         )
)

process.gen_step = cms.Path(process.generator
                            *process.genParticles)

# ============= Gen jet ================================
# Re-make genjets for 35x reprocessing of 31x MC
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

process.genjet_step = cms.Path(process.genJetParticles *
                               process.ak5GenJets *
                               process.ak7GenJets)

# =============== spectra ana ==========================
process.load("edwenger.Skims.Analysis_cff")
process.ana_step  = cms.Path(process.analysisGEN)

from edwenger.Skims.customise_cfi import *
#process =  enableMinPtHatCut(process)  # activate min pt_hat cut!

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('trkhistsGEN.root')
                                   )


# =============== Output ================================
process.output = cms.OutputModule("PoolOutputModule",
   #outputCommands = process.RAWSIMEventContent.outputCommands,
   outputCommands = cms.untracked.vstring(
    'keep *_genParticles_*_*',
    'keep *_iterativeCone5GenJets_*_*'
    ),
   fileName = cms.untracked.string('test.root'),
   dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('GEN'),
    filterName = cms.untracked.string('')
    ),
   SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('generation_step2')
    )
)


# =============== Schedule =====================

process.schedule = cms.Schedule(process.gen_step,
                                process.genjet_step,
                                process.ana_step)
