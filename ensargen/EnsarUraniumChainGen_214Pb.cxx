// *********************************************************************
// *****   
// *****             EnsarUraniumChainGen_214Pb source file                                   
// *****   							
// *********************************************************************

#include "EnsarUraniumChainGen_214Pb.h"

#include "FairPrimaryGenerator.h"

#include "TRandom.h"
#include "TParticlePDG.h"
#include "TDatabasePDG.h"
#include "TMath.h"
#include "TArrayF.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#define fPDGBetaType 11
#define fPDGType 22

using namespace std;


// -----   Default constructor   ------------------------------------------
EnsarUraniumChainGen_214Pb::EnsarUraniumChainGen_214Pb()  :
  FairGenerator(),
	fPointVtxIsSet(0), fBoxVtxIsSet(0),
  fThetaRangeIsSet(0), fPhiRangeIsSet(0),
	fX(0), fY(0), fZ(0),
	fX1(0), fY1(0), fZ1(0), fX2(0), fY2(0), fZ2(0),
	fThetaMin(0), fThetaMax(0),
	fPhiMin(0), fPhiMax(0)
{
}
// ------------------------------------------------------------------------


// -----   Standard constructor   -----------------------------------------
EnsarUraniumChainGen_214Pb::EnsarUraniumChainGen_214Pb(const char* inputFile) :
  FairGenerator(),
	fPointVtxIsSet(0), fBoxVtxIsSet(0),
  fThetaRangeIsSet(0), fPhiRangeIsSet(0),
	fX(0), fY(0), fZ(0),
	fX1(0), fY1(0), fZ1(0), fX2(0), fY2(0), fZ2(0),
	fThetaMin(0), fThetaMax(0),
	fPhiMin(0), fPhiMax(0)
{
  
  cout << "-I- EnsarUraniumChainGen_214Pb: Opening input file " << inputFile << endl;
  fFileName  = inputFile;
  
  fInputFile = new ifstream(fFileName);
  if ( ! fInputFile->is_open() ) Fatal("EnsarUraniumChainGen_214Pb","Cannot open input file.");
   
  //Read Parameters File
  ReadParameters();
}
// ------------------------------------------------------------------------


// -----   Inizialize generator   -----------------------------------------
Bool_t  EnsarUraniumChainGen_214Pb::Init()
{
		
	if (fPointVtxIsSet && fBoxVtxIsSet) {
    Fatal("Init()","EnsarUraniumChainGen_214Pb: Cannot set point and box vertices simultaneously");
  }
	
}
// ------------------------------------------------------------------------


// -----   Destructor   ---------------------------------------------------
EnsarUraniumChainGen_214Pb::~EnsarUraniumChainGen_214Pb() {

  CloseInput();

}
// ------------------------------------------------------------------------

// -----   Read events   --------------------------------------------------
Bool_t EnsarUraniumChainGen_214Pb::ReadEvent(FairPrimaryGenerator* primGen)
{
  
  
  //----- Check for input file -----
  if ( ! fInputFile->is_open() ) {
    cout << "-E- EnsarUraniumChainGen_214Pb: Input file not open!" << endl;
    return kFALSE;
  }
 
	
	
	if (fBoxVtxIsSet) {
      fX = gRandom->Uniform(fX1,fX2);
      fY = gRandom->Uniform(fY1,fY2);
			fZ = gRandom->Uniform(fZ1,fZ2);
	}

	Int_t numInicialCases=5;

	Double_t Probability_emmittedParticles [numInicialCases];
	Probability_emmittedParticles [0]=0.11;
	Probability_emmittedParticles [1]=0.402;
	Probability_emmittedParticles [2]=0.459;
	Probability_emmittedParticles [3]=0.0104;
	Probability_emmittedParticles [4]=0.0275;
	

	Double_t FinalState_daughter [numInicialCases];//final state of 214Pb*
	FinalState_daughter [0]=0;
	FinalState_daughter [1]=4;
	FinalState_daughter [2]=5;
	FinalState_daughter [3]=7;
	FinalState_daughter [4]=9;
	
			
	Double_t limits[numInicialCases+1];
	limits[0]=0;

	for (Int_t i=1;i<numInicialCases+1;i++){
		Double_t lim1, prob1;
		lim1=limits[i-1];
		prob1=Probability_emmittedParticles[i-1];
		limits[i]= lim1+ prob1;
		//cout<<"limits["<<i<<"]"<<limits[i]<<endl;//ok!
	}

	Float_t ran_ini =gRandom->Rndm();
	//cout<<"ran_ini="<<ran_ini<<endl;
	Int_t j=0;
	Int_t Case;
	int finalstate;

	if (ran_ini>limits[j] && ran_ini<limits[j+1]){
			Case=0;
	}
	else if (ran_ini>limits[j+1] && ran_ini<limits[j+2]){
			Case=1;		
	}
	else if (ran_ini>limits[j+2] && ran_ini<limits[j+3]){
			Case=2;		
	}
	else if (ran_ini>limits[j+3] && ran_ini<limits[j+4]){
			Case=3;			
	}
	else if (ran_ini>limits[j+4] && ran_ini<limits[j+5]){
			Case=4;			
	}


	finalstate=FinalState_daughter[Case];
	
	Bool_t kINFO;
	kINFO=false;
	if (kINFO==true){cout<<"Case="<<Case<<"  the nucleus is in the state="<<finalstate<<endl;}
	

	Int_t Contador=1;

	while(finalstate>0){
		
		int finalstate2;
		Int_t size=0;
		TArrayF* Energy_gammas_array;
		Energy_gammas_array=new TArrayF();
		Double_t px,py,pz;
		px=0; py=0; pz=0;

		Energy_gammas_array=Deexcitation(finalstate,finalstate2);
		TrackMomentum(Energy_gammas_array->GetAt(0), px, py, pz);
		primGen->AddTrack(fPDGType, px, py, pz, fX, fY, fZ);		
				
		if (kINFO==true){
			cout<<endl<<"Counter of gammas="<<Contador<<endl;
			cout<<"		Energy_array size="<<Energy_gammas_array->GetSize()<<endl;
			cout<<"		Energy_gamma="<<Energy_gammas_array->GetAt(0)<<endl;
			cout<<"		Final state="<<finalstate2<<endl;
			cout<<"		Ading gamma of energy="<<Energy_gammas_array->GetAt(0)<<" p="<<px<<","<<py<<","<<pz<<endl;
		}

		finalstate=finalstate2;
		Contador++;
	}

	primGen->AddTrack(fPDGType, 0.0000001, 0.0000001, 0.0000001, 0., 0., 0.);
	if (kINFO==true){cout<<"////////////////////////////////////////////////"<<endl<<endl<<endl;}
	
  return kTRUE;
  
}
// ------------------------------------------------------------------------

// -----   Private method CloseInput   ------------------------------------
void EnsarUraniumChainGen_214Pb::CloseInput() {
  if ( fInputFile ) {
    if ( fInputFile->is_open() ) {
      cout << "-I- EnsarUraniumChainGen_214Pb: Closing input file " 
	   << fFileName << endl;
      fInputFile->close();
    }
    delete fInputFile;
    fInputFile = NULL;
  }
}
// ------------------------------------------------------------------------


// ---Read Parameters File --------------------------------------------
void EnsarUraniumChainGen_214Pb::ReadParameters() {

}

// --- De-excitation Process --------------------------------------------
TArrayF* EnsarUraniumChainGen_214Pb::Deexcitation(Int_t InicialState, Int_t & FinalState) {
	
	// --- NUCLEAR DATA, deexcitation of 214Pb --- //
	Double_t Probability	[150][150];//[Nucleus inicial state][number of gammas]
	Double_t Energygammas	[150][150];
	Int_t 	 NucleusFinalState		[150][150];


	//1 excited state
	Probability					[1][1]=1.;
	Energygammas				[1][1]=0.0000532284;
	NucleusFinalState		[1][1]=0;

	//2 excited state (empty at NNDC, we filled it)
	Probability					[2][1]=1.;
	Energygammas				[2][1]=0.00006269;
	NucleusFinalState		[2][1]=0;

	//3 excited state
	Probability					[3][1]=0.109;
	Energygammas				[3][1]=0.00019619;
	NucleusFinalState		[3][1]=2;

	Probability					[3][2]=0.0188;
	Energygammas				[3][2]=0.00020568;
	NucleusFinalState		[3][2]=1;

	Probability					[3][3]=0.8722;
	Energygammas				[3][3]=0.00025886;
	NucleusFinalState		[3][3]=0;

	//4 excited state
	Probability					[4][1]=0.2824;
	Energygammas				[4][1]=0.000241995;
	NucleusFinalState		[4][1]=1;

	Probability					[4][2]=0.7176;
	Energygammas				[4][2]=0.0002952228;
	NucleusFinalState		[4][2]=0;

	//5 excited state
	Probability					[5][1]=0.0007;
	Energygammas				[5][1]=0.00029876;
	NucleusFinalState		[5][1]=1;

	Probability					[5][2]=0.9993;
	Energygammas				[5][2]=0.0003519321;
	NucleusFinalState		[5][2]=0;
	
	//6 excited state
	Probability					[6][1]=0.7299;
	Energygammas				[6][1]=0.00031433;
	NucleusFinalState		[6][1]=2;//2

	Probability					[6][2]=0.2701;
	Energygammas				[6][2]=0.00032384;
	NucleusFinalState		[6][2]=1;

	//7 excited state
	Probability					[7][1]=0.0012;
	Energygammas				[7][1]=0.0001815;
	NucleusFinalState		[7][1]=5;

	Probability					[7][2]=0.0179;
	Energygammas				[7][2]=0.0002384;
	NucleusFinalState		[7][2]=4;

	Probability					[7][3]=0.3986;
	Energygammas				[7][3]=0.0002748;
	NucleusFinalState		[7][3]=3;

	Probability					[7][4]=0.3786;
	Energygammas				[7][4]=0.000480432;
	NucleusFinalState		[7][4]=1;

	Probability					[7][5]=0.2037;
	Energygammas				[7][5]=0.00053366;
	NucleusFinalState		[7][5]=0;

	//9 excited state
	Probability					[9][1]=0.0113;
	Energygammas				[9][1]=0.00030526;
	NucleusFinalState		[9][1]=7;

	Probability					[9][2]=0.0775;
	Energygammas				[9][2]=0.00046202;
	NucleusFinalState		[9][2]=6;

	Probability					[9][3]=0.1577;
	Energygammas				[9][3]=0.00048714;
	NucleusFinalState		[9][3]=5;

	Probability					[9][4]=0.016;
	Energygammas				[9][4]=0.00054383;
	NucleusFinalState		[9][4]=4;

	Probability					[9][5]=0.1351;
	Energygammas				[9][5]=0.00058014;
	NucleusFinalState		[9][5]=3;

	Probability					[9][6]=0.3894;
	Energygammas				[9][6]=0.00078596;
	NucleusFinalState		[9][6]=1;

	Probability					[9][7]=0.213;
	Energygammas				[9][7]=0.00083907;
	NucleusFinalState		[9][7]=0;

	Int_t numGammas;
	Float_t random =gRandom->Rndm();

	if (InicialState==1 || InicialState==2){numGammas=1;}
	else if(InicialState==3 ){numGammas=3;}
	else if(InicialState==4 || InicialState==5 || InicialState==6){numGammas=2;}
	else if(InicialState==7 ){numGammas=5;}
	else if(InicialState==9 ){numGammas=7;}
	else{
		cout << "-E- EnsarUraniumChainGen_226Ra: Incorrect final state!" << endl;
	}
	
	//cout<<"		Entering into the Deexcitation function with an Inicial state="<<InicialState<<" which has a numGamma="<<numGammas<<endl;	

	TArrayF* EnergyGamma_array;
	EnergyGamma_array= new TArrayF();
	EnergyGamma_array->Set(1);

	//Limits calculus
	Double_t limits2[numGammas+1];
	limits2[0]=0;

	for (Int_t i=1;i<numGammas+1;i++){
		limits2[i]= limits2[i-1] + Probability[InicialState][i];
		//cout<<"		limits2["<<i<<"]"<<limits2[i]<<endl;
	}
	
	for (Int_t i=0;i<numGammas;i++){
		if (random>limits2[i] && random<limits2[i+1]){
				//cout<<"		Inside loop: "<<random<<" exists between "<<limits2[i]<<" and "<<limits2[i+1]<<endl;
				//cout<<"		Inside loop: the Gamma emmited is the "<<i+1<<endl;
				EnergyGamma_array->SetAt(Energygammas[InicialState][i+1],0);
				FinalState=NucleusFinalState[InicialState][i+1];
				//cout<<"		Inside loop: FinalState="<<NucleusFinalState[InicialState][i+1]<<endl;
		}
	}
	
	return EnergyGamma_array;
}

// --- Track Momentum Calculus --------------------------------------------
void EnsarUraniumChainGen_214Pb::TrackMomentum( Double_t Energy, Double_t & Px, Double_t & Py, Double_t & Pz ) {

	//Angles
	Double_t phi;		//0-2pi
	Double_t theta;	//0-pi
									//Remember: we always consider the CosTheta
									//if not it will be: theta = gRandom->Uniform(fThetaMin,fThetaMax) * TMath::DegToRad();

	if (fThetaRangeIsSet==kTRUE){
		theta = acos(gRandom->Uniform(cos(fThetaMin* TMath::DegToRad()),
                                      cos(fThetaMax* TMath::DegToRad())));
	}else { theta = TMath::ACos(1-2*gRandom->Rndm());}

	if (fPhiRangeIsSet==kTRUE){
		phi = gRandom->Uniform(fPhiMin,fPhiMax) * TMath::DegToRad();
	}else{ phi = 6.283185307  *gRandom->Rndm();}
		
	//cout<<"theta2="<<theta*180/TMath::Pi()<<"  phi2="<<phi*180/TMath::Pi()<<endl;

  //Direction of gamma RS Lab
  TVector3 direction;  
  direction = TVector3(TMath::Sin(theta)*TMath::Cos(phi),
			TMath::Sin(theta)*TMath::Sin(phi),
			TMath::Cos(theta));	

	//Momentum
	Px= Energy*direction.X();
  Py= Energy*direction.Y();
  Pz= Energy*direction.Z(); 
	
	//cout<<"TrackMomentum function  Px="<<Px<<"  Py="<<Py<<"  Pz="<<Pz<<endl; 
}
//-------------------------------------------------------------------------

ClassImp(EnsarUraniumChainGen_214Pb)