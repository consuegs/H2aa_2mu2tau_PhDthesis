#!/bin/sh 
#Join root files corresponding to data samples:
for i in A B C D
do
./hadd.sh SingleMuon_Run2018$i
done

rm SingleMuon_Run2018.root 

hadd SingleMuon_Run2018.root SingleMuon_Run2018A.root SingleMuon_Run2018B.root SingleMuon_Run2018C.root SingleMuon_Run2018D.root
rm SingleMuon_FullRun2.root
cp /nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2016/SingleMuon_Run2016.root .
cp /nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2017/SingleMuon_Run2017.root .
hadd SingleMuon_FullRun2.root SingleMuon_Run2016.root SingleMuon_Run2017.root SingleMuon_Run2018.root
