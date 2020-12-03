// This macro is used for plotting the photon hits position on
// the sensor plane. The peak distribution is fitted with a gaussian
// distribution.
// Last updated on: Nov 3, 2015, Ping & Xiaochun
//

void hXY_R_w_lens () {
	gROOT->Reset();
	gStyle->SetOptStat("e");  // onpy print entries in stat box
	//gStyle->SetOptFit(111);
	//gStyle->SetPalette(1);
	gStyle->SetOptDate(1);
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
	// Read in the ourput data from Geant4 simulation
	chDet->Add("Agel_sim.root");
	chDet->Project("hXY","y:x","pID==0 && pz>0.");
	chDet->Project("hRadi","sqrt(x*x+y*y)","pID==0 && pz>0.");

	hXY->GetYaxis()->SetTitle("X (mm)");
	hXY->GetXaxis()->SetTitle("Y (mm)");
	hXY->GetYaxis()->SetTitleColor(kBlack);
	hXY->GetYaxis()->SetTitleSize(0.05);
	hXY->GetXaxis()->SetTitleSize(0.05);
	hXY->SetLineColor(kBlack);
	hXY->Draw("");
	c1->SaveAs("figs/hXY_hits.pdf");
	c1->SaveAs("figs/hXY_hits.png");
	c1->SaveAs("figs/hXY_hits.eps");

	// Define a gauss fit function
	TF1 *g1 = new TF1("g1", "gaus",15.,20.);
	Double_t par[3];
	char name[30]; 

	hRadi->GetYaxis()->SetTitle("Counts");
	hRadi->GetXaxis()->SetTitle("Radius (mm)");
        hRadi->GetYaxis()->SetTitleColor(kBlack);
        hRadi->GetYaxis()->SetTitleSize(0.05);
        hRadi->GetXaxis()->SetTitleSize(0.05);
        hRadi->SetLineColor(kBlack);
	hRadi->Fit("g1", "R");  // "R" restricted fitting range
	g1->GetParameters(&par[0]);
	cout << " Constant: " << par[0] << " Mean: " << par[1] << "  Sigma: " << par[2] << endl;
	cout << " Integral counts within the range of 15 - 20: " << hRadi->Integral(30,40) << endl;

	// Adding fit parameters on the plot
	TPaveText *pt = new TPaveText(.45,0.55,.80,.80,"blNDC");
	pt->AddText("Aerogel simulation (3cm block)");
	pt->AddText("100 muons at 4 GeV/c");
	//sprintf(name, "Constant:  %6.1f", par[0]);
	sprintf(name, "Integrated counts (15 - 20):  %d",hRadi->Integral(30,40));
	pt->AddText(name);
	sprintf(name, "    Mean:  %6.2f mm", par[1]);
	pt->AddText(name);
	sprintf(name, "   Sigma:  %6.2f mm", par[2]);
	pt->AddText(name);

	pt->SetBorderSize(0);
	pt->SetFillColor(0);
	pt->SetTextFont(30);
	
        hRadi->Draw("");
	pt->Draw();

	c1->SaveAs("figs/hRadi_w_lens.pdf");
	c1->SaveAs("figs/hRadi_w_lens.png");
	c1->SaveAs("figs/hRadi_w_lens.eps");
}
