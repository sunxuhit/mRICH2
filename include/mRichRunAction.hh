//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
// Renamed file names
// Updated on 4/10/2021: hexc
//   Added proper fNtColID to identify the ntuple ID 

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
  G4int GetNtColID(G4int id) { return fNtColID[id];};
  
private:
  G4Timer* timer;
  // 3 ntuples and 12 + 9 + 9 variables
  G4int fNtColID[30];   // Note that the array dimension should be consistent with the total number of variables.

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*mRichRunAction_h*/
