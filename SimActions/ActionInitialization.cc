/*G4VUserActionInitialization        takes care of the user initializations
 *See Lucciano's talk at TRISEP
 */


#include "ActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "OSimDetectorConstruction.hh"



 ActionInitialization::ActionInitialization(OSimDetectorConstruction* detector):G4VUserActionInitialization(),fDetector(detector){
 }

 ActionInitialization::~ActionInitialization(){
 }


 void ActionInitialization::BuildForMaster() const {

    PitamRunAction* _runAction = new PitamRunAction(fDetector, 0);
    SetUserAction(_runAction);
 }


void ActionInitialization::Build() const {

    PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
    SetUserAction(primary);
    //SetUserAction(new PrimaryGeneratorAction);

    PitamRunAction* _runAction = new PitamRunAction(fDetector, primary );
    SetUserAction(_runAction);

    //PitamRunAction* _runAction = new PitamRunAction;
    //SetUserAction(_runAction);

    EventAction* _eventAction = new EventAction(_runAction);
    SetUserAction(_eventAction);

    SetUserAction(new SteppingAction(fDetector, _eventAction));




}
