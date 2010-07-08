#!/bin/sh

cd $CMSSW_BASE/src

# skiming code
cvs co UserCode/edwenger/Skims

# analyzers
cvs co UserCode/edwenger/VertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/TrkEffAnalyzer

# july ex. 
cvs co UserCode/ASYoon/JulyExercise
cvs co UserCode/SavedFMa/Saved

# replace with hi-specific 
rm -r UserCode/edwenger/Skims/python
mv UserCode/ASYoon/JulyExercise/python UserCode/edwenger/Skims/
#cp UserCode/ASYoon/JulyExercise/test/*.* UserCode/edwenger/Skims/test

# changes needed for 370
cp UserCode/ASYoon/JulyExercise/interface/HackedAnalyticalTrackSelector.h UserCode/edwenger/TrkEffAnalyzer/interface
cp UserCode/ASYoon/JulyExercise/src/SealModules.cc UserCode/edwenger/TrkEffAnalyzer/src

# cleanup
mv UserCode/edwenger .
mv UserCode/SavedFMa/Saved/ .
rm -r UserCode/ASYoon
rm -r UserCode/SavedFMa

scram b
