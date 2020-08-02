/* G4UserRunAction is used to specify actions taken at Begin and end of the run
 * of the simulation
 */

#include "RunAction.hh"
#include "PrimaryGenerator.hh"
#include "OSimDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


PitamRunAction::PitamRunAction() :G4UserRunAction(),fEdep(0.), fEdep2(0.) {


    // add new units for dose
  //
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;
  const G4double picogray  = 1.e-12*gray;

  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);


}

PitamRunAction::~PitamRunAction(){
}

void PitamRunAction::BeginOfRunAction(const G4Run* run)
{

    //save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    //reset accumulables to initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();



}

void PitamRunAction::EndOfRunAction(const G4Run* run)
{

    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents==0) return;

    // Compute dose = total energy deposit in a run and its variance
    //
    G4double edep  = fEdep.GetValue();
    G4double edep2 = fEdep2.GetValue();

    G4double rms = edep2 - edep*edep/nofEvents;
    if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;


    const OSimDetectorConstruction* detectorConstruction = static_cast<const OSimDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    G4double mass = detectorConstruction->GetScoringVolume()->GetMass();
    G4double dose = edep/mass;
    G4double rmsDose = rms/mass;


    const PrimaryGeneratorAction* generatorAction = static_cast<const PrimaryGeneratorAction*>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    G4String runCondition;
    if (generatorAction)
    {
        const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
        runCondition += particleGun->GetParticleDefinition()->GetParticleName();
        runCondition += " of ";
        G4double particleEnergy = particleGun->GetParticleEnergy();
        runCondition+= G4BestUnit(particleEnergy, "Energy");
    }

    if (IsMaster())
    {
        G4cout
                << G4endl
                << "--------------------End of Global Run-----------------------";
    }
    else
    {
        G4cout
                << G4endl
                << "--------------------End of Local Run------------------------";
    }

    G4cout
            << G4endl
            << " The run consists of " << nofEvents << " "<< runCondition
            << G4endl
            << " Cumulated dose per run, in scoring volume : "
            << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
            << G4endl
            << "------------------------------------------------------------"
            << G4endl
            << G4endl;
}

void PitamRunAction::AddEdep(G4double edep){

    fEdep += edep;
    fEdep2 += edep*edep;
}
