/* This file defines the sensitivedetector for oscura*/


#include "SensitiveDetector.hh"
#include "G4StepPoint.hh"
#include "OscuraAnalysis.hh"
#include <iostream>

OscuraSensitiveDetector::OscuraSensitiveDetector(G4String name) : G4VSensitiveDetector(name){

}

OscuraSensitiveDetector::~OscuraSensitiveDetector(){}


G4bool OscuraSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist){

    //G4StepPoint* point1 = aStep->GetPreStepPoint();
    //G4StepPoint* point2 = aStep->GetPostStepPoint();


    G4double eDeposit = aStep->GetTotalEnergyDeposit();

    std::cout<<"EDeposit : "<<eDeposit<<" in this step\n";

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0,eDeposit);

    return 1;

}
