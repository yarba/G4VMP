#include <iostream>
// #include <fstream>
// #include <iomanip>
#include <string>
#include<vector>

#include "TROOT.h"
#include "TFile.h"
#include "TFileMerger.h"

void MergeAnalysisFiles( std::string exp, std::string beam, std::string label )
{

   std::string dname = "/wclustre/g4v/yarba_j/g4vmp-study/"; 
   
   std::vector<std::string> sdnames;
//   sdnames.push_back("01-06-22");
//   sdnames.push_back("01-12-22");
//   sdnames.push_back("01-18-22");
   
//   std::string subdir = "ana-g4.11.0-NP500-" + exp;
//   std::string subdir = "03-25-22";
//   std::string subdir = "ana-g4.11.0-NucDestr-NP250";
//   std::string subdir = "ana-g4.11.0-QEX-Proc0-NP250-tst2";
//   std::string subdir = "ana-g4.11.0-QEX-Proc1-HARP-NA61-NP150-tst3";
//   std::string subdir = "ana-g4.11.0.r06-pion-NucDestr-NP250";
   std::string subdir = "ana-g4.11.0.r06-pion-Proc1-QEX-NP150";
   sdnames.push_back(subdir);
   
   TFileMerger* fm = new TFileMerger();
   std::string outmerge = "merge-" + beam + "_" + label + "-" + exp + ".root"; 
   fm->OutputFile( outmerge.c_str(), "RECREATE" );

   std::string rfiles = "*" + label + "*.root";
   
   for (size_t i=0; i<sdnames.size(); ++i )
   {

      std::string cmd = "ls -alF " 
                      + dname 
                      + sdnames[i] + "/"
		      + "analysis_FTFP_" + beam + "_" + exp +"/"
                      + rfiles + 
		      " | awk '{print $NF}' > rflist.txt";
      gSystem->Exec( cmd.c_str() );
            
      FILE* rflist = fopen( "rflist.txt", "r" );
      
      char rfname[256];
      while ( ! feof(rflist) )
      {
         fscanf( rflist, "%s", rfname );
         std::cout << rfname << std::endl;
         if ( strlen(rfname) == 0 ) continue;
         fm->AddFile( rfname );
         rfname[0] = 0;
      }
   
      fclose(rflist);
      
      gSystem->Exec( "rm rflist.txt" );

   }
   
   fm->Merge();
   
   return;

}
