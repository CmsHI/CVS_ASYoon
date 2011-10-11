#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2010
cvs co -r 1.6 UserCode/ASYoon/FirstHi2010/CentralityDistAna/python/centralitydistana_cfi.py # for < 399

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
cvs co -r V00-00-18 JetMETAnalysis/HcalReflagging
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter


# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/edwenger/HiEvtSelAnalyzer

cvs co -r 1.23 UserCode/edwenger/HiTrackSpectraAnalyzer/python/hitrackspectraanalyzer_cfi.py  # for <399
cvs co -r 1.22 UserCode/edwenger/HiTrkEffAnalyzer/python/hitrkEffAnalyzer_cfi.py

# for jet
# see  /UserCode/SavedFMa/Saved/Skim/scripts for up-to-date package co
# also /UserCode/SavedFMa/Saved/DiJetAna/test/dijetAna_cfg.py
#cvs co -D "2011-03-30" UserCode/SavedFMa/Saved/DiJetAna # for < 399
cvs co -d    Saved/DiJetAna UserCode/SavedFMa/Saved/DiJetAna 
cvs co -d    Saved/PatAlgos UserCode/SavedFMa/Saved/PatAlgos
cvs co -d    Saved/Skim UserCode/SavedFMa/Saved/Skim

# to replace ExtraReco_cff.py, which includes "TrackSelection_cff.py" in conflict
cvs co UserCode/ASYoon/MISC/python/ExtraReco_cff.py
cp UserCode/ASYoon/MISC/python/ExtraReco_cff.py Saved/DiJetAna/python


# centrality
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideHeavyIonCentrality
cvs co CondFormats/HIObjects
cvs co DataFormats/HeavyIonEvent
cvs co RecoHI/HiCentralityAlgos
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# tools
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer
cvs co UserCode/ASYoon/PbPbTrackingTools/CaloCompatibleTrackSelector
cvs co UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator
cvs co UserCode/ASYoon/PbPbTrackingTools/HiCaloCompatibleTrackSelector
cvs co -r 1.9 UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator/python/hitrackvalidator_cfi.py # for <399

# needed for Matt's iterative tracking
cvs co -d       MNguyen/iterTracking UserCode/MNguyen/iterTracking
cvs co -r cmssw39x_branch -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
cvs co    RecoHI/HiJetAlgos # jet - related, but needed for the above 
cvs co -d    MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer # jet - related, but needed for the above


# needed for dijetana

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/ASYoon/FirstHi2010 .

scram b
