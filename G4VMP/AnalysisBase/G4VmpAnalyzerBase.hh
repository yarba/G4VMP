#ifndef G4VmpAnalyzerBase_H
#define G4VmpAnalyzerBase_H 1

#include "G4VMP/AnalysisBase/AnalyzerWithExpDataBase.hh"

// Run/Event data products
//
#include "G4VMP/DataProducts/Interactions/G4VmpParticle.hh"   // Event data product
#include "G4VMP/DataProducts/ModelConfig/G4VmpModelConfig.hh" // Run data product

// Root-specific headers
//
#include "TFile.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "G4VMP/DataProducts/Analysis/G4VmpBeamThinTargetConfig.hh"

namespace G4VMP {

   class G4VmpAnalyzerBase : public G4VMP::AnalyzerWithExpDataBase {
   
   public:
   
      explicit G4VmpAnalyzerBase( const fhicl::ParameterSet& );
      virtual ~G4VmpAnalyzerBase();
      
      virtual void beginRun( const art::Run&  )       override;
      virtual void endJob()                           override;
         
   protected:
   
      void prepareG4PTable();
      void initXSecOnTarget( const std::string&, const G4VmpParticle& );
      bool ensureBeamTgtConfig( const art::Event& );
      
      virtual void Store4Professor( const std::string& ); 
      
      // These two data members below can go into a base class for
      // this group of analysis modules
      //
      std::string fProdLabel;
      bool        fKeepProcessing;
      TObjArray*  fModelConfig;
            
      // NOTE: Will also need XSec on TARGET !!!!!
      //
      double fXSecOnTarget; 
      bool   fXSecInit;
      
      // For cross-checks & bookkeeping on beamid-mom-target
      //
      G4VmpBeamThinTargetConfig   fBTConf;
      bool                        fConsistentRunConditions;
                  
   };

}

#endif
