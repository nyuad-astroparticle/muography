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
// $Id: ExN02DetectorConstruction.cc,v 1.22 2010/01/22 11:57:03 maire Exp $
// GEANT4 tag $Name: geant4-09-04-beta-01 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "ExN02DetectorConstruction.hh"
#include "ExN02DetectorMessenger.hh"
//#include "ExN02ChamberParameterisation.hh"
#include "ExN02MagneticField.hh"
#include "ExN02TrackerSD.hh"

//#include "G4VSensitiveDetector.hh"
#include "G4RotationMatrix.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVDivision.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4ParticleTable.hh"
#include "G4MuonPlus.hh"
#include "G4GeneralParticleSource.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02DetectorConstruction::ExN02DetectorConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 logicStrip(0), logicPixel(0),
 solidTracker(0),logicTracker(0),logicbar2(0),
 physiTracker(0), solidbar1(0), solidbar2(0), solidPixel(0),
 logicbar1(0), physicbar1(0), physicbar2(0), physiPixel(0),
 ChamberMater(0),physicbar3(0),physicbar4(0),
 stepLimit(0), fpMagField(0),
 fWorldLength(0.), fTrackerLength(0.),
 NbOfChambers(0) ,  ChamberWidth(0.),  ChamberSpacing(0.)
{
  fpMagField = new ExN02MagneticField();
  detectorMessenger = new ExN02DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02DetectorConstruction::~ExN02DetectorConstruction()
{
  delete fpMagField;
  delete stepLimit;
  //  delete chamberParam;
  delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* ExN02DetectorConstruction::Construct()
{
//--------- Material definition ---------

  G4double a, z;
  G4double density, temperature, pressure;
  G4int nel,jj,kk;

  //Air
  G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
   
  G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);

  //Lead
  G4Material* Pb = 
  new G4Material("Lead", z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
    
  //Xenon gas
  G4Material* Xenon = 
  new G4Material("XenonGas", z=54., a=131.29*g/mole, density= 5.458*mg/cm3,
                 kStateGas, temperature= 293.15*kelvin, pressure= 1*atmosphere);

  G4Element* H =new G4Element("Hydrogen","H",z=1.,a=1.01*g/mole);
  G4Element* C = new G4Element("Carbon","C", z=6.,a=12.01*g/mole);

  G4Material* sci = new G4Material("Plastic Scintillator",density = 1.050*g/cm3,nel=2);
  sci->AddElement(C,92.26*perCent);
  sci->AddElement(H,7.74*perCent);  /*Polystyrene: C_n H_n*/


  // Print all the materials defined.
  //
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

//--------- Sizes of the principal geometrical components (solids)  ---------
  
  NbOfChambers = 10;
  ChamberWidth = 2 * cm;         // level full thickness gmb
  ChamberSpacing = 7.0 * cm;
 
  fTrackerLength = 160 * cm; // Full length of Tracker
  
  ChamberMater = sci;

  fWorldLength= 5 * m; // 5m - 20m

  G4double trackerSize = 0.5*fTrackerLength;   // Half length of the Tracker
      
//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  //------------------------------ 
  // World
  //------------------------------ 

  G4double HalfWorldLength = 0.5*fWorldLength;
 
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;

  solidWorld= new G4Box("world",HalfWorldLength,HalfWorldLength,HalfWorldLength);
  logicWorld= new G4LogicalVolume( solidWorld, Air, "World", 0, 0, 0);
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 logicWorld,      // its logical volume
				 "World",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0);              // copy number
				 

  //------------------------------ 
  // Tracker
  //------------------------------
  // Example offset parameters
G4double yOffset = 9.5 * cm;
G4double zOffset = 9.5 * cm;

G4ThreeVector positionTracker = G4ThreeVector(0,0,0);
  
  //  solidTracker = new G4Box("tracker",trackerSize,trackerSize,trackerSize);
  //  logicTracker = new G4LogicalVolume(solidTracker , Air, "Tracker",0,0,0);  
  //  physiTracker = new G4PVPlacement(0,              // no rotation
  //				  positionTracker, // at (x,y,z)
  //				  logicTracker,    // its logical volume			//	  
  //				  "Tracker",       // its name
  //				  logicWorld,      // its mother  volume
  //				  false,           // no boolean operations
  //				  0);              // copy number 

  //------------------------------ 
  // Tracker segments
  //------------------------------
  // 
  // An example of Parameterised volumes
  // dummy values for G4Box -- modified by parameterised volume

 G4double GetXHalfLength1 = 20*cm; //2*cm //const;
 G4double GetXHalfLength2 = 0*cm; //0*cm;
 G4double GetYHalfLength1 = 50*cm; //20*cm;
 G4double GetYHalfLength2 = 50*cm; //20*cm;
 G4double GetZHalfLength = 10.732*cm; //1.732*cm; 
    
  solidbar1 = new G4Trd("solidbar1", GetXHalfLength1, GetXHalfLength2, GetYHalfLength1, GetYHalfLength2, GetZHalfLength);
  logicbar1 = new G4LogicalVolume(solidbar1,ChamberMater,"Bar1",0,0,0); 

  //solidbar2 = new G4Trd("solidbar2", 0*cm, 5*cm, 20*cm, 20*cm, 4*cm);
  //logicbar2 = new G4LogicalVolume(solidbar2,ChamberMater,"Bar2",0,0,0);
  
  /*  G4VPhysicalVolume* physicbar2 =   new G4PVPlacement(0,
						G4ThreeVector((jj*10-25)*cm,0,0),
					        logicbar2,
				       	        "physicbar2",
						logicWorld,
					        0,
						2000+jj); */
  


  G4RotationMatrix *rm = new G4RotationMatrix();
  rm->rotateX(180*deg);
  
  G4RotationMatrix *rn = new G4RotationMatrix();
  rn->rotateZ(90*deg);

   G4RotationMatrix *ro = new G4RotationMatrix();
   ro->rotateX(180*deg);
   ro->rotateZ(90*deg);

  G4double shiftDistance = GetXHalfLength1;
  G4double Separation = 1*cm;
  // G4double horizontalShift = 0*cm;
  G4double innerLayerGap = 2*GetZHalfLength+Separation; //4 
  G4double interLayerGap = 4*GetZHalfLength+Separation + 20*cm; //20
  G4double triangleDistance = 2*GetXHalfLength1;
 for(kk =0; kk<2; kk++){
  for(jj =0; jj<2; jj++){

    //  . X-view
    // / \
    //
    G4VPhysicalVolume* physicbar1 = new G4PVPlacement(0,
						G4ThreeVector((jj*triangleDistance-shiftDistance),0 + yOffset,kk*interLayerGap),
					        logicbar1,
				       	        "physicbar1",
						logicWorld,
					        0,
						1000+(2*jj)+100*kk); //CopyNo

    //  _
    // \ /
    //  `
    G4VPhysicalVolume* physicbar2 =   new G4PVPlacement(rm,
						G4ThreeVector((jj*triangleDistance),0+yOffset,kk*interLayerGap),
					        logicbar1,
				       	        "physicbar2",
						logicWorld,
					        0,
						1001+(2*jj)+100*kk);
    //  . Y-view
    // / 
    //
    G4VPhysicalVolume* physicbar3 =   new G4PVPlacement(rn,
						G4ThreeVector(0+yOffset,(jj*triangleDistance-shiftDistance),kk*interLayerGap+innerLayerGap),
					        logicbar1,
				       	        "physicbar3",
						logicWorld,
					        0,
						8000+(2*jj)+100*kk);
    //  _
    // \ /
    //  `
    G4VPhysicalVolume* physicbar4 =   new G4PVPlacement(ro,
						G4ThreeVector(0+yOffset,(jj*triangleDistance), kk*interLayerGap+innerLayerGap),
					        logicbar1,
				       	        "physicbar4",
						logicWorld,
					        0,
						8001+(2*jj)+100*kk);
  }						  
 }
 
  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  //  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //  G4String trackerChamberSDname = "ExN02/TrackerChamberSD";
  //  ExN02TrackerSD* aTrackerSD = new ExN02TrackerSD( trackerChamberSDname );
  //  SDman->AddNewDetector( aTrackerSD );
  
  //logicbar1->SetSensitiveDetector( aTrackerSD );
  //logicbar2->SetSensitiveDetector( aTrackerSD );


//--------- Visualization attributes -------------------------------

  G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,0.0));
  //  logicWorld  ->SetVisAttributes(BoxVisAtt);  
  //logicTracker->SetVisAttributes(BoxVisAtt);
  
  G4VisAttributes* ChamberVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  logicbar1->SetVisAttributes(ChamberVisAtt);

  //G4VisAttributes* ChamberVisAtt2 = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  //logicbar2->SetVisAttributes(ChamberVisAtt2);

  
//--------- example of User Limits -------------------------------

  // below is an example of how to set tracking constraints in a given
  // logical volume(see also in N02PhysicsList how to setup the processes
  // G4StepLimiter or G4UserSpecialCuts).
    
  // Sets a max Step length in the tracker region, with G4StepLimiter
  //
  G4double maxStep = 0.5*ChamberWidth;
  stepLimit = new G4UserLimits(maxStep);
  //logicTracker->SetUserLimits(stepLimit); //pb1

  // Set additional contraints on the track, with G4UserSpecialCuts
  //
  // G4double maxLength = 2*fTrackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //                                               minEkin));
  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02DetectorConstruction::setChamberMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {ChamberMater = pttoMaterial;
      logicbar1->SetMaterial(pttoMaterial);
      //logicbar2->SetMaterial(pttoMaterial);
      G4cout << "\n----> The chambers are " << ChamberWidth/cm << " cm of "
             << materialName << G4endl;
     }             
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02DetectorConstruction::SetMagField(G4double fieldValue)
{
  fpMagField->SetMagFieldValue(fieldValue);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
