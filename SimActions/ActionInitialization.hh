/*G4VUserActionInitialization        takes care of the user initializations
 *See Lucciano's talk at TRISEP
 */

 #ifndef ActionInit
 #define ActionInit

#include "G4VUserActionInitialization.hh"

class OSimDetectorConstruction;



 class ActionInitialization : public G4VUserActionInitialization{


    public:
        ActionInitialization(OSimDetectorConstruction* detector);
        virtual ~ActionInitialization();

        virtual void BuildForMaster() const;
        virtual void Build() const;

    private:
        OSimDetectorConstruction* fDetector;
 };

 #endif
