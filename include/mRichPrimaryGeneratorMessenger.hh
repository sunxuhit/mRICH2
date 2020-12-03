//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
// Renamed file names

#ifndef mRichPrimaryGeneratorMessenger_h
#define mRichPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class mRichPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  mRichPrimaryGeneratorMessenger(mRichPrimaryGeneratorAction*);
  ~mRichPrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  mRichPrimaryGeneratorAction* mRichAction;
  G4UIdirectory*               gunDir; 
  G4UIcmdWithADoubleAndUnit*   polarCmd;
  G4UIcmdWithAnInteger*        newEventType;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

