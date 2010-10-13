
inputDir=/Users/andreyoon/Research/pp7TeV/root_files_postApp/
inputDirSec=./../rootOutput_postApp/


#if [ -d $outputDir ]
#    then
#    echo "$outputDir exists"
#else
#    mkdir $outputDir
#    echo "$outputDir is created!"
#fi



spectraFile=CORR_MB-C10-PR9-MBskim-v0_proc0710_trkAnaNoFilter_eta_0.0to2.4_jet_0.0to60.0_trackAna_STD_GEN0_varBin1_otthist0_correct1to3i1_corrLevEff0_corrLevFak0
trkCorrFile1=TrkHistGEN_oct06_qcdMBD6TV1

anaDir=trackAna_STD
corDir=trkEffAnalyzer

isGEN=false
varBin=true


ieta=0
feta=2.4

scaleF=1E-8

rebOnly=false
rebinF=4
drawFig=true
saveFile=true


root -l CorrectTypeTwoNSave.C+\(\"$inputDir\",\"$inputDirSec\",\"$spectraFile\",\"$trkCorrFile1\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ieta\,$feta\,$scaleF\,$rebOnly\,$rebinF\,$drawFig\,$saveFile\)


