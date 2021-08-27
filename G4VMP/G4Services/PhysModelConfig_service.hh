#ifndef PhysModelConfig_SERVICE_HH
#define PhysModelConfig_SERVICE_HH

// Art
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
// --> split the one below and use separate includes in hh and cc;
// --> otherwise it won't compile   
// --> #include "art/Framework/Services/Registry/ServiceMacros.h"
#include "art/Framework/Services/Registry/ServiceDeclarationMacros.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

// fwd declaration(s)
class ModelConfigMapper;

namespace G4VMP
{

class PhysModelConfigService
{

   public:
   
      // ctor & dtor
      //
      // NOTE: the ctor MUST have these 2 input args; 
      //       otherwise the system will NOT register it as a "service"
      // 
      PhysModelConfigService( const fhicl::ParameterSet&, art::ActivityRegistry& );
      ~PhysModelConfigService();
      
      void PrintDefaultSettings();
      void ConfigureModel( const std::string&, const fhicl::ParameterSet& );
      void Reset();
      void PrintCurrentSettings();
                     
   private:
   
      // member functions
      //
      void DoConfigure( const std::string&, const std::string&, const fhicl::ParameterSet& );
      
      // data members
      //
      ModelConfigMapper*  fConfigMapper;
      bool                fVerbosity;

};

}

using G4VMP::PhysModelConfigService;
DECLARE_ART_SERVICE(PhysModelConfigService, LEGACY)


#endif
