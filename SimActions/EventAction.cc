/* G4UserEventAction dictates actions at Begin and end of an event*/

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "OscuraAnalysis.hh"

#include "OscuraHits.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"


EventAction::EventAction(PitamRunAction* runAction) : G4UserEventAction(), fRunAction(runAction), fEdep(0.)
{

  hitsCollID = -1;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;

    G4SDManager * SDman = G4SDManager::GetSDMpointer();
    if(hitsCollID<0)
    {
        G4String colNam;
        hitsCollID = SDman->GetCollectionID("hitsCollection");
    }

}

void EventAction::EndOfEventAction(const G4Event* evt )
{

    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //analysisManager->FillH1(0,fEdep);


    fRunAction->AddEdep(fEdep);

    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();



//    OscuraHitsCollection* HC = 0;
//
//    if(HCE)
//    {
//        HC = (OscuraHitsCollection*)(HCE->GetHC(hitsCollID));
//    }
//
//
//    if ( HC )
//    {
//        int n_hit = HC->entries();
//        for ( int i = 0 ; i < n_hit; i++)
//        {
//
//            G4double      energy   = (*HC)[i]->GetEnergy();
//
//            G4int         pid      = (*HC)[i]->GetParticle()->GetPDGEncoding();
//            G4double      eDep   = (*HC)[i]->GetEdep();
//
//
//
//            G4cout << "---- Hit # " << i << G4endl;
//
//            G4cout << " Energy   " <<  energy/keV   << " [keV] " <<G4endl;
//            G4cout << " EDep   " <<  eDep  << " eV " <<G4endl;
//            G4cout << " PID      " <<  pid << G4endl;
//
//        }
//
//    }
}
