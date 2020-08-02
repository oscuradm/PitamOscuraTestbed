/* G4UserSteppingAction is used to specify actions taken at each step
 * of the simulation
 */

#ifndef SimGlobalSettings_h
#define SimGlobalSettings_h

#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"


/*World shape and size*/
static const double worldDimension = 500*mm;



/*Default units for simulation*/


/*Colours pleasing to the eye*/


// Bright color scheme
static const G4Colour TolBriBlue(68./255, 119./255, 170./255);
static const G4Colour TolBriCyan(102./255, 204./255, 238./255);
static const G4Colour TolBriGreen(34./255, 136./255,  51./255);
static const G4Colour TolBriYellow(204./255, 187./255,  68./255);
static const G4Colour TolBriRed(238./255, 102./255, 119./255);
static const G4Colour TolBriPurple(170./255,  51./255, 119./255);
static const G4Colour TolBriGrey(187./255, 187./255, 187./255);

// Vibrant color scheme
static const G4Colour TolVibBlue(0./255, 119./255, 187./255);
static const G4Colour TolVibCyan(51./255, 187./255, 238./255);
static const G4Colour TolVibTeal(0./255, 153./255, 136./255);
static const G4Colour TolVibOrange(238./255, 119./255,  51./255);
static const G4Colour TolVibRed(204./255,  51./255,  17./255);
static const G4Colour TolVibMagenta(238./255,  51./255, 119./255);
static const G4Colour TolVibGrey(187./255, 187./255, 187./255);

// Muted color scheme
static const G4Colour TolMutIndigo(51./255,  34./255, 136./255);
static const G4Colour TolMutCyan(136./255, 204./255, 238./255);
static const G4Colour TolMutTeal(68./255, 170./255, 153./255);
static const G4Colour TolMutGreen(17./255, 119./255,  51./255);
static const G4Colour TolMutOlive(153./255, 153./255,  51./255);
static const G4Colour TolMutSand(221./255, 204./255, 119./255);
static const G4Colour TolMutRose(204./255, 102./255, 119./255);
static const G4Colour TolMutWine(136./255,  34./255,  85./255);
static const G4Colour TolMutPurple(170./255,  68./255, 153./255);
static const G4Colour TolMutPaleGrey(221./255, 221./255, 221./255);

// Light color scheme
static const G4Colour TolLigLightBlue(119./255, 170./255, 221./255);
static const G4Colour TolLigLightCyan(153./255, 221./255, 255./255);
static const G4Colour TolLigMint(68./255, 187./255, 153./255);
static const G4Colour TolLigPear(187./255, 204./255,  51./255);
static const G4Colour TolLigOlive(170./255, 170./255,   0./255);
static const G4Colour TolLigLightYellow(238./255, 221./255, 136./255);
static const G4Colour TolLigOrange(238./255, 136./255, 102./255);
static const G4Colour TolLigPink(255./255, 170./255, 187./255);
static const G4Colour TolLigPaleGrey(221./255, 221./255, 221./255);

//static const G4Colour TolBadData(255./255, 238./255, 153./255);


#endif
