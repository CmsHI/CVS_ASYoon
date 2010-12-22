

while read inputline
    do 
       #filename="$(echo $inputline | cut -d "/" -f12)"
       filename="$(echo $inputline | cut -d "/" -f1)"
       outputfile="$PWD/$filename/res/CMSSW_1.stdout"
       echo "file to be looked at $outputfile"
       #begin="$(cat -n $outputfile  | grep "MessageLogger" | awk '{print $1}')"
       begin="$(cat -n $outputfile  | grep "Cross-sections" | awk '{print $1}')"
       last="$(cat -n $outputfile  | grep "cmsRun ended" | awk '{print $1}')"
       echo "lines begins at $begin and ends at $last"
       range="$begin, ${last}p"
       echo $range
       sed -n "$(echo $range)" $outputfile  > ${filename}_PythiaXsection.txt
done < listOfDIR.txt
