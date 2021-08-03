#ifndef G4VmpVtx_H
#define G4VmpVtx_H

#include "G4VMP/DataProducts/Interactions/G4VmpParticle.hh"

#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Common/PtrVector.h"

#include<string>

namespace G4VMP {

class G4VmpVtx 
{

   public:
   
      // NOTE(JVY): it might also be useful to add status:
      //            none, decay, interaction (em, had, elastic, inelastic,...)
      
      G4VmpVtx() : fPhysVolumeName(""), fMaterialName(""), fIncoming(), fOutcoming() {}
      G4VmpVtx( const CLHEP::HepLorentzVector& pos, 
                const std::string& pvname, 
		const std::string& mname ) : fPosition(pos), 
		                             fPhysVolumeName(pvname), fMaterialName(mname),
		                             fIncoming(), fOutcoming() {}
      G4VmpVtx( const G4VmpVtx& rhs ) : fPosition(rhs.fPosition),
                                        fPhysVolumeName(rhs.fPhysVolumeName),
                                        fMaterialName(rhs.fMaterialName),
					fIncoming(rhs.fIncoming),
					fOutcoming(rhs.fOutcoming) {}
      ~G4VmpVtx() {}
      
      void Clear() { fPosition=CLHEP::HepLorentzVector(0.,0.,0.,0);
                     fPhysVolumeName=""; fMaterialName="";
		     fIncoming=G4VmpParticle(); fOutcoming.clear();
		     return; }
      
      void SetPosition( const CLHEP::HepLorentzVector& pos )     { fPosition=pos; return; }
      void SetPhysVolumeName( const std::string& pvname )        { fPhysVolumeName=pvname; return; }
      void SetMaterialName( const std::string& mname )           { fMaterialName=mname; return; }

      void SetIncoming( const G4VmpParticle& pin )               { fIncoming=pin; return; }
      void SetIncoming( const int pdg, const CLHEP::Hep3Vector& mom ) { fIncoming.SetPDG(pdg);
                                                                        fIncoming.SetMomentum(mom); 
									return; }
      void SetIncoming( const int pdg, const CLHEP::HepLorentzVector& mom ) { fIncoming.SetPDG(pdg); 
                                                                              fIncoming.SetMomentum(mom); 
									      return; }
      void AddOutcoming( const G4VmpParticle& pout ) { fOutcoming.push_back( pout ); return; }
      
      const CLHEP::HepLorentzVector&         GetPosition()            const { return fPosition; }
      const std::string&                     GetPhysVolumeName()      const { return fPhysVolumeName; }
      const std::string&                     GetMaterialName()        const { return fMaterialName; }    
      const G4VmpParticle&                   GetIncoming()            const { return fIncoming; }
            int                              GetNumOutcoming()        const { return fOutcoming.size(); }
      const std::vector<G4VmpParticle>&      GetAllOutcoming()        const { return fOutcoming; }
      const G4VmpParticle&                   GetOutcoming( int i )    const { return fOutcoming[i]; }

      // Patch up dictionary generation.
      // NOTE(from GenParticle, by HW):
      // There is source in art::PtrVector that should be protected and gccxml trying to instantiate it.
      // Until that is fixed, we need to provide a an operator< or else the dictionary generation fails.
      // So we provide a bogus version here. This is never actually used but,if gccxml cannot find 
      // the method, it quits.
      //
      bool operator<( const G4VmpVtx& ) const { return true; }
      
   private:
      
      // data members
      //
      CLHEP::HepLorentzVector         fPosition;
      std::string                     fPhysVolumeName;
      std::string                     fMaterialName;
      G4VmpParticle                   fIncoming;
      std::vector<G4VmpParticle>      fOutcoming;
     
};

}

#endif
