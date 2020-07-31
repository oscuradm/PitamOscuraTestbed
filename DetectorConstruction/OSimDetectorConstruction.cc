/*Test detector construction by PITAM for G4 Tutorial*/


#include "PitamDetectorConstruction.hh"
#include "OscuraBuildingBlocks.hh"

#include "SimGlobalSettings.hh"


#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"



//Detector construction class

OSimDetectorConstruction::OSimDetectorConstruction():G4VUserDetectorConstruction(), fScoringVolume(0){ }

OSimDetectorConstruction::~OSimDetectorConstruction()
{ }

G4VPhysicalVolume* OSimDetectorConstruction::Construct(){

    /*First we need the material manager*/
    G4NistManager* nist  = G4NistManager::Instance();

    /*We are skipping the "envelope"*/

    G4bool checkOverlaps = true;

    /*Geant4 detectors need 3 things defined:
     *1. Shape and size -> Solid
     *2. Add properties like material, B/E field, sensitivity -> Logical Volume
     *3. Place it in another volume (one place / repeated) -> Physical volume
     **
     *A unique physical volume which represents the experimental area must exist
     *and fully contains all other components -> The world volume
     */

    //Describe the World Volume
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld = new G4Box("World", worldDimension, worldDimension, worldDimension);

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, //box whose property is being defined
                                                        world_mat, //the material
                                                        "World"); //the name
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, //no rotation
                                                    G4ThreeVector(), //at origin
                                                    "World", //the logical volume being placed
                                                    logicWorld, //the name
                                                    0, //its mother volume
                                                    false, //no boolean operation
                                                    0, //copy number
                                                    checkOverlaps); //check overlap




    /*Oscura building blocks*/
    OscuraDetectorGeometry _OSCGeom = new OscuraDetectorGeometry()
    /*place the flange*/

    G4Material* flange_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4ThreeVector flange_pos = G4ThreeVector(0,0,FlangeZ);

    G4Tubs* FlangeShape1 = new G4Tubs("CryostatFlange",0,FlangeRadius,FlangeThickness,0.0*deg,360.0*deg);
    G4LogicalVolume* logicFlange = new G4LogicalVolume(FlangeShape1, flange_mat, "CryostatFlange");

    new G4PVPlacement (0,
                        flange_pos,
                        logicFlange,
                        "CryostatFlange",
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);


    /*Tube connecting the flange to the body*/
    G4Material* port_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4ThreeVector port_pos = G4ThreeVector(0,0,FlangeThickness);

    G4Tubs* PortShape1 = new G4Tubs("CryostatPort",PortRadiusOD-PortThickness,PortRadiusOD,PortLength,0.0*deg,360.0*deg);
    G4LogicalVolume* logicPort = new G4LogicalVolume(PortShape1, port_mat, "CryostatPort");

    new G4PVPlacement (0,
                        port_pos,
                        logicPort,
                        "CryostatPort",
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);


    /** BOX for the CCD **/





    /*Place detector*/
    G4Material* CCD1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(0,0,detectorZ);

    G4Box* ccdShape1 = new G4Box("ccd1",detectorLW,detectorLW,detectorThickness);
    G4LogicalVolume* logicCCD1 = new G4LogicalVolume(ccdShape1, CCD1_mat, "ccd1");

    new G4PVPlacement (0,
                        pos1,
                        logicCCD1,
                        "ccd1",
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);

    /*Check this*/
    fScoringVolume = logicCCD1;


    return physWorld;


}
