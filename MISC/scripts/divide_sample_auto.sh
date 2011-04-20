

while read inputline
  do
    odir=$inputline
    echo "Original directory = $odir"

    ls ./$odir/*.root | awk -F'/' '{print $3}' > templist.txt
    flist=templist.txt
    
    nfileorig="$(ls $odir | wc -l)"
    half=$((nfileorig / 2))
    echo "$nfileorig files exists in $odir and a half of them is $half"

    ndir1=${odir}_div1
    ndir2=${odir}_div2

    if [ -d $ndir1 ]
	then
	echo "$ndir1 exists"
    else
	mkdir $ndir1
	echo "$ndir1 is created"
    fi
    
    if [ -d $ndir2 ]
	then
	echo "$ndir2 exists"
    else
	mkdir $ndir2
	echo "$ndir2 is created"
    fi
    
    nfilendir1=0
    while read inputline ; do
	file=${odir}/$inputline
	echo $file
	echo "number of file in new directory is $nfilendir1"
	nfilendir1=`expr $nfilendir1 + 1`
	nfilemodulo=$(( nfilendir1 % 2 ))
	echo "modulo is $nfilemodulo"
	if [ $nfilemodulo -eq 0 ]
	    then
	    echo cp $file $ndir1
	    cp $file $ndir1
	else
	    echo cp $file $ndir2
	    cp $file $ndir2
	fi
    done < $flist	
done < listOfDIR.txt
