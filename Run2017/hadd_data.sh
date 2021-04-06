#!/bin/sh 
#Join root files corresponding to signal MC samples:
for i in B C D E F
do
./hadd.sh SingleMuon_Run2017$i
done

rm SingleMuon_Run2017.root 

hadd SingleMuon_Run2017.root SingleMuon_Run2017B.root SingleMuon_Run2017C.root SingleMuon_Run2017D.root SingleMuon_Run2017E.root SingleMuon_Run2017F.root
