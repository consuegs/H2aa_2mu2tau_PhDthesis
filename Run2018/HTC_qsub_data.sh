#!/bin/sh 
#Submit data samples:
for i in A B C D
do
./HTC_qsub_seq.sh analysis_macro analysisMacro.conf SingleMuon_Run2018$i 20
done
