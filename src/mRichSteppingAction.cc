// Updated on 12/04/2014, Hexc, Liang and Ping.
//   Fill an ntuple for storing photo hits in the photo detector
//
// Updated on 2/2/2017 for the 2nd mRICH prototype studies
//
#include "globals.hh"
#include "mRichSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Electron.hh"
#include "G4ThreeVector.hh"
#include "G4OpticalPhoton.hh"
#include "G4PionMinus.hh"

#include <iostream>
#include <fstream>
#include <cassert>

#include "g4root.hh"

using namespace std;


#ifdef G4ANALYSIS_USE
  #include "AIDA/AIDA.h"
#endif

mRichSteppingAction::mRichSteppingAction(mRichPrimaryGeneratorAction *RPrimGenAction,
					 mRichRunAction *run_action_in)
{
  run_action = run_action_in;
  rPrimGenAction = RPrimGenAction;

  uParticleChange = new G4VParticleChange();  
  
  G4String fout = "photons.txt";
  fOut.open(fout.c_str(), std::ios_base::out);

}

mRichSteppingAction::~mRichSteppingAction()
{
  fOut.close();
}

void mRichSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  //cout <<"Entry"<<endl;
  
  G4StepPoint* pPostStepPoint = aStep ->GetPostStepPoint();
  G4StepPoint* pPreStepPoint  = aStep ->GetPreStepPoint();
  G4int PID = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
  
  if ( pPostStepPoint->GetPhysicalVolume() != NULL) {
    assert (pPostStepPoint->GetPhysicalVolume());
    
    G4String tpostVol = pPostStepPoint->GetPhysicalVolume()->GetName();
    G4double ke = pPostStepPoint->GetKineticEnergy();    // in eV
    G4double wavel = ke*1240*1e5;                        // wavelength in nm
    //if (tpostVol == "phodet") {
    if (tpostVol == "sensor_0" || tpostVol == "sensor_1"||
	tpostVol == "sensor_2" || tpostVol == "sensor_3"||tpostVol == "Aerogel") {
      // get analysis manager
      G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

      G4double pcharge = pPostStepPoint->GetCharge();
      G4double g_x = pPostStepPoint->GetPosition().getX();
      G4double g_y = pPostStepPoint->GetPosition().getY();
      G4double g_z = pPostStepPoint->GetPosition().getZ();
            
      G4ThreeVector g_mom = pPostStepPoint->GetMomentumDirection();

      fOut <<iev<<" "<< g_x <<" "<< g_y <<" "<< g_z << " "<<pcharge<<" "<<ke<<" "<<wavel<<" "<< g_mom[0] <<" "<< g_mom[1] <<" "<< g_mom[2] << endl;
      if (pcharge != 0.0) {iev++;}

      G4int evtID = rPrimGenAction->getEvtID();

      // fill ntuple (ntuple ID = 2)
      int itree=2;
      analysisManager->FillNtupleDColumn(itree, 0, PID);
      analysisManager->FillNtupleDColumn(itree, 1, ke);
      analysisManager->FillNtupleDColumn(itree, 2, g_x);
      analysisManager->FillNtupleDColumn(itree, 3, g_y);
      analysisManager->FillNtupleDColumn(itree, 4, g_z);
      analysisManager->FillNtupleDColumn(itree, 5, g_mom[0]);
      analysisManager->FillNtupleDColumn(itree, 6, g_mom[1]);
      analysisManager->FillNtupleDColumn(itree, 7, g_mom[2]);
      analysisManager->FillNtupleDColumn(itree, 8, evtID);
      analysisManager->AddNtupleRow(itree);
    }
  }
  //cout <<"Out"<<endl;
}


