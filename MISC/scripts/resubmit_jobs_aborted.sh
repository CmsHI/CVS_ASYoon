

while read inputline
    do
       filename="$(echo $inputline | cut -d "/" -f1)"
       echo "file name = $filename"
       crab -status -c $filename > ${filename}_output.txt
       begin="$(cat -n ${filename}_output.txt  | grep "You can resubmit them specifying JOB numbers" | awk '{print $1}')"
       if [ -z "$begin" ]
	   then
	   echo "No Aborted jobs!"
       else
	   echo "Yes Aborted jobs!"
	   last="$(cat -n ${filename}_output.txt  | grep "Jobs Done" | awk '{print $1}')"
	   echo "new begins at $newbegin and ends at $newlast"
	   newbegin=`expr $begin + 1`
	   newlast=`expr $begin + 2`
	   range="$newbegin, ${newlast}p"
	   echo "real range is $range"
	   jobrange="$(sed -n "$(echo $range)" ${filename}_output.txt | awk '{print $4}')"
	   echo "jobs to be resumitted = $jobrange"
           #echo crab -resubmit $jobrange -c $filename
	   crab -resubmit $jobrange -c $filename
       fi
       rm ${filename}_output.txt
       sleep 5
done < listOfJobs.txt

