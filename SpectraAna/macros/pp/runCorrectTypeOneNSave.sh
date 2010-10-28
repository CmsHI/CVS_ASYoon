

inputDir=/Users/andreyoon/Research/pp7TeV/root_files/
outputDir=./../rootOutput_postApp/

if [ -d $outputDir ]
    then
    echo "$outputDir exists"
else
    mkdir $outputDir
    echo "$outputDir is created!"
fi


#spectraFile=MB-R10A-Jun14RR-MBskim-v0_proc0907
#spectraFile=JMT-R10A-Jun14RR-J15Uskim-v0_proc0907
#spectraFile=TrkHistGEN_aug06_qcdPt170HerwigJim
#trkCorrFile1=TrkHistMC_july09v2_qcdMBD6TdJuly09V3
#trkCorrFile2=TrkHistMC_july09v2_qcdPt15dJuly09
#trkCorrFile3=TrkHistMC_july09v2_qcdPt30dJuly09V2
#trkCorrFile4=TrkHistMC_july09v2_qcdPt80dJuly09V2
#trkCorrFile5=TrkHistMC_july09v2_qcdPt170dJuly09
#trkCorrFile6=TrkHistMC_july09v2_qcdPt170dJuly09
#trkCorrFile6=TrkHistGEN_aug31_v1_qcdPt300

#spectraFile=TrkHistMC_july09v2_qcdMBD6TdJuly09V3 
#spectraFile=TrkHistMC_july09v2_qcdPt30dJuly09V2
#spectraFile=TrkHistMC_july09v2_qcdPt80dJuly09V2
#trkCorrFile1=TrkHistMC_july09v2_qcdMBD6TdJuly09V3 
#trkCorrFile2=TrkHistMC_july09v2_qcdPt15dJuly09 
#trkCorrFile3=TrkHistMC_july09v2_qcdPt30dJuly09V2 
#trkCorrFile4=TrkHistMC_july09v2_qcdPt80dJuly09V2 
#trkCorrFile5=TrkHistMC_july09v2_qcdPt170dJuly09
#trkCorrFile6=TrkHistMC_july09v2_qcdPt170dJuly09

spectraFile=TrkHistMC_july09v2_qcdMBD6TdJuly09V3_div1
#spectraFile=TrkHistMC_july09v2_qcdPt30dJuly09V2_div1
#spectraFile=TrkHistMC_july09v2_qcdPt80dJuly09V2_div1
trkCorrFile1=TrkHistMC_july09v2_qcdMBD6TdJuly09V3_div2
trkCorrFile2=TrkHistMC_july09v2_qcdPt15dJuly09_div2
trkCorrFile3=TrkHistMC_july09v2_qcdPt30dJuly09V2_div2
trkCorrFile4=TrkHistMC_july09v2_qcdPt80dJuly09V2_div2
trkCorrFile5=TrkHistMC_july09v2_qcdPt170dJuly09_div2
trkCorrFile6=TrkHistMC_july09v2_qcdPt170dJuly09_div2

#anaDir=trackAna_STD
anaDir=trackAna
#anaDir=preTrackAna
corDir=trkEffAnalyzer

#anaDir=looseTrackAna_STD
#corDir=loosetrkEffAnalyzer

#anaDir=looseTrackAna
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

#scale=6.01167e+06
scale=1

debug=false
onetothree=false
correc1to3=false

drawFig=true
saveFile=true

secOrdCorrLevEf=1
secOrdCorrLevFak=2

version=1


root -l  CorrectTypeOneNSave.C++\(\"$inputDir\",\"$outputDir\",\"$spectraFile\",\"$trkCorrFile1\",\"$trkCorrFile2\",\"$trkCorrFile3\",\"$trkCorrFile4\",\"$trkCorrFile5\",\"$trkCorrFile6\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ijet\,$fjet\,$ieta\,$feta\,$scale\,$secOrdCorrLevEf\,$secOrdCorrLevFak\,$debug\,$onetothree\,$correc1to3\,$drawFig\,$saveFile\,$version\)