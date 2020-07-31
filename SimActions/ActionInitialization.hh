/*G4VUserActionInitialization        takes care of the user initializations
 *See Lucciano's talk at TRISEP
 */

 #ifndef ActionInit
 #define ActionInit

#include "G4VUserActionInitialization.hh"


 class ActionInitialization : public G4VUserActionInitialization{


    public:
        ActionInitialization();
        virtual ~ActionInitialization();

        virtual void BuildForMaster() const;
        virtual void Build() const;
 };

 #endif
