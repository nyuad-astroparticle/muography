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
// $Id: ExN02DetectorConstruction.hh,v 1.10 2008/09/22 16:41:20 maire Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02DetectorConstruction_h
#define ExN02DetectorConstruction_h 

// #include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "ExN02MagneticField.hh"
#include "G4SystemOfUnits.hh"

class G4Box;
class G4Trd;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4PVPlacement;
//class G4VPVParameterisation;
class G4PVDivision;
class G4PVReplica;
class G4UserLimits;
class ExN02DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
     ExN02DetectorConstruction();
    ~ExN02DetectorConstruction();

  public:
  
     G4VPhysicalVolume* Construct();
     
     const 
     G4VPhysicalVolume* GetTracker() {return physiTracker;};
     G4double GetTrackerFullLength() {return fTrackerLength;};
     G4double GetWorldFullLength()   {return fWorldLength;}; 
     
     void setChamberMaterial(G4String);
     void SetMagField(G4double);
     void SetMaxStep (G4double);     
     
  private:

     G4Box*             solidWorld;    // pointer to the solid envelope 
     G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
     G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope
 
     G4Box*             solidTracker;  // pointer to the solid Tracker
     G4LogicalVolume*   logicTracker;  // pointer to the logical Tracker
     G4VPhysicalVolume* physiTracker;  // pointer to the physical Tracker
     
     G4Trd*             solidbar1;  // pointer to the solid Chamber
     G4LogicalVolume*   logicbar1;  // pointer to the logical Chamber
     G4VPhysicalVolume* physicbar1;  // pointer to the physical Chamber

     G4Trd*             solidbar2;  // pointer to the solid Chamber
     G4LogicalVolume*   logicbar2;  // pointer to the logical Chamber
     G4VPhysicalVolume* physicbar2;  // pointer to the physical Chamber
     G4VPhysicalVolume* physicbar3;  // pointer to the physical Chamber
     G4VPhysicalVolume* physicbar4;  // pointer to the physical Chamber

  
     G4Box*             solidStrip;    // pointer to the solid Strip            
     G4LogicalVolume*   logicStrip;    // pointer to the logical Strip 
     G4VPhysicalVolume* physiStrip;    // pointer to the physical Strip      
  
     G4Box*             solidPixel;    // pointer to the solid Pixel
     G4LogicalVolume*   logicPixel;    // pointer to the logical Pixel
     G4VPhysicalVolume* physiPixel;    // pointer to the physical Pixel

     G4Material*         ChamberMater; // pointer to the chamber material

  //     G4VPVParameterisation* chamberParam; // pointer to chamber parameterisation
     G4UserLimits* stepLimit;             // pointer to user step limits

     ExN02MagneticField* fpMagField;   // pointer to the magnetic field 
     
     ExN02DetectorMessenger* detectorMessenger;  // pointer to the Messenger
       
     G4double fWorldLength;            // Full length of the world volume
     G4double fTrackerLength;          // Full length of Tracker
     G4int    NbOfChambers;            // Nb of chambers in the tracker region
     G4double ChamberWidth;            // width of the chambers
     G4double ChamberSpacing;	       // distance between chambers
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
