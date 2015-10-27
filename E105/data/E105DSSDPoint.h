#ifndef PNDDSSDDETECTORPOINT_H
#define PNDDSSDDETECTORPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class E105DSSDPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    E105DSSDPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    E105DSSDPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                          TVector3 posOut, TVector3 momOut, Double_t tof, Double_t length, Double_t eLoss);

    /** Destructor **/
    virtual ~E105DSSDPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    /** Accessors **/
    Double_t GetXIn()   const { return fX; }
    Double_t GetYIn()   const { return fY; }
    Double_t GetZIn()   const { return fZ; }
    Double_t GetXOut()  const { return fX_out; }
    Double_t GetYOut()  const { return fY_out; }
    Double_t GetZOut()  const { return fZ_out; }
    Double_t GetPxOut() const { return fPx_out; }
    Double_t GetPyOut() const { return fPy_out; }
    Double_t GetPzOut() const { return fPz_out; }
    Double_t GetPxIn()  const { return fPx; }
    Double_t GetPyIn()  const { return fPy; }
    Double_t GetPzIn()  const { return fPz; }

    void PositionOut(TVector3& pos) const {pos.SetXYZ(fX_out, fY_out, fZ_out);}
    void MomentumOut(TVector3& mom) const {mom.SetXYZ(fPx_out, fPy_out, fPz_out);}

  private:

    Double32_t fX_out;
    Double32_t fY_out;
    Double32_t fZ_out;
    Double32_t fPx_out;
    Double32_t fPy_out;
    Double32_t fPz_out;


    /** Copy constructor **/
    E105DSSDPoint(const E105DSSDPoint&);
    E105DSSDPoint operator=(const E105DSSDPoint&);

    ClassDef(E105DSSDPoint,2)

};

#endif
