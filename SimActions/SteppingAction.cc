/* G4UserSteppingAction is used to specify actions taken at each step
 * of the simulation
 */

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "OSimDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "OscuraAnalysis.hh"

SteppingAction::SteppingAction(OSimDetectorConstruction* det, EventAction* _eventAction):G4UserSteppingAction(),fDetector(det),fEventAction(_eventAction),fScoringVolume(0){
}

SteppingAction::~SteppingAction(){
}


void SteppingAction::UserSteppingAction(const G4Step* step){


    if (!fScoringVolume){

        const OSimDetectorConstruction* detectorConstruction = static_cast<const OSimDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detectorConstruction->GetScoringVolume();
    }


    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

    if (volume != fScoringVolume) return;


    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);

    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //G4int id=2;
    //analysisManager->FillNtupleDColumn(id,0, edepStep);

}

