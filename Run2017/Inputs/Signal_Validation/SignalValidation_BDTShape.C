#include "CMS_lumi.C"
#include "HttStylesNew.cc"
#include "HtoH.h"

//********************************************************//
//**************Switch of input variables ***************//
//********************************************************//
bool MuMu_Mass_isIN = true;
bool MuMu_Pt_isIN = false;
bool MuMu_DR_isIN = true;
bool MuMuMET_DPhi_isIN = false;
bool TrkTrk_Mass_isIN = false;
bool TrkTrk_Pt_isIN = false;
bool TrkTrk_DR_isIN = true;
bool TrkTrkMET_DPhi_isIN = false;
bool MuMuTrkTrk_Mass_isIN = false;
bool MuMuTrkTrk_Pt_isIN = false;
bool MuMuTauTau_Mass_isIN = false;
bool MuMuTauTau_Pt_isIN = false;
bool MuMuTrkTrkMET_Mass_isIN = true;
bool MET_Pt_isIN = false;

void SignalValidation_BDTShape(float mass = 15,
	TString trackCat = "_had_had",
	TString xtitle = "BDT Output",	// title of x axis
	TString ytitle = "Normalized to unity",	// title of y axis
	float xLower = -0.2,	// lower boundary of x axis
	float xUpper = 0.4,	// upper boundary of x axis
	bool logY = false	// log or linear scale of Y axis
	)
{

	gROOT->SetBatch();

	float MuMu_Mass, MuMu_Pt, MuMu_DR, MuMuMET_DPhi, TrkTrk_Mass, TrkTrk_Pt, TrkTrk_DR, TrkTrkMET_DPhi,
	MuMuTrkTrk_Mass, MuMuTrkTrk_Pt, MuMuTauTau_Mass, MuMuTauTau_Pt, MET_Pt, MuMuTrkTrkMET_Mass;
	float mvavalue;

	std::cout << std::endl << std::endl;
	std::cout << "                    Start BDT Classification" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "                    ****     ***     *******                  " << std::endl;
	std::cout << "                    *   *    *   *      *                     " << std::endl;
	std::cout << "                    * **     *   *      *                     " << std::endl;
	std::cout << "                    *   *    *   *      *                     " << std::endl;
	std::cout << "                    ****     ***        *                     " << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "--- ------------------------------------------------------------" << std::endl;
	std::cout << "***        Starting loop over the Signal Samples           ***" << std::endl;
	std::cout << "--- ------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;
	
	//// Define a string with a "." instead of a "p" for the plot's legend (cosmetic changes)	////
	TString massS, massD;
	//// Define fractional part of mass////
	int decimal = int(int(mass *10 + 0.1) % 10);

	TString str_entere_mass = std::to_string(int(mass + 0.1));
	TString str_decimal = std::to_string(int(int(mass *10 + 0.1) % 10));

	TString mass_string = str_entere_mass + "p" + str_decimal;

	if (decimal > 0)
	{
	   massS = str_entere_mass + "p" + str_decimal;
	   massD = str_entere_mass + "." + str_decimal;
	}
	else
	{
	   massS = str_entere_mass;
	   massD = str_entere_mass;
	}

	//**********Input &Output Files ***********//

	TFile *fileInterpSample = new TFile("../../Workspace_Interpolation.root");
	TFile *fileTrueSample = new TFile("../../MVA_BDT/MergeTrees/tree_s_ma" + massS + "_file.root");

	std::cout << std::endl;
	std::cout << "--- BDT Classification---" << std::endl;

	///////////////////////////////////////////////////////////////////////
	//**********BDT Classification in Categories and Regions ***********//
	///////////////////////////////////////////////////////////////////////

	//**********Loading TMVA Reader ***********//

	TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");

	if (MuMu_Mass_isIN)
		reader->AddVariable("MuMu_Mass", &MuMu_Mass);
	if (MuMu_Pt_isIN)
		reader->AddVariable("MuMu_Pt", &MuMu_Pt);
	if (MuMu_DR_isIN)
		reader->AddVariable("MuMu_DR", &MuMu_DR);
	if (MuMuMET_DPhi_isIN)
		reader->AddVariable("MuMuMET_DPhi", &MuMuMET_DPhi);
	if (TrkTrk_Mass_isIN)
		reader->AddVariable("TrkTrk_Mass", &TrkTrk_Mass);
	if (TrkTrk_Pt_isIN)
		reader->AddVariable("TrkTrk_Pt", &TrkTrk_Pt);
	if (TrkTrk_DR_isIN)
		reader->AddVariable("TrkTrk_DR", &TrkTrk_DR);
	if (TrkTrkMET_DPhi_isIN)
		reader->AddVariable("TrkTrkMET_DPhi", &TrkTrkMET_DPhi);
	if (MuMuTrkTrk_Mass_isIN)
		reader->AddVariable("MuMuTrkTrk_Mass", &MuMuTrkTrk_Mass);
	if (MuMuTrkTrk_Pt_isIN)
		reader->AddVariable("MuMuTrkTrk_Pt", &MuMuTrkTrk_Pt);
	if (MuMuTauTau_Mass_isIN)
		reader->AddVariable("MuMuTauTau_Mass", &MuMuTauTau_Mass);
	if (MuMuTauTau_Pt_isIN)
		reader->AddVariable("MuMuTauTau_Pt", &MuMuTauTau_Pt);
	if (MuMuTrkTrkMET_Mass_isIN)
		reader->AddVariable("MuMuTrkTrkMET_Mass", &MuMuTrkTrkMET_Mass);
	if (MET_Pt_isIN)
		reader->AddVariable("MET_Pt", &MET_Pt);

	reader->BookMVA("BDT", "/nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2017/MVA_BDT/ma" + mass_string + "/weights/TMVAClassification_BDT" + trackCat + ".weights.xml");

	double MuMu_Mass_D, MuMu_Pt_D, MuMu_DR_D, MuMuMET_DPhi_D, TrkTrk_Mass_D, TrkTrk_Pt_D, TrkTrk_DR_D, TrkTrkMET_DPhi_D,
	MuMuTrkTrk_Mass_D, MuMuTrkTrk_Pt_D, MuMuTauTau_Mass_D, MuMuTauTau_Pt_D, MET_Pt_D, MuMuTrkTrkMET_Mass_D;

	////////// Retrieving Workspace for Event Generation	//////////

	RooWorkspace *ws = (RooWorkspace*) fileInterpSample->Get("ws" + trackCat + "_" + mass_string);

	RooAbsPdf *SignalModel = ws->pdf("model");

	RooDataSet *Dataset_Old = SignalModel->generate(*ws->set("observables"), 5000);

	RooAbsData::setDefaultStorageType(RooAbsData::Tree);

	RooDataSet *Dataset = new RooDataSet("Dataset", "Dataset", Dataset_Old, *Dataset_Old->get());

	TTree *treeInterp = (TTree*) Dataset->tree()->Clone();

	if (MuMu_Mass_isIN) treeInterp->SetBranchAddress("MuMu_Mass", &MuMu_Mass_D);
	if (MuMu_Pt_isIN) treeInterp->SetBranchAddress("MuMu_Pt", &MuMu_Pt_D);
	if (MuMu_DR_isIN) treeInterp->SetBranchAddress("MuMu_DR", &MuMu_DR_D);
	if (MuMuMET_DPhi_isIN) treeInterp->SetBranchAddress("MuMuMET_DPhi", &MuMuMET_DPhi_D);
	if (TrkTrk_Mass_isIN) treeInterp->SetBranchAddress("TrkTrk_Mass", &TrkTrk_Mass_D);
	if (TrkTrk_Pt_isIN) treeInterp->SetBranchAddress("TrkTrk_Pt", &TrkTrk_Pt_D);
	if (TrkTrk_DR_isIN) treeInterp->SetBranchAddress("TrkTrk_DR", &TrkTrk_DR_D);
	if (TrkTrkMET_DPhi_isIN) treeInterp->SetBranchAddress("TrkTrkMET_DPhi", &TrkTrkMET_DPhi_D);
	if (MuMuTrkTrk_Mass_isIN) treeInterp->SetBranchAddress("MuMuTrkTrk_Mass", &MuMuTrkTrk_Mass_D);
	if (MuMuTrkTrk_Pt_isIN) treeInterp->SetBranchAddress("MuMuTrkTrk_Pt", &MuMuTrkTrk_Pt_D);
	if (MuMuTauTau_Mass_isIN) treeInterp->SetBranchAddress("MuMuTauTau_Mass", &MuMuTauTau_Mass_D);
	if (MuMuTauTau_Pt_isIN) treeInterp->SetBranchAddress("MuMuTauTau_Pt", &MuMuTauTau_Pt_D);
	if (MET_Pt_isIN) treeInterp->SetBranchAddress("MET_Pt", &MET_Pt_D);
	if (MuMuTrkTrkMET_Mass_isIN) treeInterp->SetBranchAddress("MuMuTrkTrkMET_Mass", &MuMuTrkTrkMET_Mass_D);

	////////// Classifiying	//////////   

	//// Interpolated	////
	TH1D *HistoInterpolated = new TH1D("MVABDTOutputInterpolated" + trackCat + "H", "", 2000, -1., 1.);

	for (int ievt = 0; ievt < treeInterp->GetEntries(); ievt++)	// Loop over tree entries
	{
		treeInterp->GetEntry(ievt);

		MuMu_Mass = float_t(MuMu_Mass_D);
		MuMu_Pt = float_t(MuMu_Pt_D);
		MuMu_DR = float_t(MuMu_DR_D);
		MuMuMET_DPhi = float_t(MuMuMET_DPhi_D);
		TrkTrk_Mass = float_t(TrkTrk_Mass_D);
		TrkTrk_Pt = float_t(TrkTrk_Pt_D);
		TrkTrk_DR = float_t(TrkTrk_DR_D);
		TrkTrkMET_DPhi = float_t(TrkTrkMET_DPhi_D);
		MuMuTrkTrk_Mass = float_t(MuMuTrkTrk_Mass_D);
		MuMuTrkTrk_Pt = float_t(MuMuTrkTrk_Pt_D);
		MuMuTauTau_Mass = float_t(MuMuTauTau_Mass_D);
		MuMuTauTau_Pt = float_t(MuMuTauTau_Pt_D);
		MET_Pt = float_t(MET_Pt_D);
		MuMuTrkTrkMET_Mass = float_t(MuMuTrkTrkMET_Mass_D);

		mvavalue = reader->EvaluateMVA("BDT");

		HistoInterpolated->Fill(mvavalue);
	}	/// End loop over tree entries
			
			
	////////// Retrieving Real Tree from Sample	//////////

	TTree *treeTrue = (TTree*) fileTrueSample->Get("tree_s" + trackCat);

	if (MuMu_Mass_isIN) treeTrue->SetBranchAddress("MuMu_Mass", &MuMu_Mass);
	if (MuMu_Pt_isIN) treeTrue->SetBranchAddress("MuMu_Pt", &MuMu_Pt);
	if (MuMu_DR_isIN) treeTrue->SetBranchAddress("MuMu_DR", &MuMu_DR);
	if (MuMuMET_DPhi_isIN) treeTrue->SetBranchAddress("MuMuMET_DPhi", &MuMuMET_DPhi);
	if (TrkTrk_Mass_isIN) treeTrue->SetBranchAddress("TrkTrk_Mass", &TrkTrk_Mass);
	if (TrkTrk_Pt_isIN) treeTrue->SetBranchAddress("TrkTrk_Pt", &TrkTrk_Pt);
	if (TrkTrk_DR_isIN) treeTrue->SetBranchAddress("TrkTrk_DR", &TrkTrk_DR);
	if (TrkTrkMET_DPhi_isIN) treeTrue->SetBranchAddress("TrkTrkMET_DPhi", &TrkTrkMET_DPhi);
	if (MuMuTrkTrk_Mass_isIN) treeTrue->SetBranchAddress("MuMuTrkTrk_Mass", &MuMuTrkTrk_Mass);
	if (MuMuTrkTrk_Pt_isIN) treeTrue->SetBranchAddress("MuMuTrkTrk_Pt", &MuMuTrkTrk_Pt);
	if (MuMuTauTau_Mass_isIN) treeTrue->SetBranchAddress("MuMuTauTau_Mass", &MuMuTauTau_Mass);
	if (MuMuTauTau_Pt_isIN) treeTrue->SetBranchAddress("MuMuTauTau_Pt", &MuMuTauTau_Pt);
	if (MET_Pt_isIN) treeTrue->SetBranchAddress("MET_Pt", &MET_Pt);
	if (MuMuTrkTrkMET_Mass_isIN) treeTrue->SetBranchAddress("MuMuTrkTrkMET_Mass", &MuMuTrkTrkMET_Mass);

	////////// Classifiying	////////// 

	//// True sample	////
	TH1D *HistoTrue = new TH1D("MVABDTOutputTrue" + trackCat + "H", "", 2000, -1., 1.);

	for (int ievt = 0; ievt < treeTrue->GetEntries(); ievt++)	// Loop over tree entries
	{
		treeTrue->GetEntry(ievt);

		mvavalue = reader->EvaluateMVA("BDT");

		HistoTrue->Fill(mvavalue);
	}	// End loop over tree entries

	//**********End of Classification ***********//

	std::cout << "==> BDT Classification is done!" << std::endl << std::endl;

	//////////////////////////////////////////////////////////////////////////////
	////////////////////// Ploting	//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	HistoInterpolated->Sumw2();
	HistoTrue->Sumw2();
	HistoInterpolated->Rebin(80);
	HistoTrue->Rebin(80);

	int nBinsNew = HistoTrue->GetNbinsX();

	for (int iB = 1; iB <= nBinsNew; iB++) HistoInterpolated->SetBinError(iB,0.);
	
	//**********Propagation of parameter uncertainties ***********//

			int nParameters = 13;

			TString Parameters[13] = { "mean_V", "width_V", "sigma_V", "mean_G1", "sigma_G1", "mean_G2", "sigma_G2", "mean_L1", "sigma_L1", "sigma_G3", "mean_L3", "sigma_L3", "sigma_G4" };

			for (int iparameter = 0; iparameter < nParameters; iparameter++)	// Loop over parameters
			{

				///////// Shift Up	///////////// 
				ws->var(Parameters[iparameter])->setVal(ws->var(Parameters[iparameter])->getValV() + ws->var(Parameters[iparameter])->getError());

				RooDataSet *DatasetUncUp_Old = SignalModel->generate(*ws->set("observables"), 5000);

				RooDataSet *DatasetUncUp = new RooDataSet("DatasetUncUp", "DatasetUncUp", DatasetUncUp_Old, *DatasetUncUp_Old->get());

				TTree *treeUncUp = (TTree*) DatasetUncUp->tree()->Clone();

				if (MuMu_Mass_isIN) treeUncUp->SetBranchAddress("MuMu_Mass", &MuMu_Mass_D);
				if (MuMu_Pt_isIN) treeUncUp->SetBranchAddress("MuMu_Pt", &MuMu_Pt_D);
				if (MuMu_DR_isIN) treeUncUp->SetBranchAddress("MuMu_DR", &MuMu_DR_D);
				if (MuMuMET_DPhi_isIN) treeUncUp->SetBranchAddress("MuMuMET_DPhi", &MuMuMET_DPhi_D);
				if (TrkTrk_Mass_isIN) treeUncUp->SetBranchAddress("TrkTrk_Mass", &TrkTrk_Mass_D);
				if (TrkTrk_Pt_isIN) treeUncUp->SetBranchAddress("TrkTrk_Pt", &TrkTrk_Pt_D);
				if (TrkTrk_DR_isIN) treeUncUp->SetBranchAddress("TrkTrk_DR", &TrkTrk_DR_D);
				if (TrkTrkMET_DPhi_isIN) treeUncUp->SetBranchAddress("TrkTrkMET_DPhi", &TrkTrkMET_DPhi_D);
				if (MuMuTrkTrk_Mass_isIN) treeUncUp->SetBranchAddress("MuMuTrkTrk_Mass", &MuMuTrkTrk_Mass_D);
				if (MuMuTrkTrk_Pt_isIN) treeUncUp->SetBranchAddress("MuMuTrkTrk_Pt", &MuMuTrkTrk_Pt_D);
				if (MuMuTauTau_Mass_isIN) treeUncUp->SetBranchAddress("MuMuTauTau_Mass", &MuMuTauTau_Mass_D);
				if (MuMuTauTau_Pt_isIN) treeUncUp->SetBranchAddress("MuMuTauTau_Pt", &MuMuTauTau_Pt_D);
				if (MET_Pt_isIN) treeUncUp->SetBranchAddress("MET_Pt", &MET_Pt_D);
				if (MuMuTrkTrkMET_Mass_isIN) treeUncUp->SetBranchAddress("MuMuTrkTrkMET_Mass", &MuMuTrkTrkMET_Mass_D);

				//------- Classifiying -------//   

				TH1D *HistoUp = new TH1D("MVABDTOutputInterpolated" + trackCat + "UpH", "", 2000, -1., 1.);

				for (int ievt = 0; ievt < treeUncUp->GetEntries(); ievt++)	// Loop over tree entries
				{
					treeUncUp->GetEntry(ievt);

					MuMu_Mass = float_t(MuMu_Mass_D);
					MuMu_Pt = float_t(MuMu_Pt_D);
					MuMu_DR = float_t(MuMu_DR_D);
					MuMuMET_DPhi = float_t(MuMuMET_DPhi_D);
					TrkTrk_Mass = float_t(TrkTrk_Mass_D);
					TrkTrk_Pt = float_t(TrkTrk_Pt_D);
					TrkTrk_DR = float_t(TrkTrk_DR_D);
					TrkTrkMET_DPhi = float_t(TrkTrkMET_DPhi_D);
					MuMuTrkTrk_Mass = float_t(MuMuTrkTrk_Mass_D);
					MuMuTrkTrk_Pt = float_t(MuMuTrkTrk_Pt_D);
					MuMuTauTau_Mass = float_t(MuMuTauTau_Mass_D);
					MuMuTauTau_Pt = float_t(MuMuTauTau_Pt_D);
					MET_Pt = float_t(MET_Pt_D);
					MuMuTrkTrkMET_Mass = float_t(MuMuTrkTrkMET_Mass_D);

					mvavalue = reader->EvaluateMVA("BDT");

					HistoUp->Fill(mvavalue);
				}	// End loop over tree entries
                                HistoUp->Rebin(80);

				///////// Shift Down	///////////// 
				ws->var(Parameters[iparameter])->setVal(ws->var(Parameters[iparameter])->getValV() - ws->var(Parameters[iparameter])->getError());

				RooDataSet *DatasetUncDown_Old = SignalModel->generate(*ws->set("observables"), 5000);

				RooDataSet *DatasetUncDown = new RooDataSet("DatasetUncDown", "DatasetUncDown", DatasetUncDown_Old, *DatasetUncDown_Old->get());

				TTree *treeUncDown = (TTree*) DatasetUncDown->tree()->Clone();

				if (MuMu_Mass_isIN) treeUncDown->SetBranchAddress("MuMu_Mass", &MuMu_Mass_D);
				if (MuMu_Pt_isIN) treeUncDown->SetBranchAddress("MuMu_Pt", &MuMu_Pt_D);
				if (MuMu_DR_isIN) treeUncDown->SetBranchAddress("MuMu_DR", &MuMu_DR_D);
				if (MuMuMET_DPhi_isIN) treeUncDown->SetBranchAddress("MuMuMET_DPhi", &MuMuMET_DPhi_D);
				if (TrkTrk_Mass_isIN) treeUncDown->SetBranchAddress("TrkTrk_Mass", &TrkTrk_Mass_D);
				if (TrkTrk_Pt_isIN) treeUncDown->SetBranchAddress("TrkTrk_Pt", &TrkTrk_Pt_D);
				if (TrkTrk_DR_isIN) treeUncDown->SetBranchAddress("TrkTrk_DR", &TrkTrk_DR_D);
				if (TrkTrkMET_DPhi_isIN) treeUncDown->SetBranchAddress("TrkTrkMET_DPhi", &TrkTrkMET_DPhi_D);
				if (MuMuTrkTrk_Mass_isIN) treeUncDown->SetBranchAddress("MuMuTrkTrk_Mass", &MuMuTrkTrk_Mass_D);
				if (MuMuTrkTrk_Pt_isIN) treeUncDown->SetBranchAddress("MuMuTrkTrk_Pt", &MuMuTrkTrk_Pt_D);
				if (MuMuTauTau_Mass_isIN) treeUncDown->SetBranchAddress("MuMuTauTau_Mass", &MuMuTauTau_Mass_D);
				if (MuMuTauTau_Pt_isIN) treeUncDown->SetBranchAddress("MuMuTauTau_Pt", &MuMuTauTau_Pt_D);
				if (MET_Pt_isIN) treeUncDown->SetBranchAddress("MET_Pt", &MET_Pt_D);
				if (MuMuTrkTrkMET_Mass_isIN) treeUncDown->SetBranchAddress("MuMuTrkTrkMET_Mass", &MuMuTrkTrkMET_Mass_D);

				//------- Classifiying -------//   

				TH1D *HistoDown = new TH1D("MVABDTOutputInterpolated" + trackCat + "DownH", "", 2000, -1., 1.);

				for (int ievt = 0; ievt < treeUncDown->GetEntries(); ievt++)	// Loop over tree entries
				{
					treeUncDown->GetEntry(ievt);

					MuMu_Mass = float_t(MuMu_Mass_D);
					MuMu_Pt = float_t(MuMu_Pt_D);
					MuMu_DR = float_t(MuMu_DR_D);
					MuMuMET_DPhi = float_t(MuMuMET_DPhi_D);
					TrkTrk_Mass = float_t(TrkTrk_Mass_D);
					TrkTrk_Pt = float_t(TrkTrk_Pt_D);
					TrkTrk_DR = float_t(TrkTrk_DR_D);
					TrkTrkMET_DPhi = float_t(TrkTrkMET_DPhi_D);
					MuMuTrkTrk_Mass = float_t(MuMuTrkTrk_Mass_D);
					MuMuTrkTrk_Pt = float_t(MuMuTrkTrk_Pt_D);
					MuMuTauTau_Mass = float_t(MuMuTauTau_Mass_D);
					MuMuTauTau_Pt = float_t(MuMuTauTau_Pt_D);
					MET_Pt = float_t(MET_Pt_D);
					MuMuTrkTrkMET_Mass = float_t(MuMuTrkTrkMET_Mass_D);

					mvavalue = reader->EvaluateMVA("BDT");

					HistoDown->Fill(mvavalue);
				}	// End loop over tree entries
				HistoDown->Rebin(80);
				
				for (int iB = 1; iB <= nBinsNew; iB++) HistoInterpolated->SetBinError(iB, TMath::Sqrt(pow(HistoInterpolated->GetBinError(iB),2)+pow(0.5*(HistoUp->GetBinContent(iB)-HistoDown->GetBinContent(iB)),2)));

				
			}	// End loop over parameters

        HistoInterpolated->Scale(1. / HistoInterpolated->GetSumOfWeights());
	HistoTrue->Scale(1. / HistoTrue->GetSumOfWeights());
	
	TH1D *RatioH = (TH1D*) HistoTrue->Clone("RatioH");
	TH1D *UnitErrorH = (TH1D*) HistoTrue->Clone("UnitErrorH");

	////// Histos Colors	////////
	int tcolor_dark_2 = kAzure;
	int tcolor_light_2 = kAzure - 2;

	int tcolor_dark_1 = kGreen + 3;
	int tcolor_light_1 = kGreen - 6;

	for (int iB = 1; iB <= nBinsNew; iB++)
	{

		double y2 = HistoInterpolated->GetBinContent(iB);
		double y2_err = HistoInterpolated->GetBinError(iB);

		double y1 = HistoTrue->GetBinContent(iB);
		double y1_err = HistoTrue->GetBinError(iB);

		double r;
		double r_err;

		double u;
		double u_err;

		if (y1 < 0.00001)
		{
			r = 0.;
			r_err = 0.;
			u = 1.;
			u_err = 0.;
		}
		else
		{
			r = y1 / y2;
			r_err = y1_err / y2;
			u = 1.;
			u_err = y2_err / y2;
		}

		RatioH->SetBinContent(iB, r);
		RatioH->SetBinError(iB, r_err);

		UnitErrorH->SetBinContent(iB, u);
		UnitErrorH->SetBinError(iB, u_err);

		//HistoTrue->SetBinError(iB, 0.);
		//HistoInterpolated->SetBinError(iB, 0.);
	}

	// Drawing in Canvas 
	TCanvas *c = new TCanvas("c", "c", 3000, 3000);
	c->cd();

	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();

	upper->cd();

	HistoTrue->Draw("h");
	HistoInterpolated->Draw("hsame");
	HistoTrue->Draw("e2same");
	
	float Kolmogorov = HistoTrue->KolmogorovTest(HistoInterpolated);

	HistoTrue->SetStats(0);
	HistoTrue->GetXaxis()->SetRangeUser(xLower, xUpper);
	HistoTrue->GetXaxis()->SetLabelSize(0.);
	HistoTrue->GetXaxis()->SetLabelOffset(0.);
	HistoTrue->GetYaxis()->SetTitleOffset(1.2);
	HistoTrue->GetYaxis()->SetTitle(ytitle);
	HistoTrue->GetYaxis()->SetTitleSize(0.045);
	HistoTrue->GetYaxis()->SetLabelSize(0.04);
	HistoTrue->GetYaxis()->SetTickLength(0.055);
	HistoTrue->GetYaxis()->SetTickSize(0.013);
	HistoTrue->GetYaxis()->SetRangeUser(0, 0.6);
	if (logY) HistoTrue->GetYaxis()->SetRangeUser(0.0001, 100 *0.6);
	HistoTrue->SetFillColorAlpha(tcolor_light_1, 0.35);
	HistoTrue->SetLineColor(tcolor_dark_1);
	HistoTrue->SetLineWidth(2);
	HistoTrue->SetLineStyle(1);
	HistoTrue->SetFillStyle(3344);

	HistoInterpolated->SetStats(0);
	HistoInterpolated->SetFillColorAlpha(tcolor_light_2, 0.35);
	HistoInterpolated->SetLineColor(tcolor_dark_2);
	HistoInterpolated->SetLineWidth(2);
	HistoInterpolated->SetLineStyle(1);
	HistoInterpolated->SetFillStyle(1001);

	upper->Modified();
	upper->SetTicks();
	upper->SetLeftMargin(0.13);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);

	TLegend *leg = new TLegend(0.2, 0.55, 0.5, 0.80);
	leg->SetTextSize(0.035);
	leg->SetHeader("       #color[436]{  m_{a_{1}} = " + massD + " GeV }");
	leg->SetLineColor(1);
	leg->SetLineWidth(2);
	leg->AddEntry(HistoTrue, "#color[1]{True sample}", "f");
	leg->AddEntry(HistoInterpolated, "#color[1]{Interpolated sample}", "f");
	leg->AddEntry((TObject*) 0, Form("Kolm. Test = %5.3f", Kolmogorov), "");
	leg->Draw();

	writeExtraText = true;
	extraText = "Simulation";
	CMS_lumi(upper, 5, 33);
        TLatex tex;
	tex.DrawLatex(-0.27, 0.61, "#color[4]{" + trackCat + "} Channel");

	if (logY) upper->SetLogy(true);

	upper->RedrawAxis();
	upper->Update();

	lower->cd();

	TLine *line = new TLine(RatioH->GetBinLowEdge(RatioH->FindBin(xLower)), 1., RatioH->GetBinLowEdge(RatioH->FindBin(xUpper)) + RatioH->GetBinWidth(RatioH->FindBin(xUpper)), 1.);
	line->SetLineColor(4);

	RatioH->Draw("e1p");
	UnitErrorH->Draw("e2same");
	RatioH->Draw("e2same");

	line->Draw("same");

	RatioH->SetStats(0);
	RatioH->GetXaxis()->SetRangeUser(xLower, xUpper);
	RatioH->GetXaxis()->SetLabelFont(42);
	RatioH->GetXaxis()->SetLabelOffset(0.03);
	RatioH->GetXaxis()->SetLabelSize(0.14);
	RatioH->GetXaxis()->SetTitleSize(0.13);
	RatioH->GetXaxis()->SetTitleOffset(1.35);
	RatioH->GetXaxis()->SetTitle(xtitle);
	RatioH->GetXaxis()->SetTickLength(0.025);
	RatioH->GetXaxis()->SetTickSize(0.08);
	RatioH->GetYaxis()->SetRangeUser(-1.01, 3.01);
	RatioH->GetYaxis()->SetLabelOffset(0.008);
	RatioH->GetYaxis()->SetLabelSize(0.08);
	RatioH->GetYaxis()->SetTitleSize(0.1);
	RatioH->GetYaxis()->SetNdivisions(6);
	RatioH->GetYaxis()->SetTitleOffset(0.45);
	RatioH->GetYaxis()->SetTitle("Ratio    ");
	RatioH->GetYaxis()->SetTickLength(0.025);
	RatioH->GetYaxis()->SetTickSize(0.02);
	RatioH->SetFillColorAlpha(tcolor_light_1, 0.4);
	RatioH->SetLineColor(tcolor_dark_1);
	RatioH->SetLineWidth(2);
	RatioH->SetLineStyle(1);
	RatioH->SetFillStyle(3344);

	UnitErrorH->SetStats(0);
	UnitErrorH->SetFillColorAlpha(tcolor_light_2, 0.35);
	UnitErrorH->SetLineColor(tcolor_dark_2);
	UnitErrorH->SetLineWidth(2);
	UnitErrorH->SetLineStyle(1);
	UnitErrorH->SetFillStyle(1001);

	lower->Modified();
	lower->SetTicks();
	lower->SetLeftMargin(0.13);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.45);

	lower->RedrawAxis();
	lower->Update();

	c->Update();
	c->Print("SignalValidation" + trackCat + "_Ma" + mass_string + ".pdf", "Portrait pdf");
	delete c;

}

void PlotAll(float mass = 15,
	TString trackCat = "_lep_lep",
	TString xtitle = "BDT Output",
	TString ytitle = "Normalized to unity",
	float xLower = -0.2,
	float xUpper = 0.4,
	bool logY = false)
{

	gROOT->SetBatch();

	int nTrackCat = 3;
	int nSamples = 19;
	TString TrackCat[] = { "_lep_lep", "_lep_had", "_had_had" };
	float mpoints[19] = { 3.6, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

	for (int isample = 0; isample < nSamples; isample++)
	{
		for (int iCat = 0; iCat < nTrackCat; iCat++)
		{
			SignalValidation_BDTShape(mpoints[isample], TrackCat[iCat], xtitle, ytitle, xLower, xUpper, false);
		}
	}
}
