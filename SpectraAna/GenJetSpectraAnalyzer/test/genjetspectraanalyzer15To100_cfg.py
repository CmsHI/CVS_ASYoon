import FWCore.ParameterSet.Config as cms

process = cms.Process("ANA")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

####################################################################################

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    #'file:myfile.root'
    'dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/y_alive/spectra/CDF_investigation/spectra_from_jet/GEN/TMPL_cmsUE_QCDJets_pthat15To100/GENv2_TMPL_cmsUE_QCDJets_pthat15To100.root'
    )
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5000) )

####################################################################################
#process.load("SpectraAna.GenJetSpectraAnalyzer.genjetspectraanalyzer_cff")

process.genjetana  = cms.EDAnalyzer('GenJetSpectraAnalyzer',
                                    #resultFile      = cms.string("/net/hisrv0001/home/y_alive/cmssw/CMSSW_3_1_1_Spectra/src/SpectraAna/GenJetSpectraAnalyzer/test/ana_test.root")
                                    resultFile = cms.string("/net/hisrv0001/home/y_alive/scratch/CDF_investigation/spectra_from_jet/ANA/TMPL_cmsUE_QCDJets_pthat15To100/ANAv2_GENv2_TMPL_cmsUE_QCDJets_pthat15To100.root")
                                    )


process.p = cms.Path(process.genjetana)
