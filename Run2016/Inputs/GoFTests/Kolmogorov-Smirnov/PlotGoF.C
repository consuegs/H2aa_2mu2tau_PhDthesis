#include "CMS_lumi.C"

void PlotGoF(TString massf = "5", TString trk = "_lep_had", bool showPValue = true, bool showKSValue = true)
{

	gROOT->SetBatch();

	TFile *file_obs = new TFile("higgsCombineTest.GoodnessOfFit.mH" + massf + trk + ".root");
	TFile *file_toys = new TFile("higgsCombineTest.GoodnessOfFit.mH" + massf + ".123456" + trk + ".root");

	double limit_obs = 0, limit_toys = 0;
	double m_a;

	///////// Data	/////////////
	TTree *tree_obs = (TTree*) file_obs->Get("limit");
	tree_obs->SetBranchAddress("limit", &limit_obs);
	tree_obs->SetBranchAddress("mh", &m_a);

	tree_obs->GetEntry(0);
    
	/////////////// Toys	///////////////
	TTree *tree_toys = (TTree*) file_toys->Get("limit");
	tree_toys->SetBranchAddress("limit", &limit_toys);

	TH1D *Histo = new TH1D("Histo", "", 600, (0.85) *tree_toys->GetMinimum("limit"), (0.95) *tree_toys->GetMaximum("limit"));

	for (int ievt = 0; ievt < tree_toys->GetEntries(); ievt++)	// Loop over tree entries
	{
		tree_toys->GetEntry(ievt);
		Histo->Fill(limit_toys, 1.);
	}

	//Histo->Scale(1 / Histo->GetSumOfWeights());
	Histo->Rebin(10);
	
	float Kolmogorov = Histo->KolmogorovTest(Histo_obs);
	cout<<"Kolmogorov test: "<< Kolmogorov << endl;

	int bin_obs = Histo->GetXaxis()->FindBin(limit_obs);
	float pvalue = Histo->Integral(bin_obs, Histo->GetNbinsX()) / Histo->GetSumOfWeights();
	cout << endl << "p-value: " << pvalue << endl << endl;

	TCanvas *c = new TCanvas("c", "c", 900, 900);
	c->SetLeftMargin(0.12);
        c->SetRightMargin(0.07);
        c->SetBottomMargin(0.12);
	c->SetTicks();
	
	c->cd();
	c->Modified();

	Histo->GetYaxis()->SetRangeUser(0., 1.6 *Histo->GetMaximum());
	Histo->GetXaxis()->SetRangeUser(0., 0.10);
	Histo->SetStats(0);
	Histo->SetLineColor(kBlack);
	Histo->SetLineWidth(1);
	Histo->SetLineStyle(1);
	Histo->SetFillColor(0);
	Histo->SetFillStyle(1001);
	Histo->GetYaxis()->SetTitleOffset(1.5);
	Histo->GetYaxis()->SetTitle("toys");
	Histo->GetYaxis()->SetTitleSize(0.038);
	Histo->GetYaxis()->SetLabelSize(0.032);
	Histo->GetYaxis()->SetTickLength(0.03);
	Histo->GetXaxis()->SetLabelFont(42);
	Histo->GetXaxis()->SetLabelSize(0.032);
	Histo->GetXaxis()->SetTitleSize(0.038);
	Histo->GetXaxis()->SetTitleOffset(1.2);
	Histo->GetXaxis()->SetTitle("KS test statistic");
	Histo->GetXaxis()->SetTickLength(0.03);

	TH1D *Histo_PValue = (TH1D*) Histo->Clone("Histo_PValue");
	Histo_PValue->SetLineColor(kBlack);
	Histo_PValue->SetLineWidth(0);
	Histo_PValue->SetFillColor(kCyan);

	TArrow *arrow = new TArrow(Histo->GetBinLowEdge(bin_obs), 0.002, Histo->GetBinLowEdge(bin_obs), 0.4 *Histo->GetBinContent(bin_obs), 0.02, "<|");
	arrow->SetAngle(50);
	arrow->SetLineWidth(3);
	arrow->SetLineColor(kBlue);
	arrow->SetFillColor(kBlue);

	for (int ibin = 1; ibin < Histo_PValue->GetXaxis()->FindBin(limit_obs); ibin++)	// Loop over bins
	{
		Histo_PValue->SetBinContent(ibin, 0.);
	}

	Histo->Draw("h");
	Histo_PValue->Draw("sameh");
	arrow->Draw();

	TLegend *leg = new TLegend(0.6, 0.55, 0.85, 0.75);
	leg->SetFillColor(0);
	leg->SetHeader(" #color[1]{  m_{a_{1}} =" + massf + " GeV }");
	leg->SetTextSize(0.035);
	leg->SetBorderSize(0);
	leg->AddEntry(Histo, "Toys", "f");
	leg->AddEntry(arrow, "Observed", "l");
	leg->Draw();

        TLatex latex;
        latex.SetTextSize(0.035);
	latex.DrawLatex(0.8, 1.02 * Histo->GetMaximum(), "#color[4]{" + trk + "} Channel");

	writeExtraText = true;
	extraText = "Work in progress";
	CMS_lumi(c, 4, 33);
	
	if (showKSValue)
	{
		TPaveLabel *KolmTest = new TPaveLabel(0.6, 0.38, 0.85, 0.45, Form("Kolm. Test = %5.3f", Kolmogorov), "NDC");
		KolmTest->SetTextSize(0.45);
		KolmTest->Draw("same");
	}
	
	if (showPValue)
	{
		TPaveLabel *PValue = new TPaveLabel(0.6, 0.45, 0.85, 0.52, Form("P(#chi^{2} > obs) = %.2f", pvalue), "NDC");
		PValue->SetTextSize(0.45);
		PValue->Draw("same");
	}

	c->Update();
	c->Print("H2aa_2mu2tau_GoFma" + massf + trk + "_KS.pdf", "Portrait pdf");
	delete c;

}

void PlotAll()
{

	//// Mass points	////
	int nSamples = 19;

	TString mpointsD[19] = { "3.6", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21" };

        int nTrackCat = 3;
	TString TrackCat[] = { "_lep_lep", "_lep_had", "_had_had" };
	
	for (int isample = 0; isample < nSamples; isample++)
	{
		for (int iCat = 0; iCat < nTrackCat; iCat++)
		{
		     PlotGoF(mpointsD[isample], TrackCat[iCat], true);
		}
	}
}
