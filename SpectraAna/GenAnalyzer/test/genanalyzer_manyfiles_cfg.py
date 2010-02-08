import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os

process = cms.Process("Ana")

process.load("FWCore.MessageService.MessageLogger_cfi")


# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.maxEvents = 100
options.output = 'test.root'
inDir = "/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_Quenched_MinBias_2800GeV_GEN_341_020510/Hydjet_Quenched_MinBias_2800GeV_GEN_341_020510/2cd3c91d56ca6f732b8741d2d845caeb/"

# register custom variables
options.register('skipEv', 1990, options.multiplicity.singleton, options.varType.int, "Number of events to skip (default=0)")

for seqNo in range(1,10):
    options.files.append( 'dcache:%s/Hydjet_Quenched_MinBias_2800GeV_cfi_py_GEN_%d.root' % (inDir,seqNo) )

    # get and parse the command line arguments
    options.parseArguments()
    
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.files),
       duplicateCheckMode = cms.untracked.string( 'noDuplicateCheck' ),
               skipEvents = cms.untracked.uint32(options.skipEv)
                            
)

process.ana = cms.EDAnalyzer('GenAnalyzer',
                             auxiliaryInfo = cms.untracked.bool(True)
                             )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string(options.output)
                                   )
#process.ana = cms.EDAnalyzer('GenAnalyzer'
#)


process.p = cms.Path(process.ana)
