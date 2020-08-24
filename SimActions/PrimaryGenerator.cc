/* G4VUserPrimaryGeneratorAction is the class controlling the particle gun.
 * It controls particle type, energy, position, momentum, polarization etc.
 *
 * This class should NOT generate primaries itself but invoke GeneratePrimaryVertex()method of the selected primary generator(s) to make primaries.
 * G4VPrimaryGenerator class provides the primary particle generator
 */

#include "PrimaryGenerator.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():G4VUserPrimaryGeneratorAction(),fParticleGun(0),fEnvelopeBox(0)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //kinematics
    //G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    //G4String particleName;
    //G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
    //fParticleGun->SetParticleDefinition(particle);
    G4double x0 = 0 +3*cm*(G4UniformRand()-0.5);
    G4double y0 = 7*cm+2*cm*(G4UniformRand()-0.5);
    G4double z0 = 5*mm-300*um+100*um*(G4UniformRand()-0.5) ;

    //Starting particles are randomly placed!!
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.1*G4UniformRand(),0.1*G4UniformRand(),1.));
    //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    //fParticleGun->SetParticleEnergy(0.*eV);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    //G4double envSizeXY = 0;
    //G4double envSizeZ = 0;

    //G4double _size=0.8;
    G4double x0 = 0 +3*cm*(G4UniformRand()-0.5);
    G4double y0 = 7*cm+2*cm*(G4UniformRand()-0.5);
    G4double z0 = 5*mm-300*um+100*um*(G4UniformRand()-0.5);

    //Starting particles are randomly placed!!
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    //Radioactive decay
    if (fParticleGun -> GetParticleDefinition() == G4Geantino::Geantino()){

        G4int Z=92, A=238;
        G4double ionCharge = 0.*eplus;
        G4double excitEnergy = 0.*eV;

        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(ionCharge);

    }

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

