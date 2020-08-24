/*Test detector construction by PITAM for G4 Tutorial*/

#ifndef OcsuraBuildingBlocks_h
#define OcsuraBuildingBlocks_h


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "SimGlobalSettings.hh"
#include "G4RotationMatrix.hh"




//Why are these needed?
class G4VPhysicalVolume;
class G4LogicalVolume;


class OscuraDetectorMaterials{

    private:
    public:
            OscuraDetectorMaterials();

            G4NistManager* nist;

            //G4Material Kapton

};


class OscuraDetectorGeometry : public OscuraDetectorMaterials {


    private:

    G4LogicalVolume* logicWorld;

    public:
    //Inits
    OscuraDetectorGeometry(G4LogicalVolume* );


    //CCDs
    G4LogicalVolume* CCD_1kBy6k(double x, double y, double z, G4String CCDName, bool checkOverlaps);


    //Si strips
    void SiBigShim(double x, double y, double z, double length, double width, double thickness, G4String ShimName, bool checkOverlaps);


    //Chips
    void ReadoutChipCROC(double x, double y, double z, G4String ChipName, bool checkOverlaps);

    //Cable
    void KaptonCableStrip(double x, double y, double z, G4String CableName, G4RotationMatrix Rm);

};
#endif
