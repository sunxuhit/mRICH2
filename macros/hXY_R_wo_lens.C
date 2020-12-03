void hXY_R_wo_lens () {
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


	TCanvas *c1 = new TCanvas("c1","c1",700,700);
	c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
	c1->SetTopMargin(0.15);
        c1->SetRightMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);
	c1->cd();

	TH2D *hXY = new TH2D("hXY","hXY",100,-50.,50.,100,-50.,50.);
	TH1D *hRadi = new TH1D("hRadi","hRadi",120,0.,60.);

	TChain *chDet = new TChain("PhotoDetector");
	chDet->Add("../build/Agel_muon_wo_lens.root");
	chDet->Project("hXY","y:x","pID==0 && pz>0.");
	chDet->Project("hRadi","sqrt(x*x+y*y)","pID==0 && pz>0.");

	hXY->GetYaxis()->SetTitle("X (mm)");
	hXY->GetXaxis()->SetTitle("Y (mm)");
	hXY->GetYaxis()->SetTitleColor(kBlack);
	hXY->GetYaxis()->SetTitleSize(0.05);
	hXY->GetXaxis()->SetTitleSize(0.05);
	hXY->SetLineColor(kBlack);
	hXY->Draw("");
	c1->SaveAs("figs/hXY_wo_lens.pdf");

	hRadi->GetYaxis()->SetTitle("Counts");
	hRadi->GetXaxis()->SetTitle("Radius (cm)");
        hRadi->GetYaxis()->SetTitleColor(kBlack);
        hRadi->GetYaxis()->SetTitleSize(0.05);
        hRadi->GetXaxis()->SetTitleSize(0.05);
        hRadi->SetLineColor(kBlack);
        hRadi->Draw("");
	c1->SaveAs("figs/hRadi_wo_lens.pdf");
}
