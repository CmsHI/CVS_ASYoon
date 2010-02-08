# Auto generated configuration file
# using: 
# Revision: 1.118 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: template_CJets_cfi.py -s GEN --conditions FrontierConditions_GlobalTag,IDEAL_31X::All --datatier GEN --eventcontent RAWSIM -n 100 --no_exec
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
    version = cms.untracked.string('$Revision: 1.118 $'),
    annotation = cms.untracked.string('__NUMEVTS__'),
    #annotation = cms.untracked.string('100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(__NUMEVTS__)
    #input = cms.untracked.int32(50)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    #outputCommands = process.RAWSIMEventContent.outputCommands,
    outputCommands = cms.untracked.vstring(
    'keep *_genParticles_*_*',
    'keep *_iterativeCone5GenJets_*_*'
    ),
    fileName = cms.untracked.string('__OUTPUTDIR__/__OUTPUT__.root'),
    #fileName = cms.untracked.string('test.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step2') 
    )
)

# Additional output definition

# Other statements
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
                                 #comEnergy = cms.double(1960.0),
                                 #comEnergy = cms.double(7000.0),
                                 comEnergy = cms.double(2360.0),
    #pythiaBeam1 = cms.untracked.string('p'),
    #pythiaBeam2 = cms.untracked.string('n'),
    #crossSection = cms.untracked.double(30000000000.0),
    #comEnergy = cms.double(7000.0),                                  
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
         pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model', 
            'MSTU(21)=1     ! Check on possible errors during program execution', 
            'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
            'PARP(89)=1960. ! sqrts for which PARP82 is set', 
            'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
            'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
            'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
            'PARP(67)=2.5    ! amount of initial-state radiation', 
            'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(62)=1.25   ! ', 
            'PARP(64)=0.2    ! ', 
            'MSTP(91)=1      !', 
            'PARP(91)=2.1   ! kt distribution', 
            'PARP(93)=15.0  ! '),
         processParameters = cms.vstring('MSEL=0         ! High Pt QCD',
                                         'MSUB(11)=1     ! Min bias process',
                                         'MSUB(12)=1     ! Min bias process',
                                         'MSUB(13)=1     ! Min bias process',
                                         'MSUB(28)=1     ! Min bias process',
                                         'MSUB(53)=1     ! Min bias process',
                                         'MSUB(68)=1     ! Min bias process',
                                         'MSUB(92)=1     ! Min bias process, single diffractive',
                                         'MSUB(93)=1     ! Min bias process, single diffractive',
                                         'MSUB(94)=1     ! Min bias process, double diffractive',
                                         'MSUB(95)=1     ! Min bias process'),
                                         #'CKIN(3)=__MINPT__     ! Pt hat lower cut',
                                         #'CKIN(4)=__MAXPT__     ! Pt hat upper cut'),
         parameterSets = cms.vstring('pythiaUESettings',
            'processParameters')
    )
)

####################################################################################

process.load('RecoJets.Configuration.GenJetParticles_cff')
process.load('RecoJets.JetProducers.ic5GenJets_cfi')
process.iterativeCone5GenJets.rParam = cms.double(0.7) 

process.genJet = cms.Sequence(process.genParticlesForJets
                              *process.iterativeCone5GenJets
                              )

#################################################################################### 

# Path and EndPath definitions
process.generation_step = cms.Path(process.generator)
process.generation_step2 = cms.Path(process.genParticles)
process.generation_jet = cms.Path(process.genJet)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,
                                process.generation_step2,
                                process.generation_jet,
                                process.out_step)
