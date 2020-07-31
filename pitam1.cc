/* GEANT4 tutorial example - pitam */


/*Detector construction goes here*/
#include "PitamDetectorConstruction.hh"
#include "ActionInitialization.hh"

/*Run manager goes here*/
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif


/*Next is physics list
 *using QBBC Physics list
 *https://indico.cern.ch/event/3190/contributions/737939/attachments/613720/844379/QBBC.pdf
 */
#include "QBBC.hh"

/*Visualiation*/
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

/*Random number generator*/
#include "Randomize.hh"


int main(int argc, char** argv){

    /*Detect interactive mode - check what this does later*/
    G4UIExecutive* ui=0;
    if(argc == 1) ui= new G4UIExecutive(argc, argv);

    //You can use G4Random::setTheEngine to choose a random number generator
    //G4Random::setTheEngine(new CLHEP::MTwistEngine) for Mersenne-Twister
    //G4Random maps to CLHEP::HEPRandom
    //See: https://www.zeuthen.desy.de/ILC/geant4/clhep-2.0.4.3/classCLHEP_1_1HepRandom.html

    /*Construct the run manager*/
    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    #else
    G4RunManager* runManager = new G4RunManager;
    #endif // G4MULTITHREADED

    /* ------------------------
     * Simulation description starts here
     * ------------------------
     */

    /* Run manager methods document:
     * http://www.apc.univ-paris7.fr/~franco/g4doxy4.10/html/class_g4_m_t_run_manager.html
     * http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4RunManager.html
     *
     * Also see whats needed: http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/html/GettingStarted/mainProgram.html?highlight=g4mtrunmanager
     */

    /*Detector construction - TODO*/
    runManager->SetUserInitialization(new PitamDetectorConstruction());

    /*Physics list - TODO*/
    G4VModularPhysicsList* physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

     // User action initialization
    runManager->SetUserInitialization(new ActionInitialization());


    /*Visualization - optional*/
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();

    /*User interface*/
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    //check if we are on macro or UI mode and start accordingly
    if (! ui){
        //batch mode
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command+filename);
    } else {
        //interative
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui; //?? here?
    }

    //job termination
    delete visManager;
    delete runManager;

}

