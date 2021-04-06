#include "CMS_lumi.C"
#include "HttStylesNew.cc"
#include "HtoH.h"
#include "TMath.h"

void Get_Composition(TString HistName = "histWeights_00NN_lep_lepH", TString region = "_00NN", TString category = "_lep_lep")
{

	float qcdScale = 2.39;
	float xsecGGH = 48.52 * 0.001;
	float lumi = 59740;

	///////////////////////////////// Directory String	////////////////////////////////////////////                    
	TString dir = "/nfs/dust/cms/user/consuegs/H2aa_2mu2tau/Run2018/";

	TFile *file_data = new TFile(dir + "CreateHistos/SingleMuon_Run2018_CompStudy_output.root");

	int nMCSamples = 25;

	TString samples[25] = {  "WW_13TeV-pythia8",	            // (0)
		"WZ_13TeV-pythia8",	                                    // (1) 
		"ZZ_13TeV-pythia8",	                                    // (2)
		"WJetsToLNu_13TeV-madgraphMLM",	                        // (3)
		"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg",	// (4)
		"ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg",	    // (5)
		"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg",	    // (6)
		"ST_tW_top_5f_inclusiveDecays_13TeV-powheg",	        // (7)
		//"TT_13TeV-powheg-pythia8",	                        // (8)
        "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8",	            // (8)                         
		"TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8",	    // (9)
		"TTToHadronic_TuneCP5_13TeV-powheg-pythia8",	        // (10)
		"DYJetsToLL_M-10to50_13TeV-madgraphMLM",	            // (11)
		"DYJetsToLL_M-50_13TeV-madgraphMLM",	                // (12) 
        //"QCD_Pt-20toInf_MuEnrichedPt15_13TeV",	            // (13)
		"QCD_Pt-20to30_MuEnrichedPt5_TuneCP5",	                // (13)
		"QCD_Pt-30to50_MuEnrichedPt5_TuneCP5",	                // (14)
		"QCD_Pt-50to80_MuEnrichedPt5_TuneCP5",	                // (15)
		"QCD_Pt-80to120_MuEnrichedPt5_TuneCP5",	                // (16)
		"QCD_Pt-120to170_MuEnrichedPt5_TuneCP5",	            // (17)
		"QCD_Pt-170to300_MuEnrichedPt5_TuneCP5",	            // (18)
		"QCD_Pt-300to470_MuEnrichedPt5_TuneCP5",	            // (19)
		"QCD_Pt-470to600_MuEnrichedPt5_TuneCP5",	            // (20)
		"QCD_Pt-600to800_MuEnrichedPt5_TuneCP5",	            // (21)
		"QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5",	            // (22)
		"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5",	            // (23)
		"SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-10"	            // (24)
	};

	float xsec[25] = { 118.7,	// WW   (0)
		27.57,	// WZ                   (1)
		12.14,	// ZZ                   (2)
		61526.7,	// WJets            (3)
		80.95,	// ST_t-channel_antitop (4)
		136.02,	// ST_t-channel_top     (5)
		35.85,	// ST_tW_antitop        (6)
		35.85,	// ST_tW_top            (7)		
		//831.6,	// TTbar            (8)
		88.29,	// TTTo2L2Nu            (8)
		365.35,	// TTToSemiLeptonic     (9)
		377.96,	// TTToHadronic         (10)	
		21658,	// DYJetsToLL_M-10to50  (11)
		6077.22, // DYJetsToLL_M-50     (12)		
        //720648000 * 0.00042,  // QCD  (13)            
		558528000 * 0.0053,	// QCD      (13)
		139803000 * 0.01182,	// QCD  (14)
		19222500 * 0.02276,	// QCD      (15)
		2758420 * 0.03844,	// QCD      (16)
		469797 * 0.05362,	// QCD      (17)
		117989 * 0.07335,	// QCD      (18)
		7820.25 * 0.10196,	// QCD      (19)
		645.528 * 0.12242,	// QCD      (20)
		187.109 * 0.13412,	// QCD      (21)
		32.3486 * 0.14552,	// QCD      (22)
		10.4305 * 0.15544,	// QCD      (23)
		xsecGGH	// ma=10                (24)
	};

	xsec[13] *= qcdScale;
	xsec[14] *= qcdScale;
	xsec[15] *= qcdScale;
	xsec[16] *= qcdScale;
	xsec[17] *= qcdScale;
	xsec[18] *= qcdScale;
	xsec[19] *= qcdScale;
	xsec[20] *= qcdScale;
	xsec[21] *= qcdScale;
	xsec[22] *= qcdScale;
	xsec[23] *= qcdScale;

	TH1D *DataOldH = (TH1D*) file_data->Get(HistName);

	////// ****Rebining ****////////
	int nBins = DataOldH->GetNbinsX();
	float xMin = DataOldH->GetBinLowEdge(1);
	float xMax = DataOldH->GetBinLowEdge(nBins + 1);

	float bins[400];
	int nBinsNew = 50;

	float binWidth = (xMax - xMin) / float(nBinsNew);
	for (int iB = 0; iB <= nBinsNew; ++iB) bins[iB] = xMin + float(iB) *binWidth;

	////// ****Histograms ****////////
	TH1D *DataH = TH1DtoTH1D(DataOldH, nBinsNew, bins, true, "_Data_new");

	TH1D *EWKH = new TH1D("EWKH", "", nBinsNew, bins);
	TH1D *TTH = new TH1D("TTH", "", nBinsNew, bins);
	TH1D *QCDH = new TH1D("QCDH", "", nBinsNew, bins);
	TH1D *DYH = new TH1D("DYH", "", nBinsNew, bins);
	TH1D *SUSYH = new TH1D("SUSYH", "", nBinsNew, bins);

	////// ****MC Histograms ****////////
	for (int isample = 0; isample < nMCSamples; isample++)
	{

		TFile *fileMC = new TFile(dir + "CreateHistos/" + samples[isample] + "_CompStudy_output.root");

		TH1D *HistOld = (TH1D*) fileMC->Get(HistName);

		TH1D *Hist = TH1DtoTH1D(HistOld, nBinsNew, bins, true, "_new_" + samples[isample]);

		TH1D *eventCount = (TH1D*) fileMC->Get("histWeightsH");
        TH1D *WeightsBTag = (TH1D*) fileMC->Get("histWeightsBTagH");
        TH1D *WeightsZeroBTag = (TH1D*) fileMC->Get("histWeightsZeroBTagH");

		float nGen = eventCount->GetSumOfWeights();
		float norm = xsec[isample] *lumi / nGen;

        norm = norm * WeightsBTag->GetSumOfWeights()/WeightsZeroBTag->GetSumOfWeights();

		TH1D *tempHist = EWKH;

		if (isample > 3 && isample < 11) tempHist = TTH;

		if (isample == 11 || isample == 12) tempHist = DYH;

		if (isample > 12 && isample < 24) tempHist = QCDH;

		if (isample == 24) tempHist = SUSYH;

		tempHist->Add(tempHist, Hist, 1., norm);
		delete fileMC;
	}

	////// ****Total Yields ****////////
	float EWKTot = 0;
	float TTTot = 0;
	float QCDTot = 0;
	float DYTot = 0;
	float SUSYTot = 0;

	////// ****Uncertainties ****////////
	///// Systematics	/////
	float lumiSys = 0.03;
	float lepSys = 0.04;

	float EWKSys = 0.20;
	float TTSys = 0.15;
	float QCDSys = 0.30;
	float DYSys = 0.05;

	///// Statistical	/////
	float EWKE2 = 0;
	float TTE2 = 0;
	float QCDE2 = 0;
	float DYE2 = 0;
	float SUSYE2 = 0;

	for (int iB = 1; iB <= nBinsNew; ++iB)
	{

		float ewkX = EWKH->GetBinContent(iB);
		float ewkE = EWKH->GetBinError(iB);

		float ttX = TTH->GetBinContent(iB);
		float ttE = TTH->GetBinError(iB);

		float qcdX = QCDH->GetBinContent(iB);
		float qcdE = QCDH->GetBinError(iB);

		float dyX = DYH->GetBinContent(iB);
		float dyE = DYH->GetBinError(iB);

		float susyX = SUSYH->GetBinContent(iB);
		float susyE = SUSYH->GetBinError(iB);

		EWKE2 += ewkE * ewkE;
		TTE2 += ttE * ttE;
		QCDE2 += qcdE * qcdE;
		DYE2 += dyE * dyE;
		SUSYE2 += susyE * susyE;

		EWKTot += ewkX;
		TTTot += ttX;
		QCDTot += qcdX;
		DYTot += dyX;
		SUSYTot += susyX;

		if (dyX < 0) dyX = 0;

		float ewkErr = ewkX * EWKSys;
		float ttErr = ttX * TTSys;
		float qcdErr = qcdX * QCDSys;
		float dyErr = dyX * DYSys;

		ttX += ewkX;
		dyX += ttX;
		qcdX += dyX;

		float lumiErr = qcdX * lumiSys;
		float lepErr = qcdX * lepSys;

		float totErr = TMath::Sqrt(lumiErr *lumiErr +
			lepErr *lepErr +
			ttErr *ttErr +
			ewkErr *ewkErr +
			qcdErr *qcdErr +
			ewkE *ewkE +
			dyE *dyE +
			ttE *ttE +
			qcdE *qcdE);

		EWKH->SetBinContent(iB, ewkX);
		TTH->SetBinContent(iB, ttX);
		DYH->SetBinContent(iB, dyX);
		QCDH->SetBinContent(iB, qcdX);
		QCDH->SetBinError(iB, totErr);
		SUSYH->SetBinError(iB, 0);
	}

	float EWKE = TMath::Sqrt(EWKE2);
	float TTE = TMath::Sqrt(TTE2);
	float QCDE = TMath::Sqrt(QCDE2);
	float DYE = TMath::Sqrt(DYE2);
	float SUSYE = TMath::Sqrt(SUSYE2);
	float BkgTot = QCDTot + EWKTot + TTTot + DYTot;

	std::cout << "Background Composition, region: " << region << ", category: " << category << std::endl;
	std::cout << "*************************************************************************************************" << std::endl;
	std::cout << std::setprecision(3);
	std::cout << "QCD : " << Form("%.2f", 100 *QCDTot / BkgTot) << " +/- " <<
		Form("%.2f", 100 *QCDTot / BkgTot *TMath::Sqrt(1 / BkgTot + (QCDE / QCDTot) *(QCDE / QCDTot))) << " % | ";
	std::cout << "EWK : " << Form("%.2f", 100 *EWKTot / BkgTot) << " +/- " <<
		Form("%.2f", 100 *EWKTot / BkgTot *TMath::Sqrt(1 / BkgTot + (EWKE / EWKTot) *(EWKE / EWKTot))) << " % | ";
	std::cout << "TTJ : " << Form("%.2f", 100 *TTTot / BkgTot) << " +/- " <<
		Form("%.2f", 100 *TTTot / BkgTot *TMath::Sqrt(1 / BkgTot + (TTE / TTTot) *(TTE / TTTot))) << " % | ";
	std::cout << "DY  : " << Form("%.2f", 100 *DYTot / BkgTot) << " +/- " <<
		Form("%.2f", 100 *DYTot / BkgTot *TMath::Sqrt(1 / BkgTot + (DYE / DYTot) *(DYE / DYTot))) << " % | ";
	std::cout << std::endl;
	std::cout << "*************************************************************************************************" << std::endl;
	std::cout << std::endl;

	std::cout << "QCD : " << Form("%.2f", QCDTot) << " +/- " << Form("%.2f", QCDE) << std::endl;
	std::cout << "EWK : " << Form("%.2f", EWKTot) << " +/- " << Form("%.2f", EWKE) << std::endl;
	std::cout << "TTJ : " << Form("%.2f", TTTot) << " +/- " << Form("%.2f", TTE) << std::endl;
	std::cout << "DY  : " << Form("%.2f", DYTot) << " +/- " << Form("%.2f", DYE) << std::endl;
	std::cout << "BKG : " << Form("%.2f", BkgTot) << std::endl;
	std::cout << "DAT : " << Form("%.2f", DataH->GetSumOfWeights()) << std::endl;
	std::cout << "ma(10) : " << Form("%.2f", SUSYTot) << " +/- " << Form("%.2f", SUSYE) << std::endl;
	std::cout << std::endl;
	
	delete file_data;

}

void Bkgd_Composition()
{

	gSystem->RedirectOutput("Bkgd_Composition.txt", "w");

	std::cout << "Background composition in SR and CRs: NNNN, 00NN, 00SemiIso, SoftIso, 00SoftIso and NN00 per category (lep-lep, lep-had, had-had):" << std::endl << std::endl;

	///////////////////////////////// Region Strings	////////////////////////////////////////////
	int nRegions = 7;

	TString regions[7] = { "Sel", "_NNNN", "_00NN", "_00SemiIso", "_SoftIso", "_00SoftIso", "_NN00" };

	///////////////////////////////// Category Strings	////////////////////////////////////////////
	int ntrackCat = 3;

	TString trackCat[] = { "_lep_lep", "_lep_had", "_had_had" };

	for (int iregion = 0; iregion < nRegions; iregion++)	// Loop over regions
	{
		for (int icat = 0; icat < ntrackCat; icat++)	// Loop over main categories
		{
			TString HistName = "histWeights" + regions[iregion] + trackCat[icat] + "H";

			Get_Composition(HistName, regions[iregion], trackCat[icat]);
		}	// End loop over main categories
	}	// End loop over regions

	gSystem->RedirectOutput(0);
}
