// 2/2/2017 hexc & Ping
// Primary generator
//
// 11/28/2020 hexc
//    Changed particle launching point from
//       particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm ,-11.0*cm));
//    to
//       particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm ,-13.0*cm));

#include "mRichPrimaryGeneratorAction.hh"
#include "mRichPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "g4root.hh"

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichPrimaryGeneratorAction::mRichPrimaryGeneratorAction(mRichRunAction* run_action_in)
  :run_action(run_action_in)
{
  particleGun = new G4ParticleGun();
  
  //create a messenger for this class
  gunMessenger = new mRichPrimaryGeneratorMessenger(this);
  
  // default event type to generate. Possible options are: 0, 1, 2, 3, 4 and 5
  ev_type = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

mRichPrimaryGeneratorAction::~mRichPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//===========================================================================

void mRichPrimaryGeneratorAction::SetOptPhotonPolar()
{
  G4double angle = G4UniformRand() * 360.0*deg;
  SetOptPhotonPolar(angle);
}

//===========================================================================

void mRichPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
  if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
    {
      G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
	"the particleGun is not an opticalphoton" << G4endl;
      return;
    }
  
  G4ThreeVector normal (1., 0., 0.);
  G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
  G4ThreeVector product = normal.cross(kphoton); 
  G4double modul2       = product*product;
  
  G4ThreeVector e_perpend (0., 0., 1.);
  if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
  G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
  
  G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
  particleGun->SetParticlePolarization(polar);
}

//===========================================================================

void mRichPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleDefinition* particle;
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //particleTable ->DumpTable("ALL");
  
  
  particleGun->SetParticleTime(0.0*ns);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  
  // G4int ev_type = 4;  // 3=parallel rays (turn off agel).   4-ring (turn agel on).
  G4double Ekin;

  if (ev_type == 0) {
    particleGun->GeneratePrimaryVertex(anEvent);
  }
  
  // 2 muons, 1 GeV  ======================================================================
  if (ev_type == 1) {            
    particle = particleTable->FindParticle("mu+");
    particleGun->SetParticleDefinition(particle);
    
    G4double momentum = 1000.*MeV;
    G4double sigmaMomentum = 0.*MeV;
    G4double sigmaAngle = 0.*deg;
    
    G4double pp = momentum + (G4UniformRand()-0.5)*sigmaMomentum;
    G4double mass = particle->GetPDGMass();
    Ekin = std::sqrt(pp*pp+mass*mass)-mass;
    particleGun->SetParticleEnergy(Ekin);
    
    G4double angle = (G4UniformRand()-0.5)*sigmaAngle;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle),0.,std::cos(angle)));
    
    G4int nparticles=2;
    G4double sigmayy = 6.0*cm;
    G4double yy;
    for (G4int i=1; i<=nparticles; i++) {
      yy = 2.0*cm + (G4UniformRand()-0.5)*sigmayy;
      particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, yy ,-13.0*cm));
      particleGun->GeneratePrimaryVertex(anEvent);
    }
  }    // ev_type=1

  // x,y=0, sweep over wavelengths 200-600 nm  ====================================================  
  if (ev_type == 2) {     
    G4int nbins=10000;    //                                                  study spectra
    particle = particleTable->FindParticle("opticalphoton");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
    particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm ,-11.0*cm));
    for (G4int i=1; i<nbins; i++) {
      Ekin = ( 1.7+(4.8-1.7)*G4UniformRand() )*eV;   // 1.7-4.8eV ~= 200-600 nm
      particleGun->SetParticleEnergy(Ekin);
      particleGun->GeneratePrimaryVertex(anEvent);
    }   // end loop over wavelengths at fixed position
  }     // end ev_type=2
  
  // fixed wavelength, x=0, sweep over y =========================================================
  if (ev_type == 3) {     
    G4int nbins=100;    //                                                  study focusing
    particle = particleTable->FindParticle("opticalphoton");
    particleGun->SetParticleDefinition(particle);
    //    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));
    //    particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0.1737, 0.9848));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    Ekin = 3.2*eV;   // ~400 nm
    particleGun->SetParticleEnergy(Ekin);
    
    for (G4int i=1; i<nbins; i++) {
      G4double angle = G4UniformRand()*360.0*deg;
      SetOptPhotonPolar(angle);
      G4double yrand = (G4UniformRand()-0.5)*8.0*cm;
      particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, yrand ,-9.5*cm));
      particleGun->GeneratePrimaryVertex(anEvent);
    }   // end loop over wavelengths at fixed position
  }
  
  // 10 muons, 5 GeV at x,y = (0,0) ===================================================================
  if (ev_type == 4) {            
    particle = particleTable->FindParticle("mu+");
    particleGun->SetParticleDefinition(particle);
    
    G4double momentum = 5000.*MeV;
    G4double sigmaMomentum = 0.*MeV;
    G4double sigmaAngle = 0.*deg;
    G4double pp = momentum + (G4UniformRand()-0.5)*sigmaMomentum;
    G4double mass = particle->GetPDGMass();
    Ekin = std::sqrt(pp*pp+mass*mass)-mass;
    particleGun->SetParticleEnergy(Ekin);
    G4double angle = (G4UniformRand()-0.5)*sigmaAngle;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));     // straight
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.139,0.990));    // 8 degrees
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.208,0.978));    // 12 degrees
    //particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0.309,0.951));    // 18 degrees
    G4int npart = 1;
    for (G4int i=1; i<=npart; i++) {
      //      if (i<=npart)particleGun->SetParticlePosition(G4ThreeVector(0.01*cm, 3.01*cm ,-11.0*cm));
      particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm ,-13.0*cm));
      particleGun->GeneratePrimaryVertex(anEvent);
    }
    
  }    // ev_type=4
  

  // 10,000 pi-, 3-15GeV at (x,y,z)=(0,0,-13)cm  ====================================================
  if(ev_type == 5) {                  
    particle = particleTable->FindParticle("pi-");
    particleGun->SetParticleDefinition(particle);
    
    G4double momentum = 300.*MeV;
    G4double sigmaMomentum = 10000.*MeV;

    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1.0));     // straight
    G4double mass = particle->GetPDGMass();

    G4double sigmaAngle = 0.*deg;
    G4double angle = (G4UniformRand()-0.5)*sigmaAngle;
    
    G4int npart = 1000;
    for (G4int i=1; i<=npart; i++) {
      G4double pp = momentum + G4UniformRand()*sigmaMomentum;  // 0 GeV < pp << 15 GeV    
      Ekin = std::sqrt(pp*pp+mass*mass) - mass;
      particleGun->SetParticleEnergy(Ekin);
      //      if (i<=npart)particleGun->SetParticlePosition(G4ThreeVector(0.01*cm, 3.01*cm ,-11.0*cm));
      particleGun->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm ,-13.0*cm));
      particleGun->GeneratePrimaryVertex(anEvent);
    } //end of i loop
  }//end of ev_type 5
  

  // find and set the primary particle position and momentum 
  G4int primID = particleGun->GetParticleDefinition()->GetPDGEncoding();
  G4double primP_mass = particleGun->GetParticleDefinition()->GetPDGMass();
  G4double eP =  particleGun->GetParticleEnergy();
  
  G4ThreeVector primP_pos = particleGun->GetParticlePosition();
  G4ThreeVector primP_mom =  sqrt(eP*eP - primP_mass*primP_mass) * particleGun->GetParticleMomentumDirection();

  G4double xP = primP_pos.getX();
  G4double yP = primP_pos.getY();
  G4double zP = primP_pos.getZ();
  
  G4double pxP = primP_mom.getX();
  G4double pyP = primP_mom.getY();
  G4double pzP = primP_mom.getZ();


  // find and set event ID
  evtID = anEvent->GetEventID();

  G4cout << "evtID = " << evtID << "   pzP: " << pzP << "  eP: " << eP << G4endl;
    
  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  // fill ntuple (ntuple ID = 3)
  int itree=3;
  analysisManager->FillNtupleDColumn(itree, 0, primID);
  analysisManager->FillNtupleDColumn(itree, 1, eP/MeV);
  analysisManager->FillNtupleDColumn(itree, 2, xP/cm);
  analysisManager->FillNtupleDColumn(itree, 3, yP/cm);
  analysisManager->FillNtupleDColumn(itree, 4, zP/cm);
  analysisManager->FillNtupleDColumn(itree, 5, pxP/MeV);
  analysisManager->FillNtupleDColumn(itree, 6, pyP/MeV);
  analysisManager->FillNtupleDColumn(itree, 7, pzP/MeV);
  analysisManager->FillNtupleDColumn(itree, 8, evtID);

  analysisManager->AddNtupleRow(itree);
  
}
