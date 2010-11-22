#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2010

# common HI ana stuffs
cvs co -r V01-02-09 HeavyIonsAnalysis/Configuration
# cvs co RecoHI/HiEgammaAlgos (before 392p5)


# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/SavedFMa/Saved/DiJetAna
cvs co UserCode/SavedFMa/Saved/PatAlgos
cvs co UserCode/SavedFMa/Saved/Skim

# centrality
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideHeavyIonCentrality
cvs co -r V00-00-06 CondFormats/HIObjects
cvs co -r V00-01-20 DataFormats/HeavyIonEvent
cvs co -r V00-01-18 RecoHI/HiCentralityAlgos
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# tools
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer
cvs co UserCode/ASYoon/PbPbTrackingTools/CaloCompatibleTrackSelector

# needed for dijetana

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/ASYoon/FirstHi2010 .
mv UserCode/SavedFMa/Saved .

#
scram b
