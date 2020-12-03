//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/12/2017, hexc & Ping for the 2nd mRICH prototype
//
#include "globals.hh"

#include "mRichPrimaryGeneratorMessenger.hh"

#include "mRichPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichPrimaryGeneratorMessenger::mRichPrimaryGeneratorMessenger(
                                          mRichPrimaryGeneratorAction* mRichGun)
:mRichAction(mRichGun)
{
  gunDir = new G4UIdirectory("/mRICH/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");
   
  polarCmd = new G4UIcmdWithADoubleAndUnit("/mRICH/gun/optPhotonPolar",this);
  polarCmd->SetGuidance("Set linear polarization");
  polarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  polarCmd->SetParameterName("angle",true);
  polarCmd->SetUnitCategory("Angle");  
  polarCmd->SetDefaultValue(-360.0);
  polarCmd->SetDefaultUnit("deg");
  polarCmd->AvailableForStates(G4State_Idle);

  // New event type message
  newEventType = new G4UIcmdWithAnInteger("/mRICH/gun/newEventType",this);
  newEventType->SetGuidance("Set new event type");
  newEventType->SetGuidance("  Choice : 0, 1, 2, 3, or 4");
  newEventType->SetParameterName("ev_type", true);
  newEventType->SetDefaultValue(0);
  newEventType->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichPrimaryGeneratorMessenger::~mRichPrimaryGeneratorMessenger()
{
  delete polarCmd;
  delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichPrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{ 
  if( command == polarCmd ) {
      G4double angle = polarCmd->GetNewDoubleValue(newValue);
      if ( angle == -360.0*deg ) {
         mRichAction->SetOptPhotonPolar();
      } else {
         mRichAction->SetOptPhotonPolar(angle);
      }
  }

  if (command == newEventType ) {
    G4int eventType = newEventType->GetNewIntValue(newValue);
    mRichAction->SetEventType(eventType);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

