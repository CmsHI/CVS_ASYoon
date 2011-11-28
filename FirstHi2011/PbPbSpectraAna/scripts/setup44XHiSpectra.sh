#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2011
cvs co UserCode/ASYoon/FirstHi2010/CentralityDistAna

# common HI ana stuffs
cvs co -r V01-02-09 HeavyIonsAnalysis/Configuration

# hcal spike cleaning
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/edwenger/HiEvtSelAnalyzer


# for jet


# tools
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer
cvs co UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator
cvs co UserCode/ASYoon/PbPbTrackingTools/HiCaloCompatibleTrackSelector
#cvs co UserCode/edwenger/Skims/prod/condor # in case condor job scripts needed

# needed for Matt's iterative tracking
cvs co -d       MNguyen/iterTracking UserCode/MNguyen/iterTracking
cvs co -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
rm CmsHi/JetAnalysis/python/EGammaAnalyzers_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/ExtraEGammaReco_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/EventSelection_cff.py # tmp fix

# needed for dijetana

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/ASYoon/FirstHi2010 .
mv UserCode/ASYoon/FirstHi2011 .

scram build -c
scram b