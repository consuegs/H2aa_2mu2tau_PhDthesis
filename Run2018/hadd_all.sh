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

#Join root files corresponding to signal MC samples:
for i in 3p6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
do
./hadd.sh SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$i
done

#Join root files corresponding to background MC samples:
./hadd.sh DYJetsToLL_M-10to50_13TeV-madgraphMLM
./hadd.sh DYJetsToLL_M-50_13TeV-madgraphMLM
./hadd.sh WW_13TeV-pythia8
./hadd.sh WZ_13TeV-pythia8
./hadd.sh ZZ_13TeV-pythia8
./hadd.sh ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg
./hadd.sh ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg
./hadd.sh ST_tW_top_5f_inclusiveDecays_13TeV-powheg
./hadd.sh ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg
./hadd.sh TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8
./hadd.sh TTToHadronic_TuneCP5_13TeV-powheg-pythia8
./hadd.sh TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8
./hadd.sh WJetsToLNu_13TeV-madgraphMLM
#./hadd.sh QCD_Pt-20toInf_MuEnrichedPt15_13TeV
./hadd.sh QCD_Pt-20to30_MuEnrichedPt5_TuneCP5  
./hadd.sh QCD_Pt-30to50_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-50to80_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-80to120_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-120to170_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-170to300_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-300to470_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-470to600_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-600to800_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5
./hadd.sh QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5


