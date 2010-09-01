

#inputDir=/home/sungho/plots/7TeV/root_files/
inputDir=/Users/andreyoon/Research/ana/spectra/pp_spectra/7TeV/root_files/
outputDir=./rootOutput_aug3/
#outputDir=.//

if [ -d $outputDir ]
    then
    echo "$outputDir exists"
else
    mkdir $outputDir
    echo "$outputDir is created!"
fi


#spectraFile=MB-C10-PR9-JMTskim-v0_proc0710_trkAnaNoFilter
#spectraFile=MB-C10-PR9-MBskim-v0_proc0710_trkAnaNoFilter
#spectraFile=MB-C10-M6RR-JMTskim-v0_proc0710_trkAnaNoFilte
#spectraFile=MB-C10-M6RR-MBskim-v0_proc0710_trkAnaNoFilte
#spectraFile=JMT-R10A-PR1-JMTskim-v0_proc0710_trkAnaNoFilte

#spectraFile=TrkHistMC_july09v2_qcdMBD6TdJuly09V3
#spectraFile=TrkHistMC_july09v2_qcdPt30dJuly09V2
#spectraFile=TrkHistMC_july09v2_qcdPt80dJuly09V2
#spectraFile=trkhists_r132440
#spectraFile=trkhists_r132440_v2 # loose track

#spectraFile=TrkHistGEN_aug06_qcdMBP0
#spectraFile=TrkHistGEN_aug06_qcdMBPY8
#spectraFile=TrkHistGEN_aug06_qcdPt30Herwig
#spectraFile=TrkHistGEN_aug06_qcdPt80Herwig
spectraFile=TrkHistGEN_aug06_qcdPt170HerwigJim

trkCorrFile1=TrkHistMC_july09v2_qcdMBD6TdJuly09V3
trkCorrFile2=TrkHistMC_july09v2_qcdPt15dJuly09
trkCorrFile3=TrkHistMC_july09v2_qcdPt30dJuly09V2
trkCorrFile4=TrkHistMC_july09v2_qcdPt80dJuly09V2
trkCorrFile5=TrkHistMC_july09v2_qcdPt170dJuly09


#spectraFile=TrkHistMC_july04_qcdMBD6T0704vbinV2
#trkCorrFile1=TrkHistMC_july04_qcdMBD6T0704vbinV2
#trkCorrFile2=TrkHistMC_july04_qcdPt15d0704vbinV2
#trkCorrFile3=TrkHistMC_july04_qcdPt15d0704vbinV2
#trkCorrFile4=TrkHistMC_july04_qcdPt15d0704vbinV2
#trkCorrFile5=TrkHistMC_july04_qcdPt170d0704vbinV2


anaDir=trackAna_STD
corDir=trkEffAnalyzer

#anaDir=looseTrackAna_STD
#corDir=loosetrkEffAnalyzer


isGEN=false
varBin=true


ijet=0
fjet=2000

#ijet=0
#fjet=60

#ijet=60
#fjet=2000

ieta=0
feta=2.4

scale=1

debug=false
onetothree=false
correc1to3=false

drawFig=true
saveFile=true



#root -l -q  CorrectTypeOneNSave.C++\(\"$inputDir\",\"$outputDir\",\"$spectraFile\",\"$trkCorrFile1\",\"$trkCorrFile2\",\"$trkCorrFile3\",\"$trkCorrFile4\",\"$trkCorrFile5\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ijet\,$fjet\,$ieta\,$feta\,$scale\,$debug\,$drawFig\,$saveFile\)


root -l  CorrectTypeOneNSave.C++\(\"$inputDir\",\"$outputDir\",\"$spectraFile\",\"$trkCorrFile1\",\"$trkCorrFile2\",\"$trkCorrFile3\",\"$trkCorrFile4\",\"$trkCorrFile5\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ijet\,$fjet\,$ieta\,$feta\,$scale\,$debug\,$onetothree\,$correc1to3\,$drawFig\,$saveFile\)