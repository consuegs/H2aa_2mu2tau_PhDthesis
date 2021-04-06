#!/bin/sh

mass=mass
massf=massf

for i in 3.6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
do

  echo "  "
  echo "  "
  
  eval "mass=${i}p0"

  if (( $(echo "${i} < 4" |bc -l) )); then
  eval "mass=3p6"
  fi

  eval "massf=${i}"
  echo "  "
  echo "Submitting to condor GoF test for mass point Ma = $massf GeV"
  echo "  "

  rm -rf GOF_ma$mass'_files'
  mkdir GOF_ma$mass'_files'
  cd GOF_ma$mass'_files/'
  cp ../HTC_qsub.sh ./
  cp ../../../DataCards/haa-13TeV_2017_ma$mass.txt ./
  cp ../../../DataCards/haa-13TeV_2017_ma$mass'_lep_lep.root' ./
  cp ../../../DataCards/haa-13TeV_2017_ma$mass'_lep_had.root' ./
  cp ../../../DataCards/haa-13TeV_2017_ma$mass'_had_had.root' ./

  for j in {1..20}
  do
   cat > HTC_TheScript_${j}.sh <<EOF
   source /cvmfs/cms.cern.ch/cmsset_default.sh
   export SCRAM_ARCH=slc6_amd64_gcc630
   cd ${CMSSW_BASE}/src
   cmsenv
   cd -

   echo "MC Toys, r fixed"
   combine -M GoodnessOfFit haa-13TeV_2017_ma$mass.txt --algo=AD --fixedSignalStrength=0.0 -m $massf -t 1000 -s ${j}

EOF
   chmod u+x HTC_TheScript_${j}.sh
   ./HTC_qsub.sh HTC_TheScript_${j}.sh HTC_TheScript_${j}
  done
  cd ../
done
