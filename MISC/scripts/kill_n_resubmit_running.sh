# listOfJobs.txt is a list of crab directory names

while read inputline
    do
       filename="$(echo $inputline | cut -d "/" -f1)"
       echo "file name = $filename"
       crab -status -c $filename > ${filename}_output.txt
       begin="$(cat -n ${filename}_output.txt  | grep "List of jobs Running" | awk '{print $1}')"
       if [ -z "$begin" ]
	   then
	   echo "No Running jobs!"
       else
	   echo "Yes Running jobs!"
	   last="$(cat -n ${filename}_output.txt  | grep "Jobs Done" | awk '{print $1}')"
	   echo "new begins at $newbegin and ends at $newlast"
	   newbegin=$begin
	   newlast=`expr $begin + 1`
	   range="$newbegin, ${newlast}p"
	   echo "real range is $range"
	   jobrange="$(sed -n "$(echo $range)" ${filename}_output.txt | awk '{print $5}')"
	   echo "jobs to be killed and resumitted = $jobrange"
	   #echo crab -kill $jobrange -c $filename
           crab -kill $jobrange -c $filename
	   sleep 5
	   #echo crab -resubmit $jobrange -c $filename
           crab -resubmit $jobrange -c $filename
       fi
       rm ${filename}_output.txt
       sleep 5
done < listOfJobs.txt

