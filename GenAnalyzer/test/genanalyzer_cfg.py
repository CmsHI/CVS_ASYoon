import FWCore.ParameterSet.Config as cms

process = cms.Process("Ana")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root'
        'dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yjlee/HYDJET_GEN_X2_MB_4.0TeV/HYDJET_GEN_X2_MB_4.0TeV/6ca09266124c2704b0cdb9d18c9c0d65/hydjet_mb_1.root'
    )
)

process.ana = cms.EDAnalyzer('GenAnalyzer',
                             auxiliaryInfo = cms.untracked.bool(True)
                             )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('gen_analyzer.root')
                                   )
process.ana = cms.EDAnalyzer('GenAnalyzer'
)


process.p = cms.Path(process.ana)
