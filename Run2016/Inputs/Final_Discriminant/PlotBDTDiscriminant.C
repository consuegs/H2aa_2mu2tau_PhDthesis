#include "CMS_lumi.C"
#include "HttStylesNew.cc"

void PlotBDTDiscriminant(TString mass = "5p0", TString massD = "5", TString trk = "_lep_lep", bool blinddata = false, bool drawLeg = true, bool logY = true)
{

	TFile *file = new TFile("../DataCards/haa-13TeV_2016_ma" + mass + trk + ".root");
	TFile *fileFit = new TFile("../DataCards/fitDiagnostics_ma" + mass + ".root");

	TH1D *histggh = (TH1D*) file->Get("ggh");
	TH1D *histData = (TH1D*) file->Get("data_obs");
	TH1D *histBkgd = (TH1D*) file->Get("bkgd");
	TH1D *histBkgdX = (TH1D*) fileFit->Get("shapes_fit_b/" + trk + "/total_background")->Clone("histBkgdX");

	int nBins = histBkgd->GetNbinsX();

	TGraphAsymmErrors *data = new TGraphAsymmErrors();
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);

	TGraphAsymmErrors *ratio = new TGraphAsymmErrors();
	ratio->SetMarkerStyle(20);
	ratio->SetMarkerSize(0.5);

	TGraphAsymmErrors *ratioERR = new TGraphAsymmErrors();
	ratioERR->SetFillColorAlpha(kBlue - 7, 0.35);

	for (int iB = 1; iB <= nBins; iB++)
	{

		double xB = histBkgdX->GetBinContent(iB);

		double x = histData->GetBinCenter(iB);
		double ex = histData->GetBinWidth(iB) / 2.;
		double y = histData->GetBinContent(iB);
		double eylow = -0.5 + TMath::Sqrt(histData->GetBinContent(iB) + 0.25);
		double eyhigh = 0.5 + TMath::Sqrt(histData->GetBinContent(iB) + 0.25);

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
			r = histData->GetBinContent(iB) / xB;
			erlow = eylow / xB;
			erhigh = eyhigh / xB;

			erERR = histBkgdX->GetBinError(iB) / xB;
		}

		if (blinddata && x > -0.5)
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

		histBkgd->SetBinContent(iB, xB);
		histBkgd->SetBinError(iB, 0);
		histggh->SetBinError(iB, 0);
	}

	TPad *upper = new TPad("upper", "pad", 0, 0.31, 1, 1);
	upper->Draw();
	TPad *lower = new TPad("lower", "pad", 0, 0, 1, 0.30);
	lower->Draw();

	upper->cd();

	histBkgd->Draw("h");
	histggh->Draw("hsame");
	data->Draw("pZ");

	upper->Modified();
	upper->SetTicks();
	upper->SetLeftMargin(0.09);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);

	histBkgd->SetStats(0);
	histBkgd->GetXaxis()->SetRangeUser(-1., 1.);
	histBkgd->GetXaxis()->SetLabelSize(0.);
	histBkgd->GetXaxis()->SetLabelOffset(0.);
	histBkgd->GetYaxis()->SetTitleOffset(0.77);
	histBkgd->GetYaxis()->SetTitle("Events / bin");
	histBkgd->GetYaxis()->SetTitleSize(0.06);
	histBkgd->GetYaxis()->SetLabelSize(0.04);
	histBkgd->GetYaxis()->SetTickLength(0.055);
	histBkgd->GetYaxis()->SetTickSize(0.013);
	histBkgd->GetYaxis()->SetRangeUser(0, 3 *histBkgd->GetMaximum());
	if (logY) histBkgd->GetYaxis()->SetRangeUser(0.01, 1000 *histBkgd->GetMaximum());
	histBkgd->SetLineColor(4);
	histBkgd->SetLineWidth(1);
	histBkgd->SetLineStyle(1);

	TH1D *histBkgdLegend = (TH1D*) histBkgd->Clone("histBkgd");
	InitHist(histBkgdLegend, "", "", TColor::GetColor(kBlue - 7), 1001);
	histBkgdLegend->SetLineColor(4);
	histBkgdLegend->SetLineWidth(1);
	histBkgdLegend->SetLineStyle(1);
	histBkgdLegend->SetFillColorAlpha(kBlue - 7, 0.35);

	histggh->SetLineColor(kRed);
	histggh->SetLineWidth(1);
	histggh->SetLineStyle(2);

	TLegend *leg = new TLegend(0.2, 0.60, 0.5, 0.85);
	leg->SetTextSize(0.045);
	leg->AddEntry(data, "observed", "lep");
	leg->AddEntry(histBkgdLegend, "bkg(+unc)", "lf");
	leg->AddEntry(histggh, "m_{a_{1}} = " + massD + " GeV", "l");
	if (drawLeg)
	{
		leg->Draw();
	}

	TLatex tex;
	tex.DrawLatex(-0.95, 1.3 *histBkgd->GetMaximum(), trk + " Channel");

	writeExtraText = false;
	extraText = "Work in progress";
	CMS_lumi(upper, 4, 33);

	if (logY) upper->SetLogy(true);

	upper->RedrawAxis();
	upper->Update();

	lower->cd();

	TLine *line = new TLine(-1., 1., 1., 1.);
	line->SetLineColor(4);
	line->SetLineColorAlpha(kBlue, 0.65);

	TMultiGraph *mg = new TMultiGraph();

	mg->Add(ratio, "PZ");
	mg->Add(ratioERR, "2");

	mg->Draw("APL");
	line->Draw("same");

	lower->Modified();
	lower->SetTicks();
	lower->SetLeftMargin(0.09);
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
	mg->GetYaxis()->SetRangeUser(-1.01, 3.01);
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

}

void PlotDiscriminant(TString mass = "5p0", TString massD = "5.0", bool blinddata = true, bool drawLeg = true, bool logY = true)
{

	gROOT->SetBatch();

	int nTrackCat = 3;
	TString TrackCat[] = { "_lep_lep", "_lep_had", "_had_had" };

	// Drawing in Canvas 
	TCanvas *c = new TCanvas("c", "c", 10, 10, 500, 500);

	for (int iCat = 0; iCat < nTrackCat; iCat++)
	{

		PlotBDTDiscriminant(mass, massD, TrackCat[iCat], blinddata, drawLeg, logY);
		c->Print("FinalDiscriminant_ma" + mass + TrackCat[iCat] + ".pdf", "Portrait pdf");
		c->Clear();
	}
	delete c;
}

void PlotAll(TString mass = "5p0", TString massD = "5", bool blinddata = false, bool drawLeg = true, bool logY = true)
{

	//// Mass points ////
	int nSamples = 19;

	TString mpoints[19] = { "3p6", "4p0", "5p0", "6p0", "7p0", "8p0", "9p0", "10p0", "11p0", "12p0", "13p0", "14p0", "15p0", "16p0", "17p0", "18p0", "19p0", "20p0", "21p0" };
	TString mpointsD[19] = { "3.6", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" };

	for (int isample = 0; isample < nSamples; isample++)

		PlotDiscriminant(mpoints[isample], mpointsD[isample], false, true, true);

}
