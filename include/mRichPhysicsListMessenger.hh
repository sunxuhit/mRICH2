//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017, hexc & Ping
// Renamed file names 
// Updated on Nov 16, 2020, hexc

#ifndef mRichPhysicsListMessenger_h
#define mRichPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

//class mRichPhysicsList;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichPhysicsListMessenger: public G4UImessenger
{
public:  
  //  mRichPhysicsListMessenger(mRichPhysicsList* );
  mRichPhysicsListMessenger( );
  ~mRichPhysicsListMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:  
  //    mRichPhysicsList*     pPhysicsList;
  
  G4UIdirectory*        mRichDir;
  G4UIdirectory*        physDir;
  G4UIcmdWithAnInteger* verboseCmd;
  G4UIcmdWithAnInteger* cerenkovCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

