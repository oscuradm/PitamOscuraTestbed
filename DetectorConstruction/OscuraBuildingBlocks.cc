/*Test detector construction by PITAM for G4 Tutorial*/


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


OscuraDetectorMaterials::OscuraDetectorMaterials(){

}


OscuraDetectorGeometry::OscuraDetectorGeometry(G4LogicalVolume* lgWorld):OscuraDetectorMaterials(){

    /*NIST Material Manager*/
    nist  = G4NistManager::Instance();

    G4LogicalVolume* logicWorld = lgWorld;

}

//CCDs
void OscuraDetectorGeometry::CCD_1kBy6k(double x, double y, double z, G4String CCDName){


    G4Material* CCD1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    G4Box* ccdShape1 = new G4Box(CCDName,17942*um,94742*um,675*um);
    G4LogicalVolume* logicCCD1 = new G4LogicalVolume(ccdShape1, CCD1_mat, CCDName);

    new G4PVPlacement (0,
                        pos1,
                        logicCCD1,
                        CCDName,
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);


}

//Si shims
void OscuraDetectorGeometry::SiBigShim(double x, double y, double z, double length, double width, double thickness, G4String ShimName){

    G4Material* SiShim1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    G4Box* SiShimShape1 = new G4Box(ShimName,length,width,thickness);
    G4LogicalVolume* logicSiShim1 = new G4LogicalVolume(SiShimShape1, SiShim1_mat, ShimName);

    new G4PVPlacement (0,
                        pos1,
                        logicSiShim1,
                        ShimName,
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);

}


//CROC and other Readout chips

void OscuraDetectorGeometry::ReadoutChipCROC(double x, double y, double z, G4String ChipName){


    //Create packaged SOIC material which is a combination of Si and Epoxy,
    //Not including the wire used to bond.
    G4Material* readoutChipMat = nist->FindOrBuildMaterial("G4_Si");




    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    G4Box* readoutChipShape = new G4Box(ChipName,x,y,z);
    G4LogicalVolume* logicalVReadoutChip = new G4LogicalVolume(readoutChipShape, readoutChipMat, ChipName);

    new G4PVPlacement (0,
                        pos1,
                        logicalVReadoutChip,
                        ChipName,
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);


}


//Kapton cable


void OscuraDetectorGeometry::KaptonCableStrip(double x, double y, double z, G4String CableName){


    //Create packaged SOIC material which is a combination of Si and Epoxy,
    //Not including the wire used to bond.
    G4Material* KaptonMat = nist->FindOrBuildMaterial("G4_KAPTON");


    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    G4Box* KaptonShape = new G4Box(CableName,x,y,z);
    G4LogicalVolume* logicalVKapton = new G4LogicalVolume(KaptonShape, KaptonMat, CableName);

    new G4PVPlacement (0,
                        pos1,
                        logicalVKapton,
                        CableName,
                        logicWorld,
                        false,
                        0,
                        checkOverlaps);


}


