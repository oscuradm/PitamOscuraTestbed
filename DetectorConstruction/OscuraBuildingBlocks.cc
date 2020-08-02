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
#include "G4VisAttributes.hh"
#include "G4AssemblyVolume.hh"

#include "G4Transform3D.hh"


OscuraDetectorMaterials::OscuraDetectorMaterials(){

}


OscuraDetectorGeometry::OscuraDetectorGeometry(G4LogicalVolume* lgWorld):OscuraDetectorMaterials(){

    /*NIST Material Manager*/
    nist  = G4NistManager::Instance();

    logicWorld = lgWorld;

}

//CCDs
void OscuraDetectorGeometry::CCD_1kBy6k(double x, double y, double z, G4String CCDName, bool checkOverlaps){


    G4Material* CCD1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    double CCD_length = 17942*um;
    double CCD_width = 94742*um;
    double CCD_thickness = 675*um;

    G4Box* ccdShape1 = new G4Box(CCDName,CCD_length/2.0,CCD_width/2.0,CCD_thickness/2.0);
    G4LogicalVolume* logicCCD1 = new G4LogicalVolume(ccdShape1, CCD1_mat, CCDName);

    G4VisAttributes CCDVisAtt(TolLigMint);
    logicCCD1->SetVisAttributes(CCDVisAtt);

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
void OscuraDetectorGeometry::SiBigShim(double x, double y, double z, double length, double width, double thickness, G4String ShimName, bool checkOverlaps){

    G4Material* SiShim1_mat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    G4Box* SiShimShape1 = new G4Box(ShimName,length/2.0,width/2.0,thickness/2.0);
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

void OscuraDetectorGeometry::ReadoutChipCROC(double x, double y, double z, G4String ChipName, bool checkOverlaps){


    //Create packaged SOIC material which is a combination of Si and Epoxy,
    //Not including the wire used to bond.
    G4Material* readoutChipMat = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);

    double ChipLength = 5*mm;
    double ChipWidth = 5*mm;
    double ChipThickness = 0.5*mm;

    G4Box* readoutChipShape = new G4Box(ChipName,ChipLength/2,ChipWidth/2,ChipThickness/2);
    G4LogicalVolume* logicalVReadoutChip = new G4LogicalVolume(readoutChipShape, readoutChipMat, ChipName);

    G4VisAttributes CROCVisAtt(TolMutPurple);
    logicalVReadoutChip->SetVisAttributes(CROCVisAtt);


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


void OscuraDetectorGeometry::KaptonCableStrip(double x, double y, double z, G4String CableName, G4RotationMatrix Rm){


    //Create packaged SOIC material which is a combination of Si and Epoxy,
    //Not including the wire used to bond.
    G4Material* KaptonMat = nist->FindOrBuildMaterial("G4_KAPTON");
    G4ThreeVector pos1 = G4ThreeVector(x,y,z);


    G4Box* KaptonShapeLong = new G4Box(CableName,12*cm/2,2*cm/2,200*um/2);
    G4String SName = CableName+"_stub";
    G4Box* KaptonShapeStub = new G4Box(SName,4*cm/2,6*cm/2,200*um/2);


    G4LogicalVolume* logicalVKaptonLong = new G4LogicalVolume(KaptonShapeLong, KaptonMat, CableName+"LV");
    G4LogicalVolume* logicalVKaptonStub = new G4LogicalVolume(KaptonShapeStub, KaptonMat, SName+"LV");

    G4VisAttributes KaptonVisAtt(TolVibOrange);
    logicalVKaptonStub->SetVisAttributes(KaptonVisAtt);
    logicalVKaptonLong->SetVisAttributes(KaptonVisAtt);



    G4AssemblyVolume* assemblyKapton = new G4AssemblyVolume();
    //This is for rotation and translation
    G4RotationMatrix Ra; G4ThreeVector Ta;



    //Fill up the assembly volume
    Ta.setX( 0 ); Ta.setY( 0 ); Ta.setZ( 0 );
    G4Transform3D TR =  G4Transform3D(Ra,Ta);
    assemblyKapton->AddPlacedVolume(logicalVKaptonLong, TR);

    Ta.setX( 0 ); Ta.setY( 4*cm ); Ta.setZ( 0 ); TR =  G4Transform3D(Ra,Ta);
    assemblyKapton->AddPlacedVolume(logicalVKaptonStub, TR);


    G4ThreeVector Tm(x,y,z);
    G4Transform3D Ma =  G4Transform3D(Rm,Tm);
    assemblyKapton->MakeImprint(logicWorld, Ma);


}


