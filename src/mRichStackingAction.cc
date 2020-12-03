//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 2/2/2017 hexc & Ping
// renamed the file names

#include "mRichStackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichStackingAction::mRichStackingAction()
: gammaCounter(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichStackingAction::~mRichStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
mRichStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      gammaCounter++;
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichStackingAction::NewStage()
{
  G4cout << "Number of optical photons produced in this event : "
         << gammaCounter << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichStackingAction::PrepareNewEvent()
{ gammaCounter = 0; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
