/*Test detector construction by PITAM for G4 Tutorial*/

#ifndef DetectorConstruction_h
#define DetectorConstruction_h


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"



//Why are these needed?
class G4VPhysicalVolume;
class G4LogicalVolume;

//Detector construction class

class OSimDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
    PitamDetectorConstruction();
    virtual ~PitamDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume;}


    protected:
        G4LogicalVolume* fScoringVolume;

};



#endif
