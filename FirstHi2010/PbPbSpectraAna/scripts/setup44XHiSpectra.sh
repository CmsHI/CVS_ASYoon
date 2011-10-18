#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2010

# hiGoodMergedTracks
cvs co -d Appeltel/PixelTracksRun2010 UserCode/Appeltel/PixelTracksRun2010 

# common HI ana stuffs
cvs co -r V01-02-09 HeavyIonsAnalysis/Configuration
# cvs co RecoHI/HiEgammaAlgos (before 392p5)

# spike cleaning and broken code cleaning..
cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
rm CmsHi/PhotonAnalysis/plugins/SinglePhotonAnalyzer.cc
rm CmsHi/PhotonAnalysis/plugins/SinglePhotonAnalyzer.h
rm CmsHi/PhotonAnalysis/plugins/MultiPhotonAnalyzer.cc
rm CmsHi/PhotonAnalysis/plugins/MultiPhotonAnalyzer.h
rm CmsHi/PhotonAnalysis/plugins/MultiPhotonAnalyzerTree.cc

# hcal spike cleaning
addpkg RecoLocalCalo/HcalRecAlgos
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/src/HBHETimingShapedFlag.cc
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/interface/HBHETimingShapedFlag.h
#cvs co -r V00-00-18 JetMETAnalysis/HcalReflagging
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/edwenger/HiEvtSelAnalyzer

# for jet
# see  /UserCode/SavedFMa/Saved/QM11Ana/scripts for up-to-date package co
addpkg RecoJets/JetProducers
cvs co    RecoHI/HiJetAlgos
cvs co -d    Saved/QM11Ana UserCode/SavedFMa/Saved/QM11Ana
cvs co -d    Saved/DiJetAna UserCode/SavedFMa/Saved/DiJetAna
cvs co -d    MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer
#cvs co -d    MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
#rm -rf MitHig/PixelTrackletAnalyzer/src/PixelHitAnalyzer.cc

# centrality
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideHeavyIonCentrality
cvs co CondFormats/HIObjects
cvs co DataFormats/HeavyIonEvent
cvs co RecoHI/HiCentralityAlgos
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# tools
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer
cvs co UserCode/ASYoon/PbPbTrackingTools/CaloCompatibleTrackSelector # need to fix
cvs co UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator
cvs co UserCode/ASYoon/PbPbTrackingTools/HiCaloCompatibleTrackSelector
#cvs co UserCode/edwenger/Skims/prod/condor # in case condor job scripts needed

# needed for Matt's iterative tracking
cvs co -d       MNguyen/iterTracking UserCode/MNguyen/iterTracking
cvs co -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
cvs co UserCode/ASYoon/MISC/python/secondStep_triplet_cff.py # tmp fix
cp UserCode/ASYoon/MISC/python/secondStep_triplet_cff.py MNguyen/iterTracking UserCode/MNguyen/iterTracking/python
rm CmsHi/JetAnalysis/python/EGammaAnalyzers_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/ExtraEGammaReco_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/EventSelection_cff.py # tmp fix

# needed for dijetana

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/ASYoon/FirstHi2010 .

# for DM work/processing
cvs co -r hi44X_01 -d  MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
cvs co -r hi44X_04 -d SimGeneral/DataMixingModule UserCode/yetkin/SimGeneral/DataMixingModule
rm MitHig/PixelTrackletAnalyzer/src/SimTrackAnalyzer.cc

# customization to run in 44X
rm FirstHi2010/PbPbSpectraAna/python/hieventSelection_cff.py
cvs co UserCode/ASYoon/MISC/python/hieventSelection_cff.py
cp UserCode/ASYoon/MISC/python/hieventSelection_cff.py FirstHi2010/PbPbSpectraAna/python/

scram build -c
scram b