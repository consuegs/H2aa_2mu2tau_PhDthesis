#!/bin/csh

mass=mass
massf=massf
category=(_lep_lep _lep_had _had_had)

for i in {3..21}

do

  for j in 0 2 4 6 8

  do

  if [[ "$i" -eq 3 && "$j" -le 4 ]]
  then
   continue
  fi

  if [[ "$i" -eq 21 && "$j" -ge 2 ]]
  then
   continue
  fi

  echo "  "
  echo "  "

  eval "mass=${i}p${j}"
  eval "massf=${i}.${j}"

  echo "Performing fitting for Ma = $mass GeV"

  combine -M FitDiagnostics --plots --saveNormalizations --saveShapes --saveWithUncertainties --saveNLL --robustFit=1 --rMin=-5 --rMax=5 -m $massf haa-13TeV_2017_ma$mass.txt

  mv fitDiagnostics.root fitDiagnostics_ma$mass.root

    for k in {1..3}

    do
 
    mv $category[$k]_CMS_th1x_prefit.png $category[$k]_CMS_th1x_prefit_$mass.png

    rm $category[$k]_CMS_th1x_prefit.png
 
    done

  done

done

