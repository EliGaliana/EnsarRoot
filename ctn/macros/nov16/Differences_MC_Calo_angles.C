////////////////////////////////////////////////////////////////////////////////////
////																			
////	--- Simulation of the Lisbon Nov-2016 setup ---						
////																			
////	Macro to check the differences of the MCTrack and CaloHit angles		
////						
////																			
////	Usage:																
////		1st: select the root file path & change the ranges (OPTIONAL)	
////		2nd: root -l Differences_MC_Calo_angles.C						
////																		
////	Calculate:
////		-Differences between MCTrack and Calo of the Theta&Phi angles 															
////		-MCTrack: Phi & Theta for each CryId							
////		-Calo: Phi & Theta for each CryId								
////		-Theta_MCTrack + Theta_Calo angles as points for each CryId 
////		-Phi_MCTrack + Phi_Calo angles as points for each CryId
////		-Theta vs Phi MCTrack for each CryId
////																			
//// **elisabet.galiana@usc.es													
//// ** Universidad de Santiago de Compostela									
//// ** Dpto. Física de Partículas 												
////////////////////////////////////////////////////////////////////////////////////




//Terminal:
// root -l outsim.root 
// TH2F *h = new TH2F("h","h",130,0,130,500,-0.45,0.45)
// ensartree->Draw("TMath::ATan2(sqrt(MCTrack.fPx*MCTrack.fPx+MCTrack.fPy*MCTrack.fPy),MCTrack.fPz)-CaloHitSim.fTheta:CrystalHitSim.fCrystalId>>h","","colz")
// ensartree->Draw("TMath::ATan2(sqrt(MCTrack.fPx*MCTrack.fPx+MCTrack.fPy*MCTrack.fPy),MCTrack.fPz)-CaloHitSim.fTheta:CrystalHitSim.fCrystalId>>h","MCTrack.fMotherId<0","colz")
//

void Differences_MC_Calo_angles() {
  
  //ROOT ENVIRONMENT
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(0);
  
  //INPUT FILE 
  char inputFile[250] = "outsim.root";                                           
  
  TFile *file1 = TFile::Open(inputFile);
  
  //READING TREE
  TTree* tree = (TTree*)file1->Get("ensartree");
  
  //HISTOGRAMS DEFINITION-----------------------------------------------------------//Change these ranges
  TH2F* h= new TH2F("h","Theta Angle (MCTrack-Calo)", 130,0,130,500,-0.45,0.45);
  TH2F* h2= new TH2F("h2","Phi Angle (MCTrack-Calo)", 130,0,130,1000,-3.14,3.14);
  
  TH2F* h3= new TH2F("h3","Theta_Calo for each CryId", 130,0,130,125,0.,2.5);
  TH2F* h4= new TH2F("h4","Phi_Calo for each CryId", 130,0,130,314,-3.14,3.14);
  
  TH2F* h5= new TH2F("h5","Theta_MCTrack for each CryId", 130,0,130,500,0.,2.5);
  TH2F* h6= new TH2F("h6","Phi_MCTrack for each CryId", 130,0,130,3600,-3.14,3.14);
  
  TH2F* h7= new TH2F("h7","Theta vs Phi MCTrack for each CryId", 1800,0,3.14,3600,-3.14,3.14);//optimum range, each cry covers 1.5º
  
  
  //----   MCTrack (input)   -------------------------------------------------------
  TClonesArray* MCTrackCA;
  EnsarMCTrack** track;
  MCTrackCA = new TClonesArray("EnsarMCTrack",5);
  TBranch *branchMCTrack = tree ->GetBranch("MCTrack");
  branchMCTrack->SetAddress(&MCTrackCA);
  
  //----- HPGe detector--------------//
  
  //HPGe Hits 
  /*TClonesArray* hpgeHitCA;
    EnsarHPGeDetHit** hpgeHit;
    hpgeHitCA = new TClonesArray("EnsarHPGeDetHit",5);
    TBranch *branchEnsarHPGeDetHit = tree ->GetBranch("HPGeDetHit");
    branchEnsarHPGeDetHit->SetAddress(&hpgeHitCA );
    
    //HPGe Points
    TClonesArray* hpgePointCA;
    EnsarHPGeDetPoint** hpgePoint;
    hpgePointCA = new TClonesArray("EnsarHPGeDetPoint",5);
    TBranch *branchEnsarHPGeDetPoint = tree ->GetBranch("HPGeDetPoint");
    branchEnsarHPGeDetPoint->SetAddress(&hpgePointCA );*/
  
  
  //----- CALIFA detector--------------//
  //Crystal Hits  
  TClonesArray* crystalHitCA;  
  R3BCaloCrystalHitSim** crystalHit;
  crystalHitCA = new TClonesArray("R3BCaloCrystalHitSim",5);
  TBranch *branchCrystalHit = tree->GetBranch("CrystalHitSim");
  branchCrystalHit->SetAddress(&crystalHitCA);
  
  //Calo Hits
  TClonesArray* caloHitCA;  
  R3BCaloHitSim** caloHit;
  caloHitCA = new TClonesArray("R3BCaloHitSim",5);
  TBranch *branchCaloHit = tree->GetBranch("CaloHitSim");
  branchCaloHit->SetAddress(&caloHitCA);
  
  
  //Crystal Points
  /*TClonesArray* crystalPointCA;  
    R3BCaloPoint** crystalPoint;
    crystalPointCA = new TClonesArray("R3BCaloPoint",5);
    TBranch *branchcrystalPoint = tree->GetBranch("CrystalPoint");
    branchcrystalPoint->SetAddress(&crystalPointCA);*/

  
  Int_t MCtracksPerEvent = 0;
  //Int_t hpgeHitsPerEvent = 0;
  //Int_t hpgePointsPerEvent = 0;
  Int_t crystalHitsPerEvent = 0;
  Int_t caloHitsPerEvent=0;
  //Int_t crystalPointPerEvent=0;
  
  TVector3 momentum;
  
  
  //TREE ENTRIES--------------------------------------------------------------------
  Long64_t nevents = tree->GetEntries();
  
  
  //LOOP IN THE EVENTS--------------------------------------------------------------
  for(int i=0;i<nevents;i++){
    if(i%1== 100) printf("Event:%i\n",i);
    energyGe = 0.;
    tree->GetEvent(i);
    
    MCtracksPerEvent     = MCTrackCA->GetEntries();
    //hpgeHitsPerEvent     = hpgeHitCA->GetEntries();
    //hpgePointsPerEvent   = hpgePointCA->GetEntries();
    crystalHitsPerEvent  = crystalHitCA->GetEntries();
    caloHitsPerEvent     = caloHitCA->GetEntries();
    //crystalPointPerEvent = crystalPointCA->GetEntries();

    if(MCtracksPerEvent>0) {
      track = new EnsarMCTrack*[MCtracksPerEvent];
      for(Int_t j=0;j<MCtracksPerEvent;j++){
	track[j] = new EnsarMCTrack;
	track[j] = (EnsarMCTrack*) MCTrackCA->At(j);
      }
    }
    /*if(hpgeHitsPerEvent>0) {
      hpgeHit = new EnsarHPGeDetHit*[hpgeHitsPerEvent];
      for(Int_t j=0;j<hpgeHitsPerEvent;j++){
      hpgeHit[j] = new EnsarHPGeDetHit;
      hpgeHit[j] = (EnsarHPGeDetHit*) hpgeHitCA->At(j);
      }
      }
      if(hpgePointsPerEvent>0) {
      hpgePoint = new EnsarHPGeDetPoint*[hpgePointsPerEvent];
      for(Int_t j=0;j<hpgePointsPerEvent;j++){
      hpgePoint[j] = new EnsarHPGeDetPoint;
      hpgePoint[j] = (EnsarHPGeDetPoint*) hpgePointCA->At(j);
      }
      }*/
    if(crystalHitsPerEvent>0) {
      crystalHit = new R3BCaloCrystalHitSim*[crystalHitsPerEvent];
      for(Int_t j=0;j<crystalHitsPerEvent;j++){
	crystalHit[j] = new R3BCaloCrystalHitSim;
	crystalHit[j] = (R3BCaloCrystalHitSim*) crystalHitCA->At(j);      
      }
    }
    if(caloHitsPerEvent>0) {
      caloHit = new R3BCaloHitSim*[caloHitsPerEvent];
      for(Int_t j=0;j<caloHitsPerEvent;j++){
	caloHit[j] = new R3BCaloHitSim;
	caloHit[j] = (R3BCaloHitSim*) caloHitCA->At(j);      
      }
    }
    /*if(crystalPointPerEvent>0) {
      crystalPoint = new R3BCaloPoint*[crystalPointPerEvent];
      for(Int_t j=0;j<crystalPointPerEvent;j++){
      crystalPoint[j] = new R3BCaloPoint;
      crystalPoint[j] = (R3BCaloPoint*) crystalPointCA->At(j);      
      }
      }*/
    
    //LOOP in MC mother tracks----------------------------------------------		
    Double_t Theta_MC=0.;
    Double_t Phi_MC=0.;
    
    for(Int_t h=0;h<MCtracksPerEvent;h++){
      
      if(track[h]->GetMotherId()<0) { //Primary Particle is MotherId=-1
	
	track[h]->GetMomentum(momentum);  
	if (h==0){
	  Theta_MC = momentum.Theta();
	  Phi_MC   = momentum.Phi();
	}
      }
    }     
    
        
    //LOOP in Calo Hits---------------- 
    Double_t Theta_Calo=0.;
    Double_t Phi_Calo=0.;
    
    for(Int_t i=0;i<caloHitsPerEvent;i++){	
      
      if (caloHitsPerEvent==1 && caloHit[i]->GetNbOfCrystalHits()==1){
	
	Theta_Calo=caloHit[i]->GetTheta();
	Phi_Calo=caloHit[i]->GetPhi();
	h7->Fill(Theta_MC,Phi_MC);
	
      }		
    }
    
    //LOOP in Crystal Hits-------------
    Int_t CryId=0.;
    
    for(Int_t j=0;j<crystalHitsPerEvent;j++){
      if(crystalHitsPerEvent==1){
	CryId=crystalHit[j]->GetCrystalId();
	
      }
      
    }
    
    //Calculation of the difference
    Double_t diff=0., diff2=0.;
    
    if(Theta_Calo>0) diff  = Theta_MC - Theta_Calo;
    diff2 = Phi_MC - Phi_Calo;
    
    if(CryId>0 && Theta_Calo>0){
      h->Fill(CryId, diff);
      h2->Fill(CryId, diff2);
      h3->Fill(CryId, Theta_Calo);
      h4->Fill(CryId, Phi_Calo);
      h5->Fill(CryId, Theta_MC);
      h6->Fill(CryId, Phi_MC);
    }
    
    
    if(MCtracksPerEvent)     delete[] track;
    //if(hpgeHitsPerEvent)     delete[] hpgeHit;
    //if(hpgePointsPerEvent)   delete[] hpgePoint;
    if(crystalHitsPerEvent)  delete[] crystalHit;
    if(caloHitsPerEvent)     delete[] caloHit;
    //if(crystalPointPerEvent) delete[] crystalPoint;
    
    
  }
  // END LOOP IN THE EVENTS---------------------------------------------------------
  
  
  
  //FILE 1 CrystalId & Theta,Phi of MCtrack
  ifstream *File1 = new ifstream("/home/fpddv1/elisabet.galiana/Escritorio/ENSARRoot/EnsarRoot_source/ctn/macros/nov16/MCTrack_CryID_Theta_Phi.dat");
  
  const Int_t nLevel=128;
  Double_t CryId[nLevel];
  Double_t Theta_read[nLevel];
  Double_t Phi_read[nLevel];
  Double_t Theta_MCTrack[nLevel];
  Double_t Phi_MCTrack[nLevel];
  
  for(Int_t i=0;i<8;i++){
    File1->ignore(256,'\n');
  }
  
  for(Int_t i = 0; i < nLevel; i++){ 
    *File1 >> CryId[i] >> Theta_read[i] >> Phi_read[i];
    
    //grad->rad
    Theta_MCTrack[i]= (Theta_read[i]*TMath::Pi())/180.;
    Phi_MCTrack[i]= (Phi_read[i]*TMath::Pi())/180.;
    
    cout<<"CryId= "<< CryId[i] <<"\t Theta_MCTrack= "<< Theta_MCTrack[i] <<"\t Phi_MCTrack= "<< Phi_MCTrack[i] << endl;
  }
  
  //FILE 2 CrystalId & Theta,Phi of CaloHit 
  ifstream *File2 = new ifstream("/home/fpddv1/elisabet.galiana/Escritorio/ENSARRoot/EnsarRoot_source/ctn/macros/nov16/Calo_CryID_Theta_Phi.dat");
  
  Double_t CryId2[nLevel];
  Double_t Theta_Calo[nLevel];
  Double_t Phi_Calo[nLevel];
  
  for(Int_t i=0;i<8;i++){
    File2->ignore(256,'\n');
  }
  
  
  for(Int_t i = 0; i < nLevel; i++){ 
    *File2 >> CryId2[i] >> Theta_Calo[i] >> Phi_Calo[i];
    cout<<"CryId2= "<< CryId2[i] <<"\t Theta_Calo= "<< Theta_Calo[i] <<"\t Phi_Calo= "<< Phi_Calo[i] << endl;
  }
  
  //GRAPH
  //MCTrack
  TGraph *gr1 = new TGraph(nLevel,CryId,Theta_MCTrack);
  TGraph *gr2 = new TGraph(nLevel,CryId, Phi_MCTrack);
  
  //Calo
  TGraph *gr3 = new TGraph(nLevel,CryId2,Theta_Calo);
  TGraph *gr4 = new TGraph(nLevel,CryId2, Phi_Calo);
  
  
  // HISTOGRAMS--------------------------------------------------------------------- 
  TLine *line1= new TLine (0,0,130,0);//lines in zero Theta&Phi
  TLine *line2= new TLine (0,0,130,0);
  
  //MCTrack & CaloHit & CryHit----------------------
  TCanvas* c1 = new TCanvas("Theta angle difference","Theta angle difference",0,0,720,900);
  c1->SetFillColor(0);
  c1->SetFrameFillColor(0);  
  h->Draw("colz");
  h->GetXaxis()->SetTitle("CryId");
  h->GetYaxis()->SetTitle("Theta_MC-Theta_Calo (rad)");
  line1->Draw();
  line1->SetLineColor(kRed);
  line1->SetLineWidth(2);
  
  TCanvas* c2 = new TCanvas("Phi angle difference","Phi angle difference",0,0,720,900);
  c2->SetFillColor(0);
  c2->SetFrameFillColor(0);  
  h2->Draw("colz");
  h2->GetXaxis()->SetTitle("CryId");
  h2->GetYaxis()->SetTitle("Phi_MC-Phi_Calo (rad)");
  line2->Draw();
  line2->SetLineColor(kRed);
  line2->SetLineWidth(2);
  
  //CaloHit & CryHit   and   MCTrack & CryHit----------
  TCanvas* c3 = new TCanvas("Theta angle for each CrystalId","Theta angle for each CrystalId",0,0,720,900);
  c3->SetFillColor(0);
  c3->SetFrameFillColor(0);  
  c3->Divide(2,1);
	
  c3->cd(1);
  h3->Draw("colz");
  h3->SetMarkerColor(kOrange);
  h3->GetXaxis()->SetTitle("CryId");
  h3->GetYaxis()->SetTitle("Theta_Calo (rad)");
  //gr1->SetMarkerStyle(20);
  //gr1->SetMarkerColor(4);
  //gr1->Draw("Psame");
  
  c3->cd(2);
  h5->Draw("colz");
  h5->SetMarkerColor(kViolet);
  h5->GetXaxis()->SetTitle("CryId");
  h5->GetYaxis()->SetTitle("Theta_MCTrack (rad)");
  
  
  //-----------------------
  TCanvas* c4 = new TCanvas("Phi angle for each CrystalId","Phi angle for each CrystalId",0,0,720,900);
  c4->SetFillColor(0);
  c4->SetFrameFillColor(0); 
  c4->Divide(2,1);
  
  c4->cd(1); 
  h4->Draw("colz");
  h4->SetMarkerColor(kOrange);
  h4->GetXaxis()->SetTitle("CryId");
  h4->GetYaxis()->SetTitle("Phi_Calo (rad)");
  //gr2->SetMarkerStyle(20);
  //gr2->SetMarkerColor(4);
  //gr2->Draw("Psame*");
  c4->cd(2); 
  h6->Draw("colz");
  h6->SetMarkerColor(kViolet);
  h6->GetXaxis()->SetTitle("CryId");
  h6->GetYaxis()->SetTitle("Phi_MCTrack (rad)");
  
  
  
  /*
  //------------------------
  TCanvas* c5 = new TCanvas("Theta_Calo & MCTrack_Points for each CrystalId","Theta_Calo & MCTrack_Points for each CrystalId",0,0,720,900);
  c5->SetFillColor(0);
  c5->SetFrameFillColor(0);  
  h3->Draw("colz");
  //h3->SetMarkerColor(kOrange);
  h3->GetXaxis()->SetTitle("CryId");
  h3->GetYaxis()->SetTitle("Theta_Calo (rad)");
  gr1->SetMarkerStyle(3);
  gr1->SetMarkerColor(4);
  gr1->Draw("Psame");
  //////////////////////////////////
  TLegend *leg1 = new TLegend(0.5,0.7,0.8,0.8);
  leg1->AddEntry(gr1, "Theta point MCTrack", "p");
  leg1->SetFillColor(0);
  leg1->Draw();
  //////////////////////////////////////////////////
  
  //------------------------
  TCanvas* c6 = new TCanvas("Phi_Calo & MCTrack_Points for each CrystalId","Phi_Calo & MCTrack_Points for each CrystalId",0,0,720,900);
  c6->SetFillColor(0);
  c6->SetFrameFillColor(0); 
  h4->Draw("colz");
  h4->SetMarkerColor(kCyan);
  h4->GetXaxis()->SetTitle("CryId");
  h4->GetYaxis()->SetTitle("Phi_Calo (rad)");
  gr2->SetMarkerStyle(3);
  gr2->SetMarkerColor(4);
  gr2->Draw("Psame");
  //////////////////////////////////
  TLegend *leg2 = new TLegend(0.5,0.7,0.8,0.8);
  leg2->AddEntry(gr2, "Phi point MCTrack", "P");
  leg2->SetFillColor(0);
  leg2->Draw();
  //////////////////////////////////////////////////
  */
  
	
  //------------------------
  TCanvas* c7 = new TCanvas("Theta_MCtrack & Calo_Points for each CrystalId","Theta_MCtrack & Calo_Points for each CrystalId",0,0,720,900);
  c7->SetFillColor(0);
  c7->SetFrameFillColor(0);  
  h5->Draw("colz");
  h5->GetXaxis()->SetTitle("CryId");
  h5->GetYaxis()->SetTitle("Theta_Calo (rad)");
  gr3->SetMarkerStyle(22);
  gr3->SetMarkerColor(kRed);
  gr3->Draw("Psame");
  //////////////////////////////////
  TLegend *leg3 = new TLegend(0.5,0.7,0.8,0.8);
  leg3->AddEntry(gr3, "Theta point of CaloHit", "p");
  leg3->SetFillColor(0);
  leg3->Draw();
  //////////////////////////////////////////////////
  
  //------------------------
  TCanvas* c8 = new TCanvas("Phi_MCtrack & Calo_Points for each CrystalId","Phi_MCtrack & Calo_Points for each CrystalId",0,0,720,900);
  c8->SetFillColor(0);
  c8->SetFrameFillColor(0);  
  h6->Draw("colz");
  h6->GetXaxis()->SetTitle("CryId");
  h6->GetYaxis()->SetTitle("Phi_Calo (rad)");
  gr4->SetMarkerStyle(22);
  gr4->SetMarkerColor(kRed);
  gr4->Draw("Psame");
  //////////////////////////////////
  TLegend *leg4 = new TLegend(0.2,0.7,0.5,0.8);
  leg4->AddEntry(gr4, "Phi point of CaloHit", "p");
  leg4->SetFillColor(0);
  leg4->Draw();
  //////////////////////////////////////////////////
  
  //------------------------
  TCanvas* c9 = new TCanvas("Theta vs Phi MCtrack","Theta vs Phi MCtrack",0,0,720,900);
  c9->SetFillColor(0);
  c9->SetFrameFillColor(0);  
  h7->Draw("colz");
}

