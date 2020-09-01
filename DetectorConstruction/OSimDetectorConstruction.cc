/*Test detector construction by PITAM for G4 Tutorial*/


#include "OSimDetectorConstruction.hh"
#include "OscuraBuildingBlocks.hh"

#include "SimGlobalSettings.hh"
#include "SensitiveDetector.hh"


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
#include "G4SDManager.hh"



//Detector construction class

OSimDetectorConstruction::OSimDetectorConstruction():G4VUserDetectorConstruction(), fScoringVolume(0){ }

OSimDetectorConstruction::~OSimDetectorConstruction()
{ }

G4VPhysicalVolume* OSimDetectorConstruction::Construct(){

    /*First we need the material manager*/
    G4NistManager* nist  = G4NistManager::Instance();

    /*Lets construct the sensitive detector here - we will add LogicalVolumes to it
     *as we construct our detector
     */


    //G4String SDName = "OscuraDetSD";
    //G4VSensitiveDetector* pSensitivePart = new OscuraSensitiveDetector(SDName);
    //G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    //SDMan->AddNewDetector(pSensitivePart);
    //and thats it - set volumes to sensitive by G4VLogicalVolume->SetSensitiveDetector(pSensitivePart) !!

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
    OscuraDetectorGeometry _OSCGeom(logicWorld);

    /*Place th Si Shim*/
    _OSCGeom.SiBigShim(0,0,5*mm,12*cm,12*cm,200*um,"BaseSiPiece", 1);

    /*Place a CCD on it*/
    double _1k6k_length = 17942*um;
    double _1k6k_width = 94742*um;


    double _SiShimThickness = 200*um;
    double _CCDThickness = 675*um;
    double _CCDZPosition = (_SiShimThickness+_CCDThickness);


    std::vector<G4LogicalVolume*> AllCCDLogVols;

    for (int i=0; i<6; i++){
        G4String _CCDModulename = "CCDModule"+std::to_string(i);

        double CCD_x = i*(_1k6k_length+1.5*mm)-6*cm+1.75*mm+_1k6k_length/2.0;
        double CCD_y = 0;

        /*Set a CCD module and mark this as a sensitive detector*/
        G4LogicalVolume* _thisCCDModule = _OSCGeom.CCD_1kBy6k(CCD_x, CCD_y, 5*mm-_CCDZPosition,_CCDModulename,1);
        //_thisCCDModule->SetSensitiveDetector(pSensitivePart);
        AllCCDLogVols.push_back(_thisCCDModule);

        /*Readout chips*/
        G4String ChipName = _CCDModulename+"chip1";
        double ChipPosition_dx = _1k6k_length/2.0-3*mm;

        _OSCGeom.ReadoutChipCROC(CCD_x-ChipPosition_dx, CCD_y + (_1k6k_width/2 + 3*mm), 5*mm-_CCDZPosition, ChipName, 1);
        ChipName = _CCDModulename+"chip2";
        _OSCGeom.ReadoutChipCROC(CCD_x+ChipPosition_dx, CCD_y + (_1k6k_width/2 + 3*mm), 5*mm-_CCDZPosition, ChipName, 1);
        ChipName = _CCDModulename+"chip3";
        _OSCGeom.ReadoutChipCROC(CCD_x-ChipPosition_dx, CCD_y - (_1k6k_width/2 + 3*mm), 5*mm-_CCDZPosition, ChipName, 1);
        ChipName = _CCDModulename+"chip4";
        _OSCGeom.ReadoutChipCROC(CCD_x+ChipPosition_dx, CCD_y - (_1k6k_width/2 + 3*mm), 5*mm-_CCDZPosition, ChipName, 1);

    }



    /*Kapton Cable*/
    G4RotationMatrix Rm;
    _OSCGeom.KaptonCableStrip(0, 7*cm, 5*mm-200*um, "CableU", Rm);
    Rm.rotateZ(180*deg);
    _OSCGeom.KaptonCableStrip(0, -7*cm, 5*mm-200*um, "CableL", Rm);




    /*Place detector*/
    G4Material* CCD1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(0,0,100*mm);

    G4Box* ccdShape1 = new G4Box("ccd1",10*mm,10*mm,675*um);
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
    //fScoringVolume = logicCCD1;
    fScoringVolume = AllCCDLogVols[4];

    //logicCCD1->SetSensitiveDetector(pSensitivePart);


    return physWorld;


}
