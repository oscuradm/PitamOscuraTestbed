/* G4UserSteppingAction is used to specify actions taken at each step
 * of the simulation
 */

#ifndef SimGlobalSettings_h
#define SimGlobalSettings_h

#include "G4SystemOfUnits.hh"

/*Detector shape and size*/
static const double detectorLW = 90*mm;
static const double detectorThickness = 0.675*mm;
/*position of the detector*/
static const double detectorZ = 229*mm;



/*Flange shape and size*/
static const double FlangeThickness = 22.352*mm;
static const double FlangeRadius = 101.219*mm;
/*Position of flange*/
static const double FlangeZ = 10.17*mm; //source 1 mm away from flange


/*World shape and size*/
static const double worldDimension = 500*mm;


/*Viewport shape*/
static const double PortLength = 3*in;
static const double PortThickness = 3*mm;
static const double PortRadiusOD = 6*in;


/*StorageBox Description*/




/*Default units for simulation*/



#endif
