#!/bin/sh

cd $CMSSW_BASE/src

# skiming code
cvs co UserCode/edwenger/Skims

# centrality related
cvs co -r UserCode/CmsHi/JulyExercise/data/CentralityTables.db
cvs co -r HEAD RecoHI/HiCentralityAlgos
cvs co -r HEAD DataFormats/HeavyIonEvent
 
# analyzers
cvs co UserCode/edwenger/VertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer

# vertex constraint for refitting
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer

# july ex. 
cvs co UserCode/ASYoon/JulyExercise
cvs co UserCode/SavedFMa/Saved

# replace with hi-specific 
rm -r UserCode/edwenger/Skims/python
mv UserCode/ASYoon/JulyExercise/python UserCode/edwenger/Skims/


# changes needed for 370
#cp UserCode/ASYoon/JulyExercise/interface/HackedAnalyticalTrackSelector.h UserCode/edwenger/TrkEffAnalyzer/interface
#cp UserCode/ASYoon/JulyExercise/src/SealModules.cc UserCode/edwenger/TrkEffAnalyzer/src

# cleanup
mv UserCode/CmsHi .
mv UserCode/edwenger .
mv UserCode/SavedFMa/Saved/ .
mv UserCode/ASYoon/PbPbTrackingTools/ .
rm -r UserCode/ASYoon
rm -r UserCode/SavedFMa

scram b
