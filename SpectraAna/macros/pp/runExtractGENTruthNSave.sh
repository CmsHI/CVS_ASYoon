

#inputDir=/home/sungho/plots/7TeV/root_files/
#inputDir=/Users/andreyoon/Research/ana/spectra/pp_spectra/7TeV/root_files/
#outputDir=./rootOutput/



if [ -d $outputDir ]
    then
    echo "$outputDir exists"
else
    mkdir $outputDir
    echo "$outputDir is created!"
fi


#cXsection=xsection_pythia6_d6tv2_july28
#file1=TrkHistGEN_july28_d6tv2_qcdPt0to20V2
#file2=TrkHistGEN_july28_d6tv2_qcdPt20to30V2
#file3=TrkHistGEN_july28_d6tv2_qcdPt30to50V2
#file4=TrkHistGEN_july28_d6tv2_qcdPt50to80V2
#file5=TrkHistGEN_july28_d6tv2_qcdPt80to120V2
#file6=TrkHistGEN_july28_d6tv2_qcdPt120to170V2
#file7=TrkHistGEN_july28_d6tv2_qcdPt170to230V2
#file8=TrkHistGEN_july28_d6tv2_qcdPt230to300V2
#file9=TrkHistGEN_july28_d6tv2_qcdPt300to380V2
#file10=TrkHistGEN_july28_d6tv2_qcdPt380to470V2

#cXsection=xsection_pythia6_p0_july28
#file1=TrkHistGEN_july28_p0_qcdPt0to20V2
#file2=TrkHistGEN_july28_p0_qcdPt20to30V2
#file3=TrkHistGEN_july28_p0_qcdPt30to50V2
#file4=TrkHistGEN_july28_p0_qcdPt50to80V2
#file5=TrkHistGEN_july28_p0_qcdPt80to120V2
#file6=TrkHistGEN_july28_p0_qcdPt120to170V2
#file7=TrkHistGEN_july28_p0_qcdPt170to230V2
#file8=TrkHistGEN_july28_p0_qcdPt230to300V2
#file9=TrkHistGEN_july28_p0_qcdPt300to380V2
#file10=TrkHistGEN_july28_p0_qcdPt380to470V2

#cXsection=xsection_pythia6_proq20_july28
#file1=TrkHistGEN_july28_proq20_qcdPt0to20V2
#file2=TrkHistGEN_july28_proq20_qcdPt20to30V2
#file3=TrkHistGEN_july28_proq20_qcdPt30to50V2
#file4=TrkHistGEN_july28_proq20_qcdPt50to80V2
#file5=TrkHistGEN_july28_proq20_qcdPt80to120V2
#file6=TrkHistGEN_july28_proq20_qcdPt120to170V2
#file7=TrkHistGEN_july28_proq20_qcdPt170to230V2
#file8=TrkHistGEN_july28_proq20_qcdPt230to300V2
#file9=TrkHistGEN_july28_proq20_qcdPt300to380V2
#file10=TrkHistGEN_july28_proq20_qcdPt380to470V2

#cXsection=xsection_pythia6_atlas_july28
#file1=TrkHistGEN_july28_atlas_qcdPt0to20
#file2=TrkHistGEN_july28_atlas_qcdPt20to30
#file3=TrkHistGEN_july28_atlas_qcdPt30to50
#file4=TrkHistGEN_july28_atlas_qcdPt50to80
#file5=TrkHistGEN_july28_atlas_qcdPt80to120
#file6=TrkHistGEN_july28_atlas_qcdPt120to170
#file7=TrkHistGEN_july28_atlas_qcdPt170to230
#file8=TrkHistGEN_july28_atlas_qcdPt230to300
#file9=TrkHistGEN_july28_atlas_qcdPt300to380
#file10=TrkHistGEN_july28_atlas_qcdPt380to470

cXsection=xsection_pythia8_tune1_july28_v3
file1=TrkHistGEN_july28_py8v3_qcdPt0to20V3
file2=TrkHistGEN_july28_py8v3_qcdPt20to30V3
file3=TrkHistGEN_july28_py8v3_qcdPt30to50V3
file4=TrkHistGEN_july28_py8v3_qcdPt50to80V3
file5=TrkHistGEN_july28_py8v3_qcdPt80to120V3
file6=TrkHistGEN_july28_py8v3_qcdPt120to170V3
file7=TrkHistGEN_july28_py8v3_qcdPt170to230V3
file8=TrkHistGEN_july28_py8v3_qcdPt230to300V3
file9=TrkHistGEN_july28_py8v3_qcdPt300to380V3
file10=TrkHistGEN_july28_py8v3_qcdPt380to470V3



anaDir=preTrackAna


isGEN=false
varBin=true

sqrts=70000

ieta=0
feta=2.4
#feta=1.0

ijet=0
fjet=2000


rebinF=4
scale=57.63 #pythia 6
#
#scale=57.71 #pythia 8
#scale=1

pythia8=false

drawFig=true
saveFile=true

root -l ExtractGENTruthNSave.C++\(\"$inputDir\",\"$outputDir\",\"$file1\",\"$file2\",\"$file3\",\"$file4\",\"$file5\",\"$file6\",\"$file7\",\"$file8\",\"$file9\",\"$file10\",\"$cXsection\",\"$anaDir\",$sqrts\,$varBin\,$ijet\,$fjet\,$ieta\,$feta\,$scale\,$rebinF\,$pythia8\,$drawFig\,$saveFile\)


