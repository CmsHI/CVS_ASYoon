

inputDir=/Users/andreyoon/Research/pbpbSpectra/firstHi2010/root_files/mc/
inputDirSec=./../rootOutput/

spectraFile=CORRv1_trkhistDATA_nov19_trkhist_c0to5_v2_eta_0.0to1.0_jet_0.0to1000.0_hitrackAna_GEN0_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0
#spectraFile=CORRv1_trkhistMC_nov21_hydjetBass0to5_higoodtrk_extra_v3_eta_0.0to1.0_jet_0.0to1000.0_hitrackAna_GEN1_varBin1_otthist0_correct1to3i0_corrLevEff0_corrLevFak0
trkCorrFile1=trkhistMC_nov21_hydjetBass0to5_higoodtrk_extra_v3

anaDir=hitrackAna
corDir=hitrkEffAnalyzer

isGEN=false
varBin=true


ieta=0
feta=1.0

#scaleF=1E-8
scaleF=1

rebOnly=true
rebinF=4
drawFig=true
saveFile=true


root -l HiCorrectTypeTwoNSave.C+\(\"$inputDir\",\"$inputDirSec\",\"$spectraFile\",\"$trkCorrFile1\",\"$anaDir\",\"$corDir\",$isGEN\,$varBin\,$ieta\,$feta\,$scaleF\,$rebOnly\,$rebinF\,$drawFig\,$saveFile\)


