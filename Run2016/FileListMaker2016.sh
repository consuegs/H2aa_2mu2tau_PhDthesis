#File lists for 2016 legacy data:
#ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2016/data/SingleMuon/SingleMuon_Run2016B-17Jul2018_ver1-v1/*root /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2016/data/SingleMuon/SingleMuon_Run2016B-17Jul2018_ver2-v1/*root > SingleMuon_Run2016B
ls /pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/2016/data_v2/SingleMuon/SingleMuon_Run2016B-17Jul2018_ver2/*root > SingleMuon_Run2016B

for i in C D E F G H
do
#ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2016/data/SingleMuon/SingleMuon_Run2016$i-17Jul2018-v1/*root > SingleMuon_Run2016$i
ls /pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/2016/data_v2/SingleMuon/SingleMuon_Run2016$i/*root > SingleMuon_Run2016$i
done

#File lists for 2016 MC ntuples v2:
for i in 3p6 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016_v2/'SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-'$i''/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$i
done

ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016/SUSYGGH_HToAA_AToTauTau_M-4_madgraph/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-4

#File lists for background MC samples
samples=(DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
WW_TuneCUETP8M1_13TeV-pythia8
WZ_TuneCUETP8M1_13TeV-pythia8
ZZ_TuneCUETP8M1_13TeV
ST_t-channel_top_4f
ST_t-channel_antitop_4f
ST_tW_top_5f
ST_tW_antitop_5f
TT_TuneCUETP8M2T4_13TeV-powheg-pythia8
WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8)

names=(DYJetsToLL_M-10to50_13TeV-madgraphMLM
DYJetsToLL_M-50_13TeV-madgraphMLM
WW_13TeV-pythia8
WZ_13TeV-pythia8
ZZ_13TeV-pythia8
ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg
ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg
ST_tW_top_5f_inclusiveDecays_13TeV-powheg
ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg
TT_13TeV-powheg-pythia8
WJetsToLNu_13TeV-madgraphMLM)
i=1

while [ $i -le ${#samples[@]} ] 
do
    echo "Creating file list for sample" ${samples[$i]} 

    #ls /pnfs/desy.de/cms/tier2/store/user/mmeyer/ntuples/2016/mc/${samples[$i]}*/*root > ${names[$i]}
    ls /pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/2016/mc/${samples[$i]}*/*root > ${names[$i]}
       
    i=`expr $i + 1` 
done

samples_DY_LM=(DYJetsToLL_M-1to5_HT-70to100
DYJetsToLL_M-1to5_HT-100to200
DYJetsToLL_M-1to5_HT-200to400
DYJetsToLL_M-1to5_HT-400to600
DYJetsToLL_M-1to5_HT-600toInf
DYJetsToLL_M-5to50_HT-70to100
DYJetsToLL_M-5to50_HT-100to200_ext
DYJetsToLL_M-5to50_HT-200to400_ext
DYJetsToLL_M-5to50_HT-400to600_ext
DYJetsToLL_M-5to50_HT-600toInf_ext)

names_DY_LM=(DYJetsToLL_M-1to5_HT-70to100
DYJetsToLL_M-1to5_HT-100to200
DYJetsToLL_M-1to5_HT-200to400
DYJetsToLL_M-1to5_HT-400to600
DYJetsToLL_M-1to5_HT-600toInf
DYJetsToLL_M-5to50_HT-70to100
DYJetsToLL_M-5to50_HT-100to200
DYJetsToLL_M-5to50_HT-200to400
DYJetsToLL_M-5to50_HT-400to600
DYJetsToLL_M-5to50_HT-600toInf)

i=1
while [ $i -le ${#samples_DY_LM[@]} ]
do
    echo "Creating file list for sample" ${samples_DY_LM[$i]}

    ls /pnfs/desy.de/cms/tier2/store/user/sconsueg/ntuples/NMSSM_2016_v3/${samples_DY_LM[$i]}*/*root > ${names_DY_LM[$i]}

    i=`expr $i + 1`
done


### --- 15to30 30to50 50to80 80to120 120to170 170to300 300to470 470to600 600to800 800to1000 --- ###
ls /pnfs/desy.de/cms/tier2/store/user/dperezad/NTuple_Production/2016/QCD_MuEnriched/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/190702_123614/0000/*.root > QCD_Pt-20toInf_MuEnrichedPt15_13TeV

__='
###############################################################################################################################
##################******************************* MC Background ************************************###########################

ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/WZ_TuneCUETP8M1_13TeV-pythia8*/*.root > WZ_13TeV-pythia8
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/ZZ_TuneCUETP8M1_13TeV-pythia8*/*.root > ZZ_13TeV-pythia8
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/WW_TuneCUETP8M1_13TeV-pythia8*/*.root > WW_13TeV-pythia8
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*/*.root > WJetsToLNu_13TeV-madgraphMLM
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/*.root > ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1/*.root > ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8*/*.root > ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8*/*.root > ST_tW_top_5f_inclusiveDecays_13TeV-powheg
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/*.root > TT_13TeV-powheg-pythia8
ls /pnfs/desy.de/cms/tier2/store/user/alkaloge/2016/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/ntuples_2016_metv2/190307_211223/0000/*.root > DYJetsToLL_M-10to50_13TeV-madgraphMLM
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/mc/RunIISummer16MiniAODv3/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8*/*.root > DYJetsToLL_M-50_13TeV-madgraphMLM


#Old file lists for 2016 legacy data:
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016B-17Jul2018_ver2-v1/*.root > Run2016B-17Jul2018_ver2-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016B-17Jul2018_ver1-v1/*.root > Run2016B-17Jul2018_ver1-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016C-17Jul2018-v1/*.root > Run2016C-17Jul2018-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016D-17Jul2018-v1/*.root > Run2016D-17Jul2018-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016E-17Jul2018-v1/*.root > Run2016E-17Jul2018-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016F-17Jul2018-v1/*.root > Run2016F-17Jul2018-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016G-17Jul2018-v1/*.root > Run2016G-17Jul2018-v1
ls /pnfs/desy.de/cms/tier2/store/user/telenz/13TeV/NTuples/2016/2016-legacy/data/Run2016-17Jul2018/SingleMuon/SingleMuon_Run2016H-17Jul2018-v1/*.root > Run2016H-17Jul2018-v1

#File lists for old 2016 MC ntuples, I have copied them to a common folder in my /nfs area, to have it in the same location as the the ntuples for the missing mass points 3p6, 6, 16 and 18 GeV, please see below:
for i in 5 7 9 11 13 15 17 19
do
ls /nfs/dust/cms/user/rasp/ntuples/NMSSM_mumutautau_ntuples/M$i/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-$i
done
for j in 3p6 4 6 8 10 12 14
do
ls /nfs/dust/cms/user/rasp/ntuples/NMSSM/SUSYGGH_HToAA_AToTauTau_M-$j_madgraph SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-$j
done


for i in 5 7 9 11 13 15 
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016/M$i/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$i
done

for j in 3p6 4 6 8 10 12 14
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016/'SUSYGGH_HToAA_AToTauTau_M-'$j'_madgraph'/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$j
done

for k in 17 19
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016/'SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-'$k'_13TeV_madgraph'/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$k
done

for l in 16 18 20 21
do
ls /nfs/dust/cms/user/consuegs/ntuples/NMSSM_2016/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-$l/*root > SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-$l
done
'

