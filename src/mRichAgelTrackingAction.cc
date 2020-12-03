// This code was copied from ECRS
// Updated on 12/2/2015 Hexc & Ping
//   Added eventID to the ntuple
// Updated on 2/2/2017, hexc & Ping

#include "mRichAgelTrackingAction.hh"

#include "G4UserTrackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"

#include "g4root.hh"

using namespace CLHEP;

mRichAgelTrackingAction::mRichAgelTrackingAction(mRichRunAction *run_action_in, mRichPrimaryGeneratorAction* gen_action_in)
{ 
  run_action = run_action_in; 
  gen_action = gen_action_in;
}

mRichAgelTrackingAction::~mRichAgelTrackingAction()
{}

void mRichAgelTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Here we print the Particle Data Group particle id number as well as the
  // energy when a new particle is created for tracking
  if (aTrack->GetParentID() != 0) {
    G4ParticleDefinition* particle = aTrack->GetDefinition();
    G4int PID = particle->GetPDGEncoding();
    G4double KE = aTrack->GetKineticEnergy();
    G4double Global_time = aTrack->GetGlobalTime();
    G4double Local_time = aTrack->GetLocalTime();
    G4double Proper_time = aTrack->GetProperTime();
    G4ThreeVector P = aTrack->GetMomentum();
    
    G4String particleName = particle->GetParticleName();
    G4ThreeVector position = aTrack->GetPosition();

    // find and set event ID
    G4int evtID = gen_action->getEvtID();
    
    // get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // fill ntuple (ntuple ID = 1)
    /*
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(0), PID);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(1),KE/MeV);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(2),position.getX());
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(3),position.getY());
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(4),position.getZ());
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(5),P.getX()/MeV);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(6),P.getY()/MeV);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(7),P.getZ()/MeV);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(8),Global_time/ms);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(9),Local_time/ms);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(10),Proper_time/ms);
    analysisManager->FillNtupleDColumn(1, run_action->GetNtColID(11),evtID);
    analysisManager->AddNtupleRow(1);
    */
  }
}

void mRichAgelTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
}
