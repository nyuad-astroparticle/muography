#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02DetectorConstruction.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "CLHEP/Units/SystemOfUnits.h"

ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction(ExN02DetectorConstruction* myDC) : myDetector(myDC)
{
    particleGun = new G4GeneralParticleSource();
}

ExN02PrimaryGeneratorAction::~ExN02PrimaryGeneratorAction()
{
    delete particleGun;
    // delete myDetector;
}

void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    particleGun->GeneratePrimaryVertex(anEvent);
}
