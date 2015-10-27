// ----------------------------------------------------------------------
// -----          EnsarBoxGenerator header file                     -----
// -----         Created 03/10/13  by P.Cabanelas                   -----
// ----------------------------------------------------------------------

/**  EnsarBoxGenerator.h
 *@author Pablo Cabanelas <pablo.cabanelas@usc.es>
 *
 * The EnsarBoxGenerator generates particles within given range
 * over pt, phi, eta, theta/cos(theta) with a fixed multiplicity per event.
 * Lorentz boost can be set also.
 * Derived from FairGenerator.
**/

#ifndef ENSAR_BOXGENERATOR_H
#define ENSAR_BOXGENERATOR_H

#include "FairGenerator.h"

#include <iostream>

class FairPrimaryGenerator;

class EnsarBoxGenerator : public FairGenerator
{
  public:

    /** Default constructor. **/
    EnsarBoxGenerator();

    /** Constructor with PDG-ID, multiplicity
     **@param pdgid Particle type (PDG encoding)
     **@param mult  Multiplicity (default is 1)
     **/
    EnsarBoxGenerator(Int_t pdgid, Int_t mult=1);

    /** Destructor **/
    virtual ~EnsarBoxGenerator() {};

    /** Modifiers **/
    void SetPDGType      (Int_t pdg)  {fPDGType = pdg;  };

    void SetMultiplicity (Int_t mult) {fMult    = mult; };

    void SetPRange(Double32_t pmin=0   , Double32_t pmax=10)
    {fPMin=pmin; fPMax=pmax; fPRangeIsSet=kTRUE;}

    void SetPtRange      (Double32_t ptmin=0   , Double32_t ptmax=10)
    {fPtMin=ptmin; fPtMax=ptmax; fPtRangeIsSet=kTRUE;};

    void SetPhiRange     (Double32_t phimin=0  , Double32_t phimax=360)
    {fPhiMin=phimin; fPhiMax=phimax;};

    void SetEtaRange     (Double32_t etamin=-5 , Double32_t etamax=7)
    {fEtaMin=etamin; fEtaMax=etamax; fEtaRangeIsSet=kTRUE;};

    void SetYRange       (Double32_t ymin=-5   , Double32_t ymax=7)
    {fYMin=ymin; fYMax=ymax; fYRangeIsSet=kTRUE;};

    void SetThetaRange   (Double32_t thetamin=0, Double32_t thetamax=90)
    {fThetaMin=thetamin; fThetaMax=thetamax; fThetaRangeIsSet=kTRUE;};

    void SetCosTheta   ()
    {fCosThetaIsSet=kTRUE;};

    //Set velocity for the Lorentz boost
    void SetBeta(Double32_t beta=0) { fBeta = beta; };
    void SetRandomBeta(Double32_t betamax=0, Double32_t betamin=0) {
      fRandomBeta = kTRUE;
      fBetaMax = betamax;
      fBetaMin = betamin;
    };


    void SetXYZ   (Double32_t x=0, Double32_t y=0, Double32_t z=0) {
      fX=x;
      fY=y;
      fZ=z;
      fPointVtxIsSet=kTRUE;
    }

    void SetBoxXYZ (Double32_t x1=0, Double32_t y1=0, Double32_t x2=0, Double32_t y2=0, Double32_t z=0) {
      fX1=x1;
      fY1=y1;
      fX2=x2;
      fY2=y2;
      fZ=z;
      fBoxVtxIsSet=kTRUE;
    }

    void SetDebug(Bool_t debug=0) {fDebug = debug;}

    /** Initializer **/
    Bool_t Init();

    /** Creates an event with given type and multiplicity.
     **@param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

  private:
    Int_t      fPDGType;             // Particle type (PDG encoding)
    Int_t      fMult;                // Multiplicity

    Double32_t fPDGMass;             // Particle mass [GeV]
    Double32_t fPtMin,  fPtMax;      // Transverse momentum range [GeV]
    Double32_t fPhiMin, fPhiMax;     // Azimuth angle range [degree]
    Double32_t fEtaMin, fEtaMax;     // Pseudorapidity range in lab system
    Double32_t fYMin,   fYMax;       // Rapidity range in lab system
    Double32_t fPMin,   fPMax;       // Momentum range in lab system
    Double32_t fThetaMin, fThetaMax; // Polar angle range in lab system [degree]
    Double32_t fX, fY, fZ;           // Point vertex coordinates [cm]
    Double32_t fX1, fY1, fX2, fY2;   // Box vertex coords (x1,y1)->(x2,y2)
    Double32_t fBeta;                // Particle velocity
    Double32_t fBetaMax, fBetaMin;   // Particle velocity range

    Bool_t     fEtaRangeIsSet;       // True if eta range is set
    Bool_t     fYRangeIsSet;         // True if rapidity range is set
    Bool_t     fThetaRangeIsSet;     // True if theta range is set
    Bool_t     fCosThetaIsSet;       // True if uniform distribution in
    //cos(theta) is set (default -> not set)
    Bool_t     fPtRangeIsSet;        // True if transverse momentum range is set
    Bool_t     fPRangeIsSet;         // True if abs.momentum range is set
    Bool_t     fPointVtxIsSet;       // True if point vertex is set
    Bool_t     fBoxVtxIsSet;         // True if box vertex is set
    Bool_t     fDebug;               // Debug switch
    Bool_t     fRandomBeta;          // True if a random distribution in beta is used

    ClassDef(EnsarBoxGenerator,1);

};


#endif
