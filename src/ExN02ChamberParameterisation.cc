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
// $Id: ExN02ChamberParameterisation.cc,v 1.9 2006/06/29 17:47:58 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02ChamberParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02ChamberParameterisation::ExN02ChamberParameterisation(  
        G4int    NoChambers, 
        G4double startZ,          //  Z of center of first 
        G4double spacingZ,        //  Z spacing of centers
        G4double widthChamber, 
        G4double lengthInitial, 
        G4double lengthFinal )
{
   fNoChambers =  NoChambers; 
   fStartZ     =  startZ; 
   fHalfWidth  =  widthChamber*0.5;
   fSpacing    =  spacingZ;
   fHalfLengthFirst = 0.5 * lengthInitial; 
   // fHalfLengthLast = lengthFinal;
   if( NoChambers > 0 ){
      fHalfLengthIncr =  0.5 * (lengthFinal-lengthInitial)/NoChambers;
      if (spacingZ < widthChamber) {
       //G4Exception("ExN02ChamberParameterisation construction: Width>Spacing"); // 4.9.0
       G4Exception("ExN02ChamberParameterisation::ExN02ChamberParameterisation()", // 4.9.5 -- Gianmarco
                   "InvalidSetup", FatalException,
                   "Width>Spacing");
      }
   }
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02ChamberParameterisation::~ExN02ChamberParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02ChamberParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  G4double      Zposition= fStartZ + (copyNo+1) * fSpacing;
  G4ThreeVector origin(0,0,Zposition);//                        implement staggering here  --  Gianmarco
  G4ThreeVector origin1(-8*mm,-8*mm,Zposition);
  G4ThreeVector origin2(-16*mm,-16*mm,Zposition);
  G4ThreeVector origin3(-24*mm,-24*mm,Zposition);
  G4ThreeVector origin4(-32*mm,-32*mm,Zposition);
  G4ThreeVector origin5(-40*mm,-40*mm,Zposition);
  G4ThreeVector origin6(-30*mm,-30*mm,Zposition);
  G4ThreeVector origin7(-20*mm,-20*mm,Zposition);
  G4ThreeVector origin8(-10*mm,-10*mm,Zposition);
  G4ThreeVector origin9(0,0,Zposition);
  
  physVol->SetTranslation(origin);
  if(copyNo == 1) physVol->SetTranslation(origin1);
  if(copyNo == 2) physVol->SetTranslation(origin2);
  if(copyNo == 3) physVol->SetTranslation(origin3);
  if(copyNo == 4) physVol->SetTranslation(origin4);
  if(copyNo == 5) physVol->SetTranslation(origin5);
  if(copyNo == 6) physVol->SetTranslation(origin6);
  if(copyNo == 7) physVol->SetTranslation(origin7);
  if(copyNo == 8) physVol->SetTranslation(origin8);
  if(copyNo == 9) physVol->SetTranslation(origin9);

  physVol->SetRotation(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02ChamberParameterisation::ComputeDimensions
(G4Box& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
  G4double  halfLength= fHalfLengthFirst + copyNo * fHalfLengthIncr;
  trackerChamber.SetXHalfLength(halfLength);
  trackerChamber.SetYHalfLength(halfLength);
  trackerChamber.SetZHalfLength(fHalfWidth);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
