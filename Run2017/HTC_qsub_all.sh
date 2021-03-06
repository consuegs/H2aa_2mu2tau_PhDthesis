#!/bin/sh 
#Submit data samples:
for i in B C D E F
do
./HTC_qsub_seq.sh analysis_macro analysisMacro.conf SingleMuon_Run2017$i 20
done

#Submit signal MC samples:
for i in 3p6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
do
./HTC_qsub_seq.sh analysis_macro analysisMacro_ggH.conf SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$i 3
done

#Submit background MC samples:
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf DYJetsToLL_M-10to50_13TeV-madgraphMLM 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf DYJetsToLL_M-50_13TeV-madgraphMLM 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf ST_tW_top_5f_inclusiveDecays_13TeV-powheg 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf WW_13TeV-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf WZ_13TeV-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf ZZ_13TeV-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf TTToHadronic_TuneCP5_13TeV-powheg-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf WJetsToLNu_13TeV-madgraphMLM 30
#./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-20toInf_MuEnrichedPt15_13TeV 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-20to30_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-30to50_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-50to80_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-80to120_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-120to170_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-170to300_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-300to470_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-470to600_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-600to800_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5 30
./HTC_qsub_seq.sh analysis_macro analysisMacro_mc.conf QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5 30

