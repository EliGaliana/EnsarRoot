// -------------------------------------------------------------------------
// -----                        R3BNeuLand header file                     -----
// -----                  Created 26/03/09  by D.Bertini               -----
// -------------------------------------------------------------------------

/**  R3BNeuLandv1.h
 **/


#ifndef R3BNEULANDV1_H
#define R3BNEULANDV1_H

#include "R3BDetector.h"
#include "TLorentzVector.h"
#include <iostream>
#include <map>
#include <TGeoMedium.h>

using namespace std;

class TClonesArray;
class R3BNeuLandPoint;
class FairVolume;



class R3BNeuLandv1 : public R3BDetector
{
  
 public:
  
  /** Default constructor **/
  R3BNeuLandv1();
  
  
  /** Standard constructor.
   *@param name    detetcor name
   *@param active  sensitivity flag
   **/
  R3BNeuLandv1(const char* name, Bool_t active);
  
  
  /** Destructor **/
  virtual ~R3BNeuLandv1();
  
  
  /** Virtual method ProcessHits
   **
   ** Defines the action to be taken when a step is inside the
   ** active volume. Creates a R3BNeuNeuLandv1Point and adds it to the
   ** collection.
   *@param vol  Pointer to the active volume
   **/
  virtual Bool_t ProcessHits(FairVolume* vol = 0);
  
  
  /** Virtual method BeginEvent
   **
   ** If verbosity level is set, print hit collection at the
   ** end of the event and resets it afterwards.
   **/
  
  virtual void BeginEvent();
  
  /** Virtual method EndOfEvent
   **
   ** If verbosity level is set, print hit collection at the
   ** end of the event and resets it afterwards.
   **/
  
  virtual void EndOfEvent();
  
  
  
  /** Virtual method Register
   **
   ** Registers the hit collection in the ROOT manager.
   **/
  virtual void Register();
  
  
  /** Accessor to the hit collection **/
  virtual TClonesArray* GetCollection(Int_t iColl) const;
  
  
  /** Virtual method Print
   **
   ** Screen output of hit collection.
   **/
  virtual void Print() const;
  
  
  /** Virtual method Reset
   **
   ** Clears the hit collection
   **/
  virtual void Reset();
  
  
  /** Virtual method CopyClones
   **
   ** Copies the hit collection with a given track index offset
   *@param cl1     Origin
   *@param cl2     Target
   *@param offset  Index offset
   **/
  virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2,
			  Int_t offset);
  
  
  /** Virtaul method Construct geometry
   **
   ** Constructs the RPC geometry
   **/
  virtual void ConstructGeometry();
  virtual void ConstructGeometry1();
  virtual void Initialize();
  virtual void SetSpecialPhysicsCuts(){;}
  void SetGeomVersion(Int_t vers ) { fVersion = vers; }
  
  //  void SaveGeoParams();
  
 private:
  
  /** Track information to be stored until the track leaves the
      active volume. **/
  Int_t          fEventID;           //!  track index
  Int_t          fTrackID;           //!  track index
  Int_t          fMot0TrackID;       //!  0th mother track index
  Int_t          fDetID;             //!  detector id
  Int_t          fCellID;            //!  detector cell id
  Int_t          fSegID;            //!  detector cell id
  Int_t          fCellHits;          //!  number of hits in the cells in an event
  Double_t       fTotalEloss;        //!  total energy loss in the cells in an event
  Double_t       fMass;              //!  mass
  TLorentzVector fPosIn, fPosOut;    //!  position
  TLorentzVector fMomIn, fMomOut;    //!  momentum
  Double32_t     fTime;              //!  time
  Double32_t     fLength;            //!  length
  Double32_t     fELoss;             //!  energy loss
  
  Int_t          fPosIndex;          //!
  TClonesArray*  fLandv1Collection;    //!  The hit collection
  Bool_t         kGeoSaved;          //!
  TList *flGeoPar;                   //!
  Int_t fVersion;                    //! geometry version
  
  
  /** Private method AddHit
   **
   ** Adds a NeuLandv1Point to the HitCollection
   **/
  R3BNeuLandPoint* AddHit(Int_t eventID, Int_t trackID,
			  Int_t mot0trackID,
			  Int_t detID, Int_t cellID, Int_t segID,
			  Double_t mass,
			  TVector3 posIn,
			  TVector3 pos_out, TVector3 momIn,
			  TVector3 momOut, Double_t time,
			  Double_t length, Double_t eLoss);
  
  
  /** Private method ResetParameters
   **
   ** Resets the private members for the track parameters
   **/
  void ResetParameters();
  
  /** Map of MCis with fixed VolID */
  map <Int_t,Int_t> fMapMcId;                                        //!

  Int_t fIDMedGas;                                                   //!

  TGeoMedium* pMedAir;                                               //!
  TGeoMedium* pMedSteel;                                             //!
  TGeoMedium* pMedGlass;                                             //!
  TGeoMedium* pMedBak;                                               //!
  TGeoMedium* pMedGas;                                               //!
  TGeoMedium* pMedGasInactive;                                       //!
  TGeoMedium* pMedAl;                                                //!
    
  
  Int_t cellid1, cellid2, cellid3, cellid4, cellid5, cellid6;        //!
  Int_t secondaries;                                                 //!
  Int_t cp1, cp2;                                                    //!
  Int_t volId1, volId2;                                              //!

  Int_t ent_part, exit_part;                                         //!
  
  ClassDef(R3BNeuLandv1,1);
  
};


inline void R3BNeuLandv1::ResetParameters() {
  fEventID = fTrackID = fDetID = fCellID = fSegID = -1;
  fMot0TrackID = -1;
  fPosIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fPosOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomIn.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fMomOut.SetXYZM(0.0, 0.0, 0.0, 0.0);
  fTime = fLength = fELoss = fMass = 0;
  fPosIndex = 0;
};

#endif 
