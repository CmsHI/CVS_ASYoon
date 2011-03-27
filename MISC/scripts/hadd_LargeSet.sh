
while read inputline
  do
    echo "==================Start======================="
    ofile="$(echo $inputline | sed 's/LargeSet1_//g' )"
    echo "output file name is $ofile"
    ifile="$(echo $inputline | awk -F"Set" '{print $1}')"
    ifile2="$(echo $inputline | awk -F"Set" '{print $2}' | awk -F"nq" '{print $2}')"
    echo "intpt files are ${ifile}*${ifile2}"
    ls ${ifile}*${ifile2}
    #echo hadd -f $ofile ${ifile}*${ifile2}
    hadd -f $ofile ${ifile}*${ifile2}
    echo "==================Finished====================="
    sleep 10
done < listOfLargetSet.txt

