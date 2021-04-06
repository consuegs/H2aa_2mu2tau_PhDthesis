#include "CMS_lumi.C"
#include "HttStylesNew.cc"

void PlotLogStoBRatio(TString mass = "5p0", TString massD = "5", bool blinddata = true, bool drawLeg = true, bool logY = true)
{

	gROOT->SetBatch();

	double lumi = 35922;
	double xsecGGH = 48.52;

	xsecGGH = xsecGGH *0.001;	// -> 2*B(H->aa)*Br(a->tautau)*B(a->mumu)

	TString trkID[] = { "_mu", "_ele", "_had" };
	TString channel[] = { "_lep_lep", "_lep_had", "_had_had" };

	TFile *fileGGH = new TFile("../SUSYGGH_BDTOutput_M-" + mass + ".root");
	TFile *fileSGGH = new TFile("../../SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-" + massD + ".root");
	TFile *file = new TFile("../SingleMuon_BDTOutput_M-" + mass + ".root");
	TFile *fileb = new TFile("../../SingleMuon_Run2016.root");

	int nBins_Log = 7;
	float bins_log[] = { -7., -4.5, -3.4, -2.8, -1.6, -0.8, -0.27, 0. };

	TH1D *LogStoBRatio_BkgdH = new TH1D("LogStoBRatio_BkgdH", "", nBins_Log, bins_log);

	TH1D *LogStoBRatio_SignalH = new TH1D("LogStoBRatio_SignalH", "", nBins_Log, bins_log);

	TH1D *LogStoBRatio_ObsH = new TH1D("LogStoBRatio_ObsH", "", nBins_Log, bins_log);

	double Signal_Norm = 0;

	double Bkgd_Norm = 0;

	for (int iTrk1 = 0; iTrk1 < 2; iTrk1++)
	{

		for (int iTrk2 = 0; iTrk2 < 2; iTrk2++)
		{
			TString bdt_channel = "_lep_lep";
			if (iTrk1 < 2 && iTrk2 < 2) bdt_channel = "_lep_had";
			if (iTrk1 == 2 && iTrk2 == 2) bdt_channel = "_had_had";

			TFile *fileDC = new TFile("../DataCards/haa-13TeV_2016_ma" + mass + bdt_channel + ".root");
			TFile *fileFit = new TFile("../DataCards/fitDiagnostics_ma" + mass + ".root");

			TH1D *histggh = (TH1D*) fileDC->Get("ggh");
			TH1D *histBkgdX = (TH1D*) fileDC->Get("bkgd");

			///////// Signal	//////////////////////////////
			TH1D *hist_signal = (TH1D*) fileGGH->Get("MVABDTOutputSel" + bdt_channel + "H");
			TH1D *hist_signal_norm = (TH1D*) fileSGGH->Get("counter_FinalEventsH_0p2" + trkID[iTrk1] + trkID[iTrk2]);
			for (int iB = 1; iB <= hist_signal->GetNbinsX(); iB++)
			{

				double s = histggh->GetBinContent(histggh->FindBin(hist_signal->GetBinCenter(iB)));
				double b = histBkgdX->GetBinContent(histBkgdX->FindBin(hist_signal->GetBinCenter(iB)));

				double logs_b = TMath::Log10(s / (s + b));

				if (logs_b < -7.) continue;

				for (int iE = 1; iE <= hist_signal->GetBinContent(iB); iE++) LogStoBRatio_SignalH->Fill(logs_b);
			}

			///////// Bkgd	//////////////////////////////
			TH1D *hist_bkgd = (TH1D*) file->Get("MVABDTOutputSoftIso" + bdt_channel + "H");
			TH1D *hist_bkgd_norm = (TH1D*) fileb->Get("counter_FinalEventsH_0p2" + trkID[iTrk1] + trkID[iTrk2]);
			for (int iB = 1; iB <= hist_bkgd->GetNbinsX(); iB++)
			{

				double s = histggh->GetBinContent(histggh->FindBin(hist_bkgd->GetBinCenter(iB)));
				double b = histBkgdX->GetBinContent(histBkgdX->FindBin(hist_bkgd->GetBinCenter(iB)));

				double logs_b = TMath::Log10(s / (s + b));

				if (logs_b < -7.) continue;

				for (int iE = 1; iE <= hist_bkgd->GetBinContent(iB); iE++) LogStoBRatio_BkgdH->Fill(logs_b);
			}

			///////// Data	//////////////////////////////
			TH1D *hist_obs = (TH1D*) file->Get("MVABDTOutputSel" + bdt_channel + "H");
			for (int iB = 1; iB <= hist_obs->GetNbinsX(); iB++)
			{

				double s = histggh->GetBinContent(histggh->FindBin(hist_obs->GetBinCenter(iB)));
				double b = histBkgdX->GetBinContent(histBkgdX->FindBin(hist_obs->GetBinCenter(iB)));

				double logs_b = TMath::Log10(s / (s + b));

				if (logs_b < -7.) continue;

				for (int iE = 1; iE <= hist_obs->GetBinContent(iB); iE++) LogStoBRatio_ObsH->Fill(logs_b);
			}

			//////////////////// Normalizations	///////////////////////////
			////// Signal	/////
			Signal_Norm = Signal_Norm + hist_signal_norm->GetSumOfWeights();

			////// Bkgd	//////
			Bkgd_Norm = Bkgd_Norm + hist_bkgd_norm->GetSumOfWeights();
		}
	}

	//////////////////// Normalizing	///////////////////////////
	////// Signal	/////
	TH1D *histWeightsGGH = (TH1D*) fileSGGH->Get("histWeightsH");
	double nGenGGH = histWeightsGGH->GetSumOfWeights();
	double gghNorm = xsecGGH *lumi / nGenGGH;

	LogStoBRatio_SignalH->Scale(1 / LogStoBRatio_SignalH->GetSumOfWeights() *Signal_Norm *gghNorm);

	////// Bkgd	//////
	LogStoBRatio_BkgdH->Scale(1 / LogStoBRatio_BkgdH->GetSumOfWeights() *LogStoBRatio_ObsH->GetSumOfWeights());

	///////////////////////////////////////////////
	///////////*****Plotting ********/////////////
	///////////////////////////////////////////////

	int nBins = LogStoBRatio_BkgdH->GetNbinsX();

	TGraphAsymmErrors *data = new TGraphAsymmErrors();
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	TGraphAsymmErrors *ratio = new TGraphAsymmErrors();
	ratio->SetMarkerStyle(20);
	ratio->SetMarkerSize(0.5);

	TGraphAsymmErrors *ratioERR = new TGraphAsymmErrors();
	ratioERR->SetFillColorAlpha(kGray + 2, 0.35);

	for (int iB = 1; iB <= nBins; iB++)
	{

		double xB = LogStoBRatio_BkgdH->GetBinContent(iB);

		double x = LogStoBRatio_ObsH->GetBinCenter(iB);
		double ex = LogStoBRatio_ObsH->GetBinWidth(iB) / 2.;
		double y = LogStoBRatio_ObsH->GetBinContent(iB);
		double eylow = -0.5 + TMath::Sqrt(LogStoBRatio_ObsH->GetBinContent(iB) + 0.25);
		double eyhigh = 0.5 + TMath::Sqrt(LogStoBRatio_ObsH->GetBinContent(iB) + 0.25);

		double r;
		double erlow;
		double erhigh;

		double erERR;

		if (xB < 0.01)
		{
			r = 0.;
			erlow = 0.;
			erhigh = 0.;

			erERR = 0.;
		}
		else
		{
			r = LogStoBRatio_ObsH->GetBinContent(iB) / xB;
			erlow = eylow / xB;
			erhigh = eyhigh / xB;

			erERR = LogStoBRatio_BkgdH->GetBinError(iB) / xB;
		}

		if (blinddata && x > -3.5)
		{
			y = 1e10;
			r = 1000;
		}

		data->SetPoint(iB - 1, x, y);
		data->SetPointError(iB - 1, ex, ex, eylow, eyhigh);

		ratio->SetPoint(iB - 1, x, r);
		ratio->SetPointError(iB - 1, ex, ex, erlow, erhigh);

		ratioERR->SetPoint(iB - 1, x, 1.);
		ratioERR->SetPointError(iB - 1, ex, ex, erERR, erERR);

		LogStoBRatio_BkgdH->SetBinContent(iB, xB);
		LogStoBRatio_BkgdH->SetBinError(iB, 0);
		LogStoBRatio_SignalH->SetBinError(iB, 0);
	}

	TCanvas *c = new TCanvas("c", "c", 3000, 3000);

	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();

	upper->cd();

	LogStoBRatio_BkgdH->Draw("h");
	LogStoBRatio_SignalH->Draw("hsame");
	data->Draw("pZ");

	upper->Modified();
	upper->SetTicks();
	upper->SetLeftMargin(0.15);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);

	LogStoBRatio_BkgdH->SetStats(0);
	LogStoBRatio_BkgdH->GetXaxis()->SetRangeUser(-7., 0.);
	LogStoBRatio_BkgdH->GetXaxis()->SetLabelSize(0.);
	LogStoBRatio_BkgdH->GetXaxis()->SetLabelOffset(0.);
	LogStoBRatio_BkgdH->GetYaxis()->SetTitleOffset(0.77);
	LogStoBRatio_BkgdH->GetYaxis()->SetTitle("Events / bin");
	LogStoBRatio_BkgdH->GetYaxis()->SetTitleSize(0.06);
	LogStoBRatio_BkgdH->GetYaxis()->SetLabelSize(0.04);
	LogStoBRatio_BkgdH->GetYaxis()->SetTickLength(0.055);
	LogStoBRatio_BkgdH->GetYaxis()->SetTickSize(0.013);
	LogStoBRatio_BkgdH->GetYaxis()->SetRangeUser(0, 3 *LogStoBRatio_BkgdH->GetMaximum());
	if (logY) LogStoBRatio_BkgdH->GetYaxis()->SetRangeUser(0.01, 1000 *LogStoBRatio_BkgdH->GetMaximum());
	LogStoBRatio_BkgdH->SetLineColor(kViolet - 6);
	LogStoBRatio_BkgdH->SetLineWidth(1);
	LogStoBRatio_BkgdH->SetLineStyle(1);

	TH1D *LogStoBRatio_BkgdHLegend = (TH1D*) LogStoBRatio_BkgdH->Clone("LogStoBRatio_BkgdH");
	InitHist(LogStoBRatio_BkgdHLegend, "", "", TColor::GetColor(kBlue - 7), 1001);
	LogStoBRatio_BkgdHLegend->SetLineColor(kViolet - 6);
	LogStoBRatio_BkgdHLegend->SetLineWidth(1);
	LogStoBRatio_BkgdHLegend->SetLineStyle(1);
	LogStoBRatio_BkgdHLegend->SetFillColorAlpha(kGray + 2, 0.35);

	LogStoBRatio_SignalH->SetLineColor(kRed);
	LogStoBRatio_SignalH->SetLineWidth(1);
	LogStoBRatio_SignalH->SetLineStyle(1);

	TLegend *leg = new TLegend(0.2, 0.60, 0.45, 0.85);
	leg->SetTextSize(0.045);
	leg->AddEntry(data, "observed", "lep");
	leg->AddEntry(LogStoBRatio_BkgdHLegend, "bkg(+unc)", "lf");
	leg->AddEntry(LogStoBRatio_SignalH, "m_{a_{1}} = " + massD + " GeV", "l");
	if (drawLeg)
	{
		leg->Draw();
	}

	TLatex tex;
	tex.DrawLatex(-6.95, 1.3 *LogStoBRatio_BkgdH->GetMaximum(), "All Channels");

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(upper, 4, 33);

	if (logY) upper->SetLogy(true);

	upper->RedrawAxis();
	upper->Update();

	lower->cd();

	TLine *line = new TLine(-7., 1., 0., 1.);
	line->SetLineColor(kViolet - 6);
	line->SetLineColorAlpha(kViolet - 6, 0.65);

	TMultiGraph *mg = new TMultiGraph();

	mg->Add(ratio, "PZ");
	mg->Add(ratioERR, "2");

	mg->Draw("APL");
	line->Draw("same");

	lower->Modified();
	lower->SetTicks();
	lower->SetLeftMargin(0.15);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.55);

	mg->GetXaxis()->SetRangeUser(-7., 0.);
	mg->GetXaxis()->SetLabelFont(42);
	mg->GetXaxis()->SetLabelOffset(0.03);
	mg->GetXaxis()->SetLabelSize(0.14);
	mg->GetXaxis()->SetTitleSize(0.13);
	mg->GetXaxis()->SetTitleOffset(1.55);
	mg->GetXaxis()->SetTitle("Log_{10}(S/(S+B))");
	mg->GetXaxis()->SetTickLength(0.025);
	mg->GetXaxis()->SetTickSize(0.08);
	mg->GetYaxis()->SetRangeUser(-0.3, 2.29);
	mg->GetYaxis()->SetLabelOffset(0.008);
	mg->GetYaxis()->SetLabelSize(0.08);
	mg->GetYaxis()->SetTitleSize(0.1);
	mg->GetYaxis()->SetNdivisions(6);
	mg->GetYaxis()->SetTitleOffset(0.4);
	mg->GetYaxis()->SetTitle("obs/bkg   ");
	mg->GetYaxis()->SetTickLength(0.025);
	mg->GetYaxis()->SetTickSize(0.02);

	lower->RedrawAxis();
	lower->Update();

	c->Update();
	c->Print("LogStoBRatio_ma" + mass + ".pdf", "Portrait pdf");
	delete c;

}

void PlotAll(TString mass = "5p0", TString massD = "5", bool blinddata = true, bool drawLeg = true, bool logY = true)
{

	//Mass points
	int nSamples = 19;

	TString mpoints[19] = { "3p6", "4p0", "5p0", "6p0", "7p0", "8p0", "9p0", "10p0", "11p0", "12p0", "13p0", "14p0", "15p0", "16p0", "17p0", "18p0", "19p0", "20p0", "21p0" };
	TString mpointsD[19] = { "3p6", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" };

	for (int isample = 0; isample < nSamples; isample++)

		PlotLogStoBRatio(mpoints[isample], mpointsD[isample], blinddata, drawLeg, logY);

}
