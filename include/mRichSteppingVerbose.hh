//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017, hexc & Ping
// Renamed file names 

class mRichSteppingVerbose;

#ifndef mRichSteppingVerbose_h
#define mRichSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichSteppingVerbose : public G4SteppingVerbose
{
 public:   

   mRichSteppingVerbose();
  ~mRichSteppingVerbose();

   void StepInfo();
   void TrackingStarted();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
