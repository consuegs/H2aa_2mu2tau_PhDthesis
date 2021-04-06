
#File lists for 2017 legacy data:
for i in B C D E F
do
ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2017/data/SingleMuon/SingleMuon_Run2017$i-31Mar2018-v1/*root > SingleMuon_Run2017$i
done

#File lists for 2017 MC ntuples v2:
for i in 3p6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2017_v2/'SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-'$i''/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$i
done

#File lists for background MC samples
samples_v3=(DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8
DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8
WW_TuneCP5_13TeV-pythia8
WZ_TuneCP5_13TeV-pythia8
ZZ_TuneCP5_13TeV-pythia8
WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8
TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8
TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8
TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8
)

samples_v4=(ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8
ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8
ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8
ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8
)

names_v3=(DYJetsToLL_M-10to50_13TeV-madgraphMLM
DYJetsToLL_M-50_13TeV-madgraphMLM
WW_13TeV-pythia8
WZ_13TeV-pythia8
ZZ_13TeV-pythia8
WJetsToLNu_13TeV-madgraphMLM
TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8
TTToHadronic_TuneCP5_13TeV-powheg-pythia8
TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8
)

names_v4=(ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg
ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg
ST_tW_top_5f_inclusiveDecays_13TeV-powheg
ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg
)

samples_QCD=(QCD_Pt-20to30_MuEnrichedPt5_TuneCP5  
QCD_Pt-30to50_MuEnrichedPt5_TuneCP5
QCD_Pt-50to80_MuEnrichedPt5_TuneCP5
QCD_Pt-80to120_MuEnrichedPt5_TuneCP5
QCD_Pt-120to170_MuEnrichedPt5_TuneCP5
QCD_Pt-170to300_MuEnrichedPt5_TuneCP5
QCD_Pt-300to470_MuEnrichedPt5_TuneCP5
QCD_Pt-470to600_MuEnrichedPt5_TuneCP5
QCD_Pt-600to800_MuEnrichedPt5_TuneCP5
QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5
QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5
)

k=1
j=1
i=1  

while [ $k -le ${#samples_QCD[@]} ] 
do
    echo "Creating file list for sample" ${samples_QCD[$k]} 
    ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2017/mc_v3/QCD/${samples_QCD[$k]}*/*root > ${samples_QCD[$k]}
      
    k=`expr $k + 1` 
done

while [ $j -le ${#samples_v3[@]} ] 
do
    echo "Creating file list for sample" ${samples_v3[$j]} 
    #ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2017/mc_v3/${samples_v3[$j]}*/*root > ${names_v3[$j]}
    ls /pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/2017/mc/${samples_v3[$j]}*/*root > ${names_v3[$j]}
      
    j=`expr $j + 1` 
done

while [ $i -le ${#samples_v4[@]} ] 
do
    echo "Creating file list for sample" ${samples_v4[$i]} 

    #ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2017/mc_v4/${samples_v4[$i]}*/*root > ${names_v4[$i]}
    ls /pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/2017/mc/${samples_v4[$i]}*/*root > ${names_v4[$i]}
      
    i=`expr $i + 1` 
done

