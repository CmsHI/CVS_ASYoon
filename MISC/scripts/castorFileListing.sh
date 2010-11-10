

if [ -f inputlist.txt ]
    then
    rm inputlist.txt
    echo "inputlist.txt exists so removed"
else
    echo "inputlist.txt doesn't exist"
fi




while read inputline
  do
     directory="$(echo $inputline)" 
     targetdir="$PWD/$(echo $inputline | cut -d "/" -f11)"

     echo $directory
     echo $targetdir

     rfdir ${directory} > list.txt
     cat $PWD/list.txt  | awk '{print "rfio:'$directory'/"$9}' > listfiles.txt

     while read inputlineline
       do
       echo "'"$inputlineline"'," >> inputlist.txt
     done < listfiles.txt
     
     rm list.txt
     rm listfiles.txt

done < listOfDIR.txt
