//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017, hexc & Ping
// Renamed file names 

#ifndef mRichStackingAction_H
#define mRichStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichStackingAction : public G4UserStackingAction
{
  public:
    mRichStackingAction();
   ~mRichStackingAction();

  public:
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int gammaCounter;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

