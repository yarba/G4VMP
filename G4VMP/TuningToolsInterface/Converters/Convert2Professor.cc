#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TSystem.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TClass.h"
#include "TKey.h"
#include "TObjArray.h"
#include "TObjString.h"


int main()
{

   std::vector<std::string> analysis_files;
   
   std::string analysis_files_dir = 
//      "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.0.r06-pion-NucDestr-NP250";
//      "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.0.r06-pion-Proc1-QEX-NP150";
//      "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.0-proton-NucDestr-NP250";
      "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.1.r07-proton-Diff-NP200";
//      "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.1.r07-pion-Diff-NP200";

   std::string analysis_file = "";

/* 
// proton IAEA
//
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_IAEA/FTFP_proton3.824GeV_C-ProcL_IAEA.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_IAEA/FTFP_proton3.824GeV_Fe-ProcL_IAEA.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_IAEA/FTFP_proton3.824GeV_Pb-ProcL_IAEA.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/*  
// pi- HARP
//
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus3.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus3.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus3.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/* 
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus5.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus5.0GeV_Cu-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus5.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/*
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus8.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus8.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus8.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/* 
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus12.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus12.0GeV_Cu-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_HARP/FTFP_piminus12.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/* 
// pi- ITEP
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_ITEP/FTFP_piminus5.0GeV_C-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_ITEP/FTFP_piminus5.0GeV_Cu-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piminus_ITEP/FTFP_piminus5.0GeV_Pb-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/* 
// pi+ HARP
/*
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus3.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus3.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus3.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/* 
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus5.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus5.0GeV_Cu-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus5.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/*
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus8.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus8.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus8.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/* 
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus12.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus12.0GeV_Cu-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_HARP/FTFP_piplus12.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/* 
// pi+ ITEP
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_ITEP/FTFP_piplus5.0GeV_C-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_ITEP/FTFP_piplus5.0GeV_Cu-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_ITEP/FTFP_piplus5.0GeV_Pb-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/*
// proton HARP
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton3.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton3.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton3.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/* */
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton5.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton5.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir 
//      + "/analysis_FTFP_proton_HARP/FTFP_proton5.0GeV_Pb-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
/* */

/*
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton8.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton8.0GeV_Cu-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton8.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/* */
// special case for Mu2e
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton8.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_HARP/FTFP_proton8.0GeV_Ta-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
/* */

/* */
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton12.0GeV_C-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
//   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton12.0GeV_Cu-ProcL_HARP.root";
//   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_HARP/FTFP_proton12.0GeV_Pb-ProcL_HARP.root";
   analysis_files.push_back( analysis_file.c_str() );
/* */

/* 
// proton ITEP
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton5.0GeV_C-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton5.0GeV_Cu-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton5.0GeV_Pb-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton7.5GeV_C-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton7.5GeV_Cu-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_ITEP/FTFP_proton7.5GeV_Pb-ProcL_ITEP.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

// NA61
//
/* */
// proton 
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_proton_NA61/FTFP_proton31.0GeV_C-ProcL_NA61.root";
   analysis_files.push_back( analysis_file.c_str() );
/* */
/* 
// pi+
//
   analysis_file = analysis_files_dir 
      + "/analysis_FTFP_piplus_NA61/FTFP_piplus60.0GeV_C-ProcL_NA61.root";
   analysis_files.push_back( analysis_file.c_str() );
*/
/*
// pi+ SAS M6E
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_SASM6E/FTFP_piplus100.0GeV_C-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_SASM6E/FTFP_piplus100.0GeV_Cu-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_piplus_SASM6E/FTFP_piplus100.0GeV_Pb-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/*
// proton SAS M6E
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_SASM6E/FTFP_proton100.0GeV_C-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_SASM6E/FTFP_proton100.0GeV_Cu-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_SASM6E/FTFP_proton100.0GeV_Pb-ProcL_SASM6E.root";
   analysis_files.push_back( analysis_file.c_str() );
*/

/*
// proton NA49
   analysis_file = analysis_files_dir + "/analysis_FTFP_proton_NA49/FTFP_proton158.0GeV_C-ProcL_NA49.root";
   analysis_files.push_back( analysis_file.c_str() );  
*/

   std::vector<std::string> skip_histo;
   skip_histo.push_back("HARP_beam2212_momentum3GeV_target82_piplus_FW_3");
   // etc. as needed, until I figure out what's wrong with specific histos
   
   std::vector<std::string> skip_params;

/* */
   skip_params.push_back("BARYON_EXCI_E_PER_WNDNUCLN");
   skip_params.push_back("BARYON_NUCDESTR_P1_TGT");
/*
   skip_params.push_back("BARYON_NUCDESTR_P2_TGT");
   skip_params.push_back("BARYON_NUCDESTR_P3_TGT");
*/
/* 
   skip_params.push_back("MESON_EXCI_E_PER_WNDNUCLN");
   skip_params.push_back("MESON_NUCDESTR_P1_TGT");
*/
   
   TFile* data_file = 0;
   std::vector<TFile*> mc_files; // should correspond to the # of universes
   int iuniv = -1;
   std::string univ_name_pattern = "0000";
   
   std::vector< std::pair<std::string,double> > default_params;
   
   // populate default parameters here !!!
/* 
   default_params.push_back( std::pair<std::string,double>("MESON_NUCDESTR_P1_TGT", 0.00481) );
   default_params.push_back( std::pair<std::string,double>("MESON_NUCDESTR_P2_TGT", 4.0) );
   default_params.push_back( std::pair<std::string,double>("MESON_NUCDESTR_P3_TGT", 2.1) );
// -->   default_params.push_back( std::pair<std::string,double>("MESON_PT2_NUCDESTR_P1", 0.035) );
// -->  default_params.push_back( std::pair<std::string,double>("MESON_PT2_NUCDESTR_P2", 0.04) );
   default_params.push_back( std::pair<std::string,double>("MESON_EXCI_E_PER_WNDNUCLN", 40.) );
*/   
/* these are fixed in diff-np200 study... 
   default_params.push_back( std::pair<std::string,double>("BARYON_NUCDESTR_P1_TGT", 1.) );
   default_params.push_back( std::pair<std::string,double>("BARYON_NUCDESTR_P2_TGT", 4.) );
   default_params.push_back( std::pair<std::string,double>("BARYON_NUCDESTR_P3_TGT", 2.1) );
   default_params.push_back( std::pair<std::string,double>("BARYON_EXCI_E_PER_WNDNUCLN", 40.) );
*/   
/* */
   default_params.push_back( std::pair<std::string,double>("BARYON_DIFF_M_TGT", 1.16) );
   default_params.push_back( std::pair<std::string,double>("BARYON_NONDIFF_M_TGT", 1.16) );
   default_params.push_back( std::pair<std::string,double>("BARYON_AVRG_PT2", 0.3) );

   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_A1", 25.0 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_B1",  1.0 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_A2",-50.34) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_B2",  1.5 ) );
/* */
/*
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC4_A1",  0.6 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC4_A2", -1.2) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC4_B2",  0.5 ) );
*/
/*
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC0_A1", 13.71 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC0_B1",  1.75 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC0_A2",-30.69) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC0_B2",  3.0 ) );
*/

/* 
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_A1",  5.77 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_B1",  0.6  ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_A2", -5.77 ) );
   default_params.push_back( std::pair<std::string,double>("BARYON_PROC1_B2",  0.8 ) );
*/
/*
   default_params.push_back( std::pair<std::string,double>("PION_DIFF_M_TGT", 1.16) );
   default_params.push_back( std::pair<std::string,double>("PION_NONDIFF_M_TGT", 1.16) );
   default_params.push_back( std::pair<std::string,double>("PION_AVRG_PT2", 0.3) );

   default_params.push_back( std::pair<std::string,double>("PION_PROC1_A1",  5.77 ) );
   default_params.push_back( std::pair<std::string,double>("PION_PROC1_B1",  0.6  ) );
   default_params.push_back( std::pair<std::string,double>("PION_PROC1_A2", -5.77 ) );
   default_params.push_back( std::pair<std::string,double>("PION_PROC1_B2",  0.8 ) );
*/

   bool same_univ = false;  
   std::vector<std::string> processed_univ; 
      
   // loop over analysis Root files (TFileDirectory, i.e. output of art-based analysis)
   //
   for ( size_t i=0; i<analysis_files.size(); ++i )
   {

      TFile* afile = TFile::Open( analysis_files[i].c_str() );
      
      // ---> afile->ls();
      
      TList* keys = afile->GetListOfKeys();
      int nkeys = keys->GetEntries();
      for ( int ie=0; ie<nkeys; ++ie )
      {
      
         TObject* obj = keys->At(ie);
	 std::string dir_name = obj->GetName();
	 
	 if ( dir_name.find("Default") != std::string::npos )
	 {
	    // extract data from "Default" dir and continue
	    //
	    std::string full_dir_name = dir_name + "/Data4Professor";
	    if ( !data_file ) 
	    {
               if ( gSystem->AccessPathName( "data" ) )
               {   
                  gSystem->mkdir( "data" );
               }
	       data_file = TFile::Open( "data/data.root", "RECREATE" );
	       // also write out parameters (if they're needed in /data at all...)
	       std::ofstream params_file_dat;
	       params_file_dat.open( "data/params.dat" );
	       std::ofstream params_file_json;
	       params_file_json.open( "data/params.json" );
	       params_file_json << "{ \"params\": { \n";
	       for ( size_t ip=0; ip<default_params.size(); ++ip )
	       {
	          params_file_dat << default_params[ip].first << "  " 
		                  << default_params[ip].second << "\n"; 
		  params_file_json << "    \"" << default_params[ip].first 
		                   << "\": " << default_params[ip].second << "\n";
	       }
	       params_file_dat.close();
	       params_file_json << "  } \n";
	       params_file_json << "}\n";
	       params_file_json.close();
	    }
	    TIter next( afile->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
	    TKey* key = (TKey*)next();
	    while ( key )
	    {
               if ( !(TClass::GetClass(key->GetClassName())->InheritsFrom(TH1::Class())) ) 
	       {
	          key = (TKey*)next();
		  continue;
	       }
	       TH1D* h = (TH1D*)key->ReadObj();
	       bool skip = false;
	       for ( size_t ihskip=0; ihskip<skip_histo.size(); ++ihskip )
	       {
	          if ( h->GetName() == skip_histo[ihskip] )
		  {
		     skip = true;
		     break;
		  }
	       }
	       if ( skip )
	       {	          
	          key = (TKey*)next();
		  continue;
	       }

// --->	
// List of particles/names: k0s, kplus, kminus,  lambda,
//                          piplus, piminus, proton      

	       // skip histots if or of not certain secondary 
	       std::string hname = h->GetName();
/*
	       if ( hname.find( "_proton_"  ) == std::string::npos &&
	            hname.find( "_neutron_" ) == std::string::npos )
	       {
	          key = (TKey*)next();
		  continue;
	       }
*/
// --->	    
/* */
	       if ( hname.find( "_k0s_" )    != std::string::npos ||
	            hname.find( "_kplus_" )  != std::string::npos ||
		    hname.find( "_kminus_" ) != std::string::npos ||
		    hname.find( "_lambda_" ) != std::string::npos ||
		    hname.find( "_antiproton" ) != std::string::npos  ||
		    ( dir_name.find("ITEP") == std::string::npos   
		      && hname.find( "_proton_" ) != std::string::npos )  
		  )
/* */
/*
	       if ( hname.find("neutron") == std::string::npos &&
	            hname.find("Neutron") == std::string::npos 
	          )
*/
	       {
// -->	          std::cout << " ... skipping " << hname << std::endl;
		  key = (TKey*)next();
		  continue;
	       }
	       
// -->	       std::cout << " ---> writing out " << hname << std::endl;
	       TH1D* hdata = new TH1D( *h );
	       // hdata->SetDirectory(0);
	       data_file->cd();
	       hdata->Write();
	       key = (TKey*)next();
	    }
	    
	    continue;
	 }
	 
	 // now get "universes"
	 
	 size_t pos = dir_name.find("Univ");
	 
	 if ( pos == std::string::npos ) continue;	 
	 
	 // check if /scan dir is there; if not, create
	 //
	 if ( gSystem->AccessPathName( "scan" ) )
	 {
	    gSystem->mkdir( "scan" );
	 }
	 	 
	 std::string univ_label = dir_name.substr( pos, 8 ); // size("Univ")+size("0000")
	 same_univ = false;	 
	 for ( size_t ipu=0; ipu<processed_univ.size(); ++ipu )
	 {
	    if ( univ_label == processed_univ[ipu] )
	    {
	       same_univ = true;
	       iuniv = ipu;
	       break;
	    }
	 }
	 if ( ! same_univ )
	 {
	    processed_univ.push_back( univ_label );
	    iuniv++;
	 }
	 int nmc = mc_files.size();
	 if ( nmc <= iuniv )
	 {
	    // no dir/file for this universe yet; create
	    //	    
	    std::string count = std::to_string(iuniv); 
	    std::string univ_name = univ_name_pattern;
	    univ_name.replace( univ_name.size()-count.size(), count.size(), count ); 
	    std::string univ_subdir = "scan/" + univ_name; 
	    if ( gSystem->AccessPathName( univ_subdir.c_str() ) )
	    {
	       gSystem->mkdir( univ_subdir.c_str() );
	    }
	    std::string mc_file_name = univ_subdir + "/g4mc.root";
	    mc_files.push_back( TFile::Open( mc_file_name.c_str(), "RECREATE" ) );
            //
	    // extract parameters !!!
	    // do it only ONCE !!!
	    if ( gSystem->AccessPathName( (univ_subdir+"/params.dat").c_str() ) )
	    {
	       std::ofstream params_file_dat;
	       params_file_dat.open( (univ_subdir+"/params.dat").c_str() );
	       std::ofstream params_file_json;
	       params_file_json.open( (univ_subdir+"/params.json").c_str() );
	       params_file_json << "{ \"params\": { \n";
	       TObjArray* objarray = (TObjArray*)afile->Get( (dir_name+"/Geant4ModelConfig").c_str() );
	       for ( int io=0; io<objarray->GetEntries(); ++io )
	       {
                  TObjString* sobj = (TObjString*)objarray->At(io);
	          std::string str = sobj->GetString().Data();
	          size_t idx1 = str.find(":");
	          std::string model = str.substr(0,idx1);
	          size_t idx2 = str.find_first_not_of(" ", idx1+1);
	          size_t idx3 = str.find("=");
	          std::string pname = str.substr(idx2,(idx3-idx2));
	          if ( pname.find("USE") != std::string::npos ) continue; // skip ON/OFF switches
		  bool iskp_found = false;
		  for ( size_t iskp=0; iskp<skip_params.size(); ++iskp )
		  {
		     if ( pname.find( skip_params[iskp] ) != std::string::npos ) 
		     {
		        iskp_found = true;
			break;
		     }
		  }
		  if ( iskp_found ) continue;
	          std::string sval = str.substr( str.find("=")+1 );
	          double val = std::stod(sval);
		  params_file_dat << pname << " " << val << "\n";
		  params_file_json << "    \"" << pname << "\": " << val << "\n";
	       }
	       params_file_dat.close();
	       params_file_json << "  } \n";
	       params_file_json << "}\n";
	       params_file_json.close();
	    }
	 }	 
	 
	 //
	 std::string full_dir_name = dir_name + "/MC4Professor";
	 TIter next( afile->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
	 TKey* key = (TKey*)next();
	 while ( key )
	 {
            if ( !(TClass::GetClass(key->GetClassName())->InheritsFrom(TH1::Class())) ) 
	    {
	          key = (TKey*)next();
		  continue;
	    }
	    TH1D* h = (TH1D*)key->ReadObj();
	    bool skip = false;
	    for ( size_t ihskip=0; ihskip<skip_histo.size(); ++ihskip )
	    {
	          if ( h->GetName() == skip_histo[ihskip] )
		  {
		     skip = true;
		     break;
		  }
	    }
	    if ( skip )
	    {	          
	          key = (TKey*)next();
		  continue;
	    }

// --->	       
	       // skip histots if not secondary proton or neutron
	       std::string hname = h->GetName();
/*
	       if ( hname.find( "_proton_"  ) == std::string::npos &&
	            hname.find( "_neutron_" ) == std::string::npos )
	       {
	          key = (TKey*)next();
		  continue;
	       }
*/
// --->	       
/* */
	       if ( hname.find( "_k0s_" )    != std::string::npos ||
	            hname.find( "_kplus_" )  != std::string::npos ||
		    hname.find( "_kminus_" ) != std::string::npos ||
		    hname.find( "_lambda_" ) != std::string::npos ||
		    ( dir_name.find("ITEP") == std::string::npos   
		      && hname.find( "_proton_" ) != std::string::npos )  
		  )
/* */
/*
	       if ( hname.find("neutron") == std::string::npos &&
	            hname.find("Neutron") == std::string::npos 
	          )
*/
	       {
// -->	          std::cout << " ... skipping " << hname << std::endl;
		  key = (TKey*)next();
		  continue;
	       }

	    TH1D* hmc = new TH1D( *h );
	    // hmc->SetDirectory(0);
	    mc_files[iuniv]->cd();
	    hmc->Write();
	    key = (TKey*)next();
	 }
	       
      }

      iuniv = -1;
      processed_univ.clear();
      afile->Close();
      
   }

   // data_file->Write(); // NO writing the file itself since histograms are already written out
                          // otherwise histograms will appear there twice
   data_file->Close();
   
   for (size_t i=0; i<mc_files.size(); ++i )
   {
      // mc_files[i]->Write(); // NO writing the file itself since histograms are already written out
                               // otherwise histograms will appear there twice
      mc_files[i]->Close();
   }

   return 0;
   
}
