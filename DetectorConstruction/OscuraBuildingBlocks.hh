/*Test detector construction by PITAM for G4 Tutorial*/

#ifndef OcsuraBuildingBlocks_h
#define OcsuraBuildingBlocks_h


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"



//Why are these needed?
class G4VPhysicalVolume;
class G4LogicalVolume;


class OscuraDetectorMaterials{

    private:
    public:
            OscuraDetectorMaterials(G4LogicalVolume* );

            G4NistManager* nist;
            //G4Material Kapton

}


class OscuraDetectorGeometry : public OscuraDetectorMaterials {

    //Inits
    OscuraDetectorGeometry(void );

    //CCDs
    void CCD_1kBy6k(double x, double y, double z, G4String CCDName);


    //Si strips
    void SiBigShim(double x, double y, double z, double length, double width, double thickness, G4String ShimName);


    //Chips
    void ReadoutChipCROC(double x, double y, double z, G4String ChipName);

}
#endif
