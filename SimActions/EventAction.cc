/* G4UserEventAction dictates actions at Begin and end of an event*/

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(PitamRunAction* runAction) : G4UserEventAction(), fRunAction(runAction), fEdep(0.){
}

EventAction::~EventAction(){
}

void EventAction::BeginOfEventAction(const G4Event*){
    fEdep = 0.;
}

void EventAction::EndOfEventAction(const G4Event* ){

    fRunAction->AddEdep(fEdep);
}
