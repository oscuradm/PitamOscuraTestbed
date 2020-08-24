/* This file defines the sensitivedetector for oscura*/
#include "G4VSensitiveDetector.hh"


#ifndef OscuraSensitiveDet_h
#define OscuraSensitiveDet_h


class G4Step;

class OscuraSensitiveDetector : public G4VSensitiveDetector{


    public:
        OscuraSensitiveDetector(G4String name);
        virtual ~OscuraSensitiveDetector();

        /*At each step this will run*/
        virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);

};

#endif
