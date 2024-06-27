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
// $Id: ExN02RunAction.cc,v 1.9 2006/06/29 17:48:16 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02RunAction.hh"

#include "G4Run.hh"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TROOT.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02RunAction::ExN02RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02RunAction::~ExN02RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  hfile = new TFile("~/GEANT4/N02/myrootfile-tri-30GeV.root","RECREATE","MC data file"); // getting thi error: "TFile LLVM Symbols Exposed"

  //TFile *hfile = new TFile();
  //hfile->SetName("/home/gb115/GEANT4/N02/myrootfile.root");
  //hfile->SetOption("RECREATE");

  T1 = new TTree("T1","G4-ttree t1");

  h1 = new TH1F("h1","hit x-dimension",10,0,9);
  h2 = new TH1F("h2","hit y-dimension",10,0,9);
  h3 = new TH1F("h3","hit z-level",10,0,9);

  hp1 = new TH1F("hp1","position x-dist",100,-5000,5000);
  hp2 = new TH1F("hp2","position y-dist",100,-5000,5000);
  hp3 = new TH1F("hp3","position z-dist",100,-5000,5000);
  hv1 = new TH1F("hv1","Xdir",100,0,1);
  hv2 = new TH1F("hv2","Ydir",100,0,1);
  hv3 = new TH1F("hv3","Zdir",100,0,1);

  //  hh1 = new TH2F("hh1","position xz-dist",100,0,6250000,50,-2500,2500);
  //  hh2 = new TH2F("hh2","position yz-dist",100,0,6250000,50,-2500,2500);
  //  hh3 = new TH2F("hh3","position xy-dist",100,0,6250000,50,-2500,2500);
  //  p3d = new TH3F("p3d","3d SPHERE",25,0,1000,25,-0,1000,25,0,1000);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::EndOfRunAction(const G4Run*)
{ 
  T1->Write();
  h1->Write();
  h2->Write();
  h3->Write();
  hp1->Write();
  hp2->Write();
  hp3->Write();
  hv1->Write();
  hv2->Write();
  hv3->Write();
  //  hh1->Write();
  //  hh2->Write();
  //  hh3->Write();
  //  p3d->Write();
  hfile->Close();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



