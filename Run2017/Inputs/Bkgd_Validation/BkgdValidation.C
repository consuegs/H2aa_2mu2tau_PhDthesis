#include "CMS_lumi.C"
#include "HttStylesNew.cc"
#include "HtoH.h"

//////////////////////****SideBands Names ****////////////////////////////////////////////////////
////// 00NN ---- 00SemiIso ---- SoftIso ---- 00SoftIso ---- NN00 ---- Sel	//
///////////////////////////////////////////////////////////////////////////////////////////////////

void BkgdValidation(TString mass = "15", TString massf = "15", TString trk = "_lep_lep", TString sideband_1 = "SoftIso", TString sideband_2 = "00NN", bool logY = true, bool showGoFtest = false)
{

	double massD = atof(mass);

	std::cout << std::endl;
	std::cout << "Mass = " << mass << std::endl;
	std::cout << std::endl;

	TString legnedstr_1 = "Soft-Iso";
	TString legnedstr_2 = "00NN";
	if (sideband_1 == "00NN") legnedstr_1 = "00NN";
	if (sideband_1 == "00SemiIso") legnedstr_1 = "00-Semi-Iso";
	if (sideband_1 == "NNNN") legnedstr_1 = "NNNN";
	if (sideband_1 == "00SoftIso") legnedstr_1 = "00-Soft-Iso";
	if (sideband_1 == "NN00") legnedstr_1 = "NN00";
    if (sideband_1 == "Sel_SS") legnedstr_1 = "Same-Sign";

	if (sideband_2 == "00NN") legnedstr_2 = "00NN";
	if (sideband_2 == "00SemiIso") legnedstr_2 = "00-Semi-Iso";
	if (sideband_2 == "NNNN") legnedstr_2 = "NNNN";
	if (sideband_2 == "00SoftIso") legnedstr_2 = "00-Soft-Iso";
	if (sideband_2 == "NN00") legnedstr_2 = "NN00";
    if (sideband_2 == "Sel_SS") legnedstr_2 = "Same-Sign";

	TFile * file;
	if (massD < 3.8) file = new TFile("../SingleMuon_BDTOutput_M-3p6.root");
	else file = new TFile("../SingleMuon_BDTOutput_M-" + mass + ".root");

	TH1D *Sideband1H_Old = (TH1D*) file->Get("MVABDTOutput" + sideband_1 + trk + "H");
	TH1D *Sideband2H_Old = (TH1D*) file->Get("MVABDTOutput" + sideband_2 + trk + "H");

	Sideband1H_Old->Rebin(100);
	Sideband2H_Old->Rebin(100);

	int nBins = Sideband1H_Old->GetNbinsX();
	float iniBin = -1.;
	float endBin = 1.;
	float bins[nBins];
	bins[0] = iniBin;
	for (int i = 1; i <= nBins; i++) bins[i] = bins[0] + i *(endBin - iniBin) / nBins;

	for (int iBins = 1; iBins < Sideband1H_Old->GetNbinsX(); iBins++)
	{
		if (Sideband1H_Old->GetBinContent(iBins) == 0. || Sideband2H_Old->GetBinContent(iBins) == 0.)
		{
			float temp = bins[iBins - (Sideband1H_Old->GetNbinsX() - nBins)];
			for (int jArr = iBins - (Sideband1H_Old->GetNbinsX() - nBins); jArr < nBins; jArr++)
			{
				bins[jArr] = bins[jArr + 1];
			}
			bins[nBins] = temp;
			nBins = nBins - 1;
		}
	}
	if (Sideband1H_Old->GetBinContent(Sideband1H_Old->GetNbinsX()) == 0. || Sideband2H_Old->GetBinContent(Sideband2H_Old->GetNbinsX()) == 0.)
	{
		bins[nBins - 1] = bins[nBins];
		nBins = nBins - 1;
	}

	TH1D *Sideband1H = (TH1D*) TH1DtoTH1D(Sideband1H_Old, nBins, bins, true, "_new");
	TH1D *Sideband2H = (TH1D*) TH1DtoTH1D(Sideband2H_Old, nBins, bins, true, "_new");

	float chi2test = Sideband2H->Chi2Test(Sideband1H, "UU");
	//cout<<" Chi2 test: "<< chi2test << endl;
	float Kolmogorov = Sideband2H->KolmogorovTest(Sideband1H);
	//cout<<" Kolmogorov test: "<< Kolmogorov << endl;

	double ScaleFactor = 1. / Sideband1H->GetSumOfWeights();

	Sideband1H->Scale(1. / Sideband1H->GetSumOfWeights());
	Sideband2H->Scale(1. / Sideband2H->GetSumOfWeights());

	int tcolor = kBlack;

	////// Histos Colors	////////
	int tcolor_2 = kAzure + 1;
	if (sideband_1 == "00NN") tcolor_2 = kRed + 2;
	if (sideband_1 == "00SemiIso") tcolor_2 = kOrange + 7;
	if (sideband_1 == "NNNN") tcolor_2 = kGreen + 3;
	if (sideband_1 == "00SoftIso") tcolor_2 = kBlue + 3;
	if (sideband_1 == "NN00") tcolor_2 = kRed - 7;
	if (sideband_1 == "Sel_SS") tcolor_2 = kAzure;
	if (sideband_1 == "SoftIso") tcolor_2 = kTeal + 4;

	TGraphAsymmErrors *data = new TGraphAsymmErrors();
	data->SetMarkerStyle(20);
	data->SetLineColor(tcolor_2);
	data->SetLineWidth(2);
	data->SetMarkerColor(tcolor_2);
	data->SetMarkerSize(3.5);

	TGraphAsymmErrors *ratio = new TGraphAsymmErrors();
	ratio->SetMarkerStyle(20);
	ratio->SetLineColor(tcolor_2);
	ratio->SetLineWidth(2);
	ratio->SetMarkerColor(tcolor_2);
	ratio->SetMarkerSize(3.5);

	TGraphAsymmErrors *ratioERR = new TGraphAsymmErrors();
	ratioERR->SetFillColorAlpha(tcolor, 0.55);

	for (int iB = 1; iB <= nBins; iB++)
	{

		double y2 = Sideband2H->GetBinContent(iB);
		double y2_err = Sideband2H->GetBinError(iB);

		double x1 = Sideband1H->GetBinCenter(iB);
		double x1_err = Sideband1H->GetBinWidth(iB) / 2.;
		double y1 = Sideband1H->GetBinContent(iB);
		double y1_errlow = TMath::Sqrt(y1 *ScaleFactor + (ScaleFactor *ScaleFactor) / 4) - ScaleFactor / 2;
		double y1_errhigh = TMath::Sqrt(y1 *ScaleFactor + (ScaleFactor *ScaleFactor) / 4) + ScaleFactor / 2;

		double r;
		double r_errlow;
		double r_errhigh;

		double u;
		double u_err;

		if (y2 < 0.000001)
		{
			r = 0.;
			r_errlow = 0.;
			r_errhigh = 0.;

			u = 1.;
			u_err = 0.;
		}
		else
		{
			r = y1 / y2;
			r_errlow = y1_errlow / y2;
			r_errhigh = y1_errhigh / y2;

			u = 1.;
			u_err = y2_err / y2;
		}

		data->SetPoint(iB - 1, x1, y1);
		data->SetPointError(iB - 1, x1_err, x1_err, y1_errlow, y1_errhigh);

		ratio->SetPoint(iB - 1, x1, r);
		ratio->SetPointError(iB - 1, x1_err, x1_err, r_errlow, r_errhigh);

		ratioERR->SetPoint(iB - 1, x1, u);
		ratioERR->SetPointError(iB - 1, x1_err, x1_err, u_err, u_err);

		Sideband2H->SetBinError(iB, 0);
	}

	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();

	upper->cd();

	Sideband2H->Draw();
	data->Draw("pZ");

	upper->Modified();
	upper->SetTicks();
	upper->SetLeftMargin(0.13);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);

	Sideband2H->SetStats(0);
	Sideband2H->GetXaxis()->SetRangeUser(-1., 1.);
	Sideband2H->GetXaxis()->SetLabelSize(0.);
	Sideband2H->GetXaxis()->SetLabelOffset(0.);
	Sideband2H->GetYaxis()->SetTitleOffset(1.2);
	Sideband2H->GetYaxis()->SetTitle("Normalized to unity");
	Sideband2H->GetYaxis()->SetTitleSize(0.045);
	Sideband2H->GetYaxis()->SetLabelSize(0.04);
	Sideband2H->GetYaxis()->SetTickLength(0.055);
	Sideband2H->GetYaxis()->SetTickSize(0.013);
	Sideband2H->GetYaxis()->SetRangeUser(0, 3 *Sideband2H->GetMaximum());
	if (logY) Sideband2H->GetYaxis()->SetRangeUser(0.000002, 1000);
	Sideband2H->SetLineColor(tcolor);
	Sideband2H->SetLineWidth(2);
	Sideband2H->SetLineStyle(1);

	TH1D *Sideband2H_legend = (TH1D*) Sideband2H->Clone("Sideband2H_legend");
	Sideband2H_legend->SetFillColorAlpha(tcolor, 0.45);

	TLegend *leg = new TLegend(0.15, 0.65, 0.62, 0.85);
	leg->SetTextSize(0.035);
	leg->SetHeader("                  #color[436]{  m_{a_{1}} = " + massf + " GeV }");
	leg->SetLineColor(kBlack);
	leg->SetLineWidth(2);
	leg->AddEntry(data, "Validation Sideband (#color[4]{" + legnedstr_1 + "})", "lpe");
	leg->AddEntry(Sideband2H_legend, "Background Model (#color[4]{" + legnedstr_2 + "})", "lf");
	leg->Draw();

	TLatex tex;
	tex.DrawLatex(-0.95, 1.3 *Sideband2H->GetMaximum(), "#color[4]{" + trk + "} Channel");

	writeExtraText = false;
	extraText = "Work in progress";
	CMS_lumi(upper, 5, 33);

	if (showGoFtest)
	{
		TPaveLabel *KolmTest = new TPaveLabel(0.67, 0.63, 0.93, 0.7, Form("Kolm. Test = %5.3f", Kolmogorov), "NDC");
		KolmTest->SetTextSize(0.45);
		KolmTest->Draw("same");
		TPaveLabel *Chi2test = new TPaveLabel(0.67, 0.53, 0.93, 0.6, Form("Chi2 Test = %5.3f", chi2test), "NDC");
		Chi2test->SetTextSize(0.45);
		Chi2test->Draw("same");
	}

	if (logY) upper->SetLogy(true);

	upper->RedrawAxis();
	upper->Update();

	lower->cd();

	TLine *line = new TLine(-1., 1., 1., 1.);
	line->SetLineColor(4);
	line->SetLineColor(tcolor);

	TMultiGraph *mg = new TMultiGraph();

	mg->Add(ratio, "PZ");
	mg->Add(ratioERR, "2");

	mg->Draw("APL");
	line->Draw("same");

	lower->Modified();
	lower->SetTicks();
	lower->SetLeftMargin(0.13);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.35);

	mg->GetXaxis()->SetRangeUser(-1., 1.);
	mg->GetXaxis()->SetLabelFont(42);
	mg->GetXaxis()->SetLabelOffset(0.03);
	mg->GetXaxis()->SetLabelSize(0.14);
	mg->GetXaxis()->SetTitleSize(0.13);
	mg->GetXaxis()->SetTitleOffset(1.35);
	mg->GetXaxis()->SetTitle("BDT Output");
	mg->GetXaxis()->SetTickLength(0.025);
	mg->GetXaxis()->SetTickSize(0.08);
	mg->GetYaxis()->SetRangeUser(-3.01, 5.01);
	mg->GetYaxis()->SetLabelOffset(0.008);
	mg->GetYaxis()->SetLabelSize(0.08);
	mg->GetYaxis()->SetTitleSize(0.1);
	mg->GetYaxis()->SetNdivisions(6);
	mg->GetYaxis()->SetTitleOffset(0.45);
	mg->GetYaxis()->SetTitle("Ratio");
	mg->GetYaxis()->SetTickLength(0.025);
	mg->GetYaxis()->SetTickSize(0.02);

	lower->RedrawAxis();
	lower->Update();

}

void PlotAll()
{

	gROOT->SetBatch();

	//// Mass points	////
	int nSamples = 19;
	int nSidebands = 7;
	TString sidebands[7] = { "00NN", "00SemiIso", "SoftIso", "00SoftIso", "NN00", "NNNN", "Sel_SS" };

	TString mpoints[19] = { "3p6", "4p0", "5p0", "6p0", "7p0", "8p0", "9p0", "10p0", "11p0", "12p0", "13p0", "14p0", "15p0", "16p0", "17p0", "18p0", "19p0", "20p0", "21p0" };
	TString mpointsD[19] = { "3.6", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" };

	int nTrackCat = 3;
	TString TrackCat[] = { "_lep_lep", "_lep_had", "_had_had" };
	TString sideband1[] = { "SoftIso", "00SoftIso" };
	TString sideband2[] = { "NNNN" };
	TString sideband3[] = { "Sel_SS" };

	// Drawing in Canvas    
	TCanvas *c = new TCanvas("c", "c", 3000, 3000);

	for (int isample = 0; isample < nSamples; isample++)
	{
		for (int iCat = 0; iCat < nTrackCat; iCat++)
		{
			BkgdValidation(mpoints[isample], mpointsD[isample], TrackCat[iCat], sideband1[0], sideband2[0], true, false);
			c->Print("Bkgd_Validation_" + sideband1[0] + "_ma" + mpoints[isample] + TrackCat[iCat] + ".pdf", "Portrait pdf");
			c->Clear();
			BkgdValidation(mpoints[isample], mpointsD[isample], TrackCat[iCat], sideband1[1], sideband2[0], true, false);
			c->Print("Bkgd_Validation_" + sideband1[1] + "_ma" + mpoints[isample] + TrackCat[iCat] + ".pdf", "Portrait pdf");
			c->Clear();
			BkgdValidation(mpoints[isample], mpointsD[isample], TrackCat[iCat], sideband3[0], sideband2[0], true, false);
			c->Print("Bkgd_Validation_" + sideband3[0] + "_ma" + mpoints[isample] + TrackCat[iCat] + ".pdf", "Portrait pdf");
			c->Clear();
		}
	}
	delete c;
	}
