/////////////////////////////////////////////////////////////////////////////
// 2/2/2017 hexc & Ping
// renamed file names
//
#ifndef mRichSteppingAction_h
#define mRichSteppingAction_h 1

#include "mRichRunAction.hh"
#include "mRichPrimaryGeneratorAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4VDiscreteProcess.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include <iostream>

class mRichAnalysisManager;

class mRichSteppingAction : public G4UserSteppingAction 
{
  G4int iev;
  
public:
  
  mRichSteppingAction(mRichPrimaryGeneratorAction *gen_action_in, mRichRunAction *run_action_in);
  virtual ~mRichSteppingAction();
  void UserSteppingAction(const G4Step* aStep);
  mRichAnalysisManager* getRAnalysisManager()
  {return  ranalysisManager; }
  G4double getHpdPhElectronKE() 
  {return HpdPhElectronKE; }
  
private:
  std::fstream fOut;
  
  mRichAnalysisManager* ranalysisManager;
  mRichPrimaryGeneratorAction* rPrimGenAction;
  G4double HpdPhElectronKE;
  G4VParticleChange* uParticleChange;
  
  mRichRunAction *run_action;
};
#endif
