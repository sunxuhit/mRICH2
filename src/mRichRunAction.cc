// 2/2/2017, hexc & Ping
// Make this appear first!
#include "G4Timer.hh"

#include "mRichRunAction.hh"

#include "G4Run.hh"
#include "g4root.hh"

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichRunAction::mRichRunAction()
{
  timer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichRunAction::~mRichRunAction()
{
  delete timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichRunAction::BeginOfRunAction(const G4Run* aRun)
{
  int i,j;

  string treeName[3]={"AerogelRICH","Sensor","EventGenerator"};
  int upper[3]={12,9,9};    //number of branches
  string description[3]={"New Particle","all hits", "generated primary particle"};
  string branchName[3][12]={{"pID","kE","x","y","z","px","py","pz","gTime","localTime",
			    "properTime","evtID"},
			    {"pID","kE","x","y","z","px","py","pz","evtID","","",""},
			    {"primID","eP","xP","yP","zP","pxP","pyP","pzP","evtID","","",""}};

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();
  // Book histograms, ntuple
  
  // Create analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in Analysis.hh
  
  G4cout << "##### Get the analysis manager " << "  " << this << G4endl;
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  G4cout << "Using " << analysisManager->GetType() << " analysis manager" << G4endl;
  
  // Create directories 
  
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  
  // Open an output file
  
  G4String fileName = "Agel_output";
  analysisManager->OpenFile(fileName);
  analysisManager->SetFirstNtupleId(1);

  for (i=0;i<3;i++) {
    analysisManager->CreateNtuple(treeName[i].c_str(), description[i].c_str());
    for (j=0;j<upper[i];j++) analysisManager->CreateNtupleDColumn(i+1, branchName[i][j].c_str());
    analysisManager->FinishNtuple(i+1);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void mRichRunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // save histograms 
  
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
