//---------------------------------------------------
//---- plotting tool 2D: extract time dependence ----
//---------------------------------------------------

#include "TDRStyle.cc"

void MeasureTime(std::string nameInFileRoot) {
 
  std::string var_Y = "deltaEtaSuperClusterAtVtx";
 int NBIN_Y = 200;
 float MIN_Y = -0.02;
 float MAX_Y = 0.02;
 std::string varHR_Y = "#Delta#eta";
 
 std::string var_X = "time/1000000.";
 int NBIN_X = 2000;
 float MIN_X = 1466500000;
 float MAX_X = 1468000000;
 std::string varHR_X = "time";
 std::string globalCut = "mll>80 && mll<100 && ETSC>20 && abs(etaSC)<1.5";
  
  
 TDRStyle();
 gStyle->SetTitleYOffset(1.1);
 gStyle->cd();
 
 if (varHR_X == "") {
  varHR_X = var_X;
 }
 if (varHR_Y == "") {
  varHR_Y = var_Y;
 }
 gStyle->SetOptStat(0);
 TFile* f_Sig;
 TTree* t_Sig;
 TH2F* h_Sig;
 std::string vNameSig = nameInFileRoot;
 
 TString name;
 f_Sig = new TFile (vNameSig.c_str());
 t_Sig = (TTree*) f_Sig -> Get ("ntupleEcalAlignment/myTree");
 
 //---- setup reasonable time range
 MIN_X = t_Sig->GetMinimum("time") / 1000000.;
 MAX_X = t_Sig->GetMaximum("time") / 1000000.;
 
//  NBIN_X = (MAX_X - MIN_X) / 3.6; //---- 1 hour, in musec units
 NBIN_X = (MAX_X - MIN_X) * 10000; //---- 1 hour, in musec units
 
 std::cout << " MIN_X  = " << MIN_X << std::endl;
 std::cout << " MAX_X  = " << MAX_X << std::endl;
 std::cout << " NBIN_X = " << NBIN_X << std::endl;
 std::cout << " MAX_X - MIN_X = " << MAX_X - MIN_X << std::endl;
 
 

 name = Form ("hSig");
 h_Sig = new TH2F(name.Data(),"",NBIN_X,MIN_X,MAX_X,NBIN_Y,MIN_Y,MAX_Y);
 
 TString weight = Form ("1");
 TString toDraw;
 toDraw = Form ("%s:%s >> hSig",var_Y.c_str(),var_X.c_str());
 weight = Form ("(%s)",globalCut.c_str());
 t_Sig->Draw(toDraw.Data(),weight.Data(),"goff");

 //---- estetica
 h_Sig->SetMarkerColor (kRed);
 h_Sig->SetLineColor (kRed);
 h_Sig->SetLineWidth(3);
 h_Sig->SetLineStyle(1);
 h_Sig->GetXaxis()->SetTitle(varHR_X.c_str());
 h_Sig->GetYaxis()->SetTitle(varHR_Y.c_str());

 TH2F* sum_h_Sig  = new TH2F("sum_h_Sig","",NBIN_X,MIN_X,MAX_X,NBIN_Y,MIN_Y,MAX_Y);
 sum_h_Sig->Add(h_Sig);
 sum_h_Sig->GetXaxis()->SetTitle(varHR_X.c_str());
 sum_h_Sig->GetYaxis()->SetTitle(varHR_Y.c_str());
 
 TProfile* sum_h_Sig_tx = (TProfile*) sum_h_Sig->ProfileX();
 sum_h_Sig_tx->SetMarkerSize (2);
 sum_h_Sig_tx->SetMarkerStyle (22);
 sum_h_Sig_tx->SetMarkerColor (kRed);
 sum_h_Sig_tx->SetLineColor (kRed);
 sum_h_Sig_tx->SetLineWidth(3);
 sum_h_Sig_tx->SetLineStyle(1);
 
 
 TCanvas* cc2D = new TCanvas("cc2D","cc2D",700,700);
 cc2D->SetGrid();
 sum_h_Sig->Draw("colz");
 sum_h_Sig_tx->Draw("EPsame");
  
 
 TCanvas* cc2D_x = new TCanvas("cc2D_x","cc2D_x",700,700);
 cc2D_x->SetGrid();
 sum_h_Sig_tx->Draw("PE");
 
 sum_h_Sig_tx->SaveAs("test.root");
 
}

