/* G4UserSteppingAction is used to specify actions taken at each step
 * of the simulation
 */

#ifndef SteppingAction_h
#define SteppingAction_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"


class EventAction;
class G4LogicalVolume;
class OSimDetectorConstruction;


class SteppingAction : public G4UserSteppingAction{

    public:
        SteppingAction(OSimDetectorConstruction* det, EventAction* _eventAction);
        virtual ~SteppingAction();


        virtual void UserSteppingAction(const G4Step*);

    private:
        EventAction* fEventAction;
        G4LogicalVolume* fScoringVolume;
        OSimDetectorConstruction* fDetector;

};


#endif
