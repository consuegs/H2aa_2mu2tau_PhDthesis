#!/bin/sh 
#Submit data samples:
for i in B C D E F
do
./HTC_qsub_seq.sh analysis_macro analysisMacro.conf SingleMuon_Run2017$i 20
done
