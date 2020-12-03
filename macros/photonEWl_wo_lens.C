void photonEWl_wo_lens () {
	gROOT->Reset();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);
	gStyle->SetPalette(1);
	gStyle->SetOptDate(0);
	gStyle->SetOptTitle(0000);

	gStyle->SetCanvasColor(kWhite);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFrameFillColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetStatColor(kWhite);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	// gStyle->SetLabelSize(.05,"X");
	// gStyle->SetLabelSize(.05,"Y");
	gStyle->SetLabelColor(1,"X");
	gStyle->SetLabelColor(1,"Y");


	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);
	c1->cd();


	TH1D *hTotalE = new TH1D("hTotalE","hTotalE",100,1.5,4.5);
	TH1D *hNonScatE = new TH1D("hNonScatE","hNonScatE",100,1.5,4.5);
	TH1D *hScatE = new TH1D("hScatE","hScatE",100,1.5,4.5);
	TH1D *hTotalWl = new TH1D("hTotalWl","hTotalWl",100,300,620);
	TH1D *hNonScatWl = new TH1D("hNonScatWl","hNonScatWl",100,300,620);
	TH1D *hScatWl = new TH1D("hScatWl","hScatWl",100,300,620);
/*
	hTotalE->Sumw2();
	hNonScatE->Sumw2();
	hScatE->Sumw2();
	hTotalWl->Sumw2();
	hNonScatWl->Sumw2();
	hScatWl->Sumw2();
*/

	TChain *chAll = new TChain("AgelRich");
	chAll->Add("../build/Agel_muon_wo_lens.root");

	chAll->Project("hTotalE","kE*1.e6","pID==0 && pz>0 && z>-50. && z< -30.");
	chAll->Project("hTotalWl","1240./(kE*1.e6)","pID==0 && pz>0 && z>-50. && z< -30.");

	TChain *chDet = new TChain("PhotoDetector");
	chDet->Add("../build/Agel_muon_wo_lens.root");
	chDet->Project("hNonScatE","kE*1.e6","pID==0 && pz>0.");
	chDet->Project("hNonScatWl","1240./(kE*1.e6)","pID==0 && pz>0.");

	hScatE->Add(hTotalE, hNonScatE, 1., -1.);
	hScatWl->Add(hTotalWl, hNonScatWl, 1., -1.);

	hTotalE->GetXaxis()->SetRangeUser(1.9,4.2);
	hTotalE->GetYaxis()->SetRangeUser(0.,1500.);
	hTotalE->GetYaxis()->SetTitle("Counts");
	hTotalE->GetXaxis()->SetTitle("Photon Energy (eV)");
	hTotalE->GetYaxis()->SetTitleColor(kBlack);
	hTotalE->GetYaxis()->SetTitleSize(0.05);
	hTotalE->GetXaxis()->SetTitleSize(0.05);
	hTotalE->SetLineColor(kBlack);
	hTotalE->Draw("");
	hNonScatE->SetLineColor(kBlue);
	hNonScatE->Draw("SAME");
	hScatE->SetLineColor(kRed);
	hScatE->Draw("SAME");
	TLegend *leg = new TLegend(0.2,0.72,0.5,0.88);
        leg->SetTextSize(0.04);
        leg->SetLineColor(4);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetMargin(0.1);
        leg->SetFillStyle(0);
        leg->SetTextAlign(12);
        leg->SetBorderSize(0);
        leg->AddEntry(hTotalE,"    total","pl");
        leg->AddEntry(hNonScatE,"    non-scattered","pl");
        leg->AddEntry(hScatE,"    scattered","pl");
	leg->Draw();
	c1->SaveAs("figs/hPhotonE_wo_lens.pdf");

	hTotalWl->GetXaxis()->SetRangeUser(300,620);
	hTotalWl->GetYaxis()->SetTitle("Counts");
	hTotalWl->GetXaxis()->SetTitle("Photon Wavelength (nm)");
        hTotalWl->GetYaxis()->SetTitleColor(kBlack);
        hTotalWl->GetYaxis()->SetTitleSize(0.05);
        hTotalWl->GetXaxis()->SetTitleSize(0.05);
        hTotalWl->SetLineColor(kBlack);
        hTotalWl->Draw("");
        hNonScatWl->SetLineColor(kBlue);
        hNonScatWl->Draw("SAME");
        hScatWl->SetLineColor(kRed);
        hScatWl->Draw("SAME");
	TLegend *leg = new TLegend(0.6,0.7,0.8,0.85);
        leg->SetTextSize(0.04);
        leg->SetLineColor(4);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetMargin(0.1);
        leg->SetFillStyle(0);
        leg->SetTextAlign(12);
        leg->SetBorderSize(0);
        leg->AddEntry(hTotalWl,"    total","pl");
        leg->AddEntry(hNonScatWl,"    non-scattered","pl");
        leg->AddEntry(hScatWl,"    scattered","pl");
        leg->Draw();
	c1->SaveAs("figs/hPhotonWL_wo_lens.pdf");
}
