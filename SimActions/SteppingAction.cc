/* G4UserSteppingAction is used to specify actions taken at each step
 * of the simulation
 */

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "PitamDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

SteppingAction::SteppingAction(EventAction* _eventAction):G4UserSteppingAction(),fEventAction(_eventAction),fScoringVolume(0){
}

SteppingAction::~SteppingAction(){
}


void SteppingAction::UserSteppingAction(const G4Step* step){


    if (!fScoringVolume){

        const PitamDetectorConstruction* detectorConstruction = static_cast<const PitamDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
    }


    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

    if (volume != fScoringVolume) return;


    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);
}

