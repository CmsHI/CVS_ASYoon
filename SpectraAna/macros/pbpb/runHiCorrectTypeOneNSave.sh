
outputDir=/Users/andreyoon/Research/pbpbSpectra/rootOutput/jan112011/

if [ -d $outputDir ]
    then
    echo "$outputDir exists"
else
    mkdir $outputDir
    echo "$outputDir is created!"
fi

#dirData=/Users/andreyoon/Research/pbpbSpectra/FirstHi2010/root_files/data/
#dirData=/Users/andreyoon/Research/pbpbSpectra/FirstHi2010/root_files/mc/
#dirCorr=/Users/andreyoon/Research/pbpbSpectra/firstHi2010/root_files/mc/

dirData=/Users/andreyoon/Research/pbpbSpectra/root_files/data/
dirCorr=/Users/andreyoon/Research/pbpbSpectra/root_files/mc/

# make sure *to* and *To*

#data
#spectraFile=HCPR-hcpr-spectra-v2-0to5_proc_jan102011
#spectraFile=HCPR-hcpr-spectra-v2-5to10_proc_jan102011
#spectraFile=HCPR-hcpr-spectra-v2-10to30_proc_jan102011
#spectraFile=HCPR-hcpr-spectra-v2-30to50_proc_jan102011
spectraFile=HCPR-hcpr-spectra-v2-50to100_proc_jan102011

# all centrality
#spectraFile=trkhist_dec222010_v1_hydjetBassAllCent_off393
#spectraFile=trkhist_dec222010_v1_hydjetBassAllCent_dijet50

trkCorrFile1=trkhist_dec222010_v1_hydjetBassAllCent_off393
trkCorrFile2=trkhist_dec222010_v1_hydjetBassAllCent_dijet30
trkCorrFile3=trkhist_dec222010_v1_hydjetBassAllCent_dijet50
trkCorrFile4=trkhist_dec222010_v1_hydjetBassAllCent_dijet80
trkCorrFile5=trkhist_dec222010_v1_hydjetBassAllCent_dijet110
trkCorrFile6=trkhist_dec222010_v1_hydjetBassAllCent_dijet170


# 50~100% 
#spectraFile=trkhist_dec222010_v1_hydjetBass50to100_off393_v2
#spectraFile=trkhist_dec222010_v1_hydjetBass50to100_dijet30
#spectraFile=trkhist_dec222010_v1_hydjetBass50to100_dijet50
#spectraFile=trkhist_dec222010_v1_hydjetBass50to100_dijet80

#trkCorrFile1=trkhist_dec222010_v1_hydjetBass50to100_off393_v2
#trkCorrFile2=trkhist_dec222010_v1_hydjetBass50to100_dijet30
#trkCorrFile3=trkhist_dec222010_v1_hydjetBass50to100_dijet50
#trkCorrFile4=trkhist_dec222010_v1_hydjetBass50to100_dijet80
#trkCorrFile5=trkhist_dec222010_v1_hydjetBass50to100_dijet110
#trkCorrFile6=trkhist_dec222010_v1_hydjetBass50to100_dijet170

# 30~50%
#spectraFile=trkhist_dec222010_v1_hydjetBass30to50_off393_v2 
#spectraFile=trkhist_dec222010_v1_hydjetBass30to50_dijet30
#spectraFile=trkhist_dec222010_v1_hydjetBass30to50_dijet50
#spectraFile=trkhist_dec222010_v1_hydjetBass30to50_dijet80

#trkCorrFile1=trkhist_dec222010_v1_hydjetBass30to50_off393_v2
#trkCorrFile2=trkhist_dec222010_v1_hydjetBass30to50_dijet30
#trkCorrFile3=trkhist_dec222010_v1_hydjetBass30to50_dijet50
#trkCorrFile4=trkhist_dec222010_v1_hydjetBass30to50_dijet80
#trkCorrFile5=trkhist_dec222010_v1_hydjetBass30To50_dijet110
#trkCorrFile6=trkhist_dec222010_v1_hydjetBass30To50_dijet170

# 10~30% 
#spectraFile=trkhist_dec222010_v1_hydjetBass10to30_off393_v3
#spectraFile=trkhist_dec222010_v1_hydjetBass10to30_dijet30
#spectraFile=trkhist_dec222010_v1_hydjetBass10to30_dijet50
#spectraFile=trkhist_dec222010_v1_hydjetBass10to30_dijet80

#trkCorrFile1=trkhist_dec222010_v1_hydjetBass10to30_off393_v2
#trkCorrFile2=trkhist_dec222010_v1_hydjetBass10to30_dijet30
#trkCorrFile3=trkhist_dec222010_v1_hydjetBass10to30_dijet50
#trkCorrFile4=trkhist_dec222010_v1_hydjetBass10to30_dijet80
#trkCorrFile5=trkhist_dec222010_v1_hydjetBass10to30_dijet110
#trkCorrFile6=trkhist_dec222010_v1_hydjetBass10to30_dijet170

# 5~10%
#spectraFile=trkhist_dec222010_v1_hydjetBass5to10_off393_v2
#spectraFile=trkhist_dec222010_v1_hydjetBass5to10_dijet30
#spectraFile=trkhist_dec222010_v1_hydjetBass5to10_dijet50
#spectraFile=trkhist_dec222010_v1_hydjetBass5to10_dijet80

#trkCorrFile1=trkhist_dec222010_v1_hydjetBass5to10_off393_v2
#trkCorrFile2=trkhist_dec222010_v1_hydjetBass5to10_dijet30
#trkCorrFile3=trkhist_dec222010_v1_hydjetBass5to10_dijet50
#trkCorrFile4=trkhist_dec222010_v1_hydjetBass5to10_dijet80
#trkCorrFile5=trkhist_dec222010_v1_hydjetBass5To10_dijet110
#trkCorrFile6=trkhist_dec222010_v1_hydjetBass5To10_dijet170

# 0~5%
#spectraFile=trkhist_dec222010_v1_hydjetBass0to5_off393
#spectraFile=trkhist_dec222010_v1_hydjetBass0to5_dijet30
#spectraFile=trkhist_dec222010_v1_hydjetBass0to5_dijet50_v2
#spectraFile=trkhist_dec222010_v1_hydjetBass0to5_dijet80

#trkCorrFile1=trkhist_dec222010_v1_hydjetBass0to5_off393
#trkCorrFile2=trkhist_dec222010_v1_hydjetBass0to5_dijet30
#trkCorrFile3=trkhist_dec222010_v1_hydjetBass0to5_dijet50_v2
#trkCorrFile4=trkhist_dec222010_v1_hydjetBass0to5_dijet80
#trkCorrFile5=trkhist_dec222010_v1_hydjetBass0To5_dijet110
#trkCorrFile6=trkhist_dec222010_v1_hydjetBass0To5_dijet170


anaDir=hitrackAna
corDir=hitrkEffAnalyzer

#anaDir=looseTrackAna_STD
#corDir=loosetrkEffAnalyzer

isGEN=false
varBin=true


ijet=0
fjet=1000

ieta=0
#feta=2.4
feta=1.0


scale=1

debug=true
onetothree=false
correc1to3=false


drawFig=true
saveFile=true

secOrdCorrLevEf=0
secOrdCorrLevFak=0

version=1


root -l  HiCorrectTypeOneNSave.C++\(\"$dirData\",\"$dirCorr\",\"$outputDir\",\"$spectraFile\",\"$trkCorrFile1\",\"$trkCorrFile2\",\"$trkCorrFile3\",\"$trkCorrFile4\",\"$trkCorrFile5\",\"$trkCorrFile6\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ijet\,$fjet\,$ieta\,$feta\,$scale\,$secOrdCorrLevEf\,$secOrdCorrLevFak\,$debug\,$onetothree\,$correc1to3\,$drawFig\,$saveFile\,$version\)