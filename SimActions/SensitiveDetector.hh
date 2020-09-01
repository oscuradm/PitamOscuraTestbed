/* This file defines the sensitivedetector for oscura*/
#include "G4VSensitiveDetector.hh"
#include "OscuraHits.hh"

#ifndef OscuraSensitiveDet_h
#define OscuraSensitiveDet_h


class G4Step;
class G4HCofThisEvent;


class OscuraSensitiveDetector : public G4VSensitiveDetector{


    public:
        OscuraSensitiveDetector(G4String& name);
        virtual ~OscuraSensitiveDetector();

        /*At each step this will run*/
        virtual void   Initialize(G4HCofThisEvent* );
        virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
        virtual void   EndOfEvent();


        int HCID;
        OscuraHitsCollection* hitsCollection;



};

#endif
