
   file_dir_local += "/analysis_" + model + "_" + beam + "_" + experiment;
      
   std::string fname = file_dir_global + "/"
                     + file_dir_local;
   fname += "/" + model + "_" + beam + momentum 
          + "_" + target + "-ProcL_" + experiment + ".root";
   
   file = TFile::Open( fname.c_str() );

   std::string fitsname = dir_fits + "/" + "ipolhistos.root";  // Professor
//   std::string fitsname = dir_fits + "/" + "predictions_tnc_25_1.root"; // Apprentice
   TFile* file_fits = 0 ;
   if ( plot_fits )
   {
      file_fits = TFile::Open( fitsname.c_str() );
   }

      
   std::string fname_sim_best_fit = file_dir_global + "/" + dir_sim_best_fit;
   fname_sim_best_fit += "/analysis_" + model + "_" + beam + "_" + experiment;
   fname_sim_best_fit += "/" + model + "_" + beam + momentum 
                        + "_" + target + "-ProcL_" + experiment + ".root";
   
   TFile* file_sim_best_fit = 0;
   if ( plot_sim_best_fit ) 
   {
      file_sim_best_fit = TFile::Open( fname_sim_best_fit.c_str() );
   }
