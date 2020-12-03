// 10/6/2014: Hexc, Olesya - This is a new file which is copied from ECRS2014
//   used for writing out the track info when it is created.
// 12/2/2015: Hexc - add primaryGeneratorAction to the constructor argument
#ifndef mRichAgelTrackingAction_h
#define mRichAgelTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "mRichPrimaryGeneratorAction.hh"

#include "G4Track.hh"

#include "mRichRunAction.hh"

class mRichAgelTrackingAction : public G4UserTrackingAction
{
public:
  mRichAgelTrackingAction(mRichRunAction* run_action_in, mRichPrimaryGeneratorAction* gen_action_in);
  ~mRichAgelTrackingAction();
  
  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
  
private:
  mRichRunAction *run_action;
  mRichPrimaryGeneratorAction *gen_action;
};

#endif
