/* G4VUserPrimaryGeneratorAction is the class controlling the particle gun.
 * It controls particle type, energy, position, momentum, polarization etc.
 *
 * This class should NOT generate primaries itself but invoke GeneratePrimaryVertex()method of the selected primary generator(s) to make primaries.
 * G4VPrimaryGenerator class provides the primary particle generator
 */

#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh



#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {


    public:
        PrimaryGeneratorAction();
        virtual ~PrimaryGeneratorAction();

        virtual void GeneratePrimaries(G4Event *);

        //for access
        const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    private:
        G4ParticleGun* fParticleGun;
        G4Box* fEnvelopeBox;

};


#endif
