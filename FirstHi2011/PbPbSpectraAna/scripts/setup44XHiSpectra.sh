#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2011
cvs co UserCode/ASYoon/FirstHi2010/CentralityDistAna

# common HI ana stuffs
cvs co -r V01-02-09 HeavyIonsAnalysis/Configuration
cvs co CondFormats/HIObjects
cvs co DataFormats/HeavyIonEvent
cvs co RecoHI/HiCentralityAlgos

# centrality (temporary for Hydjet)
cvs co -d CmsHi/Analysis2010/python UserCode/CmsHi/Analysis2010/python

# hcal spike cleaning
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/edwenger/HiEvtSelAnalyzer
cvs co UserCode/ASYoon/SpectraAna/GenSimSpectraValidator

# for jet (icPu5 pat jet)
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
rm CmsHi/JetAnalysis/python/EGammaAnalyzers_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/ExtraEGammaReco_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/EventSelection_cff.py # tmp fix
rm CmsHi/JetAnalysis/python/ExtraPfReco_cff.py # tmp fix
cp CmsHi/JetAnalysis/data/JEC_HI_PFTower_413patch2_2011_v3.db UserCode/ASYoon/FirstHi2011/PbPbSpectraAna/test

# tools
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer
cvs co UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator
cvs co UserCode/ASYoon/PbPbTrackingTools/HiCaloCompatibleTrackSelector
#cvs co UserCode/edwenger/Skims/prod/condor # in case condor job scripts needed

# needed for HI iterative tracking
cvs co -r V01-04-07 RecoHI/HiTracking
cvs co UserCode/MNguyen/Configuration/python/hiIterTracking_cff.py
cp UserCode/MNguyen/Configuration/python/hiIterTracking_cff.py RecoHI/HiTracking/python # consolidation
cvs co -d MNguyen/iterTracking UserCode/MNguyen/iterTracking

# needed for DM reconstruction
cvs co -d SimGeneral/DataMixingModule UserCode/yetkin/SimGeneral/DataMixingModule
cvs co -r hi44X_01 -d  MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer # this is needed for above
rm MitHig/PixelTrackletAnalyzer/src/SimTrackAnalyzer.cc

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/ASYoon/FirstHi2010 .
mv UserCode/ASYoon/FirstHi2011 .

scram build -c
scram b
