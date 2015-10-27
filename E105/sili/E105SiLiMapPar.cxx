#include <iostream>
#include "E105SiLiMapPar.h"
#include "FairParamList.h"


using namespace std;

// ------   Constructor   --------------------------------------------------
E105SiLiMapPar::E105SiLiMapPar(const char* name, const char* title,
                       const char* context)
  : FairParGenericSet(name, title, context),
    fType(-1),
    fXmin(0),
    fXmax(0),
    fYmin(0),
    fYmax(0),
    fZmin(0),
    fZmax(0),
    fMapName(TString("")),
    fPosX(0),
    fPosY(0),
    fPosZ(0),
    fScale(0)
{
}
// -------------------------------------------------------------------------

E105SiLiMapPar::E105SiLiMapPar()
  :fType(-1),
   fXmin(0),
   fXmax(0),
   fYmin(0),
   fYmax(0),
   fZmin(0),
   fZmax(0),
   fMapName(TString("")),
   fPosX(0),
   fPosY(0),
   fPosZ(0),
   fScale(0)
{

}
// -------------------------------------------------------------------------

// ------   Destructor   ---------------------------------------------------
E105SiLiMapPar::~E105SiLiMapPar() { }
// -------------------------------------------------------------------------



ClassImp(E105SiLiMapPar)

