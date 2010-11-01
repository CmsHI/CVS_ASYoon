#! /bin/bash


HLT='/users/cer/HI_HLT_Test391_V0/HIon/V5'
L1T='L1Menu_Commissioning2010_v4'

rm -f OnData_HLT_TEST.py
rm -f OnLine_HLT_TEST.py

nameTag="HI_HLT_Test391_V0_V5"

# for Offline MC running 
hltGetConfiguration --process TEST --full --offline --mc  $HLT TEST > offline_mc_${nameTag}.py

# for Online MC running
hltGetConfiguration --process TEST --full --online --mc  $HLT TEST > online_mc_${nameTag}.py

# for Offline DATA running
hltGetConfiguration --process TEST --full --offline --data --l1 $L1T $HLT TEST > offline_data_${nameTag}.py

# for Online DATA running
hltGetConfiguration --process TEST --full --online  --data --l1 $L1T $HLT TEST > online_data_${nameTag}.py

{
    head -n1 online_data_${nameTag}.py
      echo
      edmConfigFromDB --configName $HLT | hltDumpStream
} > streams.txt

### change autoCond['startup'] to autoCond['mc']
