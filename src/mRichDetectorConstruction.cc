// Detector construction
//
// Updated on 11/28/2020: hexc
//    One needs to set LENS either to 0 or 1 for choosing plano lens or Fresnel lens,
//    respectively. Default is set to 1.
//
// Updated on 4/11/2021: hexc
//    Clean up the code and add proper comments
//
#include "mRichDetectorConstruction.hh"
#include "mRichMaterial.h"
#include "mRichParameters.h"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "UltraFresnelLens.hh"

#include <cmath>
#include <string>
#include <iostream>
#include "G4VisAttributes.hh"


using namespace CLHEP;
using namespace std;

//---------------------------------------------------------------------------------//
//mRichDetectorConstruction::mRichDetectorConstruction(G4double blockThicknessAdd)
mRichDetectorConstruction::mRichDetectorConstruction()
{
  //agel_thicknessAdd = blockThicknessAdd;
  //G4cout << "Additional aerogel block thickness: " << agel_thicknessAdd << G4endl;
}

//---------------------------------------------------------------------------------//
mRichDetectorConstruction::~mRichDetectorConstruction(){;}

//---------------------------------------------------------------------------------//
G4VPhysicalVolume* mRichDetectorConstruction::Construct() {

  int LENS=1;              //1=Fresnel lens, 0=Plano lens

  SetMaterial();           //defined material in mRICHMaterial.cc
  SetParameters(LENS);     //don't change the order of these lines
  
  //============================//
  //  GEOMETRY                  //
  //============================//
  build_expHall();    // must build expHall and holder box first   
  build_holderBox();
  
  build_foamHolder();
  build_aerogel();    // one can comment out this function call for not including the
                      //    aerogel block in the detector constr.
  
  G4Material *LensMaterial = G4Material::GetMaterial("Acrylic");
  G4ThreeVector LensPosition = G4ThreeVector(0.0*mm,0.0*mm,lens_z);
  if (LENS) new UltraFresnelLens(LensMaterial,hollowVolume->GetPhysicalVolume());
  else build_planoLens();
  
  
  build_SensorPlane();
  build_mirror();        // Enable mirror set
  build_readout();
  
  //===========================//
  //  SURFACES                 //
  //===========================//
  //-------------------------- Air plane ------------------------------//
  //copy it to material file later
  G4OpticalSurface* OpAirSurface = new G4OpticalSurface("AirSurface");
  OpAirSurface->SetType(dielectric_dielectric);
  OpAirSurface->SetFinish(polished);
  OpAirSurface->SetModel(glisur);
  
  //-------
  // Generate & Add Material Properties Table attached to the optical surfaces
  //-------
  const G4int num = 2;
  G4double Ephoton[num] = {2.034*eV, 4.136*eV};
  
  //OpticalAirSurface
  G4double Reflectivity[num] = {0.3, 0.5};
  G4double Efficiency[num]   = {0.8, 1.0};

  G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();
  myST2->AddProperty("REFLECTIVITY", Ephoton, Reflectivity, num);
  myST2->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);

  OpAirSurface->SetMaterialPropertiesTable(myST2);

  //always return the physical World
  return expHall->GetPhysicalVolume();

} //end of construction

//---------------------------------------------------------------------------------//
BOX::BOX(BoxParameters boxPar, G4LogicalVolume* motherLV)
{
  box = new G4Box(boxPar.name,boxPar.halfXYZ[0],boxPar.halfXYZ[1],boxPar.halfXYZ[2]);
  log = new G4LogicalVolume(box,boxPar.material,boxPar.name,0,0,0);
  phys = new G4PVPlacement(0,boxPar.posXYZ,log,boxPar.name,
			  motherLV,false,0,true);    // added for checking overlaps

 G4VisAttributes* visAtt = new G4VisAttributes(boxPar.color);
 visAtt->SetVisibility(boxPar.visibility);
 visAtt->SetForceWireframe(boxPar.wireframe);
 visAtt->SetForceSolid(boxPar.surface);
 log->SetVisAttributes(visAtt);
}
//---------------------------------------------------------------------------------//
BOX::~BOX(){;}

//---------------------------------------------------------------------------------//
POLYHEDRA::POLYHEDRA(PolyhedraParameters par,G4LogicalVolume* motherLV)
{
  polyhedra=new G4Polyhedra(par.name, par.start,par.theta, par.numSide,
                            par.num_zLayer,par.z, par.rinner, par.router);
  log = new G4LogicalVolume(polyhedra,par.material,par.name,0,0,0);
  phys = new G4PVPlacement(0,par.pos,log,par.name,
                           motherLV,false,0);

  G4VisAttributes* visAtt = new G4VisAttributes(par.color);
  visAtt->SetVisibility(par.visibility);
  visAtt->SetForceWireframe(par.wireframe);
  visAtt->SetForceSolid(par.surface);
  log->SetVisAttributes(visAtt);
}
//---------------------------------------------------------------------------------//
POLYHEDRA::~POLYHEDRA(){;}

//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_expHall()
{
  BoxParameters expHallPar;
  SetExpHallPar(&expHallPar);
  expHall = new BOX(expHallPar, 0);
}

//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_holderBox()
{
  BoxParameters holderBoxPar;
  SetHolderBoxPar(&holderBoxPar);
  holderBox = new BOX(holderBoxPar,expHall->GetLogicalVolume());

  //hollow volume of holder box
  BoxParameters hollowVolumePar;
  SetHollowVolumePar(&hollowVolumePar);
  hollowVolume = new BOX(hollowVolumePar, holderBox->GetLogicalVolume());
}

//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_foamHolder()
{ 
  PolyhedraParameters polyPar;
  SetFoamHolderPar(&polyPar);
  POLYHEDRA* foamHolderPoly = new POLYHEDRA(polyPar, hollowVolume->GetLogicalVolume());
 
  BoxParameters boxPar;                                                   
  SetFoamHolderPar(&boxPar);
  BOX* foamHolderBox = new BOX(boxPar, hollowVolume->GetLogicalVolume());
}

//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_aerogel()
{
  BoxParameters aerogelPar;
  SetAerogelPar(&aerogelPar);
  aerogel = new BOX(aerogelPar, hollowVolume->GetLogicalVolume());

  G4OpticalSurface* OpWaterSurface = new G4OpticalSurface("WaterSurface");
  OpWaterSurface->SetType(dielectric_dielectric);
  OpWaterSurface->SetFinish(ground);
  OpWaterSurface->SetModel(unified);

  //copy it to material file later
  const G4int num = 2;
  G4double Ephoton[num] = {2.034*eV, 4.136*eV};

  new G4LogicalBorderSurface("WaterSurface",aerogel->GetPhysicalVolume(),expHall->GetPhysicalVolume(),OpWaterSurface);

  //  G4double RefractiveIndex[num] = {1.35, 1.40};    // Wrong! 11/28/2020
  G4double RefractiveIndex[num] = {1.03, 1.03};
  G4double SpecularLobe[num]    = {0.3, 0.3};
  G4double SpecularSpike[num]   = {0.2, 0.2};
  G4double Backscatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

  myST1->AddProperty("RINDEX",                Ephoton, RefractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);

  OpWaterSurface->SetMaterialPropertiesTable(myST1);
}
//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_SensorPlane()
{
  G4double last_x = glassWindow_halfXYZ[0] + sensorGap; // adding extra space between H13700's
  G4double last_y = last_x;

  BoxParameters tmp_par;

  BOX* glassWindow[4];
  BOX* phoDet[4];

  int i;
  for (i=0;i<4;i++) {
    if (i==0) {
      phodet_x = last_x;
      phodet_y = last_y;
    }
    else {
      phodet_x = -last_y;
      phodet_y = last_x;
    }

    SetGlassWindowPar(&tmp_par, i+1, G4ThreeVector(phodet_x, phodet_y, glassWindow_z));
    glassWindow[i] = new BOX(tmp_par, hollowVolume->GetLogicalVolume());

    SetSensorPar(&tmp_par, i+1, G4ThreeVector(phodet_x, phodet_y, phodet_z));
    phoDet[i] = new BOX(tmp_par, hollowVolume->GetLogicalVolume());

    last_x = phodet_x;
    last_y = phodet_y;
  }//end of for(i)     
}
//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_readout()
{
  PolyhedraParameters readoutPar;
  SetReadoutPar(&readoutPar);
  POLYHEDRA* readout = new POLYHEDRA(readoutPar, hollowVolume->GetLogicalVolume());
}
//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_mirror()
{
  PolyhedraParameters mirrorPar;
  SetMirrorPar(&mirrorPar);
  POLYHEDRA* mirror = new POLYHEDRA(mirrorPar, hollowVolume->GetLogicalVolume());

  //-----------
  //   Optical properties of the interface between the Air and Reflective Surface 
  //   For Mirror, reflectivity is set at 95% and specular reflection is assumed.
  //-----------
  G4OpticalSurface *OpticalAirMirror = new G4OpticalSurface("AirMirrorSurface");
  OpticalAirMirror->SetModel(unified);
  OpticalAirMirror->SetType(dielectric_dielectric);
  OpticalAirMirror->SetFinish(polishedfrontpainted);
  
  const G4int NUM = 2;
  G4double lambda_min = 200*nm ;
  G4double lambda_max = 700*nm ;
  
  G4double XX[NUM] = {h_Planck*c_light/lambda_max, h_Planck*c_light/lambda_min} ;
  G4double ICEREFLECTIVITY[NUM]      = {0.95, 0.95};
  
  G4MaterialPropertiesTable *AirMirrorMPT = new G4MaterialPropertiesTable();
  AirMirrorMPT->AddProperty("REFLECTIVITY", XX, ICEREFLECTIVITY,NUM);
  OpticalAirMirror->SetMaterialPropertiesTable(AirMirrorMPT);

  new G4LogicalBorderSurface("Air/Mirror Surface",hollowVolume->GetPhysicalVolume(),
			     mirror->GetPhysicalVolume(),OpticalAirMirror);
}

//---------------------------------------------------------------------------------//
void mRichDetectorConstruction::build_planoLens()
{
  G4VSolid* box = new G4Box("box",planoLens_R,planoLens_R,planoLens_R);
  G4VSolid* tub = new G4Tubs("tub",0,planoLens_D/2.0,planoLens_ET/2.0,0,twopi);

  G4VSolid* solidSphere=new G4Orb("solidSphere",planoLens_R);
  G4SubtractionSolid* tmp1 = new G4SubtractionSolid("tmp1",solidSphere,box,
						  0,G4ThreeVector(0,0,planoLens_CT-planoLens_ET));
  G4UnionSolid* planoLens = new G4UnionSolid("planoLens", tmp1, tub,
  					   0,G4ThreeVector(0,0,-planoLens_R+planoLens_CT-planoLens_ET/2.0));

  //G4LogicalVolume* log1 = new G4LogicalVolume(solidSphere,Air_Opt,"sphere",0,0,0);
  //G4LogicalVolume* log2 = new G4LogicalVolume(tub,Air_Opt,"tub",0,0,0);
  G4LogicalVolume* log = new G4LogicalVolume(planoLens,NBK7,"planoLens",0,0,0);
  new G4PVPlacement(0,G4ThreeVector(0,0,LENS_z),log,"planoLens",
		    hollowVolume->GetLogicalVolume(),false,0);

  G4VisAttributes* visAtt = new G4VisAttributes(G4Color(0.125,0.431,0.918));
  visAtt->SetVisibility(true);
  visAtt->SetForceWireframe(true);
  visAtt->SetForceSolid(false);
  log->SetVisAttributes(visAtt);
}
