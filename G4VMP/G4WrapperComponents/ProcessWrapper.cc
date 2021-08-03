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
#include "G4VMP/G4WrapperComponents/ProcessWrapper.hh"

ProcessWrapper::~ProcessWrapper()
{
  
   // Need to see how desctructors of other data members work !!!...
   // ... to avoid potential memory leaks...
   //
   
   // NOTE: no need to call CleanUp() because all those 
   //       "particle changes" should be taken care of by base dtor(s) 
   //       and the dtor of G4VParticleChange cleans up properly;
   //       however, a warning will be given that 
   //       "theListOfSecondaries is not empty"...
   //      ... and we should probably redirect it to the MessageLogger
   //       NOTE: the code itself is under geant4/source/track/src 
}


G4double ProcessWrapper::PostStepGetPhysicalInteractionLength(const G4Track&,
                        	     		                    G4double,
			                                            G4ForceCondition* condition)
{

  *condition = NotForced;
  G4double z = DBL_MAX;

  return z;

}

G4VParticleChange* ProcessWrapper::PostStepDoIt( const G4Track& track, const G4Step& step )
{

   // See note/comment(s) in the code of CleanUp 
   //
   CleanUp();
   
   return G4HadronicProcess::PostStepDoIt( track, step );
   
}


void ProcessWrapper::CleanUp()
{

// this has to be done here, i.e. outside of G4VParticleChange,
// because G4VParticleChange::Clear() only resets the counters
// but does NOT empty the container of secondaries;
// moreover, in the header there's even a comment that the list
// of secondaries gets emptied by the tracking/stepping manager(s);
// and if one looks inside G4SteppingManager2.cc code, that's
// exactly how it's done as the G4VParticleChange::GetSecondary(int) 
// returns a NON-const pointer to the G4Track...    
// 
// all in all, the design of G4VParticleChange appears ungly,
// or at least it's not clear what stays behid such approach
//
// so let's try to "hide" it and make a protected method called 
// by PostStepDo it before anything else, because making an app 
// do such cleanup will look even uglier

/*   
   for ( int i=0; i<pParticleChange->GetNumberOfSecondaries(); ++i )
   {
      delete pParticleChange->GetSecondary(i);
   }   
   pParticleChange->Clear();
*/
   
   for ( int i=0; i<theTotalResult->GetNumberOfSecondaries(); ++i )
   {
      delete theTotalResult->GetSecondary(i);
   }
   theTotalResult->Clear();
   
   return;

}
