#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/ASYoon/FirstHi2010/PbPbSpectraAna

# analyzers
cvs co UserCode/edwenger/HiVertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer
cvs co UserCode/SavedFMa/Saved/DiJetAna
cvs co UserCode/SavedFMa/Saved/PatAlgos


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
#scram b