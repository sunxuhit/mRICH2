#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "mRichMaterial.h"


G4Material* Water;
G4Material* Aluminum;
G4Material* Air;
G4Material* Air_Opt;
G4Material* Acrylic;
G4Material* Aerogel1;
G4Material* Aerogel2;
G4Material* NBK7;
G4Material* Borosilicate;
//---------------------------------------------------------------------------//
//
//---------------------------------------------------------------------------//
void SetMaterial()
{
  G4NistManager * nist = G4NistManager::Instance();
  
  //Gean4 Predefined
  Water= nist->FindOrBuildMaterial("G4_Water");
  Aluminum= nist->FindOrBuildMaterial("G4_Al");
  
  SetAir();
  SetAir_Opt();
  SetAcrylic();
  SetNBK7_SCHOTT();
  SetAerogel1();
  SetAerogel2();
  SetBorosilicate();
}
//---------------------------------------------------------------------------//
void SetAir()
{
  //using same photon energy array as aerogel 1
  G4double Agel1PhotonEnergy[nEntries1] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,     // 610, 600, 590, 580, (nm)  
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,     // 570, 560, 550, 540,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,     // 530, 520, 510, 500,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,     // 490, 480, 470, 460,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,     // 450, 440, 430, 420,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,     // 410, 400, 390, 380,  
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,     // 370, 360, 350, 340,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };   // 330, 320, 310, 300.

  G4double AirRefractiveIndex[nEntries1] =
    { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", Agel1PhotonEnergy, AirRefractiveIndex , nEntries1);

  G4NistManager * nist = G4NistManager::Instance();
  Air= nist->FindOrBuildMaterial("G4_AIR");
  Air->SetMaterialPropertiesTable(myMPT);
}

//---------------------------------------------------------------------------//
void SetAir_Opt()
{
  G4Element* N = new G4Element("Nitrogen", "N",  7 , 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O",  8 , 16.00*g/mole);
  
  G4double PhotonEnergy_Air_Opt[nEntries_Air_Opt] = {2.034*eV, 4.136*eV};
  G4double RefractiveIndex_Air_Opt[nEntries_Air_Opt] = {1.00, 1.00};

  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", PhotonEnergy_Air_Opt, RefractiveIndex_Air_Opt, nEntries_Air_Opt);

  Air_Opt = new G4Material("Air_Opt", 1.29*mg/cm3, 2);
  Air_Opt->AddElement(N, 70.*perCent);
  Air_Opt->AddElement(O, 30.*perCent);
  Air_Opt->SetMaterialPropertiesTable(myMPT);
}
//---------------------------------------------------------------------------//
void SetNBK7_SCHOTT()
{
  int i;

  //same photon energy array as aerogel 1
  G4double Agel1PhotonEnergy[nEntries1] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,     // 610, 600, 590, 580, (nm)
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,     // 570, 560, 550, 540,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,     // 530, 520, 510, 500,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,     // 490, 480, 470, 460,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,     // 450, 440, 430, 420,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,     // 410, 400, 390, 380,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,     // 370, 360, 350, 340,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };   // 330, 320, 310, 300.
  
  G4double NBK7RefractiveIndex[nEntries1];
  for (i=0;i<nEntries1;i++) {
    NBK7RefractiveIndex[i]=1.517;//n_NBK7_SCHOTT(Agel1PhotonEnergy[i]/eV);
    G4cout<<":::::::: mRICHMaterial:: SetBNK7_SCHOTT >>>> i="<<i<<
      " E="<<Agel1PhotonEnergy[i]<<" n="<<NBK7RefractiveIndex[i]<<G4endl;
  }
  
  G4double a=(1.0/0.0020857)*m;
  printf(":::::::::::::::: mRICHMaterial::SetNBK7_SCHOTT >>>> a=%.2lf\n",a);
  G4double NBK7Absorption[nEntries1]=
    { a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a,
      a,         a,         a,         a};
      /*
      00.667*cm, 00.037*cm, 00.333*cm,
      00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm,
      00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm};
      */
    
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX" ,Agel1PhotonEnergy, NBK7RefractiveIndex,nEntries1);
  myMPT->AddProperty("ABSLENGTH", Agel1PhotonEnergy, NBK7Absorption,nEntries1);

  G4NistManager * nist = G4NistManager::Instance();
  NBK7=new G4Material("NBK7", 2.46*mg/cm3,1);
  NBK7->AddMaterial(nist->FindOrBuildMaterial("G4_Pyrex_Glass"),1.0);
  NBK7->SetName("NBK7_glass");
  NBK7->SetMaterialPropertiesTable(myMPT);

}
//---------------------------------------------------------------------------//
G4double n_NBK7_SCHOTT(G4double E)
{
  int i;

  G4double c[3][2]={{1.03961212,  0.00600069867},
                    {0.231792344, 0.0200179144},
                    {1.01046945,  103.560653}};

  G4double lambda=1.239/E;      //in micrometer
  G4double sum=1;

  for (i=0;i<3;i++) sum=sum+(c[i][0]*pow(lambda,2))/(pow(lambda,2)-c[i][1]);
  return sqrt(sum);
}
//---------------------------------------------------------------------------//
void SetAcrylic()
{
  G4Element* H = new G4Element("Hydrogen", "H",  1 , 1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O",  8 , 16.00*g/mole);
  G4Element* C = new G4Element("Carbon"  ,"C" , 6., 12.01*g/mole);
  
  //same photon energy array as aerogel 1
  G4double Agel1PhotonEnergy[nEntries1] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,     // 610, 600, 590, 580, (nm)
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,     // 570, 560, 550, 540,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,     // 530, 520, 510, 500,  
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,     // 490, 480, 470, 460,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,     // 450, 440, 430, 420,  
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,     // 410, 400, 390, 380,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,     // 370, 360, 350, 340,  
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };   // 330, 320, 310, 300.

  G4double AcRefractiveIndex[nEntries1] =
    { 1.4902, 1.4907, 1.4913, 1.4918, 1.4924,   // 610, 600, 590, 580, 570,
      1.4930, 1.4936, 1.4942, 1.4948, 1.4954,   // 560, 550, 540, 530, 520,  (this line is interpolated)
      1.4960, 1.4965, 1.4971, 1.4977, 1.4983,   // 510, 500, 490, 480, 470,
      1.4991, 1.5002, 1.5017, 1.5017, 1.5017,   // 460, 450, 440, 430, 420,
      1.5017, 1.5017, 1.5017, 1.5017, 1.5017,   // 410,  
      1.5017, 1.5017, 1.5017, 1.5017, 1.5017,   // 360,     look up values below 435 
      1.5017, 1.5017};
  
  G4double AcAbsorption[nEntries1] =
    {25.25*cm, 25.25*cm, 25.25*cm, 25.25*cm,
     25.25*cm, 25.25*cm, 25.25*cm, 25.25*cm,
     25.25*cm, 25.25*cm, 25.25*cm, 25.25*cm,
     25.25*cm, 25.25*cm, 25.25*cm, 25.25*cm,
     25.25*cm, 25.25*cm, 25.25*cm, 25.25*cm,
     25.25*cm, 00.667*cm, 00.037*cm, 00.333*cm,
     00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm,
     00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm};
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX" ,Agel1PhotonEnergy, AcRefractiveIndex,nEntries1);
  myMPT->AddProperty("ABSLENGTH", Agel1PhotonEnergy, AcAbsorption,nEntries1);
  
  Acrylic=new G4Material("Acrylic", 1.19*g/cm3, 3);
  Acrylic->AddElement(C, 5);
  Acrylic->AddElement(H, 8);     // molecular ratios
  Acrylic->AddElement(O, 2);
  Acrylic->SetMaterialPropertiesTable(myMPT);
}
//---------------------------------------------------------------------------//
void SetAerogel1()
{
  G4Element* O = new G4Element("Oxygen"  , "O",  8 , 16.00*g/mole);
  G4Element* Si= new G4Element("Silicon", "Si", 14, 28.00*g/mole);

  G4double Agel1PhotonEnergy[nEntries1] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,     // 610, 600, 590, 580, (nm) 
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,     // 570, 560, 550, 540,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,     // 530, 520, 510, 500,     
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,     // 490, 480, 470, 460,            
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,     // 450, 440, 430, 420,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,     // 410, 400, 390, 380,                               
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,     // 370, 360, 350, 340,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };   // 330, 320, 310, 300.

  G4double Agel1RefractiveIndex[nEntries1] =
    { 1.02435, 1.0244,  1.02445, 1.0245,  1.02455,
      1.0246,  1.02465, 1.0247,  1.02475, 1.0248,
      1.02485, 1.02492, 1.025,   1.02505, 1.0251,
      1.02518, 1.02522, 1.02530, 1.02535, 1.0254,
      1.02545, 1.0255,  1.02555, 1.0256,  1.02568,
      1.02572, 1.0258,  1.02585, 1.0259,  1.02595,
      1.026,   1.02608};
  
  G4double Agel1Absorption[nEntries1] =    //from Hubert                                               
    { 3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
      15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
      45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
      52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
      30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
      17.500*m, 14.500*m };
  
  G4double Agel1Rayleigh[nEntries1];
  //const G4double AerogelTypeAClarity = 0.00719*micrometer*micrometer*micrometer*micrometer/cm;
  const G4double AerogelTypeAClarity = 0.0020*micrometer*micrometer*micrometer*micrometer/cm;
  G4double Cparam    =  AerogelTypeAClarity*cm/(micrometer*micrometer*micrometer*micrometer);
  G4double PhotMomWaveConv = 1239*eV*nm;
  
  if(Cparam != 0.0 ) {
    for(int i=0; i<nEntries1; i++ ){
      G4double ephoton = Agel1PhotonEnergy[i];
      //In the following the 1000 is to convert form nm to micrometer
      G4double wphoton=(PhotMomWaveConv/ephoton)/(1000.0*nm);
      Agel1Rayleigh[i]=(std::pow(wphoton,4))/Cparam;
    }
  }
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", Agel1PhotonEnergy, Agel1RefractiveIndex, nEntries1);
  myMPT->AddProperty("ABSLENGTH", Agel1PhotonEnergy, Agel1Absorption,nEntries1);
  myMPT->AddProperty("RAYLEIGH", Agel1PhotonEnergy, Agel1Rayleigh, nEntries1);  //Need table of rayleigh Scattering!!!
  myMPT->AddConstProperty("SCINTILLATIONYIELD",0./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",1.0);

  Aerogel1 = new G4Material("Aerogel1", 0.02*g/cm3, 2);
  Aerogel1->AddElement(Si, 1);
  Aerogel1->AddElement(O, 2);

  Aerogel1->SetMaterialPropertiesTable(myMPT);

}
//---------------------------------------------------------------------------//
void SetAerogel2()
{
  G4Element* O = new G4Element("Oxygen"  , "O",  8 , 16.00*g/mole);
  G4Element* Si= new G4Element("Silicon", "Si", 14, 28.00*g/mole);

  G4double Agel2PhotonEnergy[nEntries2]=
    {1.87855*eV,1.96673*eV,2.05490*eV,2.14308*eV,2.23126*eV,
     2.31943*eV,2.40761*eV,2.49579*eV,2.58396*eV,2.67214*eV,
     2.76032*eV,2.84849*eV,2.93667*eV,3.02485*eV,3.11302*eV,
     3.20120*eV,3.28938*eV,3.37755*eV,3.46573*eV,3.55391*eV,
     3.64208*eV,3.73026*eV,3.81844*eV,3.90661*eV,3.99479*eV,
     4.08297*eV,4.17114*eV,4.25932*eV,4.34750*eV,4.43567*eV,
     4.52385*eV,4.61203*eV,4.70020*eV,4.78838*eV,4.87656*eV,
     4.96473*eV,5.05291*eV,5.14109*eV,5.22927*eV,5.31744*eV,
     5.40562*eV,5.49380*eV,5.58197*eV,5.67015*eV,5.75833*eV,
     5.84650*eV,5.93468*eV,6.02286*eV,6.11103*eV,6.19921*eV };

  G4double Agel2RefractiveIndex[nEntries2] =
    {1.02825,1.02829,1.02834,1.02839,1.02844,
     1.02849,1.02854,1.02860,1.02866,1.02872,
     1.02878,1.02885,1.02892,1.02899,1.02906,
     1.02914,1.02921,1.02929,1.02938,1.02946,
     1.02955,1.02964,1.02974,1.02983,1.02993,
     1.03003,1.03014,1.03025,1.03036,1.03047,
     1.03059,1.03071,1.03084,1.03096,1.03109,
     1.03123,1.03137,1.03151,1.03166,1.03181,
     1.03196,1.03212,1.03228,1.03244,1.03261,
     1.03279,1.03297,1.03315,1.03334,1.03354};

  G4double Agel2Absorption[nEntries2] =      //from Marco                                               
    {17.5000*cm,17.7466*cm,17.9720*cm,18.1789*cm,18.3694*cm,
     18.5455*cm,18.7086*cm,18.8602*cm,19.0015*cm,19.1334*cm,
     19.2569*cm,19.3728*cm,19.4817*cm,19.5843*cm,19.6810*cm,
     19.7725*cm,19.8590*cm,19.9410*cm,20.0188*cm,20.0928*cm,
     18.4895*cm,16.0174*cm,13.9223*cm,12.1401*cm,10.6185*cm,
     9.3147*cm,8.1940*cm,7.2274*cm,6.3913*cm,5.6659*cm,
     5.0347*cm,4.4841*cm,4.0024*cm,3.5801*cm,3.2088*cm,
     2.8817*cm,2.5928*cm,2.3372*cm,2.1105*cm,1.9090*cm,
     1.7296*cm,1.5696*cm,1.4266*cm,1.2986*cm,1.1837*cm,
     1.0806*cm,0.9877*cm,0.9041*cm,0.8286*cm,0.7603*cm };

  G4double Agel2Rayleigh[nEntries2] =         //from Marco                                              
    {35.1384*cm, 29.24805*cm, 24.5418*cm, 20.7453*cm, 17.6553*cm,
     15.1197*cm, 13.02345*cm, 11.2782*cm, 9.81585*cm, 8.58285*cm,
     7.53765*cm, 6.6468*cm, 5.88375*cm, 5.22705*cm, 4.6596*cm,
     4.167*cm, 3.73785*cm, 3.36255*cm, 3.03315*cm, 2.7432*cm,
     2.487*cm, 2.26005*cm, 2.05845*cm, 1.87875*cm, 1.71825*cm,
     1.57455*cm, 1.44555*cm, 1.3296*cm, 1.2249*cm, 1.1304*cm,
     1.04475*cm, 0.9672*cm, 0.89655*cm, 0.83235*cm, 0.77385*cm,
     0.7203*cm, 0.67125*cm, 0.6264*cm, 0.58515*cm, 0.54735*cm,
     0.51255*cm, 0.48045*cm, 0.45075*cm, 0.4233*cm, 0.39795*cm,
     0.37455*cm, 0.3528*cm, 0.33255*cm, 0.3138*cm, 0.29625*cm};


  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  myMPT->AddProperty("RINDEX", Agel2PhotonEnergy, Agel2RefractiveIndex, nEntries2);
  myMPT->AddProperty("ABSLENGTH", Agel2PhotonEnergy, Agel2Absorption,nEntries2);
  myMPT->AddProperty("RAYLEIGH", Agel2PhotonEnergy, Agel2Rayleigh, nEntries2);
  myMPT->AddConstProperty("SCINTILLATIONYIELD",0./MeV);
  myMPT->AddConstProperty("RESOLUTIONSCALE",1.0);

  Aerogel2 = new G4Material("Aerogel2", 0.02*g/cm3, 2);
  Aerogel2->AddElement(Si, 1);
  Aerogel2->AddElement(O, 2);

  Aerogel2->SetMaterialPropertiesTable(myMPT);
}
//---------------------------------------------------------------------------//
void SetBorosilicate()
{
  G4double Agel1PhotonEnergy[nEntries1] =                                                               
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,     // 610, 600, 590, 580, (nm) 
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,     // 570, 560, 550, 540,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,     // 530, 520, 510, 500,                                
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,     // 490, 480, 470, 460,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,     // 450, 440, 430, 420,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,     // 410, 400, 390, 380,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,     // 370, 360, 350, 340,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };   // 330, 320, 310, 300.

  G4double glassRefractiveIndex[nEntries1] =
    { 1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47,  1.47, 1.47,  1.47,
      1.47, 1.47};

  G4double glassAbsorption[nEntries1] =
    {4.25*cm, 4.25*cm, 4.25*cm, 4.25*cm,
     4.25*cm, 4.25*cm, 4.25*cm, 4.25*cm,
     4.25*cm, 4.25*cm, 4.25*cm, 4.25*cm,
     4.25*cm, 4.25*cm, 4.25*cm, 4.25*cm,
     4.25*cm, 4.25*cm, 4.25*cm, 4.25*cm,
     4.25*cm, 00.667*cm, 00.037*cm, 00.333*cm,
     00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm,
     00.001*cm, 00.001*cm, 00.001*cm, 00.001*cm};
  
  G4MaterialPropertiesTable* myMPT = new G4MaterialPropertiesTable();
  //same photon energy array as aerogel 1
  myMPT->AddProperty("RINDEX", Agel1PhotonEnergy, glassRefractiveIndex, nEntries1);
  myMPT->AddProperty("ABSLENGTH", Agel1PhotonEnergy, glassAbsorption, nEntries1);

  G4NistManager * nist = G4NistManager::Instance();
  Borosilicate = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
  Borosilicate->SetMaterialPropertiesTable(myMPT);
}
