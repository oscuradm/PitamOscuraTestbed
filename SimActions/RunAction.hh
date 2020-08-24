/* G4UserRunAction is used to specify actions taken at Begin and end of the run
 * of the simulation
 */

#ifndef RunAction_h
#define RunAction_h 1



#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"

class G4Run;
class PrimaryGeneratorAction;
class OSimDetectorConstruction;


/* As an example, we will use EndOfRunAction() to calculate dose in a selected volume
 * via stepping and event actions
 */

class PitamRunAction : public G4UserRunAction
{
    public:
        PitamRunAction(OSimDetectorConstruction* det, PrimaryGeneratorAction* prim);
        virtual ~PitamRunAction();

        //virtual G4Run* GenerateRun();
        virtual void BeginOfRunAction(const G4Run* );
        virtual void EndOfRunAction(const G4Run* );

        void AddEdep (G4double edep);


    private:
        G4Accumulable<G4double> fEdep;
        G4Accumulable<G4double> fEdep2;

        OSimDetectorConstruction*      fDetector;
        PrimaryGeneratorAction*    fPrimary;

        G4ParticleDefinition* fParticle;
        G4double              fEkin;



};


#endif
