/// Date created: November, 2020
/// Authors: hexc

#include "mRichActionInitialization.hh"
#include "mRichRunAction.hh"
#include "mRichAgelTrackingAction.hh"
#include "mRichSteppingAction.hh"
#include "mRichPrimaryGeneratorAction.hh"
#include "mRichStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichActionInitialization::mRichActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichActionInitialization::~mRichActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichActionInitialization::BuildForMaster() const
{
  SetUserAction(new mRichRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichActionInitialization::Build() const
{
  mRichRunAction* runAction = new mRichRunAction();
  SetUserAction(runAction);

  //  mRichEventAction* evtAction = new mRichEventAction(runAction);
  //  SetUserAction(evtAction);

  mRichPrimaryGeneratorAction* genAction = new mRichPrimaryGeneratorAction(runAction);
  SetUserAction(genAction);

  mRichSteppingAction* steppingAction = new mRichSteppingAction(genAction, runAction);
  SetUserAction(steppingAction);

  SetUserAction(new mRichAgelTrackingAction(runAction, genAction));
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
