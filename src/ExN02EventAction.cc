//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN02EventAction.cc,v 1.11 2006/06/29 17:48:05 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "ExN02EventAction.hh"
#include "ExN02RunAction.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "TMath.h"
#include "TRandom3.h"
#include "TTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02EventAction::ExN02EventAction(ExN02RunAction* myrun,ExN02PrimaryGeneratorAction* myprimary) : run_action(myrun),gen_action(myprimary)
{
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02EventAction::~ExN02EventAction()
{
  // delete run_action;
  // delete gen_action;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02EventAction::BeginOfEventAction(const G4Event*)
{
  // fired=0;
  // trigA=0;
  // trigB=0;
  // trigC=0;
  // trigger=0;
  // lasthit=50000; //any number greather than 10000
  // hit=0;
  // ll=10;

  // for (int oo=0; oo<200; oo++){
  //   hx[oo]=0;
  //   //hy[oo]=0;
  //   hz[oo]=0;
  // }
  // for (int ooo=0; ooo<10; ooo++){
  //   hpl1[ooo]=0;
  //   hpl8[ooo]=0;
  // }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02EventAction::EndOfEventAction(const G4Event* evt)
{


  // G4int evid = evt->GetEventID();

  // G4double px;
  // G4double py;
  // G4double pz;

  // G4double pxx;
  // G4double pyy;
  // G4double pzz;

  // G4double dx;
  // G4double dy;
  // G4double dz;

  // G4double r2;

  // // get number of stored trajectories
  // //
  // G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  // G4int n_trajectories = 0;

  // if(!run_action->T1->GetBranchStatus("evid"))    run_action->T1->Branch("evid",&evid,"evid/I");
  // if(!run_action->T1->GetBranchStatus("nrgpri"))  run_action->T1->Branch("nrgpri",&nrgpri,"nrgpri/D");
  // if(!run_action->T1->GetBranchStatus("fired"))   run_action->T1->Branch("fired",&fired,"fired/I");
  // if(!run_action->T1->GetBranchStatus("trigger"))   run_action->T1->Branch("trigger",&trigger,"trigger/I");
  // if(!run_action->T1->GetBranchStatus("tetaev"))  run_action->T1->Branch("tetaev",&tetaev,"tetaev/D");
  // if(!run_action->T1->GetBranchStatus("phiev"))  run_action->T1->Branch("phiev",&phiev,"phiev/D");
  // if(!run_action->T1->GetBranchStatus("px"))  run_action->T1->Branch("px",&px,"px/D");
  // if(!run_action->T1->GetBranchStatus("py"))  run_action->T1->Branch("py",&py,"py/D");
  // if(!run_action->T1->GetBranchStatus("pz"))  run_action->T1->Branch("pz",&pz,"pz/D");
  // if(!run_action->T1->GetBranchStatus("dx"))  run_action->T1->Branch("dx",&dx,"dx/D");
  // if(!run_action->T1->GetBranchStatus("dy"))  run_action->T1->Branch("dy",&dy,"dy/D");
  // if(!run_action->T1->GetBranchStatus("dz"))  run_action->T1->Branch("dz",&dz,"dz/D");
  // if(!run_action->T1->GetBranchStatus("hit"))  run_action->T1->Branch("hit",&hit,"hit/I");

  // if(!run_action->T1->GetBranchStatus("hx"))  run_action->T1->Branch("hx",hx,"hx[hit]/I");
  // if(!run_action->T1->GetBranchStatus("hz"))  run_action->T1->Branch("hz",hz,"hz[hit]/I");
  // if(!run_action->T1->GetBranchStatus("ll"))  run_action->T1->Branch("ll",&ll,"ll/I");

  // if(!run_action->T1->GetBranchStatus("hpl1"))  run_action->T1->Branch("hpl1",hpl1,"hpl1[ll]/I");
  // if(!run_action->T1->GetBranchStatus("hpl8"))  run_action->T1->Branch("hpl8",hpl8,"hpl8[ll]/I");
  
  // if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();


  // // periodic printing
  // //
  // if (evid < 100 || evid%100 == 0) {
  //   G4cout << ">>> Event " << evt->GetEventID() << G4endl;
  //   //G4cout << "    " << n_trajectories 
  //   //	   << " trajectories stored in this event." << G4endl;
  // }

  // //if(fired==1)    G4cout << ">>>>>>> detector fired by muon <<<<<<<"<< G4endl;
  // if(trigA==1 && trigB==1 && trigC==1) trigger=1;

  // if(trigger==1){
  //   G4cout << ">>>>>>> this muon has been detected <<<<<<<"<< G4endl;
  //   for(int jj=0; jj<hit; jj++){ //strettamente minore di hit, perche' l'ultimo hit e' 0 0 0
  //     //G4cout << "hit: "<< jj << " "<<hx[jj]<<" " << " Plane: " << hz[jj] <<" hpl1: "<< hpl1[7] <<" "<< ll <<G4endl;
  //   }
  // }
  // nrgpri  = gen_action->getenergy;
  // tetaev    = gen_action->tetadeg;
  // phiev     = gen_action->phideg;
  
  // px  = gen_action->Xstart;
  // py  = gen_action->Ystart;
  // pz  = gen_action->Zstart;

  // //  pxx = gen_action->xx;
  // //  pyy = gen_action->yy;
  // //  pzz = gen_action->zz;
  // //  run_action->p3d->Fill(pxx,pyy,pzz);

  // dx  = gen_action->Xdir;
  // dy  = gen_action->Ydir;
  // dz  = gen_action->Zdir;

  // r2 = px*px+py*py;

  // run_action->hp1->Fill(px);
  // run_action->hp2->Fill(py);
  // run_action->hp3->Fill(pz);

  // run_action->hv1->Fill(dx);
  // run_action->hv2->Fill(dy);
  // run_action->hv3->Fill(dz);

  // //  run_action->hh1->Fill(px,pz);
  // //  run_action->hh2->Fill(py,pz);
  // //  run_action->hh3->Fill(px,py);
 
  // if(fired==1) run_action->T1->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
