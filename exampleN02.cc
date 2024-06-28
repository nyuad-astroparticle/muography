#include "ExN02DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02RunAction.hh"
#include "ExN02EventAction.hh"
#include "ExN02SteppingAction.hh"
#include "ExN02SteppingVerbose.hh"
#include "Randomize.hh"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

using namespace CLHEP;

int main(int argc, char** argv)
{
  // User Verbose output class
  G4VSteppingVerbose* verbosity = new ExN02SteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);

  // Run manager
  G4RunManager* runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  ExN02DetectorConstruction* detector = new ExN02DetectorConstruction;
  runManager->SetUserInitialization(detector);

  G4VUserPhysicsList* physics = new ExN02PhysicsList;
  runManager->SetUserInitialization(physics);

  // User Action classes
  ExN02PrimaryGeneratorAction* gen_action = new ExN02PrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);

  ExN02RunAction* run_action = new ExN02RunAction;
  runManager->SetUserAction(run_action);

  ExN02EventAction* event_action = new ExN02EventAction(run_action, gen_action);
  runManager->SetUserAction(event_action);

  G4UserSteppingAction* stepping_action = new ExN02SteppingAction(run_action, event_action);
  runManager->SetUserAction(stepping_action);

  // Initialize G4 kernel
  runManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  G4UIExecutive* ui = nullptr; // Declare ui outside conditional scope
  G4VisManager* visManager = new G4VisExecutive; 
  visManager->Initialize();

  if (argc != 1) // batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else // interactive mode : define UI session
  {
    ui = new G4UIExecutive(argc, argv);
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
  }

  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not
  // be deleted in the main() program!
  delete ui;
  delete visManager;
  delete runManager;
  delete verbosity;

  return 0;
}
