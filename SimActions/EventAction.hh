/* G4UserEventAction dictates actions at Begin and end of an event*/

#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"
#include "globals.hh"

class PitamRunAction;

class EventAction : public G4UserEventAction{


    public:
        EventAction(PitamRunAction* runActn);
        virtual ~EventAction();

        virtual void BeginOfEventAction(const G4Event* event);
        virtual void EndOfEventAction(const G4Event* event);

        void AddEdep(G4double edep) { fEdep += edep; }

    private:
        PitamRunAction* fRunAction;
        G4double fEdep;

};

#endif
