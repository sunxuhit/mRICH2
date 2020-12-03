//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017, hexc & Ping
//

#include "mRichPhysicsListMessenger.hh"

//#include "mRichPhysicsList.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//mRichPhysicsListMessenger::mRichPhysicsListMessenger(mRichPhysicsList* pPhys)
//:pPhysicsList(pPhys)
mRichPhysicsListMessenger::mRichPhysicsListMessenger()
{
  /*
  mRichDir = new G4UIdirectory("/mRICH/");
  mRichDir->SetGuidance("UI commands of this example");
  
  physDir = new G4UIdirectory("/mRICH/phys/");
  physDir->SetGuidance("PhysicsList control");
 
  verboseCmd = new G4UIcmdWithAnInteger("/mRICH/phys/verbose",this);  
  verboseCmd->SetGuidance("set verbose for physics processes");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  cerenkovCmd = new G4UIcmdWithAnInteger("/mRICH/phys/cerenkovMaxPhotons",this);  
  cerenkovCmd->SetGuidance("set max nb of photons per step");
  cerenkovCmd->SetParameterName("MaxNumber",false);
  cerenkovCmd->SetRange("MaxNumber>=0");
  cerenkovCmd->AvailableForStates(G4State_Idle);  
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichPhysicsListMessenger::~mRichPhysicsListMessenger()
{
  delete verboseCmd;
  delete cerenkovCmd;
  delete physDir;
  delete mRichDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichPhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{
  /*
  if( command == verboseCmd )
   { pPhysicsList->SetVerbose(verboseCmd->GetNewIntValue(newValue));}
   
  if( command == cerenkovCmd )
   {pPhysicsList->SetNbOfPhotonsCerenkov(cerenkovCmd->GetNewIntValue(newValue));}
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
