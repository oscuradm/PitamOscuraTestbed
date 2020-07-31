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
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction():G4VUserPrimaryGeneratorAction(),fParticleGun(0),fEnvelopeBox(0)
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //kinematics
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName="gamma");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.1*G4UniformRand(),0.1*G4UniformRand(),1.));
    fParticleGun->SetParticleEnergy(5.*MeV);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

    G4double envSizeXY = 0;
    G4double envSizeZ = 0;

    G4double _size=0.8;
    G4double x0 = _size * envSizeXY * (G4UniformRand()-0.5);
    G4double y0 = _size * envSizeXY * (G4UniformRand()-0.5);
    G4double z0 = -0.5 * envSizeZ;

    //Starting particles are randomly placed!!
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

