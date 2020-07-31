/*G4VUserActionInitialization        takes care of the user initializations
 *See Lucciano's talk at TRISEP
 */


#include "ActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"



 ActionInitialization::ActionInitialization():G4VUserActionInitialization(){
 }

 ActionInitialization::~ActionInitialization(){
 }


 void ActionInitialization::BuildForMaster() const {

    PitamRunAction* _runAction = new PitamRunAction;
    SetUserAction(_runAction);
 }


void ActionInitialization::Build() const {

    SetUserAction(new PrimaryGeneratorAction);

    PitamRunAction* _runAction = new PitamRunAction;
    SetUserAction(_runAction);

    EventAction* _eventAction = new EventAction(_runAction);
    SetUserAction(_eventAction);

    SetUserAction(new SteppingAction(_eventAction));




}
