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
// $Id: ExN02PrimaryGeneratorAction.cc,v 1.7 2006/06/29 17:48:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
#include <stdio.h>
#include "TFile.h"
#include "TH1.h"
#include "TRandom3.h"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction(ExN02DetectorConstruction* myDC) : myDetector(myDC)
{

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

// default particle

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("mu-");
  
  particleGun->SetParticleDefinition(particle);

  //particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


  //particleGun->SetParticleEnergy(3.0*GeV);

  //getenergy = particleGun->GetParticleEnergy();

  //energy=0.;                     // 
  //while(energy<0.3){             // 
  //  energy=hist->GetRandom();    // 
  //}                              //
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::~ExN02PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double steta;
  G4double mu;
  G4double teta;
  G4double phi;

  G4double pos1;
  G4double pos2;

  particleGun->SetParticleEnergy(30.0*GeV);
  getenergy = particleGun->GetParticleEnergy();

  //_____.....-----'''''-----....._____  

  // G4double position = -0.5*(myDetector->GetWorldFullLength());
  //pos1 = (G4UniformRand()-0.5)*(myDetector->GetWorldFullLength());
  //pos2 = (G4UniformRand()-0.5)*(myDetector->GetWorldFullLength());
  //particleGun->SetParticlePosition(G4ThreeVector(pos1,pos2,0));
  //oggi


  G4double radius  = 0.5*(myDetector->GetWorldFullLength());
  steta  = G4UniformRand();     //steta varia tra 0 e +1
  teta = std::acos(steta);                //teta tra 0 e pi/2
  phi = G4UniformRand();
  phi*=3.1415926;
  phi*=2.0;      //phi estratto tra 0 e 2*pi                                    
  Xstart = radius*std::sin(teta)*std::sin(phi);
  Ystart = radius*std::sin(teta)*std::cos(phi);
  Zstart = radius*std::cos(teta);

  // particleGun->SetParticlePosition(G4ThreeVector(Xstart,Ystart,-1*Zstart+50*cm)); //-1*Zstart + 50*cm -> centro sfera altezza piani trigger
  //particleGun->SetParticlePosition(G4ThreeVector(Xstart,Ystart,-1*Zstart-48*cm));    // The Right One
  //particleGun->SetParticlePosition(G4ThreeVector(0,0,220*cm));    // The Right One

  particleGun->SetParticlePosition(G4ThreeVector(Xstart,Ystart,Zstart+50*cm));


  // __________.....-----'''''~'''''-----.....__________
  // Sampling a Direction from an Isotropic Distribution
  tetadeg =0;

  steta  = G4UniformRand();     // steta varia tra 0 e +1
  mu = 2*steta - 1;             // mu varia tra -1 e +1
  steta  = G4UniformRand();     // steta varia tra 0 e +1
  phi=2*3.1415926*steta;

  Xdir = std::sqrt(1-mu*mu)*std::cos(phi);
  Ydir = std::sqrt(1-mu*mu)*std::sin(phi);
  Zdir = mu;

  G4ThreeVector v(Xdir,Ydir,-1*Zdir); //The Right One
  //G4ThreeVector v(0,0,-1);

  particleGun->SetParticleMomentumDirection(v);
  //G4cout<<"***************** teta: "<< teta << " phi: " << phi << G4endl;
  //  G4cout<<"***************** v: "<< v << G4endl;
  //  G4cout<<"********* norma (v): "<< std::sqrt(Xdir*Xdir+Ydir*Ydir+Zdir*Zdir) << G4endl;


  G4ThreeVector cosdir = particleGun->GetParticleMomentumDirection();
  //G4cout<<"***************** cosdir: "<< cosdir[2] << G4endl;

  tetadeg = std::acos(cosdir[2])/3.14159*180;
  phideg  = std::atan2(cosdir[1],cosdir[0])/3.14159*180;

  //G4cout<<"***************** thets: "<< tetadeg << " phideg: "<< phideg << G4endl;
  xx = 1*m*std::sin(tetadeg*3.14/180)*std::sin(phideg*3.14/180);
  yy = 1*m*std::sin(tetadeg*3.14/180)*std::cos(phideg*3.14/180);
  zz = 1*m*std::cos(tetadeg*3.14/180);

  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
