//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
// Renamed file names and made changes for the 2nd mRICH prototype

#ifndef mRichDetectorConstruction_h
#define mRichDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Polyhedra.hh"

#include "mRichParameters.h"

class BOX
{
private:
  G4Box* box;
  G4LogicalVolume* log;
  G4VPhysicalVolume* phys;

public:
  BOX(BoxParameters boxPar, G4LogicalVolume* motherLV);
  ~BOX();
  G4VPhysicalVolume* GetPhysicalVolume() {return phys;}
  G4LogicalVolume* GetLogicalVolume() {return log;}
};
//------------------------------------------------------------------------//
class POLYHEDRA
{
private:
  G4Polyhedra* polyhedra;
  G4LogicalVolume* log;
  G4VPhysicalVolume* phys;

public:
  POLYHEDRA(PolyhedraParameters par, G4LogicalVolume* motherLV);
  ~POLYHEDRA();
  G4VPhysicalVolume* GetPhysicalVolume() {return phys;}
  G4LogicalVolume* GetLogicalVolume() {return log;}
};
//------------------------------------------------------------------------//
class mRichDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  mRichDetectorConstruction();
  //mRichDetectorConstruction(G4double);
  ~mRichDetectorConstruction();
  
public:
  G4VPhysicalVolume* Construct();
  void build_expHall();
  void build_holderBox();
  void build_foamHolder();
  void build_aerogel();
  void build_SensorPlane();
  void build_readout();
  void build_mirror();
  void build_planoLens();

private:
  BOX* expHall;
  BOX* holderBox;          //holderBox is unneccessery to be predefine here
  BOX* hollowVolume;
  BOX* aerogel;
};


#endif /*mRichDetectorConstruction_h*/
