#!/bin/sh
# $1 - datacard file w/o .txt extension
# $2 - mass

rm workspace_${1}.root
combineTool.py -M T2W -i $1.txt -o workspace_${1}.root
#combineTool.py -m $2 -M Impacts --allPars --doInitialFit --robustFit 1  --rMin -10 --rMax 10 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd FITTER_NEW_CROSSING_ALGO -d workspace_${1}.root -t -1
#combineTool.py -m $2 -M Impacts --robustFit 1 --doFits  --rMin -10 --rMax 10 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd FITTER_NEW_CROSSING_ALGO -d workspace_${1}.root -t -1
combineTool.py -m $2 -M Impacts --allPars --doInitialFit --robustFit 1  --rMin -5 --rMax 5 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd FITTER_NEW_CROSSING_ALGO -d workspace_${1}.root -t -1
combineTool.py -m $2 -M Impacts --robustFit 1 --doFits  --rMin -5 --rMax 5 --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd FITTER_NEW_CROSSING_ALGO -d workspace_${1}.root -t -1
combineTool.py -m $2 -M Impacts -o impacts_${1}.json -d workspace_${1}.root
plotImpacts.py -i impacts_${1}.json -o impacts_${1}
