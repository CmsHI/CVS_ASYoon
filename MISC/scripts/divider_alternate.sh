

# idea is to first create dir1 and dir2 
# copy files to dir1 and dir2 alternatively
# this way, don't need to bother with the number of files business


odir=$1
flist=$2
#nfile=$2

nfileorig="$(ls $odir | wc -l)"
half=$((nfileorig / 2))
echo "$nfileorig files exists in $odir and a half of them is $half"

ndir1=${odir}_div1
ndir2=${odir}_div2
ndir3=${odir}_div3
ndir4=${odir}_div4
ndir5=${odir}_div5
ndir6=${odir}_div6
ndir7=${odir}_div7
ndir8=${odir}_div8
echo "newly created directories are $ndir1, $ndir2, $ndir3, $ndir4, $ndir5, $ndir6, $ndir7, $ndir8"

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

if [ -d $ndir3 ]
then
    echo "$ndir3 exists"
else
    mkdir $ndir3
    echo "$ndir3 is created"
fi

if [ -d $ndir4 ]
then
    echo "$ndir4 exists"
else
    mkdir $ndir4
    echo "$ndir4 is created"
fi

if [ -d $ndir5 ]
then
    echo "$ndir5 exists"
else
    mkdir $ndir5
    echo "$ndir5 is created"
fi

if [ -d $ndir6 ]
then
    echo "$ndir6 exists"
else
    mkdir $ndir6
    echo "$ndir6 is created"
fi


if [ -d $ndir7 ]
then
    echo "$ndir7 exists"
else
    mkdir $ndir7
    echo "$ndir7 is created"
fi

if [ -d $ndir8 ]
then
    echo "$ndir8 exists"
else
    mkdir $ndir8
    echo "$ndir8 is created"
fi




test=$(( nfileorig % 2 ))
echo $test
#ls ${odir} > list.txt
#cat $PWD/list.txt  | awk '{print $9}' > listfiles.txt

nfilendir1=0

while read inputline ; do
    file=${odir}/$inputline
    echo $file
    #nfilendir1="$(ls $ndir1 | wc -l)"
    #nfilendir1 = $(( nfilendir1 + 1 ))
    echo "number of file in new directory is $nfilendir1"  
    #nfilemodulo=$(( nfilendir1 % 2 ))
    nfilendir1=`expr $nfilendir1 + 1`
    nfilemodulo=$(( nfilendir1 % 8 ))    
    echo "modulo is $nfilemodulo"
    if [ $nfilemodulo -eq 0 ] 
    then 
	echo cp $file $ndir1
	cp $file $ndir1
    elif [ $nfilemodulo -eq 1 ]
    then
	echo cp $file $ndir2
	cp $file $ndir2
    elif [ $nfilemodulo -eq 2 ]
    then
        echo cp $file $ndir3
        cp $file $ndir3
    elif [ $nfilemodulo -eq 3 ]
    then
        echo cp $file $ndir4
        cp $file $ndir4
    elif [ $nfilemodulo -eq 4 ]
    then
        echo cp $file $ndir5
        cp $file $ndir5                    
    elif [ $nfilemodulo -eq 5 ]
    then
        echo cp $file $ndir6
        cp $file $ndir6          
    elif [ $nfilemodulo -eq 6 ]
    then
        echo cp $file $ndir7
        cp $file $ndir7          
    else 
        echo cp $file $ndir8
        cp $file $ndir8
    fi
done < $flist