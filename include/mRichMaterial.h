#ifndef mRichMaterial_H
#define mRichDetectorConstruction_H 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

//------------------------------------------------------------------//
extern G4Material* Water;
extern G4Material* Aluminum;
extern G4Material* Air;
extern G4Material* Acrylic;
extern G4Material* NBK7;            //Borosilicate glass from SCHOTT
extern G4Material* Borosilicate;    //Pyrex_Glass 

extern G4Material* Air_Opt;
enum {nEntries_Air_Opt=2};

extern G4Material* Aerogel1;        //Hubert aerogel, n=1.025
enum {nEntries1=32};                //will be used in multiple places

extern G4Material* Aerogel2;        //Marco aerogel, n=1.03
enum {nEntries2=50};

//------------------------------------------------------------------//
void SetMaterial();
void SetAir();
void SetAir_Opt();
void SetNBK7_SCHOTT();
void SetAcrylic();
void SetAerogel1();
void SetAerogel2();
void SetBorosilicate();

G4double n_NBK7_SCHOTT(G4double E);

#endif
