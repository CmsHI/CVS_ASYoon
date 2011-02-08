#grep "271547" /tmp/y_alive/*.log | grep "Job submitted" | awk -F'/' '{print $4}' | awk -F'.' '{print $1".root"}'



#dir=$1
dir=JM-R10A-PR4-Jet50Uskim-v0_sub1
odir=${dir}_qurantine

if [ -d $odir ]
    then
    echo "$odir exists"
else
    mkdir $odir
    echo "$odir is created!"
fi

while read inputline
    do
      filename="$(echo $inputline | awk '{ print $2}')"
      #echo "file number is $filename"
      corrfile="$(grep $filename /tmp/y_alive/*.log | grep "Job submitted" | awk -F'/' '{print $4}' | awk -F'.' '{print $1".root"}')"
      echo "corrupted file is $corrfile"
      #echo mv ./$dir/$corrfile ./$odir
      mv ./$dir/$corrfile ./$odir
done < rm.sh
