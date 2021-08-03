#ifndef G4VmpBeamThinTargetConfig_H
#define G4VmpBeamThinTargetConfig_H 1

#include <string>
#include <TNamed.h>

// NO namespece !!!
//

class G4VmpBeamThinTargetConfig : public TNamed {
   
   public:
   
      G4VmpBeamThinTargetConfig() : TNamed(),
                                    fBeamPartID(0), 
				    fBeamMomentum(-1.), 
		                    fTargetID(0) {}
      G4VmpBeamThinTargetConfig( const int, const double, const int );
      G4VmpBeamThinTargetConfig( const G4VmpBeamThinTargetConfig& );
      G4VmpBeamThinTargetConfig( TRootIOCtor* );
      
      ~G4VmpBeamThinTargetConfig() {}
      
      void SetBeamPartID( const int pid ) { fBeamPartID=pid; return; }
      void SetBeamMomentum( const double m ) { fBeamMomentum=m; return; }
      void SetTargetID( const int tid ) { fTargetID=tid; return; }
      
      int    GetBeamPartID()   const { return fBeamPartID; }
      double GetBeamMomentum() const { return fBeamMomentum; }
      int    GetTargetID()     const { return fTargetID; }
      
      virtual void Print( Option_t* opt="" ) const;
      
      bool operator==( const G4VmpBeamThinTargetConfig& ) const;
               
   private:
      
      int    fBeamPartID;
      double fBeamMomentum;
      int    fTargetID;

// this is mandatory because it derives from TObject (via TNamed)
//                           
ClassDef(G4VmpBeamThinTargetConfig,10)

};


#endif
