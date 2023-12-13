#include "mRichParameters.h"

#include <cmath>

using namespace std;

#include "globals.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"

#include "mRichMaterial.h"
#include "UltraFresnelLens.hh"


G4double optHolderBox_halfXYZ[3];
G4double optHollowVol_halfXYZ[3];
G4ThreeVector optHollowVol_posXYZ;

G4double foamHolder_halfXYZ[3];
G4double foamHolder_posz;

G4double agel_posz;

G4double LENSHalfXYZ[3];
G4double LENS_z;
G4double LENSFocalLength;

G4double lens_z;   // poor variable name choice, given the defined LENS_z
G4double lens_halfz;
G4double GrooveWidth;

G4double planoLens_ET;

G4double sensor_total_halfx;
G4double roHolderBox_halfXYZ[3];
G4ThreeVector roHolderBox_posXYZ;
G4double roHollowVol_halfXYZ[3];
G4ThreeVector roHollowVol_posXYZ;

G4double phodet_x;
G4double phodet_y;

G4double glsWindow_z;
G4double phoSensor_z;
G4double phoAnode_z;
G4double readout_z[2];
//----------------------------------------------------//
void SetParameters(int LENS)
{
	//--------------------Optical Holder Box Key Parameters-----------------------------//
  GrooveWidth              = (G4double) 1.0/GrooveDensity;
  G4double NumberOfGrooves = floor(GrooveDensity*(LensEffDiameter/2.0));
  G4double Rmin1           = (NumberOfGrooves-1)*(GrooveWidth);
  G4double Rmax1           = (NumberOfGrooves-0)*(GrooveWidth);
  lens_halfz               = (GetSagita(Rmax1)-GetSagita(Rmin1)+centerThickness)/2.0; // remove this line later

  planoLens_ET = planoLens_CT-planoLens_R+sqrt(pow(planoLens_R,2)-pow(planoLens_D/2.0,2));

  if (LENS) {  // build Fresnel lens
    LENSHalfXYZ[0]  = LensHalfx;
    LENSHalfXYZ[1]  = LENSHalfXYZ[0];
    LENSHalfXYZ[2]  = (GetSagita(Rmax1)-GetSagita(Rmin1)+centerThickness)/2.0 ;
    LENSFocalLength = focalLength;
    printf("Num. of grooves=%.6lf, groove width=%.6lf\n",NumberOfGrooves,GrooveWidth);
  }
  else {       //build plano lens
    LENSHalfXYZ[0]  = planoLens_D/2.0;
    LENSHalfXYZ[1]  = LENSHalfXYZ[0];
    LENSHalfXYZ[2]  = planoLens_CT/2.0;
    LENSFocalLength = planoLens_BFL;
    printf("======================== planoLens_ET=%.4lf ===================\n",planoLens_ET);
  }
  
  foamHolder_halfXYZ[0] = agel_halfXYZ[0]+foamHolderThicknessXYZ[0];
  foamHolder_halfXYZ[1] = foamHolder_halfXYZ[0];
  foamHolder_halfXYZ[2] = foamHolderThicknessXYZ[2]/2.0;
  
  optHolderBox_halfXYZ[0] = max(foamHolder_halfXYZ[0], LENSHalfXYZ[0]) +0.1*cm + box_thicknessXYZ[0];
  optHolderBox_halfXYZ[1] = optHolderBox_halfXYZ[0];
  optHolderBox_halfXYZ[2] = (box_thicknessXYZ[2]+2*foamHolder_halfXYZ[2]+2*agel_halfXYZ[2]+lens_gap+2*LENSHalfXYZ[2]+LENSFocalLength)/2.0;
  
  optHollowVol_halfXYZ[0] = optHolderBox_halfXYZ[0]-box_thicknessXYZ[0];
  optHollowVol_halfXYZ[1] = optHollowVol_halfXYZ[0];
  optHollowVol_halfXYZ[2] = (2*optHolderBox_halfXYZ[2]-box_thicknessXYZ[2])/2.0;
  
  optHollowVol_posXYZ=G4ThreeVector(0.0*cm,0.0*cm,-optHolderBox_halfXYZ[2]+box_thicknessXYZ[2]+optHollowVol_halfXYZ[2]);
  
  // foamHolder_posz=-optHollowVol_halfXYZ[2]+BoxDelz+foamHolder_halfXYZ[2];
  foamHolder_posz=-optHollowVol_halfXYZ[2]+foamHolder_halfXYZ[2];
  agel_posz=foamHolder_posz+foamHolder_halfXYZ[2]+agel_halfXYZ[2];
  
  if (LENS) {
    lens_z=agel_posz+agel_halfXYZ[2]+lens_halfz+lens_gap;  //remove this line
    LENS_z=agel_posz+agel_halfXYZ[2]+lens_halfz+lens_gap;
    // glsWindow_z=LENS_z-LENSHalfXYZ[2]+LENSFocalLength+glsWindow_halfXYZ[2]; //out of focus. But this makes sense.
  }
  else {
    LENS_z=agel_posz+agel_halfXYZ[2]+lens_gap+planoLens_R;
    // glsWindow_z=LENS_z-planoLens_R+planoLens_CT+planoLens_BFL+glsWindow_halfXYZ[2];
  }

	//--------------------Readout Holder Box Key Parameters-----------------------------//
	roHolderBox_halfXYZ[0] = optHolderBox_halfXYZ[0]; // same as optHolderBox_halfXYZ
	roHolderBox_halfXYZ[1] = optHolderBox_halfXYZ[1]; // same as optHolderBox_halfXYZ
	roHolderBox_halfXYZ[2] = 20.0*mm; // temp setting
  roHolderBox_posXYZ = G4ThreeVector(0.0*cm,0.0*cm,optHolderBox_halfXYZ[2]+roHolderBox_halfXYZ[2]);

	roHollowVol_halfXYZ[0] = roHolderBox_halfXYZ[0]-box_thicknessXYZ[0];
	roHollowVol_halfXYZ[1] = roHolderBox_halfXYZ[1]-box_thicknessXYZ[1];
	roHollowVol_halfXYZ[2] = (2.0*roHolderBox_halfXYZ[2]-box_thicknessXYZ[2])/2.0;
  roHollowVol_posXYZ = G4ThreeVector(0.0*cm,0.0*cm,-box_thicknessXYZ[2]/2.0);

  sensor_total_halfx = 2.0*pmt_halfXYZ[0]+pmtGap;
  
  glsWindow_z = -roHollowVol_halfXYZ[2]+roAirGap; // w.r.t. Readout Hollow Volume
  phoSensor_z = glsWindow_z+glsWindow_halfXYZ[2]+phoSensor_halfXYZ[2];
  phoAnode_z  = phoSensor_z+phoSensor_halfXYZ[2]+phoAnode_halfXYZ[2];
  
  //Is readout_z match to GEMC simulation?
  readout_z[0]=glsWindow_z-glsWindow_halfXYZ[2];
  readout_z[1]=phoSensor_z+phoSensor_halfXYZ[2];
  
  PrintParameters(LENS);
}
//----------------------------------------------------//
void PrintParameters(int LENS)
{
  
  ofstream textfile;                                                                                                                                        
  textfile.open("mRICHdimension.txt");                                                                                                                      
  textfile<<"=====================================================================\n";                                                                      
  textfile<<"                   " <<agel_halfXYZ[2]*2<< "mm thick Aerogel\n";                                                                                    
  textfile<<"=====================================================================\n";                                                                      
  textfile<<"Printing detector positions and sizes ...\n\n";                                                                                                
  textfile<<"hold box       position=(0.0, 0.0, "<<optHolderBox_posXYZ[2]<<")mm half size in XYZ=("<<optHolderBox_halfXYZ[0]<<", "<<optHolderBox_halfXYZ[1]<<", "<<optHolderBox_halfXYZ[2]<<")mm\n";
  textfile<<"hollowVol      position=(0.0, 0.0, "<<optHollowVol_posXYZ[2]<<")mm half size in XYZ=("<<optHollowVol_halfXYZ[0]<<", "<<optHollowVol_halfXYZ[1]<<", "<<optHollowVol_halfXYZ[2]<<")mm\n";
  textfile<<"aerogel        position=(0.0, 0.0, "<<optHollowVol_posXYZ[2]+agel_posz<<")mm half size in XYZ=("<<agel_halfXYZ[0]<<", "<<agel_halfXYZ[1]<<", "<<agel_halfXYZ[2]<<")mm\n";          
  if (LENS) textfile<<"fresnel lens   ";
  else textfile<<"plano lens     ";
  textfile<<"position=(0.0, 0.0, "<<optHollowVol_posXYZ[2]+LENS_z<<")mm half size in XYZ=("<<LENSHalfXYZ[0]<<", "<<LENSHalfXYZ[1]<<","<<LENSHalfXYZ[2]<<")mm\n";
  textfile<<"photon sensor  position=(0.0, 0.0, "<<optHollowVol_posXYZ[2]+phoSensor_z<<")mm half size in XYZ=("<<phoSensor_halfXYZ[0]<<", "<<phoSensor_halfXYZ[1]<<", "<<phoSensor_halfXYZ[2]<<")mm\n";       
  textfile<<"glass window   pos_z="<<optHollowVol_posXYZ[2]+glsWindow_z<<"mm , half_z= "<<glsWindow_halfXYZ[2]<<"mm\n";                                                             
  textfile<<"sensor_total_halfx="<<sensor_total_halfx<<"mm\n";                                                                                              
  textfile<<"readout        position=(0.0, 0.0, "<<optHollowVol_posXYZ[2]+readout_z[0]<<" and "<<optHollowVol_posXYZ[2]+readout_z[1]<<")mm\n";                                                            
  textfile<<"=====================================================================\n";                                                                      
  textfile.close();
}
//----------------------------------------------------//
void SetExpHallPar(BoxParameters* boxPar)
{
  int i=0;
  
  sprintf(boxPar->name,"World");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=expHall_halfXYZ[i];
  boxPar->posXYZ=expHall_posXYZ;
  boxPar->material=Air;
  boxPar->sensitivity=0;
  
  boxPar->color=G4Colour(0.0,0.0,0.0);
  boxPar->visibility=false;                 //keep it false, please.
  boxPar->wireframe=false;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetOptHolderBoxPar(BoxParameters* boxPar)
{
  int i=0;
  
  sprintf(boxPar->name,"OptHolderBox");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=optHolderBox_halfXYZ[i];
  boxPar->posXYZ=optHolderBox_posXYZ;
  boxPar->material=Aluminum;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(0.51,0.97,0.95);
  boxPar->color=G4Colour(0.7529, 0.7529, 0.7529);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetOptHollowVolumePar(BoxParameters* boxPar)
{
  int i;
  
  sprintf(boxPar->name,"OptHollowVolume");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=optHollowVol_halfXYZ[i];
  boxPar->posXYZ=optHollowVol_posXYZ;
  boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  boxPar->color=G4Colour(1.0,1.0,1.0);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
  
}
//----------------------------------------------------//
void SetFoamHolderPar(BoxParameters* boxPar)
{
  int i;
  
  sprintf(boxPar->name,"FoamHolder");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=foamHolder_halfXYZ[i];
  boxPar->posXYZ=G4ThreeVector(0.0*cm,0.0*cm,foamHolder_posz);
  boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(0.0,1.0,0.0);
  boxPar->color=G4Colour(0.498,1.0,0.8314);
  boxPar->visibility=true;
  // boxPar->visibility=false;
  boxPar->wireframe=true;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetFoamHolderPar(PolyhedraParameters* par)
{
  sprintf(par->name,"FoamHolder");
  par->pos=G4ThreeVector(0,0,0);
  par->start=45.0*myPI/180.0;
  par->theta=2*myPI;
  par->numSide=4;
  par->num_zLayer=2;
  
  par->z[0]=agel_posz-agel_halfXYZ[2];   //front of agel
  par->z[1]=agel_posz+agel_halfXYZ[2];   //back of sensor plane
  //G4cout<<"mirror length_="<<par->z[1]-par->z[0]<<endl;
  
  par->rinner[0]=agel_halfXYZ[0];
  par->rinner[1]=agel_halfXYZ[0];
  
  par->router[0]=par->rinner[0]+foamHolderThicknessXYZ[0];
  par->router[1]=par->rinner[1]+foamHolderThicknessXYZ[0];
  
  par->material=Air_Opt;
  par->sensitivity=0;
  
  // par->color=G4Colour(0.0,1.0,0.0);
  par->color=G4Colour(0.498,1.0,0.8314);
  par->visibility=true;
  // par->visibility=false;
  par->wireframe=true;
  par->surface=false;
}
//----------------------------------------------------//
void SetAerogelPar(BoxParameters* boxPar)
{
  int i;
  
  sprintf(boxPar->name,"Aerogel");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=agel_halfXYZ[i];
  boxPar->posXYZ=G4ThreeVector(agel_posx,agel_posy,agel_posz);
  boxPar->material=Aerogel2;
  //boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(1.0,0.65,0.0);
  boxPar->color=G4Colour(0.9137,0.5882,0.4784);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetMirrorPar(PolyhedraParameters* par)
{
  sprintf(par->name,"mirror");
  par->pos=G4ThreeVector(0,0,0);
  par->start=45.0*myPI/180.0;
  par->theta=2*myPI;
  par->numSide=4;
  par->num_zLayer=2;
  
  //par->z[0]=LENS_z+LENSHalfXYZ[2]+lens_gap;   //back of lens+air gap
  par->z[0] = optHollowVol_halfXYZ[2] - LENSFocalLength + lens_gap;  
  par->z[1] = optHollowVol_halfXYZ[2] - lens_gap;   //front of sensor plane
  G4cout<<"mirror length_="<<par->z[1]-par->z[0]<<endl;
  /*
  par->z[0]=lens_z+lens_halfz+lens_gap;   //back of lens+air gap
  par->z[1]=glsWindow_z-glsWindow_halfXYZ[2];   //front of sensor plane
  G4cout<<"mirror length_="<<par->z[1]-par->z[0]<<endl;
  */  
  par->rinner[0]=agel_halfXYZ[0];
  par->rinner[1]=sensor_total_halfx;

  par->router[0]=par->rinner[0]+mirrorThickness;
  par->router[1]=par->rinner[1]+mirrorThickness;
  
  par->material=Aluminum;
  par->sensitivity=0;

  par->color=G4Colour(1.0,1.0,0.0);
  par->visibility=true;
  par->wireframe=true;
  par->surface=false;
}
//----------------------------------------------------//
void SetRoHolderBoxPar(BoxParameters* boxPar)
{
  int i=0;
  
  sprintf(boxPar->name,"RoHolderBox");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=roHolderBox_halfXYZ[i];
  boxPar->posXYZ=roHolderBox_posXYZ;
  boxPar->material=Aluminum;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(0.51,0.97,0.95);
  boxPar->color=G4Colour(0.7529, 0.7529, 0.7529);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetRoHollowVolumePar(BoxParameters* boxPar)
{
  int i;
  
  sprintf(boxPar->name,"RoHollowVolume");
  for (i=0;i<3;i++) boxPar->halfXYZ[i]=roHollowVol_halfXYZ[i];
  boxPar->posXYZ=roHollowVol_posXYZ;
  boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  boxPar->color=G4Colour(1.0,1.0,1.0);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
  
}
//----------------------------------------------------//
void SetGlassWindowPar(BoxParameters* boxPar,int  i, G4ThreeVector glassWindow_posXYZ)
{
  int j;
  
  sprintf(boxPar->name, "glassWindow_%d",i);
  for (j=0;j<3;j++) boxPar->halfXYZ[j]=glsWindow_halfXYZ[j];
  boxPar->posXYZ=glassWindow_posXYZ;  //see mRichDetectorConstruction.cc
  boxPar->material=Borosilicate;
  boxPar->sensitivity=0;

  // boxPar->color=G4Colour(0.101,0.737,0.612);
  boxPar->color=G4Colour(0.6902,0.7686,0.8706);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
}

//----------------------------------------------------//
void SetSensorPar(BoxParameters* boxPar, int i, G4ThreeVector phodet_posXYZ)
{
  int j;

  sprintf(boxPar->name, "sensor_%d",i);
  for (j=0;j<3;j++) boxPar->halfXYZ[j]=phoSensor_halfXYZ[j];
  boxPar->posXYZ=phodet_posXYZ;      //see mRichDetectorConstruction.cc
  boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(1.0,1.0,0.0);
  boxPar->color=G4Colour(0.9412,0.902,0.549);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  // boxPar->surface=false;
  boxPar->surface=true;
}
//----------------------------------------------------//
void SetAnodePar(BoxParameters* boxPar, int i, G4ThreeVector phoAnode_posXYZ)
{
  int j;

  sprintf(boxPar->name, "anode_%d",i);
  for (j=0;j<3;j++) boxPar->halfXYZ[j]=phoAnode_halfXYZ[j];
  boxPar->posXYZ=phoAnode_posXYZ;      //see mRichDetectorConstruction.cc
  boxPar->material=Air_Opt;
  boxPar->sensitivity=0;
  
  // boxPar->color=G4Colour(0.101,0.737,0.612);
  boxPar->color=G4Colour(0.3922,0.5843,0.9294);
  boxPar->visibility=true;
  boxPar->wireframe=true;
  boxPar->surface=false;
}
//----------------------------------------------------//
void SetReadoutPar(PolyhedraParameters* par)
{
  sprintf(par->name,"readout");
  par->pos=G4ThreeVector(0,0,0);
  par->start=45.0*myPI/180.0;
  par->theta=2*myPI;
  par->numSide=4;
  par->num_zLayer=2;

  par->z[0]=readout_z[0];
  par->z[1]=readout_z[1];

  par->rinner[0]=sensor_total_halfx;
  par->rinner[1]=par->rinner[0];

  par->router[0]=par->rinner[0]+readoutThickness;
  par->router[1]=par->router[0];

  par->material=Aluminum;
  par->sensitivity=0;

  par->color=G4Colour(1.0,0.0,0.0);
  par->visibility=true;
  par->wireframe=true;
  par->surface=false;
}
