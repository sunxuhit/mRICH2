/// Date created: November, 2020
/// Authors: hexc

#ifndef mRichActionInitialization_h
#define mRichActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class mRichActionInitialization : public G4VUserActionInitialization
{
  public:
    mRichActionInitialization();
    virtual ~mRichActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
