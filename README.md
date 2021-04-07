# Analyses/H2aa_2mu2tau_PhDthesis

**Analysis Framework of the DESY CMS Higgs -> tautau group for H->aa->2mu2tau analysis**

`Search for light bosons in the final state with muons and tau leptons with CMS Run II data`


See also the code documentation [Doxygen](https://www.desy.de/~consuegs/docs/analysis-framework/doxygen/) page


This repository contains only specific code to be used for the analysis


* [Installation](#installation)
* [Analysis note](#analysis-note)
* [Main analysis macro](#main-analysis-macro)
* [NAF Submission](#naf-submission)
* [Detailed Description](#detailed-description)



## Installation

The Repository can be checked out via:

```bash
git clone https://github.com/consuegs/H2aa_2mu2tau_PhDthesis.git
```

Scale factors and efficiencies can be obtained from the [Desy Tau Analyses repository](https://github.com/DesyTau/DesyTauAnalysesRun2_25ns)

For instructions on how to synchronize your area with GitHub for NTuple production, please refer to [Desy Tau Analyses main twiki](https://twiki.cern.ch/twiki/bin/viewauth/CMS/DesyTauAnalysesRun2)


## Analysis note 

This analysis is documented in the CMS Analysis note [AN-2018/081](http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2018/081) (CMS internal access) and the PhD Thesis (publicly available), which can be accessed in the following locations:

Desy publication database:

[PUBDB-2020-04343](https://bib-pubdb1.desy.de/record/450397)

Bibliotek Uni Hamburg:

[https://ediss.sub.uni-hamburg.de/handle/ediss/8690](https://ediss.sub.uni-hamburg.de/handle/ediss/8690)

iCMS:

[http://cms.cern.ch/iCMS/jsp/iCMS.jsp?mode=single&part=publications](http://cms.cern.ch/iCMS/jsp/iCMS.jsp?mode=single&part=publications)

CDS:

[CERN-THESIS-2020-181](https://cds.cern.ch/record/2744082)

Inspire:

[https://inspirehep.net/literature/1830713](https://inspirehep.net/literature/1830713)


## Main analysis macro

The main analysis macro (analysis_macro.cpp) is integrated to the Desy Tau Analyses framework and should be compiled from [${CMSSW_BASE}/src/DesyTauAnlalysis/NtupleMaker/bin/](${CMSSW_BASE}/src/DesyTauAnlalysis/NtupleMaker/bin/).

The macro performs an offline selection of a pair of muons and a pair of tracks after the online selection of events with isolated single muon triggers. A configuration file is used as input. 

Configuration files are available separately for data, background MC, and signal MC samples for the 2016, 2017, and 2018 periods:
* [analysisMacro.conf](Run2016/analysisMacro.conf)
* [analysisMacro_mc.conf](Run2016/analysisMacro_mc.conf)
* [analysisMacro_ggH.conf](Run2016/analysisMacro_ggH.conf)


The configuration `.conf` file passes general information to initialise the main function:

```cpp
int main(int argc, char *argv[])
{
	// analysis code
}
...   
```

The names of the config parameters were created to be self-explanatory.

In **data** the year and the json file with the certified lumisections must be specified, e.g.
```ini
...
IsData = true
year = 2016
ApplyGoodRunSelection = true
jsonFile = Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.json
...
```

#### Event loop

The event loop starts like this:
```cpp
for (int iCand = 0; iCand < numberOfCandidates; iCand++)
{
	tree_->GetEntry(iCand);
	events++;
	// apply selection criteria
}
```
where the events are read from the ntuple files. The predefined selection cuts summarized in the configuration file are read and applied to the event within the event loop. 
Generator event weights in MC and JSON certified lumisection selections in data are also considered.

##### Veto on events with at leat one b-tagged jet

A line in the configuration file defines the working point to be used for the b-tagging:

```
btagCut = 0.6321
```
A veto on events with at least one b-tagged jet is applied (the deep flavour algorithm with the medium working point is used).


##### Muons and tracks

Muon and tracks have its own set of cuts defined in the configuration file:

```ini
ptGoodMuonCut = 3
ptIsoMuonCut = 25
etaMuonCut = 2.4
dxyMuonCut = 0.05
dzMuonCut = 0.1

btagCut = 0.6321

dRMuonsCut = 1.5
ptSumDiMuCut = 45
ptSumDiTrkCut = 10
massDiMuCut = 3.4
dxyDiMuCut = 0.01
dzDiMuCut = 0.03

ptTrkLooseCut = 1.5
ptTrkCut = 2.0
etaTrkCut = 2.4

dxyTrkLooseCut = 1.0
dxyTrkCut = 0.02
dzTrkLooseCut = 1.0
dzTrkCut = 0.04
```

The analysis macro can be executed by issuing the command:

```bash
analysis_macro analysisMacro.conf FileListName
```

## NAF Submission

Bash scripts to submit to the NAF condor queue are available:

`HTC_qsub_all.sh` - all jobs

`HTC_qsub_data.sh` - data only jobs 

`HTC_qsub_bkgd.sh` - background MC only jobs 

`HTC_qsub_susy.sh` - signal only jobs 

```bash
./HTC_qsub_all.sh
```

After the jobs are submitted directories called `FileListName_files` are created. In each of these directories the following set of files are created:
* `FileListName_$JobNumber` - file containing paths to ntuples stored at TIER-2 DESY
* `FileListName_$JobNumber.root` - the output root file which contains a set of trees corresponding to the signal region (SR) and Control regions (CRs) filled with the information of relevant variables used for the MVA discrimination
* `FileListName_$JobNumber.error` - a file that contains information on whether the executable ran with no fatal errors
* `FileListName_$JobNumber.out` -  a file that contains information on the number of processed events and warnings 
* `FileListName_$JobNumber.log` -  a file that contains information on CPU, disks, and memory use by the corresponding job
* `FileListName_$JobNumber.sh` - SCRAM architecture and CMSSW environment for the job
* `FileListName_$JobNumber.submit` - HTCondor submit configuration file. If the job finished with error it can be resubmited by issuing the command
```bash
./resubmit.sh
```

Once the directory `FileListName_files` is created and all the jobs finished correctly, one can proceed to merge the output root files by issuing the command:

```bash
./hadd_all.sh - merge all jobs
./hadd_data.sh - merge data only jobs 
./hadd_bkgd.sh - merge background MC only jobs 
./hadd_susy.sh - merge signal only jobs 

```


## Detailed Description

$year directory:

* `${your_directory}/H2aa_2mu2tau_PhDthesis/Run$year/`

Filelists:

* `${your_directory}/H2aa_2mu2tau_PhDthesis/Run${year}/FileListMaker${year}.sh`


Merge step to leave only three analysis categories (lep_lep, lep_had, and had_had) out of the initial 9 categories (e.g ele_ele, ele_mu, mu_ele, mu_mu for lep_lep), defined in analysis_macro.cpp

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/MVA_BDT/`

-Merge Trees:

* `MergeTrees.C`

`MergeAll()`



### Interpolation procedure

* `ForInterpolation.C:`

-For each generated mass point there are 4 discriminating variables assumed to be uncorrelated. An analytic function is associated to each of the 4 distributions and a MLF is performed to determine the optimal parameters

-The procedure is repeated for each of the generated mass points per category

-The vales of the parameters of the fit are stored as a function of the generated mass points

`GetFittingPar()` `Parameters_ForInterpolation.root`

-An interpolation procedure is used to determine the value of each parameter for a step of 0.2 GeV and, with this, the corresponding 4-dimensional pdfs are generated

`Wspacewrite()` `Workspace_Interpolation.root`

`$category = lep_lep, lep_had, had_had`

-All signal samples are generated with toys and the training `(trainBDT_$category.py)` is performed independently for each mass point and category

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/MVA_BDT/`

set environment of CMSSW 8_1_0


#### BDT training

-Train the BDT executing file:

* `TrainAll.sh`

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/`

Classification of data is performed with the weight files produced in the training. The output of this step are root files called `SUSY*_BDTOutput_M-.root` and `SingleMuon_BDTOutput_M-*.root` containing the BDT output histograms

Interpolation of signal acceptance with 0.2 GeV step

Creation of all the datacards for limit computation using the files above as input

All the steps mentioned above are performed automatically with `RunAllInputs()`

* `CreateInputs.C`


`RunAllInputs()` `SUSY*_BDTOutput_M-.root` and `SingleMuon_BDTOutput_M-*.root` with the BDT output histograms

Option of submitting this time consuming step to condor with:

* `SubmitCreateInputs.sh`

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/DataCards/`

-Run combine tool locally:

* `run_combine.sh`

or submit to condor

* `SubmitRunCombine.sh`

-Fit diagnostics:

* `Fitting.sh`

### Main plotting macros 

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/Final_Discriminant/`

#### Final discriminant (BDT output):

* `PlotBDTDiscriminant.C`

`PlotAll()`

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/Bkgd_Validation/`

 #### Validation of Background Model:

* `BkgdValidation.C`

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/Signal_Validation/`

* `SignalValidation.C`

`GetFittingParVal()` `Parameters_ForValidation.root`

`Validation()` Validation/

### Limits:

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/Inputs/DataCards/`

* `PlotLimits.C`

### Run 2 combination directory 

`${your_directory}/H2aa_2mu2tau_PhDthesis/Run2Combination/`

-Script to copy the datacards from 2016, 2017, and 2018 folders:

* `CopyAll.sh`

#### Run combine tool:

* `run_combine.sh`

#### Limits:

* `PlotLimits.C`

### Computation of Trk Iso SF 

[H->tau tau meeting (16.12.2019)-Trk isolation SF](https://indico.desy.de/indico/event/24401/)

`${your_directory}/H2aa_2mu2tau_PhDthesis/${year}/TrkIso_SF_ZTT/`

### Interpretation of results in the context of the 2HDM+S and Dark Photon models 

Description of the benchmark models and the macros in:

`${your_directory}/H2aa_2mu2tau_PhDthesis/Interpretation/`

can be found in the following dedicated twiki page:

[HaaInterpretations](https://twiki.cern.ch/twiki/bin/view/CMS/HaaInterpretations)


#### Brief workflow:

-First create ntuple out of .dat file provided by the theoretists, which contains: type of the 2HDM, mass of the pseudoscalar a in GeV, BR(a -> tautau), and BR(a -> mumu)

* `Entuplizing.C`

-Plot the limits on
<img src="https://render.githubusercontent.com/render/math?math=(\sigma_{h}/\sigma_\text{SM}) \cdot \mathcal{B}(h\rightarrow a_{1}a_{1})">
as a function of the mass of the pseudoscalar for each type of 2HDM+1S model (for an specific value of tan<img src="https://render.githubusercontent.com/render/math?math=\beta">)

`${your_directory}/H2aa_2mu2tau_PhDthesis/Interpretation/Exclusion_Limits_2mu2tau_2HDM_1S/`

* `PlotExclusion.C`

-Plot the limits on sigma/sigma_{SM}* BR(h->aa) as a function of the mass of the pseudoscalar for each type of 2HDM+1S model as a function of tan<img src="https://render.githubusercontent.com/render/math?math=\beta">

* `PlotExclusion3D.C`

-Plot the limits on sigma/sigma_{SM}* BR(h->aa) as a function of the mass of the pseudoscalar for Dark Photon model

`${your_directory}/H2aa_2mu2tau_PhDthesis/Interpretation/Exclusion_Limits_2mu2tau_DarkPhoton/`

* `PlotExclusion.C`

If further clarifications are needed please contact: [sandra.consuegra.rodriguez@desy.de](sandra.consuegra.rodriguez@desy.de), [sandra.consuegra.rodriguez@cern.ch](sandra.consuegra.rodriguez@cern.ch)

#### Instructions last updated: 07.04.2021
