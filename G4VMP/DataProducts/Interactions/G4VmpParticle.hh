#ifndef G4VmpParticle_H
#define G4VmpParticle_H

#include "CLHEP/Vector/LorentzVector.h"

#include<string>

namespace G4VMP {

class G4VmpParticle
{

   public:
   
      G4VmpParticle();
      G4VmpParticle( const int, const CLHEP::HepLorentzVector& );
      G4VmpParticle( const int, const CLHEP::Hep3Vector& );
      G4VmpParticle( const G4VmpParticle& );
      ~G4VmpParticle() {}

      G4VmpParticle& operator=( const G4VmpParticle& other ) { fPDG=other.fPDG; fMomentum=other.fMomentum; return *this; }

      void SetPDG( const int );
      void SetMomentum( const CLHEP::HepLorentzVector& );
      void SetMomentum( const CLHEP::Hep3Vector& );
      
      int                            GetPDG() const { return fPDG; }
      std::string                    GetName() const;
      const CLHEP::HepLorentzVector& GetMomentum() const { return fMomentum; }
      
      // Patch up dictionary generation.
      // NOTE(from GenParticle, originally by HW):
      // There is source in art::PtrVector that should be protected and gccxml trying to instantiate it.
      // Until that is fixed, we need to provide a an operator< or else the dictionary generation fails.
      // So we provide a bogus version here. This is never actually used but,if gccxml cannot find 
      // the method, it quits.
      //
      bool operator<( const G4VmpParticle& ) const { return true; }

   private:
   
      // data members
      //
      int                     fPDG;
      CLHEP::HepLorentzVector fMomentum;

};

}

#endif
