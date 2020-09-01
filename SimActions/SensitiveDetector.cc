/* This file defines the sensitivedetector for oscura*/


#include "SensitiveDetector.hh"
#include "G4StepPoint.hh"
#include "OscuraAnalysis.hh"
#include <iostream>
#include "OscuraHits.hh"

OscuraSensitiveDetector::OscuraSensitiveDetector(G4String& name) : G4VSensitiveDetector(name)
{

    G4String HCname;
    collectionName.insert("hitsCollection");
    HCID = -1;

}

OscuraSensitiveDetector::~OscuraSensitiveDetector() {}

void OscuraSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{

    //Hit = new OscuraHit();

    hitsCollection = new OscuraHitsCollection(GetName(),collectionName[0]);

    if(HCID<0)
    {
        HCID = GetCollectionID(0);
    }
    HCE->AddHitsCollection(HCID,hitsCollection);
}

void OscuraSensitiveDetector::EndOfEvent()
{
}



G4bool OscuraSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{

    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4StepPoint* postStep = aStep->GetPostStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());



    G4double eDeposit = aStep->GetTotalEnergyDeposit();
    //Hit->Add(eDeposit, 10);

    //G4cout<<"EDeposit : "<<eDeposit<<" in this step\n";

    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //analysisManager->FillH1(0,eDeposit);


    OscuraHit* newHit = new OscuraHit();

    newHit->SetEnergy( aStep->GetPreStepPoint()->GetTotalEnergy() );
    newHit->SetParticle( aStep->GetTrack()->GetDefinition() );
    newHit->Add(eDeposit, 10);

    hitsCollection->insert( newHit );

    return 1;

}
