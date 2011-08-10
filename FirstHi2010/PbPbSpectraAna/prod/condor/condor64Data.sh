#!/bin/bash

dir=`pwd`
#ldir=~/scratch01/condor
ldir=/net/hisrv0001/home/y_alive/scratch2/condor
echo $subfile
#mkdir -p $ldir
mkdir -p /tmp/y_alive
exe=$dir/$1
cfg=$2
infile=$4
outfile=$1-output-$infile-`date +"%s"`
subfile=subfile_$outfile

shift # don't count the exe as the arguments

cat > $subfile <<EOF

Universe     = vanilla

Notification = Error
Executable   = $exe
Arguments    = $@
Requirements = (Mips > 900) && (ARCH=="X86_64")
Image_Size = 1800 Meg
Rank         = Mips
GetEnv       = True

Initialdir   = $dir
Input        = /dev/null
Output       = $ldir/$outfile.out
Error        = $ldir/$outfile.err
Log          = $ldir/$outfile.log
Notify_user  = y_alive@mit.edu

+AccountingGroup = "group_cmshi.sungho"
transfer_input_files = $cfg,json.txt 
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT

Queue
EOF

#sleep 1
cat $subfile

echo Executable   = $exe
echo Arguments    = $@


condor_submit $subfile
#sleep 1
rm $subfile
