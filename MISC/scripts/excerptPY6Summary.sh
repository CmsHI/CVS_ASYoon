#!/bin/sh

outputDir=xsection
outputName=pythia6_d6t_2760GeV_feb102011

if [ -d $outputDir ]
    then
    echo "$outputDir exists"
else
    mkdir $outputDir
    echo "$outputDir is created!"
fi

while read inputline
  do 
    filename="$(echo $inputline | cut -d "/" -f1)"  
    outputfile="$PWD/$filename/res/CMSSW_1.stdout" 
    echo "file to be looked at $outputfile" 
    begin="$(cat -n $outputfile  | grep "Cross-sections" | awk '{print $1}')" 
    last="$(cat -n $outputfile  | grep "cmsRun ended" | awk '{print $1}')" 
    echo "lines begins at $begin and ends at $last" 
    range="$begin, ${last}p"                                                                                                                            
    echo $range                                                                                                                                         
    sed -n "$(echo $range)" $outputfile  > ./xsection/${filename}_PythiaXsection.txt  
done < listOfJobs.txt

grep "All included" ./xsection/*.txt | awk '{print $1,$11}' | sed s/D/E/g > ./xsection/xsection_$outputName.dat