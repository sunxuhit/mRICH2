// Updated on 12/04/2014, Hexc, Liang and Ping.
//   Fill an ntuple for storing photo hits in the photo detector
//
// Updated on 2/2/2017 for the 2nd mRICH prototype studies
//
// Updated on 12/7/20: Hexc
//   Updated the output written to ntuple properly. Cleaned up the code.
//
// Updated on 4/10/2021: hexc
//   Fixed a problem of filling ntuple variables. 

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
}

mRichSteppingAction::~mRichSteppingAction()
{
}

void mRichSteppingAction::UserSteppingAction(const G4Step* aStep)
{  
  evtID = rPrimGenAction->getEvtID();
  
  G4StepPoint* pPostStepPoint = aStep->GetPostStepPoint();
  G4StepPoint* pPreStepPoint  = aStep->GetPreStepPoint();

  G4int PID = aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
  
  if ( pPostStepPoint->GetPhysicalVolume() != NULL) {
    assert (pPostStepPoint->GetPhysicalVolume());
  
    // Find the physical volume name of the this step.
    G4String preStepVol = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    G4String postStepVol = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
    
    G4cout << "PreStep volume: " << preStepVol << "      PostStep volume: " << postStepVol << G4endl;
        
    //
    // In order to record the hits on sensors, one needs to make sure that "build_readout()"
    // is called in "Construct" member function of the mRICHDetectorConstruction class.
    // Also added "readout" volume for test the lens focal point.
    //
    
    if (postStepVol == "sensor_1" || postStepVol == "sensor_2"||
	postStepVol == "sensor_3" || postStepVol == "sensor_4"||
	postStepVol == "Aerogel"  || postStepVol == "readout" ) {    
      
      // Only check the hits in the readout volume
      //if (preStepVol == "readout" ) {
      
      G4double ke = aStep->GetPreStepPoint()->GetKineticEnergy();    // in eV
      G4double wavel = ke*1240*1e5;                        // wavelength in nm
      
      G4double pcharge = aStep->GetPreStepPoint()->GetCharge();
      G4double g_x = aStep->GetPreStepPoint()->GetPosition().getX();
      G4double g_y = aStep->GetPreStepPoint()->GetPosition().getY();
      G4double g_z = aStep->GetPreStepPoint()->GetPosition().getZ();
      
      G4ThreeVector g_mom = aStep->GetPostStepPoint()->GetMomentumDirection();
      
      G4cout << evtID <<"  "<< g_x <<"  "<< g_y <<"  "<< g_z << " charge: "<<pcharge<<" "<<ke<<" "<<wavel<<" "<< g_mom[0] <<" "<< g_mom[1] <<" "<< g_mom[2] << G4endl;
      
      //  if (pcharge != 0.0) {iev++;}
      
      
      // get analysis manager
      G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
      
      // fill ntuple (ntuple ID = 2)
      int itree = 2, startID = 12;
      double dummy = 999;
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), PID);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), ke);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_x);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_y);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_z);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_mom[0]);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_mom[1]);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), g_mom[2]);
      analysisManager->FillNtupleDColumn(itree, run_action->GetNtColID(startID++), evtID);
      analysisManager->AddNtupleRow(itree);
    }
  }
}
