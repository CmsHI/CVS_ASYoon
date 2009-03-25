import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
                #'file:/net/hisrv0001/home/y_alive/cmssw/CMSSW_2_2_4-HiEventEmbedding/src/HIProdAlgos/HIEventEmbedder/test/edmfile_hyd_pyq_eve1.root'
                #'file:/net/hisrv0001/home/y_alive/cmssw/CMSSW_2_2_4-HiEventEmbedding/src/HIProdAlgos/HIEventEmbedder/test/edmfile_gammajet_mixed_eve1.root'
                'file:/net/hisrv0001/home/y_alive/cmssw/CMSSW_2_2_4-HiEventEmbedding/src/HIProdAlgos/HIEventEmbedder/test/edmfile_mixed_default_noAna.root'
                )
)

process.demo = cms.EDAnalyzer('EmbedderAnalyzer',
                              isMixed = cms.untracked.bool(True)
)

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('test_hydjet.root')
                                   )


process.p = cms.Path(process.demo)
