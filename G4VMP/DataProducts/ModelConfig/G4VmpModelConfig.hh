#ifndef G4VmpModelConfig_H
#define G4VmpModelConfig_H

#include "fhiclcpp/fwd.h"

#include<string>
#include <vector>
#include <map>

namespace G4VMP {

class G4VmpModelConfig
{

   public:
   
      G4VmpModelConfig() : fDefaultPhysics(true) {}
      G4VmpModelConfig( const bool& flag ) : fDefaultPhysics(flag) {}
      G4VmpModelConfig( const G4VmpModelConfig& rhs ) : fDefaultPhysics(rhs.fDefaultPhysics),
                                                        fModelConfig(rhs.fModelConfig) {} 
      ~G4VmpModelConfig() {}
      
      void Fill( const fhicl::ParameterSet& );
      void Insert( const std::string&, const std::string&, const double& );
            
      bool                                                IsDefaultPhysics() const { return fDefaultPhysics; }
      std::vector<std::string>                            GetConfiguredModels() const;      
      const std::vector< std::pair<std::string,double> >* GetConfig( const std::string& ) const;
      
      // Patch up dictionary generation.
      // NOTE(from GenParticle, originally by HW):
      // There is source in art::PtrVector that should be protected and gccxml trying to instantiate it.
      // Until that is fixed, we need to provide a an operator< or else the dictionary generation fails.
      // So we provide a bogus version here. This is never actually used but,if gccxml cannot find 
      // the method, it quits.
      //
      bool operator<( const G4VmpModelConfig& ) const { return true; }
   
   private:
   
      // private member functions
      //
      void DoFill( std::string&, std::string&, fhicl::ParameterSet& );  
      
      // data members
      //
      bool fDefaultPhysics;
      //
      // NOTE-1(JVY): the reason of using this construct is because there's already
      //            a "standard" (Art's) dictionary for it (art/Persistency/StdDictionaries)
      //
      // NOTE-2(JVY): at present, only those parameters different from DEFAULTS will be stored
      //              although in the future we might consider a bit more extensive options
      //
      std::map< std::string, std::vector< std::pair<std::string,double> > > fModelConfig;

};

}

#endif
