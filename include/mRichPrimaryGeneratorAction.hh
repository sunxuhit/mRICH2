//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
//

#ifndef mRichPrimaryGeneratorAction_h
#define mRichPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "mRichRunAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class mRichPrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  mRichPrimaryGeneratorAction(mRichRunAction*);
  ~mRichPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);
  
  void SetOptPhotonPolar();
  void SetOptPhotonPolar(G4double);
  void SetEventType(G4int eventType) { ev_type = eventType; };
  G4int getEvtID() { return evtID; };
  
private:
  G4ParticleGun* particleGun;
  mRichPrimaryGeneratorMessenger* gunMessenger;
  mRichRunAction* run_action;
  G4int ev_type, evtID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*mRichPrimaryGeneratorAction_h*/
