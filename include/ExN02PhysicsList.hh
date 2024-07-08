/************************************
        ╔═╗╦ ╦╦ ╦╔═╗╦╔═╗╔═╗
        ╠═╝╠═╣╚╦╝╚═╗║║  ╚═╗
        ╩  ╩ ╩ ╩ ╚═╝╩╚═╝╚═╝
            ╦  ╦╔═╗╔╦╗     
            ║  ║╚═╗ ║      
            ╩═╝╩╚═╝ ╩      

Define all the physical interactions
needed for the simulation.

Includes Radioactive Decay and some
stuff for correctly releasing energy
in metals.
************************************/

#ifndef ExN02PhysicsList_hh
#define ExN02PhysicsList_hh

// Geant4 Classes that we are using
#include "G4VModularPhysicsList.hh"

class ExN02PhysicsList : public G4VModularPhysicsList
{
    public:
        ExN02PhysicsList();      // Constructor
        ~ExN02PhysicsList();     // Destructor

        void ConstructProcess() override;
};

#endif