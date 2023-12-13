#ifndef mRichParameters_H
#define mRichParameters_H 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4Colour.hh"

const double myPI=4*atan(1);
//----------------------The Experimental Hall ------------------------------//
const G4double expHall_halfXYZ[3]  = {150.0*mm, 150.0*mm, 150.0*mm};
const G4ThreeVector expHall_posXYZ = G4ThreeVector();

//--------------------Optical Holder Box Key Parameters-----------------------------//
// const G4double inch_to_mm               = 25.4*mm // 1" = 25.4mm
const G4double BoxDelz                  = 2.0*mm; // extract space between components
const G4double box_thicknessXYZ[3]      = {(1.0/4.0)*25.4*mm, (1.0/4.0)*25.4*mm, (1.0/16.0)*25.4*mm};

extern G4double optHolderBox_halfXYZ[3];
const G4ThreeVector optHolderBox_posXYZ = G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm);
extern G4double optHollowVol_halfXYZ[3];
extern G4ThreeVector optHollowVol_posXYZ;//=G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm);
//------------------------- Aerogel Key Parameters---------------------//
const G4double foamHolderThicknessXYZ[3] = {10.0*mm, 10.0*mm, 10.0*mm};
extern G4double foamHolder_halfXYZ[3];
extern G4double foamHolder_posz;

const G4double agel_posx = 0*mm;
const G4double agel_posy = 0*mm;
extern G4double agel_posz;

const G4double agel_halfXYZ[3] = {55.25*mm, 55.25*mm, 15.0*mm};
//extern G4ThreeVector agel_posXYZ;

//------------------------------Lens key parameters------------------------//
extern G4double LENSHalfXYZ[3];
extern G4double LENS_z;
extern G4double LENSFocalLength;
//------------------------Fresnel Lens Key Parameters----------------------//
const G4double lens_n          = 1.49;
// const G4double LensHalfx       = (5.25/2.0)*2.54*cm;
// const G4double LensHalfy       = (5.25/2.0)*2.54*cm;
const G4double LensHalfx       = (5.0/2.0)*25.4*mm; // 5"*5" Fresnel Lens
const G4double LensHalfy       = (5.0/2.0)*25.4*mm;
const G4double LensDiameter    = 2.0*sqrt(2.0)*LensHalfx;
const G4double centerThickness = 0.06*25.4*mm;
extern G4double lens_halfz;

// const G4double focalLength     = 3.0*25.4*mm; // 3" focal length
const G4double focalLength     = 6.0*25.4*mm; // 6" focal length
const G4double GrooveDensity   = 125.0/(25.4*mm);
const G4double LensEffDiameter = 152.4*mm; // 6"
extern G4double GrooveWidth;

const G4double lens_gap = (1.0/8.0)*25.4*mm; //1/8 inch
extern G4double lens_z; 
extern G4double lens_holdbox_posz;
//--------------------------Plano Lens Parameters----------------------------//
const G4double planoLens_CT  = 17.0*mm;
const G4double planoLens_R   = 103.4*mm;
const G4double planoLens_BFL = 189.0*mm;
const G4double planoLens_D   = 100.0*mm;
extern G4double planoLens_ET;
//--------------------------- mirror key parameters ------------------------//
const G4double mirrorThickness = 2.0*mm;

//--------------------Readout Holder Box Key Parameters-----------------------------//
extern G4double roHolderBox_halfXYZ[3]; // same as optHolderBox_halfXYZ
extern G4ThreeVector roHolderBox_posXYZ;
extern G4double optHollowVol_halfXYZ[3];
extern G4ThreeVector roHollowVol_posXYZ;
const G4double roAirGap = 3.0*mm; // air gap between PMT surface and Optical Box

//---------------------------Photodetector Key Parameters-------------------//
const G4double pmt_halfXYZ[3] = {51.8/2.0*mm, 51.8/2.0*mm, 32.1/2.0*mm};
// const G4double pmtGap = 3.0/2.0*mm; // half width of the gap
const G4double pmtGap = 2.7*mm; // full width of the gap

const G4double glsWindow_halfXYZ[3] = {51.8/2.0*mm, 51.8/2.0*mm, 1.5/2.0*mm};

const G4double phoSensor_halfXYZ[3] = {48.5/2.0*mm, 48.5/2.0*mm, 1.5/2.0*mm};
extern G4double phodet_x;
extern G4double phodet_y;

const G4double phoAnode_halfXYZ[3] = {51.8/2.0*mm, 51.8/2.0*mm, (32.1-1.5-1.5)/2.0*mm};

extern G4double glsWindow_z;
extern G4double phoSensor_z;
extern G4double phoAnode_z;
extern G4double sensor_total_halfx;

//-----------------------Readout Electronics Key Parameters-----------------//
const G4double readout_halfz    = 4.0*mm;
const G4double readoutThickness = 2.0*mm;
extern G4double readout_z[2];

//--------------------------------------------------------------------------//
class BoxParameters
{ 
 public:
  char name[50];
  G4double halfXYZ[3];
  G4ThreeVector posXYZ;
  G4Material* material;
  int sensitivity;

  G4Colour color;
  bool visibility;
  bool wireframe;
  bool surface;
};
//--------------------------------------------------------------------------//
class PolyhedraParameters
{
 public:
  char name[50];
  G4ThreeVector pos;
  G4double start;
  G4double theta;
  G4int numSide;
  G4int num_zLayer;
  G4double z[4];                      //max. layer is 3
  G4double rinner[4];
  G4double router[4];
  G4Material* material;
  int sensitivity;

  G4Colour color;
  bool visibility;
  bool wireframe;
  bool surface;
};
//--------------------------------------------------------------------------//  
void SetParameters(int LENS);
void SetExpHallPar(BoxParameters* boxPar);
void SetOptHolderBoxPar(BoxParameters* boxPar);
void SetOptHollowVolumePar(BoxParameters* boxPar);
void SetFoamHolderPar(BoxParameters* boxPar);
void SetFoamHolderPar(PolyhedraParameters* par);
void SetAerogelPar(BoxParameters* boxPar);
void SetMirrorPar(PolyhedraParameters* par);
void SetRoHolderBoxPar(BoxParameters* boxPar);
void SetRoHollowVolumePar(BoxParameters* boxPar);
void SetGlassWindowPar(BoxParameters* boxPar,int  i, G4ThreeVector glassWindow_posXYZ);
void SetSensorPar(BoxParameters* boxPar, int i, G4ThreeVector sensor_posXYZ);
void SetAnodePar(BoxParameters* boxPar, int i, G4ThreeVector anode_posXYZ);
void SetReadoutPar(PolyhedraParameters* par);
void PrintParameters(int LENS);

//--------------------------------------------------------------------------//


#endif
