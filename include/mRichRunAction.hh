//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
// Renamed file names

#ifndef mRichRunAction_h
#define mRichRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"
#include "mRichRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;

class mRichRunAction : public G4UserRunAction
{
public:
  mRichRunAction();
  ~mRichRunAction();
  
public:
  void BeginOfRunAction(const G4Run* aRun);
  void EndOfRunAction(const G4Run* aRun);
  //G4int GetNtColID(G4int id) { return fNtColID[id];};
  
private:
  G4Timer* timer;
  //G4int fNtColID[30];  // The length of the array should be increased if more variables are added.
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*mRichRunAction_h*/
