#include "CMS_lumi.C"
#include "HttStylesNew.cc"
#include "HtoH.h"

using namespace RooFit;

void GetFittingParVal()
{
        // Silence INFO messages
        RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
        // Silence additional MINUIT output 
        RooMsgService::instance().setSilentMode(true);
        // Silence Info in TCanvas::Print: messages
        gErrorIgnoreLevel = kWarning;

	//// Mass points	////
	int nSamples = 18;

	float points[18] = { 3.6, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

	//// Mass point of 10 GeV removed for validation procedure 	////
	TString mpoints[18] = { "3p6", "4", "5", "6", "7", "8", "9", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" };

	///////////////////////////////// Category Strings	//////////////////////////////////////////
	int nCategories = 3;
	TString categories[3] = { "lep_lep", "lep_had", "had_had" };

	float Par_1[3] = { 0.0375148, 0.036999, 0.0364409 };
	float Par_2[3] = { 0.00804069, 0.00788601, 0.00817561 };
	float Par_3[3] = { 0.0611471, 0.0611454, 0.0598584 };
	float Par_4[3] = { 0.00837859, 0.00837859, 0.00877093 };
	float Par_5[3] = { 0.899948, 0.893934, 0.895971 };

	float Par_6[3] = { 0.03798388, 0.04020731, 0.04233213 };
	float Par_7[3] = { 0.00327519, 0.0056714, 0.007209588 };
	float Par_8[3] = { 0, 0.0307573, 0.247995 };
	float Par_9[3] = { 0.004320131, 0.003069381, 0.002486288 };
	float Par_10[3] = { 0.03722824, 0.03760699, 0.03452946 };
	float Par_11[3] = { -0.07015738, -0.08169356, -0.09413662 };
	float Par_12[3] = { -0.01137329, -0.0177734, -0.02389334 };

	float Par_13[3] = { 127.979, 123.171, 118.015 };
	float Par_14[3] = { 4.21009, 3.93595, 3.10159 };
	float Par_15[3] = { 19.2472, 21.3161, 23.8543 };

	float df[3] = { 2, 3, 3 };

	///////////////////////////////// Parameter Strings	//////////////////////////////////////////
	int nParameters = 19;
	TString Parameters[19] = { "mean_V", "width_V", "sigma_V", "mean_G1", "sigma_G1", "mean_G2", "sigma_G2", "frac", "mean_L1", "sigma_L1", "mean_G3", "sigma_G3", "mean_L2", "sigma_L2", "frac1", "mean_L3", "sigma_L3", "mean_G4", "sigma_G4" };

	TGraphErrors *gr[nParameters];

	for (int i = 0; i < nParameters; i++)
	{
		gr[i] = new TGraphErrors(nSamples);
	}

	///////////////////////////////// Directory String	//////////////////////////////////////////           
	TString dir = "/nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2016/";

	ostringstream str;
	str << "Chi2_Summary_validation.txt";
	string nn = str.str();
	const char *p = nn.c_str();
	std::ofstream textFile(p);

	for (int icategory = 0; icategory < nCategories; icategory++)	// Loop over categories
	{

		for (int isample = 0; isample < nSamples; isample++)	// Loop over samples
		{

			TFile *fileInput = new TFile(dir + "MVA_BDT/MergeTrees/tree_s_ma" + mpoints[isample] + "_file.root");

                        std::cout << std::endl << std::endl;
	                std::cout << "--- ------------------------------------------------------------------------- --- " << std::endl;
	                std::cout << "       *** Saving fit parameters for mass point: " << points[isample] << ", category: " << categories[icategory] << " ***" << std::endl;
	                std::cout << "--- ------------------------------------------------------------------------- --- " << std::endl;
	                std::cout << std::endl << std::endl;

			TTree *tree_s = (TTree*) fileInput->Get("tree_s_" + categories[icategory]);

			//// Declare observables	////
			RooRealVar MuMu_Mass("MuMu_Mass", "MuMu_Mass", 3.5, 22);
			RooRealVar TrkTrk_DR("TrkTrk_DR", "TrkTrk_DR", 0, 1.5);
			RooRealVar MuMu_DR("MuMu_DR", "MuMu_DR", 0., 1.5);
			RooRealVar MuMuTrkTrkMET_Mass("MuMuTrkTrkMET_Mass", "MuMuTrkTrkMET_Mass", 50, 250);

			//// For Voigtian (MuMu_Mass)	////
			RooRealVar mean_V("mean_V", "mean_V", points[isample], points[isample] - 0.025, points[isample] + 0.025);
			RooRealVar width_V("width_V", "width_V", 0.00607522 *points[isample], 0.00607522 *points[isample] - 0.002, 0.00607522 *points[isample] + 0.002);
			RooRealVar sigma_V("sigma_V", "sigma_V", 0.00853482 *points[isample], 0.00853482 *points[isample] - 0.002, 0.00853482 *points[isample] + 0.002);

			//// For 2 Gaussian (MuMu_DR)	////       
			RooRealVar mean_G1("mean_G1", "mean_G1", Par_1[icategory] *points[isample], Par_1[icategory] *points[isample] - 0.044, Par_1[icategory] *points[isample] + 0.05);
			RooRealVar sigma_G1("sigma_G1", "sigma_G1", Par_2[icategory] *points[isample], Par_2[icategory] *points[isample] - 0.005, Par_2[icategory] *points[isample] + 0.005);
			RooRealVar mean_G2("mean_G2", "mean_G2", Par_3[icategory] *points[isample], Par_3[icategory] *points[isample] - 0.05, Par_3[icategory] *points[isample] + 0.05);
			RooRealVar sigma_G2("sigma_G2", "sigma_G2", Par_4[icategory] *points[isample], Par_4[icategory] *points[isample] - 0.005, Par_4[icategory] *points[isample] + 0.005);
			RooRealVar frac("frac", "frac", Par_5[icategory]);

                        //// For 2 Landau (TrkTrk_DR)	//// 
			RooRealVar mean_L1("mean_L1", "mean_L1", Par_6[icategory] *points[isample] + Par_11[icategory], Par_6[icategory] *points[isample] + Par_11[icategory] - 0.015, Par_6[icategory] *points[isample] + Par_11[icategory] + 0.015);
			RooRealVar sigma_L1("sigma_L1", "sigma_L1", Par_7[icategory] *points[isample] + Par_12[icategory], Par_7[icategory] *points[isample] + Par_12[icategory] - 0.0015, Par_7[icategory] *points[isample] + Par_12[icategory] + 0.0015);
			RooRealVar mean_G3("mean_G3", "mean_G3", 0);
			RooRealVar sigma_G3("sigma_G3", "sigma_G3", Par_9[icategory] *points[isample] + Par_10[icategory], Par_9[icategory] *points[isample] + Par_10[icategory] - 0.0015, Par_9[icategory] *points[isample] + Par_10[icategory] + 0.0015);
			RooRealVar mean_L2("mean_L2", "mean_L2", 0.0610851);
			RooRealVar sigma_L2("sigma_L2", "sigma_L2", 0.0264235);
			RooRealVar frac1("frac1", "frac1", Par_8[icategory]);

			//// For Convolution of Landau and Gaussian (MuMuTrkTrkMET_Mass) 	////    
			RooRealVar mean_L3("mean_L3", "mean_L3", Par_13[icategory], Par_13[icategory] - 2, Par_13[icategory] + 2);
			RooRealVar sigma_L3("sigma_L3", "sigma_L3", Par_14[icategory], Par_14[icategory] - 2, Par_14[icategory] + 2);
			RooRealVar mean_G4("mean_G4", "mean_G4", 0.1);
			RooRealVar sigma_G4("sigma_G4", "sigma_G4", Par_15[icategory], Par_15[icategory] - 2, Par_15[icategory] + 2);

			//// Declare Functions	////
			RooVoigtian Voigtian("Voigtian", "Voigtian", MuMu_Mass, mean_V, width_V, sigma_V);
			RooGaussian Gaussian1("Gaussian1", "Gaussian1", MuMu_DR, mean_G1, sigma_G1);
			RooGaussian Gaussian2("Gaussian2", "Gaussian2", MuMu_DR, mean_G2, sigma_G2);
			RooLandau Landau1("Landau1", "Landau1", TrkTrk_DR, mean_L1, sigma_L1);
			RooGaussian Gaussian3("Gaussian3", "Gaussian3", TrkTrk_DR, mean_G3, sigma_G3);
			RooFFTConvPdf Convoluted("Convoluted", "Convoluted", TrkTrk_DR, Landau1, Gaussian3);
			RooLandau Landau2("Landau2", "Landau2", TrkTrk_DR, mean_L2, sigma_L2);
			RooLandau Landau3("Landau3", "Landau3", MuMuTrkTrkMET_Mass, mean_L3, sigma_L3);
			RooGaussian Gaussian4("Gaussian4", "Gaussian4", MuMuTrkTrkMET_Mass, mean_G4, sigma_G4);

			//// Add pdfs to be used in model 	////
			RooAbsPdf *Signal_Model_MuMu_Mass = new RooVoigtian("Signal_Model_MuMu_Mass", "Signal_Model_MuMu_Mass", MuMu_Mass, mean_V, width_V, sigma_V);
			RooAbsPdf *Signal_Model_MuMu_DR = new RooAddPdf("Signal_Model_MuMu_DR", "Signal_Model_MuMu_DR", RooArgList(Gaussian1, Gaussian2), RooArgList(frac));
			RooAbsPdf *Signal_Model_TrkTrk_DR = new RooAddPdf("Signal_Model_TrkTrk_DR", "Signal_Model_TrkTrk_DR", RooArgList(Landau2, Convoluted), RooArgList(frac1));
			RooAbsPdf *Signal_Model_MuMuTrkTrkMET_Mass = new RooFFTConvPdf("Signal_Model_MuMuTrkTrkMET_Mass", "Signal_Model_MuMuTrkTrkMET_Mass", MuMuTrkTrkMET_Mass, Landau3, Gaussian4);

			//// Create a binned datasets that imports contents of TH1 and associates its contents to observable	////
			RooDataSet dataSR("dataSR", "dataSR", RooArgSet(MuMu_Mass, MuMu_DR, TrkTrk_DR, MuMuTrkTrkMET_Mass), Import(*tree_s));

			//// Fitting Signal Models to Histograms	//// 
			RooFitResult * r_MuMu_Mass;
			RooFitResult * r_TrkTrk_DR;
			RooFitResult * r_MuMu_DR;

			r_MuMu_Mass = Signal_Model_MuMu_Mass->fitTo(dataSR, Save());
			r_TrkTrk_DR = Signal_Model_TrkTrk_DR->fitTo(dataSR, Save());
			r_MuMu_DR = Signal_Model_MuMu_DR->fitTo(dataSR, Save());

			//// For computation of the chi square/ndof appearing in the plots	////
			RooPlot *frame_MuMu_Mass = MuMu_Mass.frame(points[isample] - 1., points[isample] + 1, 500);
			dataSR.plotOn(frame_MuMu_Mass);
			Signal_Model_MuMu_Mass->plotOn(frame_MuMu_Mass);
			RooPlot *frame_TrkTrk_DR = TrkTrk_DR.frame(0, 1.5, 100);
			dataSR.plotOn(frame_TrkTrk_DR);
			Signal_Model_TrkTrk_DR->plotOn(frame_TrkTrk_DR);
			RooPlot *frame_MuMu_DR = MuMu_DR.frame(0, 1.5, 50);
			dataSR.plotOn(frame_MuMu_DR);
			Signal_Model_MuMu_DR->plotOn(frame_MuMu_DR);

			textFile << "Chi2/NoF: " << categories[icategory] << "--> MuMu_Mass" << "-->" << mpoints[isample] << " = " << frame_MuMu_Mass->chiSquare(3) << std::endl;
			textFile << "Chi2/NoF: " << categories[icategory] << "--> MuMu_DR" << "-->" << mpoints[isample] << " = " << frame_MuMu_DR->chiSquare(4) << std::endl;
			textFile << "Chi2/NoF: " << categories[icategory] << "--> TrkTrk_DR" << "-->" << mpoints[isample] << " = " << frame_TrkTrk_DR->chiSquare(df[icategory]) << std::endl;

			gr[0]->SetPoint(isample, points[isample], mean_V.getVal());
			gr[0]->SetPointError(isample, 0., mean_V.getError());
			gr[0]->GetYaxis()->SetRangeUser(0, 35);
			gr[1]->SetPoint(isample, points[isample], width_V.getVal());
			gr[1]->SetPointError(isample, 0., width_V.getError());
			gr[1]->GetYaxis()->SetRangeUser(0, width_V.getVal() + 0.1);
			gr[2]->SetPoint(isample, points[isample], sigma_V.getVal());
			gr[2]->SetPointError(isample, 0., sigma_V.getError());
			gr[2]->GetYaxis()->SetRangeUser(0, sigma_V.getVal() + 0.2);
			gr[3]->SetPoint(isample, points[isample], mean_G1.getVal());
			gr[3]->SetPointError(isample, 0., mean_G1.getError());
			gr[3]->GetYaxis()->SetRangeUser(0, mean_G1.getVal() + 0.5);
			gr[4]->SetPoint(isample, points[isample], sigma_G1.getVal());
			gr[4]->SetPointError(isample, 0., sigma_G1.getError());
			gr[4]->GetYaxis()->SetRangeUser(0, sigma_G1.getVal() + 0.1);
			gr[5]->SetPoint(isample, points[isample], mean_G2.getVal());
			gr[5]->SetPointError(isample, 0., mean_G2.getError());
			gr[5]->GetYaxis()->SetRangeUser(0, mean_G2.getVal() + 1);
			gr[6]->SetPoint(isample, points[isample], sigma_G2.getVal());
			gr[6]->SetPointError(isample, 0., sigma_G2.getError());
			gr[6]->GetYaxis()->SetRangeUser(0, sigma_G2.getVal() + 0.1);
			gr[7]->SetPoint(isample, points[isample], frac.getVal());
			gr[7]->SetPointError(isample, 0., frac.getError());
			gr[7]->GetYaxis()->SetRangeUser(frac.getVal() - 0.1, frac.getVal() + 0.1);
			gr[8]->SetPoint(isample, points[isample], mean_L1.getVal());
			gr[8]->SetPointError(isample, 0., mean_L1.getError());
			gr[8]->GetYaxis()->SetRangeUser(0, mean_L1.getVal() + 0.5);
			gr[9]->SetPoint(isample, points[isample], sigma_L1.getVal());
			gr[9]->SetPointError(isample, 0., sigma_L1.getError());
			gr[9]->GetYaxis()->SetRangeUser(0, sigma_L1.getVal() + 0.1);
			gr[10]->SetPoint(isample, points[isample], mean_G3.getVal());
			gr[10]->SetPointError(isample, 0., mean_G3.getError());
			gr[10]->GetYaxis()->SetRangeUser(mean_G3.getVal() - 0.1, mean_G3.getVal() + 0.1);
			gr[11]->SetPoint(isample, points[isample], sigma_G3.getVal());
			gr[11]->SetPointError(isample, 0., sigma_G3.getError());
			gr[11]->GetYaxis()->SetRangeUser(sigma_G3.getVal() - 0.1, sigma_G3.getVal() + 0.1);
			gr[12]->SetPoint(isample, points[isample], mean_L2.getVal());
			gr[12]->SetPointError(isample, 0., mean_L2.getError());
			gr[12]->GetYaxis()->SetRangeUser(mean_L2.getVal() - 0.1, mean_L2.getVal() + 0.1);
			gr[13]->SetPoint(isample, points[isample], sigma_L2.getVal());
			gr[13]->SetPointError(isample, 0., sigma_L2.getError());
			gr[13]->GetYaxis()->SetRangeUser(sigma_L2.getVal() - 0.1, sigma_L2.getVal() + 0.1);
			gr[14]->SetPoint(isample, points[isample], frac1.getVal());
			gr[14]->SetPointError(isample, 0., frac1.getError());
			gr[14]->GetYaxis()->SetRangeUser(frac1.getVal() - 0.1, frac1.getVal() + 0.1);
			gr[15]->SetPoint(isample, points[isample], mean_L3.getVal());
			gr[15]->SetPointError(isample, 0., mean_L3.getError());
			gr[15]->GetYaxis()->SetRangeUser(mean_L3.getVal() - 2, mean_L3.getVal() + 2);
			gr[16]->SetPoint(isample, points[isample], sigma_L3.getVal());
			gr[16]->SetPointError(isample, 0., sigma_L3.getError());
			gr[16]->GetYaxis()->SetRangeUser(sigma_L3.getVal() - 1, sigma_L3.getVal() + 2);
			gr[17]->SetPoint(isample, points[isample], mean_G4.getVal());
			gr[17]->SetPointError(isample, 0., mean_G4.getError());
			gr[17]->GetYaxis()->SetRangeUser(mean_G4.getVal() - 0.1, mean_G4.getVal() + 0.1);
			gr[18]->SetPoint(isample, points[isample], sigma_G4.getVal());
			gr[18]->SetPointError(isample, 0., sigma_G4.getError());
			gr[18]->GetYaxis()->SetRangeUser(sigma_G4.getVal() - 1, sigma_G4.getVal() + 2);
		}

		//// Save TGraphErrors which will serve as input for interpolation procedure for mass points between the 1 GeV step	////
		TFile f("Parameters_ForValidation.root", "UPDATE");

		for (int i = 0; i < nParameters; i++)
		{
			gr[i]->Write(categories[icategory] + "_" + Parameters[i]);
		}
	}
}

void Validation(TString mass = "10")
{

	gROOT->SetBatch();
        // Silence INFO messages
        RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
        // Silence additional MINUIT output 
        RooMsgService::instance().setSilentMode(true);
        // Silence Info in TCanvas::Print: messages
        gErrorIgnoreLevel = kWarning;

	double massD = 10;
	int j = 0, k = 0;

	///////////////////////////////// Variable Strings	//////////////////////////////////////////
	TString variables[4] = { "MuMu_Mass", "TrkTrk_DR", "MuMu_DR", "MuMuTrkTrkMET_Mass" };

	///////////////////////////////// Category Strings	//////////////////////////////////////////
	int nCategories = 3;
	TString categories[3] = { "lep_lep", "lep_had", "had_had" };
	float df[3] = { 2, 3, 3 };

	//// Tgraphs	////
	//// Number of Tgraphs corresponding to one category	////
	int nParameters = 19;
	//// Total number of Tgraphs	////
	int nTotTGraphErrors = 57;

	//// Define Tgraphs arrays to be used for retrieving Tgraphs from root files	////
	TGraphErrors *gr[nTotTGraphErrors];
	TGraphErrors *gr_val[nTotTGraphErrors];

	TString Parameters[19] = { "mean_V", "width_V", "sigma_V", "mean_G1", "sigma_G1", "mean_G2", "sigma_G2", "frac", "mean_L1", "sigma_L1", "mean_G3", "sigma_G3", "mean_L2", "sigma_L2", "frac1", "mean_L3", "sigma_L3", "mean_G4", "sigma_G4" };

	///////////////////////////////// Directory String	////////////////////////////////////////// 
	TString dir = "/nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2016/";
	TFile *fileInput = new TFile(dir + "MVA_BDT/MergeTrees/tree_s_ma" + mass + "_file.root");

	//// Open root files containing Tgraphs for each of the 19 parameters	////  
	TFile *f = TFile::Open(dir + "Parameters_ForInterpolation.root");
	TFile *f_val = TFile::Open("Parameters_ForValidation.root");

	//// To retrieve Tgraphs from root file	////
	for (int icategory = 0; icategory < nCategories; icategory++)	// Loop over categories
	{
		for (int i = 0; i < nParameters; i++)
		{
			gr[j] = new TGraphErrors(nParameters);
			gr_val[j] = new TGraphErrors(nParameters);
			f->GetObject(categories[icategory] + "_" + Parameters[i], gr[j]);
			f_val->GetObject(categories[icategory] + "_" + Parameters[i], gr_val[j]);
			j = j + 1;
		}
	}

	//// Closing Tgraph input files	////
	f->Close();
	f_val->Close();

	for (int icategory = 0; icategory < nCategories; icategory++)	// Loop over categories
	{

		TTree *tree_s = (TTree*) fileInput->Get("tree_s_" + categories[icategory]);

		//// Declare observables	////
		RooRealVar MuMu_Mass("MuMu_Mass", "MuMu_Mass", 3.5, 22);
		RooRealVar TrkTrk_DR("TrkTrk_DR", "TrkTrk_DR", 0, 1.5);
		RooRealVar MuMu_DR("MuMu_DR", "MuMu_DR", 0., 1.5);
		RooRealVar MuMuTrkTrkMET_Mass("MuMuTrkTrkMET_Mass", "MuMuTrkTrkMET_Mass", 50, 250);

		//// For Voigtian (MuMu_Mass)	////
		RooRealVar mean_V("mean_V", "mean_V", gr[0 + k]->Eval(massD, 0, "S"));
		RooRealVar width_V("width_V", "width_V", gr[1 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_V("sigma_V", "sigma_V", gr[2 + k]->Eval(massD, 0, "S"));

		//// For Voigtian (MuMu_Mass)- Validation	////
		RooRealVar mean_V_val("mean_V_val", "mean_V_val", gr_val[0 + k]->Eval(massD, 0, "S"));
		RooRealVar width_V_val("width_V_val", "width_V_val", gr_val[1 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_V_val("sigma_V_val", "sigma_V_val", gr_val[2 + k]->Eval(massD, 0, "S"));

		//// For Convolution of Landau and Gaussian (MuMu_DR)	////
		RooRealVar mean_G1("mean_G1", "mean_G1", gr[3 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G1("sigma_G1", "sigma_G1", gr[4 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G2("mean_G2", "mean_G2", gr[5 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G2("sigma_G2", "sigma_G2", gr[6 + k]->Eval(massD, 0, "S"));
		RooRealVar frac("frac", "frac", gr[7 + k]->Eval(massD, 0, "S"));

		//// For Convolution of Landau and Gaussian (MuMu_DR)- Validation	////
		RooRealVar mean_G1_val("mean_G1_val", "mean_G1_val", gr_val[3 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G1_val("sigma_G1_val", "sigma_G1_val", gr_val[4 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G2_val("mean_G2_val", "mean_G2_val", gr_val[5 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G2_val("sigma_G2_val", "sigma_G2_val", gr_val[6 + k]->Eval(massD, 0, "S"));
		RooRealVar frac_val("frac_val", "frac_val", gr_val[7 + k]->Eval(massD, 0, "S"));

		//// For 2 Landau (TrkTrk_DR)	////
		RooRealVar mean_L1("mean_L1", "mean_L1", gr[8 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L1("sigma_L1", "sigma_L1", gr[9 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G3("mean_G3", "mean_G3", gr[10 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G3("sigma_G3", "sigma_G3", gr[11 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_L2("mean_L2", "mean_L2", gr[12 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L2("sigma_L2", "sigma_L2", gr[13 + k]->Eval(massD, 0, "S"));
		RooRealVar frac1("frac1", "frac1", gr[14 + k]->Eval(massD, 0, "S"));

		//// For 2 Landau (TrkTrk_DR)- Validation	////
		RooRealVar mean_L1_val("mean_L1_val", "mean_L1_val", gr_val[8 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L1_val("sigma_L1_val", "sigma_L1_val", gr_val[9 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G3_val("mean_G3_val", "mean_G3_val", gr_val[10 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G3_val("sigma_G3_val", "sigma_G3_val", gr_val[11 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_L2_val("mean_L2_val", "mean_L2_val", gr_val[12 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L2_val("sigma_L2_val", "sigma_L2_val", gr_val[13 + k]->Eval(massD, 0, "S"));
		RooRealVar frac1_val("frac1_val", "frac1_val", gr_val[14 + k]->Eval(massD, 0, "S"));

		//// For Convolution of Landau and Gaussian (MuMuTrkTrkMET_Mass)	////
		RooRealVar mean_L3("mean_L3", "mean_L3", gr[15 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L3("sigma_L3", "sigma_L3", gr[16 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G4("mean_G4", "mean_G4", gr[17 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G4("sigma_G4", "sigma_G4", gr[18 + k]->Eval(massD, 0, "S"));

		//// For Convolution of Landau and Gaussian (MuMuTrkTrkMET_Mass)- Validation	////
		RooRealVar mean_L3_val("mean_L3_val", "mean_L3_val", gr_val[15 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_L3_val("sigma_L3_val", "sigma_L3_val", gr_val[16 + k]->Eval(massD, 0, "S"));
		RooRealVar mean_G4_val("mean_G4_val", "mean_G4_val", gr_val[17 + k]->Eval(massD, 0, "S"));
		RooRealVar sigma_G4_val("sigma_G4_val", "sigma_G4_val", gr_val[18 + k]->Eval(massD, 0, "S"));

		//// Declare Functions	////
		RooVoigtian Voigtian("Voigtian", "Voigtian", MuMu_Mass, mean_V, width_V, sigma_V);
		RooGaussian Gaussian1("Gaussian1", "Gaussian1", MuMu_DR, mean_G1, sigma_G1);
		RooGaussian Gaussian2("Gaussian2", "Gaussian2", MuMu_DR, mean_G2, sigma_G2);
		RooLandau Landau1("Landau1", "Landau1", TrkTrk_DR, mean_L1, sigma_L1);
		RooGaussian Gaussian3("Gaussian3", "Gaussian3", TrkTrk_DR, mean_G3, sigma_G3);
		RooFFTConvPdf Convoluted("Convoluted", "Convoluted", TrkTrk_DR, Landau1, Gaussian3);
		RooLandau Landau2("Landau2", "Landau2", TrkTrk_DR, mean_L2, sigma_L2);
		RooLandau Landau3("Landau3", "Landau3", MuMuTrkTrkMET_Mass, mean_L3, sigma_L3);
		RooGaussian Gaussian4("Gaussian4", "Gaussian4", MuMuTrkTrkMET_Mass, mean_G4, sigma_G4);

		//// Declare Functions- Validation	////
		RooVoigtian Voigtian_val("Voigtian_val", "Voigtian_val", MuMu_Mass, mean_V_val, width_V_val, sigma_V_val);
		RooGaussian Gaussian1_val("Gaussian1_val", "Gaussian1_val", MuMu_DR, mean_G1_val, sigma_G1_val);
		RooGaussian Gaussian2_val("Gaussian2_val", "Gaussian2_val", MuMu_DR, mean_G2_val, sigma_G2_val);
		RooLandau Landau1_val("Landau1_val", "Landau1_val", TrkTrk_DR, mean_L1_val, sigma_L1_val);
		RooGaussian Gaussian3_val("Gaussian3_val", "Gaussian3_val", TrkTrk_DR, mean_G3_val, sigma_G3_val);
		RooFFTConvPdf Convoluted_val("Convoluted_val", "Convoluted_val", TrkTrk_DR, Landau1_val, Gaussian3_val);
		RooLandau Landau2_val("Landau2_val", "Landau2_val", TrkTrk_DR, mean_L2_val, sigma_L2_val);
		RooLandau Landau3_val("Landau3_val", "Landau3_val", MuMuTrkTrkMET_Mass, mean_L3_val, sigma_L3_val);
		RooGaussian Gaussian4_val("Gaussian4_val", "Gaussian4_val", MuMuTrkTrkMET_Mass, mean_G4_val, sigma_G4_val);

		//// Add pdfs to be used in model	//// 
		RooAbsPdf *Signal_Model_MuMu_Mass = new RooVoigtian("Signal_Model_MuMu_Mass", "Signal_Model_MuMu_Mass", MuMu_Mass, mean_V, width_V, sigma_V);
		RooAbsPdf *Signal_Model_MuMu_DR = new RooAddPdf("Signal_Model_MuMu_DR", "Signal_Model_MuMu_DR", RooArgList(Gaussian1, Gaussian2), RooArgList(frac));
		RooAbsPdf *Signal_Model_TrkTrk_DR = new RooAddPdf("Signal_Model_TrkTrk_DR", "Signal_Model_TrkTrk_DR", RooArgList(Landau2, Convoluted), RooArgList(frac1));
		RooAbsPdf *Signal_Model_MuMuTrkTrkMET_Mass = new RooFFTConvPdf("Signal_Model_MuMuTrkTrkMET_Mass", "Signal_Model_MuMuTrkTrkMET_Mass", MuMuTrkTrkMET_Mass, Landau3, Gaussian4);

		//// Add pdfs to be used in model	////
		RooAbsPdf *Signal_Model_MuMu_Mass_val = new RooVoigtian("Signal_Model_MuMu_Mass_val", "Signal_Model_MuMu_Mass_val", MuMu_Mass, mean_V_val, width_V_val, sigma_V_val);
		RooAbsPdf *Signal_Model_MuMu_DR_val = new RooAddPdf("Signal_Model_MuMu_DR_val", "Signal_Model_MuMu_DR_val", RooArgList(Gaussian1_val, Gaussian2_val), RooArgList(frac_val));
		RooAbsPdf *Signal_Model_TrkTrk_DR_val = new RooAddPdf("Signal_Model_TrkTrk_DR_val", "Signal_Model_TrkTrk_DR_val", RooArgList(Landau2_val, Convoluted_val), RooArgList(frac1_val));
		RooAbsPdf *Signal_Model_MuMuTrkTrkMET_Mass_val = new RooFFTConvPdf("Signal_Model_MuMuTrkTrkMET_Mass_val", "Signal_Model_MuMuTrkTrkMET_Mass_val", MuMuTrkTrkMET_Mass, Landau3_val, Gaussian4_val);

		//// Create a binned datasets that imports contents of TH1 and associates its contents to observable	////
		RooDataSet dataSR("dataSR", "dataSR", RooArgSet(MuMu_Mass, MuMu_DR, TrkTrk_DR, MuMuTrkTrkMET_Mass), Import(*tree_s));

		//// For computation of the chi square/ndof appearing in the plots	////      
		RooPlot *frame_MuMu_Mass_forchi = MuMu_Mass.frame(massD - 1., massD + 1, 500);
		dataSR.plotOn(frame_MuMu_Mass_forchi);
		Signal_Model_MuMu_Mass->plotOn(frame_MuMu_Mass_forchi);
		RooPlot *frame_TrkTrk_DR_forchi = TrkTrk_DR.frame(0, 0.8, 100);
		dataSR.plotOn(frame_TrkTrk_DR_forchi);
		Signal_Model_TrkTrk_DR->plotOn(frame_TrkTrk_DR_forchi);
		RooPlot *frame_MuMu_DR_forchi = MuMu_DR.frame(0, 0.8, 50);
		dataSR.plotOn(frame_MuMu_DR_forchi);
		Signal_Model_MuMu_DR->plotOn(frame_MuMu_DR_forchi);
		RooPlot *frame_MuMuTrkTrkMET_Mass_forchi = MuMuTrkTrkMET_Mass.frame(50, 250, 50);
		dataSR.plotOn(frame_MuMuTrkTrkMET_Mass_forchi);
		Signal_Model_MuMuTrkTrkMET_Mass->plotOn(frame_MuMuTrkTrkMET_Mass_forchi);

		double chi_MuMu_Mass = frame_MuMu_Mass_forchi->chiSquare(3);
		double chi_TrkTrk_DR = frame_TrkTrk_DR_forchi->chiSquare(df[icategory]);
		double chi_MuMu_DR = frame_MuMu_DR_forchi->chiSquare(4);
		double chi_MuMuTrkTrkMET_Mass = frame_MuMuTrkTrkMET_Mass_forchi->chiSquare(3);

		RooPlot *frame_MuMu_Mass_forchi_val = MuMu_Mass.frame(massD - 1., massD + 1, 500);
		dataSR.plotOn(frame_MuMu_Mass_forchi_val);
		Signal_Model_MuMu_Mass_val->plotOn(frame_MuMu_Mass_forchi_val);
		RooPlot *frame_TrkTrk_DR_forchi_val = TrkTrk_DR.frame(0, 0.8, 100);
		dataSR.plotOn(frame_TrkTrk_DR_forchi_val);
		Signal_Model_TrkTrk_DR_val->plotOn(frame_TrkTrk_DR_forchi_val);
		RooPlot *frame_MuMu_DR_forchi_val = MuMu_DR.frame(0, 0.8, 50);
		dataSR.plotOn(frame_MuMu_DR_forchi_val);
		Signal_Model_MuMu_DR_val->plotOn(frame_MuMu_DR_forchi_val);
		RooPlot *frame_MuMuTrkTrkMET_Mass_forchi_val = MuMuTrkTrkMET_Mass.frame(50, 250, 50);
		dataSR.plotOn(frame_MuMuTrkTrkMET_Mass_forchi_val);
		Signal_Model_MuMuTrkTrkMET_Mass_val->plotOn(frame_MuMuTrkTrkMET_Mass_forchi_val);

		double chi_MuMu_Mass_val = frame_MuMu_Mass_forchi_val->chiSquare(3);
		double chi_TrkTrk_DR_val = frame_TrkTrk_DR_forchi_val->chiSquare(df[icategory]);
		double chi_MuMu_DR_val = frame_MuMu_DR_forchi_val->chiSquare(4);
		double chi_MuMuTrkTrkMET_Mass_val = frame_MuMuTrkTrkMET_Mass_forchi_val->chiSquare(3);

		float binWidth_MuMu_Mass = (MuMu_Mass.getMax() - MuMu_Mass.getMin()) / frame_MuMu_Mass_forchi_val->GetNbinsX();
		float binWidth_TrkTrk_DR = (TrkTrk_DR.getMax() - TrkTrk_DR.getMin()) / frame_TrkTrk_DR_forchi_val->GetNbinsX();
		float binWidth_MuMu_DR = (MuMu_DR.getMax() - MuMu_DR.getMin()) / frame_MuMu_DR_forchi_val->GetNbinsX();
		float binWidth_MuMuTrkTrkMET_Mass = (MuMuTrkTrkMET_Mass.getMax() - MuMuTrkTrkMET_Mass.getMin()) / frame_MuMuTrkTrkMET_Mass_forchi_val->GetNbinsX();

		TCanvas *c1 = MakeCanvas("c1", "c1", 900, 900);
		c1->SetLeftMargin(0.12);
		c1->SetBottomMargin(0.1);

		//// Make plot of binned dataset showing Poisson error bars (RooFit default)	////
		RooPlot *frame_MuMu_Mass = MuMu_Mass.frame(Name("H->aa->mumutautau"), Title("   "));
		frame_MuMu_Mass->SetMarkerStyle(21);
		frame_MuMu_Mass->SetMarkerSize(0.8);
		frame_MuMu_Mass->SetStats(0);
		frame_MuMu_Mass->GetXaxis()->SetTitle("m(#mu_{1}, #mu_{2})[GeV]");
		frame_MuMu_Mass->GetYaxis()->SetTitle(Form("Events / %.3f GeV", binWidth_MuMu_Mass));
		frame_MuMu_Mass->GetXaxis()->SetTitleOffset(1.2);
		frame_MuMu_Mass->GetYaxis()->SetTitleOffset(1.5);
		frame_MuMu_Mass->SetMarkerSize(0.4);
		frame_MuMu_Mass->GetXaxis()->SetLabelSize(0.03);
		frame_MuMu_Mass->GetYaxis()->SetLabelSize(0.03);
		frame_MuMu_Mass->GetXaxis()->SetRangeUser(massD - 1, massD + 3);

		RooPlot *frame_TrkTrk_DR = TrkTrk_DR.frame(Name("H->aa->mumutautau"), Title("   "));
		frame_TrkTrk_DR->SetMarkerStyle(21);
		frame_TrkTrk_DR->SetMarkerSize(0.8);
		frame_TrkTrk_DR->SetStats(0);
		frame_TrkTrk_DR->GetXaxis()->SetTitle("#DeltaR(trk_{1}, trk_{2})");
		frame_TrkTrk_DR->GetYaxis()->SetTitle(Form("Events / %.3f", binWidth_TrkTrk_DR));
		frame_TrkTrk_DR->GetXaxis()->SetTitleOffset(1.2);
		frame_TrkTrk_DR->GetYaxis()->SetTitleOffset(1.5);
		frame_TrkTrk_DR->SetMarkerSize(0.4);
		frame_TrkTrk_DR->GetXaxis()->SetLabelSize(0.03);
		frame_TrkTrk_DR->GetYaxis()->SetLabelSize(0.03);
		frame_TrkTrk_DR->GetXaxis()->SetRangeUser(0, 1.5);

		RooPlot *frame_MuMu_DR = MuMu_DR.frame(Name("H->aa->mumutautau"), Title("   "));
		frame_MuMu_DR->SetMarkerStyle(21);
		frame_MuMu_DR->SetMarkerSize(0.8);
		frame_MuMu_DR->SetStats(0);
		frame_MuMu_DR->GetXaxis()->SetTitle("#DeltaR(#mu_{1}, #mu_{2})");
		frame_MuMu_DR->GetYaxis()->SetTitle(Form("Events / %.2f", binWidth_MuMu_DR));
		frame_MuMu_DR->GetXaxis()->SetTitleOffset(1.2);
		frame_MuMu_DR->GetYaxis()->SetTitleOffset(1.5);
		frame_MuMu_DR->SetMarkerSize(0.4);
		frame_MuMu_DR->GetXaxis()->SetLabelSize(0.03);
		frame_MuMu_DR->GetYaxis()->SetLabelSize(0.03);
		frame_MuMu_DR->GetXaxis()->SetRangeUser(0, 1.5);

		RooPlot *frame_MuMuTrkTrkMET_Mass = MuMuTrkTrkMET_Mass.frame(Name("H->aa->mumutautau"), Title("   "));
		frame_MuMuTrkTrkMET_Mass->SetMarkerStyle(21);
		frame_MuMuTrkTrkMET_Mass->SetMarkerSize(0.8);
		frame_MuMuTrkTrkMET_Mass->SetStats(0);
		frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetTitle("m(#mu_{1}-#mu_{2}-trk_{1}-trk_{2}, MET)[GeV]");
		frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binWidth_MuMuTrkTrkMET_Mass));
		frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetTitleOffset(1.2);
		frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetTitleOffset(1.5);
		frame_MuMuTrkTrkMET_Mass->SetMarkerSize(0.4);
		frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetLabelSize(0.03);
		frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetLabelSize(0.03);
		frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetRangeUser(50, 250);

		//// Plotting on frame MuMu_Mass    ////   
		dataSR.plotOn(frame_MuMu_Mass, Binning(500), DataError(RooAbsData::SumW2));
		Signal_Model_MuMu_Mass->plotOn(frame_MuMu_Mass, LineColor(kBlue));
		Signal_Model_MuMu_Mass_val->plotOn(frame_MuMu_Mass, LineColor(kRed));

		//// Plotting on frame TrkTrk_DR 	////          
		dataSR.plotOn(frame_TrkTrk_DR, Binning(100), DataError(RooAbsData::SumW2));
		Signal_Model_TrkTrk_DR->plotOn(frame_TrkTrk_DR, LineColor(kBlue));
		Signal_Model_TrkTrk_DR_val->plotOn(frame_TrkTrk_DR, LineColor(kRed));

		//// Plotting on frame MuMu_DR	////
		dataSR.plotOn(frame_MuMu_DR, Binning(50), DataError(RooAbsData::SumW2));
		Signal_Model_MuMu_DR->plotOn(frame_MuMu_DR, LineColor(kBlue));
		Signal_Model_MuMu_DR_val->plotOn(frame_MuMu_DR, LineColor(kRed));

		//// Plotting on frame MuMuTrkTrkMET_Massint j= 0, k=0;	////
		dataSR.plotOn(frame_MuMuTrkTrkMET_Mass, Binning(50), DataError(RooAbsData::SumW2));
		Signal_Model_MuMuTrkTrkMET_Mass->plotOn(frame_MuMuTrkTrkMET_Mass, LineColor(kBlue));

		//// Selecting legend names for MuMu_Mass	////
		for (int i = 0; i < frame_MuMu_Mass->numItems(); i++)
		{
			TString obj_name = frame_MuMu_Mass->nameOf(i);
			if (obj_name == "") continue;
			
		}
		TString names_MuMu_Mass[] = { "h_dataSR",
			"Signal_Model_MuMu_Mass_Norm[MuMu_Mass]",
			"Signal_Model_MuMu_Mass_val_Norm[MuMu_Mass]",
			"" };
		TString signs_MuMu_Mass[] = { "Real Sample",
			"Fitting of Real Sample",
			"Fitting of Interpolation",
			"" };

		//// Selecting legend names for TrkTrk_DR	////
		for (int i = 0; i < frame_TrkTrk_DR->numItems(); i++)
		{
			TString obj_name = frame_TrkTrk_DR->nameOf(i);
			if (obj_name == "") continue;
			
		}
		TString names_TrkTrk_DR[] = { "h_dataSR",
			"Signal_Model_TrkTrk_DR_Norm[TrkTrk_DR]",
			"Signal_Model_TrkTrk_DR_val_Norm[TrkTrk_DR]",
			"" };
		TString signs_TrkTrk_DR[] = { "Real Sample",
			"Fitting of Real Sample",
			"Fitting of Interpolation",
			"" };

		//// Selecting legend names for MuMu_DR	////
		for (int i = 0; i < frame_MuMu_DR->numItems(); i++)
		{
			TString obj_name = frame_MuMu_DR->nameOf(i);
			if (obj_name == "") continue;
			
		}
		TString names_MuMu_DR[] = { "h_dataSR",
			"Signal_Model_MuMu_DR_Norm[MuMu_DR]",
			"Signal_Model_MuMu_DR_val_Norm[MuMu_DR]",
			"" };
		TString signs_MuMu_DR[] = { "Real Sample",
			"Fitting of Real Sample",
			"Fitting of Interpolation",
			"" };

		//// Selecting legend names for MuMuTrkTrkMET_Mass	////
		for (int i = 0; i < frame_MuMuTrkTrkMET_Mass->numItems(); i++)
		{
			TString obj_name = frame_MuMuTrkTrkMET_Mass->nameOf(i);
			if (obj_name == "") continue;
			
		}
		TString names_MuMuTrkTrkMET_Mass[] = { "h_dataSR",
			"Signal_Model_MuMuTrkTrkMET_Mass_Norm[MuMuTrkTrkMET_Mass]",
			"" };
		TString signs_MuMuTrkTrkMET_Mass[] = { "Real Sample",
			"Fitting of Real Sample",
			"" };

		//// Legend for MuMu_Mass	////
		TLegend *legend_MuMu_Mass = new TLegend(0.49, 0.50, 0.92, 0.74);
		legend_MuMu_Mass->SetTextFont(42);
		legend_MuMu_Mass->SetTextSize(0.035);
		legend_MuMu_Mass->SetHeader("m_{a_{1}}=" + mass + " GeV", "C");
		Int_t i_MuMu_Mass = -1;
		while (names_MuMu_Mass[++i_MuMu_Mass] != "")
		{
			TObject *obj = frame_MuMu_Mass->findObject(names_MuMu_Mass[i_MuMu_Mass].Data());
			if (i_MuMu_Mass == 0) legend_MuMu_Mass->AddEntry(obj, signs_MuMu_Mass[i_MuMu_Mass], "lpe");
			else
			{
				legend_MuMu_Mass->AddEntry(obj, signs_MuMu_Mass[i_MuMu_Mass], "l");
			}
		}
		legend_MuMu_Mass->AddEntry((TObject*) 0, Form("#color[4]{#chi^{2}/ndof = %.2f}", chi_MuMu_Mass), "");
		legend_MuMu_Mass->AddEntry((TObject*) 0, Form("#color[2]{#chi^{2}/ndof = %.2f}", chi_MuMu_Mass_val), "");

		//// Legend for TrkTrk_DR	////
		TLegend *legend_TrkTrk_DR = new TLegend(0.49, 0.50, 0.92, 0.74);
		legend_TrkTrk_DR->SetTextFont(42);
		legend_TrkTrk_DR->SetTextSize(0.035);
		legend_TrkTrk_DR->SetHeader("m_{a_{1}}=" + mass + " GeV", "C");
		Int_t i_TrkTrk_DR = -1;
		while (names_TrkTrk_DR[++i_TrkTrk_DR] != "")
		{
			TObject *obj = frame_TrkTrk_DR->findObject(names_TrkTrk_DR[i_TrkTrk_DR].Data());
			if (i_TrkTrk_DR == 0) legend_TrkTrk_DR->AddEntry(obj, signs_TrkTrk_DR[i_TrkTrk_DR], "lpe");
			else
			{
				legend_TrkTrk_DR->AddEntry(obj, signs_TrkTrk_DR[i_TrkTrk_DR], "l");
			}
		}
		legend_TrkTrk_DR->AddEntry((TObject*) 0, Form("#color[4]{#chi^{2}/ndof = %.2f}", chi_TrkTrk_DR), "");
		legend_TrkTrk_DR->AddEntry((TObject*) 0, Form("#color[2]{#chi^{2}/ndof = %.2f}", chi_TrkTrk_DR_val), "");

		//// Legend for MuMu_DR	////
		TLegend *legend_MuMu_DR = new TLegend(0.49, 0.50, 0.92, 0.74);
		legend_MuMu_DR->SetTextFont(42);
		legend_MuMu_DR->SetTextSize(0.035);
		legend_MuMu_DR->SetHeader("m_{a_{1}}=" + mass + " GeV", "C");
		Int_t i_MuMu_DR = -1;
		while (names_MuMu_DR[++i_MuMu_DR] != "")
		{
			TObject *obj = frame_MuMu_DR->findObject(names_MuMu_DR[i_MuMu_DR].Data());
			if (i_MuMu_DR == 0) legend_MuMu_DR->AddEntry(obj, signs_MuMu_DR[i_MuMu_DR], "lpe");
			else
			{
				legend_MuMu_DR->AddEntry(obj, signs_MuMu_DR[i_MuMu_DR], "l");
			}
		}
		legend_MuMu_DR->AddEntry((TObject*) 0, Form("#color[4]{#chi^{2}/ndof = %.2f}", chi_MuMu_DR), "");
		legend_MuMu_DR->AddEntry((TObject*) 0, Form("#color[2]{#chi^{2}/ndof = %.2f}", chi_MuMu_DR_val), "");

		//// Legend for MuMuTrkTrkMET_Mass	////
		TLegend *legend_MuMuTrkTrkMET_Mass = new TLegend(0.57, 0.60, 0.93, 0.76);
		legend_MuMuTrkTrkMET_Mass->SetTextFont(42);
		legend_MuMuTrkTrkMET_Mass->SetTextSize(0.03);
		legend_MuMuTrkTrkMET_Mass->SetHeader("m_{a_{1}}=" + mass + " GeV", "C");
		Int_t i_MuMuTrkTrkMET_Mass = -1;
		while (names_MuMuTrkTrkMET_Mass[++i_MuMuTrkTrkMET_Mass] != "")
		{
			TObject *obj = frame_MuMuTrkTrkMET_Mass->findObject(names_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass].Data());
			if (i_MuMuTrkTrkMET_Mass == 0) legend_MuMuTrkTrkMET_Mass->AddEntry(obj, signs_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass], "lpe");
			else
			{
				legend_MuMuTrkTrkMET_Mass->AddEntry(obj, signs_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass], "l");
			}
		}
		legend_MuMuTrkTrkMET_Mass->AddEntry((TObject*) 0, Form("#color[4]{#chi^{2}/ndof = %.2f}", chi_MuMuTrkTrkMET_Mass), "");

		frame_MuMu_Mass->Draw();
		legend_MuMu_Mass->Draw();
		writeExtraText = true;
		extraText = "Work in progress";
		CMS_lumi(c1, 4, 33);
		plotchannel(" _" + categories[icategory] + " Channel");
		c1->SaveAs(categories[icategory] + "_" + variables[0] + "_" + mass + ".pdf");
		frame_TrkTrk_DR->Draw();
		legend_TrkTrk_DR->Draw();
		writeExtraText = true;
		extraText = "Work in progress";
		CMS_lumi(c1, 4, 33);
		plotchannel(" _" + categories[icategory] + " Channel");
		c1->SaveAs(categories[icategory] + "_" + variables[1] + "_" + mass + ".pdf");
		frame_MuMu_DR->Draw();
		legend_MuMu_DR->Draw();
		writeExtraText = true;
		extraText = "Work in progress";
		CMS_lumi(c1, 4, 33);
		plotchannel(" _" + categories[icategory] + " Channel");
		c1->SaveAs(categories[icategory] + "_" + variables[2] + "_" + mass + ".pdf");
		frame_MuMuTrkTrkMET_Mass->Draw();
		legend_MuMuTrkTrkMET_Mass->Draw();
		writeExtraText = true;
		extraText = "Work in progress";
		CMS_lumi(c1, 4, 33);
		plotchannel(" _" + categories[icategory] + " Channel");
		c1->SaveAs(categories[icategory] + "_" + variables[3] + "_" + mass + ".pdf");
                delete c1;

		k = k + 19;
	}
}

void PlotAllPdfs()
{

	gROOT->SetBatch();
        // Silence INFO messages
        RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
        // Silence additional MINUIT output 
        RooMsgService::instance().setSilentMode(true);
        // Silence Info in TCanvas::Print: messages
        gErrorIgnoreLevel = kWarning;

	///////////////////////////////// Variable Strings	//////////////////////////////////////////
	TString variables[4] = { "MuMu_Mass", "TrkTrk_DR", "MuMu_DR", "MuMuTrkTrkMET_Mass" };

	///////////////////////////////// Category Strings	//////////////////////////////////////////
	int nCategories = 3;
	TString categories[3] = { "lep_lep", "lep_had", "had_had" };

	///////////////////////////////// Directory String	//////////////////////////////////////////  
	TString dir = "/nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2016/";

	//// Open root file containing workspaces for each of the interpolated mass points and for each category	////
	TFile *f = TFile::Open(dir + "Workspace_Interpolation.root");

	//// Workspaces	////
	//// Number of workspaces corresponding to one category	////
	int nWorkspaces = 95;
	//// Total number of workspaces	////
	int nTotWorkspaces = 285;

	//// Counter for number of workspaces	////
	int k = 0;

	//// Define a new empty workspace array	////
	RooWorkspace *w[nTotWorkspaces];
	//// String mass point	////
	TString m_points[nTotWorkspaces];

	//// Filling the workspaces	////
	for (int icategory = 0; icategory < nCategories; icategory++)	// Loop over categories
	{
		for (double mass = 3.60; mass <= 21.0; mass += 0.20)	// Loop over masses
		{
			std::cout << std::endl << std::endl;
	                std::cout << "--- ------------------------------------------------------------------------- --- " << std::endl;
	                std::cout << "       *** Plot pdfs for mass point: " << mass << ", category: " << categories[icategory] << " ***" << std::endl;
	                std::cout << "--- ------------------------------------------------------------------------- --- " << std::endl;
	                std::cout << std::endl << std::endl;

			//// Define a string with a "." instead of a "p" for the plot's legend (cosmetic changes)	////
			TString massS;
			//// Define fractional part of mass////
			int decimal = int(int(mass *10 + 0.1) % 10);

			TString str_entere_mass = std::to_string(int(mass + 0.1));
			TString str_decimal = std::to_string(int(int(mass *10 + 0.1) % 10));

			TString mass_string = str_entere_mass + "p" + str_decimal;

			if (decimal > 0)
			{
				massS = str_entere_mass + "." + str_decimal;
			}
			else
			{
				massS = str_entere_mass;
			}

			//// Retrieve workspaces from file 	//// 
			w[k] = new RooWorkspace("ws_" + categories[icategory] + "_" + mass_string, "ws_" + categories[icategory] + "_" + mass_string);
			w[k] = (RooWorkspace*) f->Get("ws_" + categories[icategory] + "_" + mass_string);

			//// Retrieve variables, pdf and data from workspaces	////
			RooRealVar *MuMu_Mass = w[k]->var ("MuMu_Mass");
			RooRealVar *MuMu_DR = w[k]->var ("MuMu_DR");
			RooRealVar *TrkTrk_DR = w[k]->var ("TrkTrk_DR");
			RooRealVar *MuMuTrkTrkMET_Mass = w[k]->var ("MuMuTrkTrkMET_Mass");
			RooAbsPdf *model = w[k]->pdf("model");
			RooAbsPdf *Signal_Model_MuMu_Mass = w[k]->pdf("Signal_Model_MuMu_Mass");
			RooAbsPdf *Signal_Model_MuMu_DR = w[k]->pdf("Signal_Model_MuMu_DR");
			RooAbsPdf *Signal_Model_TrkTrk_DR = w[k]->pdf("Signal_Model_TrkTrk_DR");
			RooAbsPdf *Signal_Model_MuMuTrkTrkMET_Mass = w[k]->pdf("Signal_Model_MuMuTrkTrkMET_Mass");
			RooAbsData *data = w[k]->data("modelData");

			//// SaveAs structure of composite p.d.f.	////
			model->SaveAs("t");

			//// Plot pdfs	////
			TCanvas *c1 = MakeCanvas("c1", "c1", 900, 900);
			c1->SetLeftMargin(0.12);
			c1->SetBottomMargin(0.1);

			RooPlot *frame_MuMu_Mass = MuMu_Mass->frame(Name("H->aa->mumutautau"), Title("   "));
			float binWidth_MuMu_Mass = (MuMu_Mass->getMax() - MuMu_Mass->getMin()) / frame_MuMu_Mass->GetNbinsX();
			frame_MuMu_Mass->SetMarkerStyle(21);
			frame_MuMu_Mass->SetMarkerSize(0.8);
			frame_MuMu_Mass->SetStats(0);
			frame_MuMu_Mass->GetXaxis()->SetTitle("m(#mu_{1}, #mu_{2})[GeV]");
			frame_MuMu_Mass->GetYaxis()->SetTitle(Form("Events / %.3f GeV", binWidth_MuMu_Mass));
			frame_MuMu_Mass->GetXaxis()->SetTitleOffset(1.2);
			frame_MuMu_Mass->GetYaxis()->SetTitleOffset(1.7);
			frame_MuMu_Mass->SetMarkerSize(0.4);
			frame_MuMu_Mass->GetXaxis()->SetLabelSize(0.03);
			frame_MuMu_Mass->GetYaxis()->SetLabelSize(0.03);
			frame_MuMu_Mass->GetXaxis()->SetRangeUser(mass - 1, mass + 1);

			RooPlot *frame_TrkTrk_DR = TrkTrk_DR->frame(Name("H->aa->mumutautau"), Title("   "));
			float binWidth_TrkTrk_DR = (TrkTrk_DR->getMax() - TrkTrk_DR->getMin()) / frame_TrkTrk_DR->GetNbinsX();
			frame_TrkTrk_DR->SetMarkerStyle(21);
			frame_TrkTrk_DR->SetMarkerSize(0.8);
			frame_TrkTrk_DR->SetStats(0);
			frame_TrkTrk_DR->GetXaxis()->SetTitle("#DeltaR(trk_{1}, trk_{2})");
			frame_TrkTrk_DR->GetYaxis()->SetTitle(Form("Events / %.3f", binWidth_TrkTrk_DR));
			frame_TrkTrk_DR->GetXaxis()->SetTitleOffset(1.2);
			frame_TrkTrk_DR->GetYaxis()->SetTitleOffset(1.7);
			frame_TrkTrk_DR->SetMarkerSize(0.4);
			frame_TrkTrk_DR->GetXaxis()->SetLabelSize(0.03);
			frame_TrkTrk_DR->GetYaxis()->SetLabelSize(0.03);
			frame_TrkTrk_DR->GetXaxis()->SetRangeUser(0, 1.5);

			RooPlot *frame_MuMu_DR = MuMu_DR->frame(Name("H->aa->mumutautau"), Title("   "));
			float binWidth_MuMu_DR = (MuMu_DR->getMax() - MuMu_DR->getMin()) / frame_MuMu_DR->GetNbinsX();
			frame_MuMu_DR->SetMarkerStyle(21);
			frame_MuMu_DR->SetMarkerSize(0.8);
			frame_MuMu_DR->SetStats(0);
			frame_MuMu_DR->GetXaxis()->SetTitle("#DeltaR(#mu_{1}, #mu_{2})");
			frame_MuMu_DR->GetYaxis()->SetTitle(Form("Events / %.2f", binWidth_MuMu_DR));
			frame_MuMu_DR->GetXaxis()->SetTitleOffset(1.2);
			frame_MuMu_DR->GetYaxis()->SetTitleOffset(1.7);
			frame_MuMu_DR->SetMarkerSize(0.4);
			frame_MuMu_DR->GetXaxis()->SetLabelSize(0.03);
			frame_MuMu_DR->GetYaxis()->SetLabelSize(0.03);
			frame_MuMu_DR->GetXaxis()->SetRangeUser(0, 1.5);

			RooPlot *frame_MuMuTrkTrkMET_Mass = MuMuTrkTrkMET_Mass->frame(Name("H->aa->mumutautau"), Title("   "));
			float binWidth_MuMuTrkTrkMET_Mass = (MuMuTrkTrkMET_Mass->getMax() - MuMuTrkTrkMET_Mass->getMin()) / frame_MuMuTrkTrkMET_Mass->GetNbinsX();
			frame_MuMuTrkTrkMET_Mass->SetMarkerStyle(21);
			frame_MuMuTrkTrkMET_Mass->SetMarkerSize(0.8);
			frame_MuMuTrkTrkMET_Mass->SetStats(0);
			frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetTitle("m(#mu_{1}-#mu_{2}-trk_{1}-trk_{2}, MET)[GeV]");
			frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetTitle(Form("Events / %.0f GeV", binWidth_MuMuTrkTrkMET_Mass));
			frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetTitleOffset(1.2);
			frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetTitleOffset(1.7);
			frame_MuMuTrkTrkMET_Mass->SetMarkerSize(0.4);
			frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetLabelSize(0.03);
			frame_MuMuTrkTrkMET_Mass->GetYaxis()->SetLabelSize(0.03);
			frame_MuMuTrkTrkMET_Mass->GetXaxis()->SetRangeUser(50, 250);

			//// Plotting on frame MuMu_Mass	////   
			Signal_Model_MuMu_Mass->plotOn(frame_MuMu_Mass, Binning(500), LineColor(kBlue));

			//// Plotting on frame TrkTrk_DR	////                
			Signal_Model_TrkTrk_DR->plotOn(frame_TrkTrk_DR, Binning(100), LineColor(kBlue));

			//// Plotting on frame MuMu_DR	////
			Signal_Model_MuMu_DR->plotOn(frame_MuMu_DR, Binning(50), LineColor(kBlue));

			//// Plotting on frame MuMuTrkTrkMET_Mass	////     
			Signal_Model_MuMuTrkTrkMET_Mass->plotOn(frame_MuMuTrkTrkMET_Mass, Binning(50), LineColor(kBlue));

			//// Selecting legend names for MuMu_Mass	////
			for (int i = 0; i < frame_MuMu_Mass->numItems(); i++)
			{
				TString obj_name = frame_MuMu_Mass->nameOf(i);
				if (obj_name == "") continue;
				
			}
			TString names_MuMu_Mass[] = { "Signal_Model_MuMu_Mass_Norm[MuMu_Mass]",
				"" };
			TString signs_MuMu_Mass[] = { "Interpolated signal",
			};

			//// Selecting legend names for TrkTrk_DR	////
			for (int i = 0; i < frame_TrkTrk_DR->numItems(); i++)
			{
				TString obj_name = frame_TrkTrk_DR->nameOf(i);
				if (obj_name == "") continue;
				
			}
			TString names_TrkTrk_DR[] = { "Signal_Model_TrkTrk_DR_Norm[TrkTrk_DR]",
				"" };
			TString signs_TrkTrk_DR[] = { "Interpolated signal",
			};

			//// Selecting legend names for MuMu_DR	////

			for (int i = 0; i < frame_MuMu_DR->numItems(); i++)
			{
				TString obj_name = frame_MuMu_DR->nameOf(i);
				if (obj_name == "") continue;
				
			}
			TString names_MuMu_DR[] = { "Signal_Model_MuMu_DR_Norm[MuMu_DR]",
				"" };
			TString signs_MuMu_DR[] = { "Interpolated signal",
			};

			//// Selecting legend names for MuMuTrkTrkMET_Mass	////
			for (int i = 0; i < frame_MuMuTrkTrkMET_Mass->numItems(); i++)
			{
				TString obj_name = frame_MuMuTrkTrkMET_Mass->nameOf(i);
				if (obj_name == "") continue;
				
			}
			TString names_MuMuTrkTrkMET_Mass[] = { "Signal_Model_MuMuTrkTrkMET_Mass_Norm[MuMuTrkTrkMET_Mass]",
				"" };
			TString signs_MuMuTrkTrkMET_Mass[] = { "Interpolated signal",
			};

			//// Legend for MuMu_Mass	////
			TLegend *legend_MuMu_Mass = new TLegend(0.65, 0.66, 0.93, 0.76);
			legend_MuMu_Mass->SetTextFont(42);
			legend_MuMu_Mass->SetTextSize(0.027);
			legend_MuMu_Mass->SetHeader("m_{a_{1}}=" + massS + " GeV", "C");
			Int_t i_MuMu_Mass = -1;
			while (names_MuMu_Mass[++i_MuMu_Mass] != "")
			{
				TObject *obj = frame_MuMu_Mass->findObject(names_MuMu_Mass[i_MuMu_Mass].Data());
				if (i_MuMu_Mass == 0) legend_MuMu_Mass->AddEntry(obj, signs_MuMu_Mass[i_MuMu_Mass], "l");
				else
				{
					legend_MuMu_Mass->AddEntry(obj, signs_MuMu_Mass[i_MuMu_Mass], "lf");
				}
			}

			//// Legend for TrkTrk_DR	////
			TLegend *legend_TrkTrk_DR = new TLegend(0.65, 0.66, 0.93, 0.76);
			legend_TrkTrk_DR->SetTextFont(42);
			legend_TrkTrk_DR->SetTextSize(0.027);
			legend_TrkTrk_DR->SetHeader("m_{a_{1}}=" + massS + " GeV", "C");
			Int_t i_TrkTrk_DR = -1;
			while (names_TrkTrk_DR[++i_TrkTrk_DR] != "")
			{
				TObject *obj = frame_TrkTrk_DR->findObject(names_TrkTrk_DR[i_TrkTrk_DR].Data());
				if (i_TrkTrk_DR == 0) legend_TrkTrk_DR->AddEntry(obj, signs_TrkTrk_DR[i_TrkTrk_DR], "l");
				else
				{
					legend_TrkTrk_DR->AddEntry(obj, signs_TrkTrk_DR[i_TrkTrk_DR], "lf");
				}
			}

			//// Legend for MuMu_DR	////
			TLegend *legend_MuMu_DR = new TLegend(0.65, 0.66, 0.93, 0.76);
			legend_MuMu_DR->SetTextFont(42);
			legend_MuMu_DR->SetTextSize(0.027);
			legend_MuMu_DR->SetHeader("m_{a_{1}}=" + massS + " GeV", "C");
			Int_t i_MuMu_DR = -1;
			while (names_MuMu_DR[++i_MuMu_DR] != "")
			{
				TObject *obj = frame_MuMu_DR->findObject(names_MuMu_DR[i_MuMu_DR].Data());
				if (i_MuMu_DR == 0) legend_MuMu_DR->AddEntry(obj, signs_MuMu_DR[i_MuMu_DR], "l");
				else
				{
					legend_MuMu_DR->AddEntry(obj, signs_MuMu_DR[i_MuMu_DR], "lf");
				}
			}

			//// Legend for MuMuTrkTrkMET_Mass	////
			TLegend *legend_MuMuTrkTrkMET_Mass = new TLegend(0.65, 0.66, 0.93, 0.76);
			legend_MuMuTrkTrkMET_Mass->SetTextFont(42);
			legend_MuMuTrkTrkMET_Mass->SetTextSize(0.027);
			legend_MuMuTrkTrkMET_Mass->SetHeader("m_{a_{1}}=" + massS + " GeV", "C");
			Int_t i_MuMuTrkTrkMET_Mass = -1;
			while (names_MuMuTrkTrkMET_Mass[++i_MuMuTrkTrkMET_Mass] != "")
			{
				TObject *obj = frame_MuMuTrkTrkMET_Mass->findObject(names_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass].Data());
				if (i_MuMuTrkTrkMET_Mass == 0) legend_MuMuTrkTrkMET_Mass->AddEntry(obj, signs_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass], "l");
				else
				{
					legend_MuMuTrkTrkMET_Mass->AddEntry(obj, signs_MuMuTrkTrkMET_Mass[i_MuMuTrkTrkMET_Mass], "lf");
				}
			}
			frame_MuMu_Mass->Draw();
			legend_MuMu_Mass->Draw();
			writeExtraText = true;
			extraText = "Work in progress";
			CMS_lumi(c1, 4, 33);
			plotchannel(" _" + categories[icategory] + " Channel");
			c1->SaveAs(dir + "PlotAllPdfs/ma" + mass_string + "_" + categories[icategory] + "_" + variables[0] + ".pdf");
			frame_TrkTrk_DR->Draw();
			legend_TrkTrk_DR->Draw();
			writeExtraText = true;
			extraText = "Work in progress";
			CMS_lumi(c1, 4, 33);
			plotchannel(" _" + categories[icategory] + " Channel");
			c1->SaveAs(dir + "PlotAllPdfs/ma" + mass_string + "_" + categories[icategory] + "_" + variables[1] + ".pdf");
			frame_MuMu_DR->Draw();
			legend_MuMu_DR->Draw();
			writeExtraText = true;
			extraText = "Work in progress";
			CMS_lumi(c1, 4, 33);
			plotchannel(" _" + categories[icategory] + " Channel");
			c1->SaveAs(dir + "PlotAllPdfs/ma" + mass_string + "_" + categories[icategory] + "_" + variables[2] + ".pdf");
			frame_MuMuTrkTrkMET_Mass->Draw();
			legend_MuMuTrkTrkMET_Mass->Draw();
			writeExtraText = true;
			extraText = "Work in progress";
			CMS_lumi(c1, 4, 33);
			plotchannel(" _" + categories[icategory] + " Channel");
			c1->SaveAs(dir + "PlotAllPdfs/ma" + mass_string + "_" + categories[icategory] + "_" + variables[3] + ".pdf");
                        delete c1;
			k = k + 1;	// Counter for number of workspaces                    

		}
	}
}
