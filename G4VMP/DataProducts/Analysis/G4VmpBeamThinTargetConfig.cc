
#include <TRootIOCtor.h>

#include "G4VMP/DataProducts/Analysis/G4VmpBeamThinTargetConfig.hh"

#include <cassert>

#include <iostream>


G4VmpBeamThinTargetConfig::G4VmpBeamThinTargetConfig( const int pid, 
                                                      const double m, 
						      const int tid )
   : TNamed()
{

   fBeamPartID   = pid;
   fBeamMomentum = m;
   fTargetID     = tid;

}

G4VmpBeamThinTargetConfig::G4VmpBeamThinTargetConfig( const G4VmpBeamThinTargetConfig& rhs )
   : TNamed(rhs)
{

   fBeamPartID = rhs.fBeamPartID;
   fBeamMomentum = rhs.fBeamMomentum;
   fTargetID = rhs.fTargetID;

}

bool G4VmpBeamThinTargetConfig::operator==( const G4VmpBeamThinTargetConfig& rhs ) const
{

   return ( fBeamPartID==rhs.fBeamPartID && 
            fabs(fBeamMomentum-rhs.fBeamMomentum) < 1.e-10 && 
	    fTargetID==rhs.fTargetID );

}

G4VmpBeamThinTargetConfig::G4VmpBeamThinTargetConfig( TRootIOCtor* )
   : TNamed(), fBeamPartID(0), fBeamMomentum(-1.), fTargetID(0)
{
}

void G4VmpBeamThinTargetConfig::Print( Option_t* ) const
{

   std::cout << " OBJ: BeamThinTargetConfig" << "\t" 
             << GetName() << "\t" << GetTitle() 
	     << std::endl;
   
   std::cout << " Beam Particle ID = " << fBeamPartID << std::endl;
   std::cout << " Beam Momentum = " << fBeamMomentum << std::endl;
   std::cout << " Target ID (Z) = " << fTargetID << std::endl;
      
   return;

}
