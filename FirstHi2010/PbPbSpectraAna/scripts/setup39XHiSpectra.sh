#!/bin/sh

cd $CMSSW_BASE/src

# skiming and ana
cvs co UserCode/FirstHi2010/PbPbSpectraAna

# centrality related 
#cvs co -r UserCode/CmsHi/JulyExercise/data/CentralityTables.db
#cvs co -r HEAD RecoHI/HiCentralityAlgos
#cvs co -r HEAD DataFormats/HeavyIonEvent
 
# analyzers
cvs co UserCode/edwenger/VertexAnalyzer
cvs co UserCode/edwenger/HiTrackSpectraAnalyzer
cvs co UserCode/edwenger/HiTrkEffAnalyzer

# needed for dijetana
#cvs co DataFormats/HeavyIonEvent
#cvs co HeavyIonsAnalysis/Configuration
#cvs co RecoHI/HiMuonAlgos

# vertex constraint for refitting
cvs co UserCode/ASYoon/PbPbTrackingTools/VertexConstraintProducer

# setting and cleanup
mv UserCode/edwenger .
mv UserCode/ASYoon/PbPbTrackingTools .
mv UserCode/FirstHi2010 .

#scram b
