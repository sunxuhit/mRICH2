// --------------------------------------------------------------
//                 GEANT 4 - ULTRA experiment example
// --------------------------------------------------------------
//
// Code developed by:
// B. Tome, M.C. Espirito-Santo, A. Trindade, P. Rodrigues 
//
//    ****************************************************
//    *      UltraFresnelLens.cc
//    ****************************************************
//
//    Class for definition of the Ultra Fresnel Lens. 
//    An  UltraFresnelLens object is created in the UltraDetectorConstruction class.
//    This class makes use of the UltraFresnelLensParameterisation class.
//    The lens profile is define through the GetSagita method.   
//
#include <cmath>
#include "UltraFresnelLens.hh"
#include "mRichParameters.h"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4IntersectionSolid.hh"

using namespace CLHEP;

UltraFresnelLens::UltraFresnelLens(G4Material* Material, G4VPhysicalVolume * MotherPV) 
{
  
  LensMaterial    = Material ;
  G4cout<<" ***** Material *** "<<LensMaterial<<" *****"<<G4endl;

  LensPosition    = G4ThreeVector(0.0*cm,0.0*cm,lens_z);
  LensEffRadius   = LensEffDiameter/2.0;

  if( GrooveWidth <= 0 ){
    //       G4Exception("UltraFresnelLens constructor: GrooveWidth<=0");
    G4cout << "UltraFresnelLens constructor: GrooveWidth<=0" << G4endl;
  }

  BuildLens(MotherPV) ;
  
}


UltraFresnelLens::~UltraFresnelLens(  )
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UltraFresnelLens::BuildLens(G4VPhysicalVolume *MotherPV){

  const int maxGrooves=500;
  
  G4Material *LensMotherMaterial = MotherPV->GetLogicalVolume()->GetMaterial() ;
  G4cout<<"\n*** in BuildLens: mother vol made of ***"<< LensMotherMaterial<<" *************\n";
  G4cout<<"\n*** in BuildLens: lens made of ***"<< LensMaterial<<" *************\n";
  
  //====================================================================================//
  //build lens hold box
  G4double lens_holdbox_halfz=lens_halfz;

  G4Box* lens_holdbox_box = new G4Box("lens_holdbox_box", LensHalfx, LensHalfx, lens_holdbox_halfz);
  G4LogicalVolume* lens_holdbox_log = new G4LogicalVolume(lens_holdbox_box,LensMotherMaterial,"lens_holdbox");
  G4VPhysicalVolume* lens_holdbox_phys = new G4PVPlacement(0,LensPosition,"lens_holdbox", lens_holdbox_log, MotherPV,false,0);
  
  G4VisAttributes* SurfaceVisAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  SurfaceVisAtt1->SetVisibility(false);
  SurfaceVisAtt1->SetForceWireframe(true);
  lens_holdbox_log->SetVisAttributes(SurfaceVisAtt1);
  //====================================================================================//
  //build grooves
  G4Polycone *Groove_poly[maxGrooves]; 
  G4LogicalVolume *Groove_log[maxGrooves];
  G4VPhysicalVolume *Groove_phys[maxGrooves];

  //SurfaceVisAtt1 = new G4VisAttributes(G4Colour(0.635,0.902,0.988));                      
  //SurfaceVisAtt1 = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  //SurfaceVisAtt1->SetVisibility(true);                                                                            
  //SurfaceVisAtt1->SetForceWireframe(true);
  //SurfaceVisAtt1->SetForceSolid(true);

  for (int igroove=0;igroove<maxGrooves;igroove++) {
    // G4VisAttributes* SurfaceVisAtt2 = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
    G4VisAttributes* SurfaceVisAtt2 = new G4VisAttributes(G4Colour(0.2745,0.5098,0.7059));
    //SurfaceVisAtt1 = new G4VisAttributes(G4Colour((double)(160.0-igroove)/20.0,(double) 1.0*(1.0-(160.0-igroove)/20.0),1.0));
    //if (abs(igroove-150)<10) {
    SurfaceVisAtt2->SetVisibility(true);
    SurfaceVisAtt2->SetForceWireframe(true);
    SurfaceVisAtt2->SetForceSolid(false);
    //}
    //else SurfaceVisAtt1->SetVisibility(false);
    
    //Grooves' inner and outer radius
    G4double iRmin1 = (igroove+0)*GrooveWidth;
    G4double iRmax1 = (igroove+1)*GrooveWidth;
    G4double iRmin2 = iRmin1;
    G4double iRmax2 = iRmin2+0.0001;
    
    G4double lens_poly_rmin[3] = {iRmin1, iRmin1, iRmin2};
    G4double lens_poly_rmax[3] = {iRmax1, iRmax1, iRmax2};
    
    if (iRmax1>LensDiameter/2.0) break;     //if iRmin1>Lens radius, outside the lens, break
    
    //====================================================================================//
    //phi angle (from Ping)
    G4double phi1;
    G4double phi2;
    G4double deltaPhi;
    
    if (iRmax1<LensHalfx) {   //1/4 of a full circle
      phi1=0;                  //in rad
      deltaPhi=twopi;          //in rad. two pi
      //phi1=45*pi/180;
      //deltaPhi=45*pi/180;             //make drawing
    }
    else {
      phi1=acos(LensHalfx/iRmax1);   //in rad
      phi2=asin(LensHalfx/iRmax1);   //in rad, assume lens is square -> halfy=halfx
      deltaPhi=phi2-phi1;
      //if ($iholdbox==0) {print "this is ", $igroove, "th grooves, phi1=",$phi1,", delPhi=",$deltaPhi,"\n";}
    }
    //====================================================================================//
    //grooves profile
    //G4double dZ=0.06*2.54*cm;      //center thickness=0.06 inches
    G4double lens_poly_z[3];
    int numOfLayer;
   
    if (iRmin1<LensEffRadius) {   //if iRmin>=effective radius, dZ=0, i.e. flat
      numOfLayer=3;
      G4double dZ = GetSagita(iRmax1) - GetSagita(iRmin1);
      lens_poly_z[0]=lens_halfz;
      lens_poly_z[1]=-lens_halfz+dZ;
      lens_poly_z[2]=-lens_halfz;
    }
    else {
      numOfLayer=2;
      lens_poly_z[0] = lens_halfz;
      lens_poly_z[1] = lens_halfz-centerThickness;
      lens_poly_z[2] = 0;
    }
    
    //====================================================================================//
    int repeat=1;
    int draw=1;
    char grooveName[30];
    
    if (iRmax1>=LensHalfx) { repeat=4; }   //4 edges
    for (int i=0;i<repeat;i++) {
      if (repeat==4) sprintf(grooveName,"groove%d_edge%d",igroove+1,i+1);
      else sprintf(grooveName,"groove%d",igroove+1);
      
      Groove_poly[i]=new G4Polycone(grooveName,phi1,deltaPhi, numOfLayer, lens_poly_z, lens_poly_rmin, lens_poly_rmax);
      Groove_log[i]=new G4LogicalVolume(Groove_poly[i],LensMaterial,grooveName,0,0,0);
      Groove_phys[i]=new G4PVPlacement(0,G4ThreeVector(0,0,0),Groove_log[i],grooveName,
				       lens_holdbox_log,false,0);
      
      Groove_log[i]->SetVisAttributes(SurfaceVisAtt2);
      phi1=phi1+halfpi;   //g4 pre-defined: halfpi=pi/2
    }
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//==============================================================================

G4double GetSagita(G4double radius) 
{
  
  G4double Conic = -1.0;                                  // original:
  //G4int lens_type = 3;
  G4int lens_type = 5;
  G4double Curvature;
  G4double Aspher[8] = {0,0,0,0,0,0,0,0};
  
  if (lens_type == 1) {
    Curvature = 0.00437636761488/mm;
    Aspher[0] = 4.206739256e-05/(mm);
    Aspher[1] = 9.6440152e-10/(mm3);
    Aspher[2] = -1.4884317e-15/(mm2*mm3);
  }
  else  if (lens_type == 2) {
    Curvature = 0.0132/mm;                // r=77mm, f~14cm
    Aspher[0] = 32.0e-05/(mm);
    Aspher[1] = -2.0e-7/(mm3);
    Aspher[2] =  1.2e-13/(mm2*mm3);
  }
  else  if (lens_type == 3) {
    Curvature = 0.0150/mm;         // r=77mm, f~12.5cm
    Aspher[0] = 42.0e-05/(mm);
    Aspher[1] = -3.0e-7/(mm3);
    Aspher[2] =  1.2e-13/(mm2*mm3);
  }
  else if (lens_type == 4) {
    Curvature = 0.0175/mm;         // r=77mm, f~10cm
    Aspher[0] = 72.0e-05/(mm);
    Aspher[1] = -5.0e-7/(mm3);
    Aspher[2] =  1.2e-13/(mm2*mm3);
  }
  else  if (lens_type==5) {
    Curvature=1/(focalLength*(lens_n-1));
  } 
  
  G4double TotAspher = 0.0*mm ;
  
  for(G4int k=1;k<9;k++){
    TotAspher += Aspher[k-1]*std::pow(radius,2*k) ;
  }
  
  G4double ArgSqrt = 1.0-(1.0+Conic)*std::pow(Curvature,2)*std::pow(radius,2) ; // note conic=-1, so ArgSqrt = 1.0
  
  if (ArgSqrt < 0.0){
    //     G4Exception("UltraFresnelLensParameterisation::Sagita: Square Root of <0 !");
    G4cout << "UltraFresnelLensParameterisation::Sagita: Square Root of <0 !" << G4endl;
  }
  G4double Sagita_value = Curvature*std::pow(radius,2)/(1.0+std::sqrt(ArgSqrt)) + TotAspher;

  return Sagita_value ;
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
