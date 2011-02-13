#!/bin/sh

outputDir=xsection
outputName=pythia6_d6t_2760GeV_feb102011

i=0
xsec_cum=0
while read inputline
  do 
    filename="$(echo $inputline | cut -d "/" -f1)"
    echo "file name = $filename"
    grep $filename ./xsection/xsection_$outputName.dat | awk '{print $2}'
    axsec[$i]="$(grep $filename ./xsection/xsection_$outputName.dat | awk '{print $2}')"
    echo "$i th cross section = ${axsec[$i]}"
    if [ $i -gt 0 ]
    	then 
	echo "$xsec_cum and ${axsec[$i]} is added"
    	xsec_cum=`echo $xsec_cum  ${axsec[$i]} | awk '{print $1+$2}'`
	echo " result is = $xsec_cum"
    fi
    i=$((i+1))
done < orderedList.txt

echo "Sum of all the cross section except for the first pt_hat bin = $xsec_cum"

xsec_1st=`echo ${axsec[0]} $xsec_cum | awk '{print $1-$2}'`
echo $xsec_1st > ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[1]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[2]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[3]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[4]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[5]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[6]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[7]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[8]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[9]} >> ./xsection/xsection_${outputName}_recast.dat
echo ${axsec[10]} >> ./xsection/xsection_${outputName}_recast.dat


