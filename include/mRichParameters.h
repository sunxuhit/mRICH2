#ifndef mRichParameters_H
#define mRichParameters_H 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4Colour.hh"

const double myPI=4*atan(1);
//----------------------The experimental Hall ------------------------------//
const G4double expHall_halfXYZ[3]={15.0*cm,15.0*cm,15.0*cm};
const G4ThreeVector expHall_posXYZ=G4ThreeVector();

//--------------------Holder box key parameters-----------------------------//
const G4double BoxDelz = 2.0*mm;   // extract space between components
//const G4double box_thicknessXYZ[4] = {(1./4.)*2.54*cm,(1./4.)*2.54*cm,(1./16.)*2.54*cm,0.16*cm};
const G4double box_thicknessXYZ[4] = {(1./4.)*2.54*cm,(1./4.)*2.54*cm,(1./16.)*2.54*cm,(1./4.)*2.54*cm};
const G4ThreeVector acrylicBox_posXYZ=G4ThreeVector(0.0*cm,0.0*cm,0.0*cm);

extern G4double acrylicBox_halfXYZ[3];
extern G4ThreeVector hollow_posXYZ;//=G4ThreeVector(0.0*cm,0.0*cm,0.0*cm);
extern G4double hollow_halfXYZ[3];
//------------------------- Aerogel gel key parameters---------------------//
const G4double foamHolderThicknessXYZ[3]={1.0*cm,1.0*cm,1.0*cm};
extern G4double foamHolder_halfXYZ[3];
extern G4double foamHolder_posz;

const G4double agel_posx=0*cm;
const G4double agel_posy=0*cm;
extern G4double agel_posz;

const G4double agel_halfXYZ[3]={5.525*cm,5.525*cm,1.65*cm};
//extern G4ThreeVector agel_posXYZ;

//------------------------------Lens key parameters------------------------//
extern G4double LENSHalfXYZ[3];
extern G4double LENS_z;
extern G4double LENSFocalLength;
//------------------------Fresnel lens key parameters----------------------//
const G4double lens_n=1.49;
//const G4double lens_halfz = 0.3*cm;
const G4double LensHalfx=(5.25/2.0)*2.54*cm;
const G4double LensHalfy=(5.25/2.0)*2.54*cm;
extern G4double lens_halfz;
const G4double LensDiameter=2.0*sqrt(2.0)*LensHalfx;
const G4double centerThickness=0.06*2.54*cm; 

//G4double focalLength=7.62*cm;
const G4double focalLength=6.0*2.54*cm;
const G4double GrooveDensity=125.0/(2.54*cm);
extern G4double GrooveWidth;
const G4double LensEffDiameter=15.24*cm;
//const G4double halfThickness=0.102*cm;

extern G4double lens_z;
const G4double lens_gap=25.4/8.0*mm;    //1/8 inch
extern G4double lens_holdbox_posz;
//--------------------------Plano lens parameters----------------------------//
const G4double planoLens_CT=17*mm;
extern G4double planoLens_ET;
const G4double planoLens_R=103.4*mm;
const G4double planoLens_BFL=189.0*mm;
const G4double planoLens_D=100.0*mm;
//---------------------------Photodetector key parameters-------------------//
const G4double sensorGap=0.05*cm;      //half width of the gap

const G4double glassWindow_halfXYZ[3]={5.2/2.0*cm,5.2/2.0*cm,0.075*cm};

const G4double phodet_halfXYZ[3]={2.4*cm,2.4*cm,0.075*cm};
extern G4double phodet_x;
extern G4double phodet_y;

extern G4double glassWindow_z;
extern G4double phodet_z;
extern G4double sensor_total_halfx;

//--------------------------- mirror key parameters ------------------------//
const G4double mirrorThickness=0.2*cm;

//-----------------------Readout Electronics key parameters-----------------//
const G4double readout_halfz = 0.4*cm;
const G4double readoutThickness=0.2*cm;
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
void SetHolderBoxPar(BoxParameters* boxPar);
void SetHollowVolumePar(BoxParameters* boxPar);
void SetFoamHolderPar(BoxParameters* boxPar);
void SetFoamHolderPar(PolyhedraParameters* par);
void SetAerogelPar(BoxParameters* boxPar);
void SetGlassWindowPar(BoxParameters* boxPar,int  i, G4ThreeVector glassWindow_posXYZ);
void SetSensorPar(BoxParameters* boxPar, int i, G4ThreeVector sensor_posXYZ);
void SetMirrorPar(PolyhedraParameters* par);
void SetReadoutPar(PolyhedraParameters* par);
void PrintParameters(int LENS);

//--------------------------------------------------------------------------//


#endif
