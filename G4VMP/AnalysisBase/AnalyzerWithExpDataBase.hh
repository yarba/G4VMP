#ifndef AnalyzerWithExpDataBase_H
#define AnalyzerWithExpDataBase_H 1


#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Run.h"

#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "messagefacility/MessageLogger/MessageLogger.h" 

#include "G4VMP/ExpDataAccess/ExpDataAccess.hh"
#include "G4VMP/ExpDataAccess/JSON2Data.hh"

namespace G4VMP {

   class AnalyzerWithExpDataBase : public art::EDAnalyzer {
   
   public:
   
      explicit AnalyzerWithExpDataBase( const fhicl::ParameterSet& );
      virtual ~AnalyzerWithExpDataBase();
      
      virtual void endJob()                           override;
         
   protected:
                     
      bool matchVDBRec2MC( const int&, const double&, const int& );
      bool findExpDataByBeamTarget( const int&, const double&, const int& );
      virtual TH1* matchExpSpectrum2MC( const int&, const std::vector<std::string>&, const int& ) { return NULL; }
      
      void  rebinMC2Data( const std::string& ); 
      TH1D* copyHisto2TFS( TH1D*, const std::string& );
      virtual void  Store4Professor( const std::string& ) { return; }
      
      void overlayDataMC();
      
      bool                                   fIncludeExpData;
      bool                                   fUseJSONASCII;
      
      std::vector<int>                       fVDBRecordID;
      // --> VDBConnect*                            fVDBConnect;
      ExpDataAccess*                         fVDBConnect;
      JSON2Data*                             fJSON2Data;
//
      std::map< int, std::string >           fJSONRecords;
      std::vector< std::pair<int,TH1*> >     fVDBRecID2MC;
      
      // diagnostics output
      //
      mf::LogInfo fLogInfo;
        
   };

}

#endif
