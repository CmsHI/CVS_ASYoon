
v=$1
vmax=$2
try=$3

#i="1"
j="1"



while read inputline
  do
     directory="$(echo $inputline)" 
     targetdir="$PWD/$(echo $inputline | cut -d "/" -f11)"
     echo $directory
     echo $targetdir

     rfdir ${directory} > list.txt
     #cat $PWD/list.txt  | awk '{print $9}' > listfiles.txt
     cat $PWD/list.txt  | awk '{print "rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/"$9}' > listfiles.txt
     #cat $PWD/list.txt  | test="$(awk '{print $9}')" 
     #test="$(cat $PWD/listfiles.txt)"
     #test="$(more)"
     #echo -n $test
     #echo \'$test\'\,  > listInputFiles.txt
     #echo \'$test\'\, 
     while read inputlineline
       do
       echo "'"$inputlineline"',"
     done < listfiles.txt
     #echo "'$test',"
     #cat $PWD
     #while read inputline2 ; do
     #  file=${directory}/$inputline2
     #  echo $file
     #  rfcp $file $targetdir
     #  #echo $file $targetdir
     #done < listfiles.txt
     
     rm list.txt
     rm listfiles.txt

     #mergedfile="TrkHistGEN_oct06_$(echo $inputline | cut -d "/" -f11).root"
     ##echo hadd -T $mergedfile ./$(echo $inputline | cut -d "/" -f11)/*.root
     #hadd -T $mergedfile ./$(echo $inputline | cut -d "/" -f11)/*.root
     #sleep 30
done < listOfDIR.txt

