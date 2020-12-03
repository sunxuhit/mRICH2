// This code is used for EIC detector R&D project

// Date created:  8/6/2014, hexc
// Date updated: 12/4/2014, hexc, Liang, Ping
//               10/22/2015, hexc and Ping
//                  Adding a variable length for the aerogel block
// Date updated: 2/2/2017, hexc, Ping
//    Updated the code for the 2nd mRICH prototype
//
// Date updated: 11/10/2020, hexc
//    Updating the code for new GEANT4 release G4.10.6 and for running in
//    multithreaded mode.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#include "G4RunManager.hh"
//#include "G4UImanager.hh"

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "Randomize.hh"

#include "mRichDetectorConstruction.hh"
// Commented out by HEXC, Nov 20, 2013
//#include "mRichPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "G4PhysListFactory.hh"
#include "G4OpticalPhysics.hh"
//#include "QGSP_BERT.hh"
#include "mRichPrimaryGeneratorAction.hh"
#include "mRichRunAction.hh"
//#include "mRichEventAction.hh"
#include "mRichSteppingAction.hh"
#include "mRichSteppingVerbose.hh"
#include "mRichStackingAction.hh"
#include "mRichAgelTrackingAction.hh"
#include "mRichActionInitialization.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

namespace {
    void PrintUsage() {
      G4cerr << " Usage: " << G4endl;
      G4cerr << " LoopPanel [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
      G4cerr << "   note: -t option is available only for multi-threaded mode."
	     << G4endl;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 7 ) {
    PrintUsage();
    return 1;
  }
  
  
  G4String macro;
  G4String session;
#ifdef G4MULTITHREADED
  G4int nThreads = 3;
#endif
  
  for ( G4int i=1; i<argc; i=i+2 ) {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
#ifdef G4MULTITHREADED
    else if ( G4String(argv[i]) == "-t" ) {
      nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  } 
  
  
  // Detect interactive mode (if no macro provided) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if ( ! macro.size() ) {
    ui = new G4UIExecutive(argc, argv, session);
  }
  
  // Choose the Random engine
  //
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  G4cout << "<<<<<< Running multi-threaded mode.>>>>>>" << G4endl;
  if ( nThreads > 0 ) { 
    runManager->SetNumberOfThreads(nThreads);
  }
#else
  G4RunManager* runManager = new G4RunManager;
  G4cout << "<<<<<<Running single-threaded mode.>>>>>>" << G4endl;
#endif
  
  runManager->SetUserInitialization(new mRichDetectorConstruction);

  // Setting up physics process list
  //
  // Activate necessary physics process, including optical physics processes
  G4PhysListFactory factory;
  G4VModularPhysicsList* phys = NULL;
  G4String physName = "";
  char* path = getenv("PHYSLIST");
  if (path) {
      physName = G4String(path);
  } else {
    //      physName = "FTFP_BERT";  // default
      physName = "QGSP_BERT";  // default
  }
  
  // reference PhysicsList via its name
  if (factory.IsReferencePhysList(physName)) {
    phys = factory.GetReferencePhysList(physName);
  }
  
  //
  // Now add and configure optical physics
  //
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  opticalPhysics->Configure(kCerenkov, true);
  opticalPhysics->Configure(kScintillation, true);  
  opticalPhysics->Configure(kAbsorption, true);
  opticalPhysics->Configure(kRayleigh, true);
  opticalPhysics->Configure(kMieHG, true); 
  opticalPhysics->Configure(kBoundary, true);      
  //opticalPhysics->Configure(kWLS, true);

  //opticalPhysics->SetCerenkovStackPhotons(false);

  // Set control parameters for scintillation
  // Followed from: 
  // https://indico.cern.ch/event/789510/contributions/3279418/attachments/1818134/2972494/AH_OpticalPhotons_slides.pdf
  opticalPhysics->SetScintillationYieldFactor(1.0);
  opticalPhysics->SetScintillationExcitationRatio(0.0);

  // changed from 100 (fiberPanel) to 20 (mRICH)
  opticalPhysics->SetMaxNumPhotonsPerStep(20);
  opticalPhysics->SetMaxBetaChangePerStep(10.0);
  
  phys->RegisterPhysics(opticalPhysics);
  phys->DumpList();
  
  runManager->SetUserInitialization(phys);

  // Set user action initialization
  //
  runManager->SetUserInitialization(new mRichActionInitialization());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
