

inputDir=/Users/andreyoon/Research/ana/spectra/pp_spectra/7TeV/root_files/
outputDir=./rootOutput/

#if [ -d $outputDir ]
#    then
#    echo "$outputDir exists"
#else
#    mkdir $outputDir
#    echo "$outputDir is created!"
#fi

#spectraFile=MB-C10-PR9-MBskim-v0_proc0710_trkAnaNoFilter
spectraFile=MB-C10-M6RR-MBskim-v0_proc0710_trkAnaNoFilte
#spectraFile=trkhists_r132440
#spectraFile=trkhists_r132440_v2
evteffFile=TrkHistMC_july09v2_qcdMBD6TdJuly09V3

anaDir=trackAna_STD
corDir=trkEffAnalyzer

#anaDir=looseTrackAna_STD
#corDir=loosetrkEffAnalyzer

#corrF=1
corrF=1.07716

isGEN=false
saveFile=true

root -l -q GetCorrectedNumEvent.C+\(\"$inputDir\",\"$outputDir\",\"$spectraFile\",\"$evteffFile\",\"$anaDir\",\"$corDir\",$corrF\,$isGEN\,$saveFile\)