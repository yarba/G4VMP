
#include "general.h"


std::string momentum   = "3.824GeV";
std::string target     = "Pb";
std::string experiment = "IAEA";

std::string dir_fits =
//   "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-nucdestr-IAEA-ITEP-HARP/tunes-poly3-p2-4-p3-2.1-scan25";
//   "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-nucdestr-IAEA-ITEP-HARP/tunes-poly3-scan25";
//
// this is a test Apprentice vs Professor
//
   "/work1/g4v/yarba_j/Apprentice-vs-Prof-g4.11.0-FTFP-Fall2022/tunes_poly3"; // Professor
//   "/work1/g4v/yarba_j/Apprentice-vs-Prof-g4.11.0-FTFP/tune_val+errs_px3qx0"; // Apprentice

// std::string dir_sim_best_fit = "bestfit-nucdestr-iaea-itep-harp-2022";  
std::string dir_sim_best_fit = "tune-candidate-NucDestrProc1QEX-2022-tst3";

std::vector<TCanvas*> canvas;
std::vector<TPad*> pads;
std::vector<double> chi2_def;
std::vector<double> chi2_fit;
std::vector<double> chi2_sim_best_fit;
std::vector<int> NDF;


void PrepareCanvas();

#include "PlotHisto.C"
#include "PlotGraph.C"

#include "Chi2.C"

void PlotSensitivityIAEA( std::string dir_local, 
		      std::string mdl,
		      std::string bm,
		      std::string sec,
		      bool        plot_mc_spread=true,
		      bool        plot_fits=false,
		      bool        plot_sim_best_fit=false  
		    )
{

   file_dir_local = dir_local;
   model = mdl;
   beam  = bm;
   secondary = sec;
   
   LogX = true;
   LogY = true;
   
   std::vector<std::string> select_plots;
   select_plots.push_back("theta=15 ");
   select_plots.push_back("theta=60 ");

#include "OpenFiles_Fragment.C"

   PrepareCanvas();

   int iuniv = -1;
   std::string univ_name_pattern = "0000";

#include "FindDefaultDir_Fragment.C"

   std::string full_dir_name = def_dir_name + "/Data4Professor";
   
   std::cout << full_dir_name << std::endl;
   
//         TIter next( file->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
   TIter itr_def( file->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
   TKey* hkey_def = (TKey*)itr_def(); // alternative: itr_def.Next()
   
   if ( ! hkey_def )
   {
      std::cout << " invalid hkey_def " << std::endl;
   }
   
   int icount = -1;

   while ( hkey_def )
   {
      
#include "GeneralSelection_Fragment.C"

      std::string hdtitle = hd->GetTitle();
      bool selected_found = false;
      for ( size_t isel=0; isel<select_plots.size(); ++isel )
      {
         if ( hdtitle.find( select_plots[isel] ) == std::string::npos )
	 {
	    continue;
	 }
	 else 
	 {
	    selected_found = true;
	    break;
	 } 
      }
      if ( !selected_found )
      {
         hkey_def = (TKey*)itr_def();
	 continue;
      }
      
      hd->GetXaxis()->SetTitle("Kinetic energy of secondary neutron [MeV]");
      hd->GetYaxis()->SetTitle("d#sigma / dE d#Theta [mb/srad/MeV]");
            
      std::cout << " processing/plotting data histo --> " << hdname << std::endl;

#include "TheHistos_Fragment.C"
// #include "TheHistos_BW_Fragment.C"
      
      hkey_def = (TKey*)itr_def();

      // draw histo titles
      //
      std::string htitle = hmc->GetTitle();
      double x1 = hd->GetBinCenter(1) - hd->GetBinWidth(1);
      double x2 = hd->GetBinCenter(hd->GetNbinsX()) + hd->GetBinWidth(hd->GetNbinsX());
      double xpos = x1;
      if ( x2 > 500. )
      {
         xpos += 0.02*(x2-x1) ;
      }
      else
      {
         xpos += 0.025*(x2-x1) ;
      }
      TLatex* hltxt = new TLatex( xpos, 0.25*ymax, htitle.c_str() );
      hltxt->SetTextSize(0.06);
      //
      // NOTE: we're already at the hd/hmc histogram, and that's where
      //       we need to be in order to draw a text over it
      // 
// -->      hltxt->Draw();

   }

   for ( size_t ih=0; ih<canvas.size(); ++ih )
   {
      secondary[0] = std::tolower(secondary[0]);
      std::string gtitle = "G4/FTF: " + momentum + " " + beam + " on " + target
                         + " #rightarrow " + secondary + " + X; data by " + experiment;
      TLatex* gltxt = new TLatex( 0.3, 0.955, gtitle.c_str() );
      gltxt->SetTextSize(0.05); // 0.025);
      canvas[ih]->cd();
// -->      gltxt->Draw();
      canvas[ih]->Update(); 
      std::string output = canvas[ih]->GetName();
//      output += ".png";
      output += ".eps";
      canvas[ih]->Print( output.c_str() );
   }
   
   for ( size_t indf=0; indf<NDF.size(); ++indf )
   {
      std::cout << " DEFAULT:      chi2/NDF = " << chi2_def[indf] <<  "/" << NDF[indf] << std::endl;
      std::cout << " FITS:         chi2/NDF = " << chi2_fit[indf] <<  "/" << NDF[indf] << std::endl;
      std::cout << " SIM BEST FIT: chi2/NDF = " << chi2_sim_best_fit[indf] <<  "/" << NDF[indf] << std::endl;
   }

   return;

}

void PrepareCanvas()
{

   canvas.clear();
   pads.clear();
   chi2_def.clear();
   chi2_fit.clear();
   chi2_sim_best_fit.clear();
   NDF.clear();
   
   if ( experiment.empty() )
   {
      std::cout << " experiment is not defined; can NOT prepare canvas " << std::endl;
   }

   std::string cname = "cnv_" + model + "_" + beam + momentum + "_" + target + "_" + secondary + "_"
                     + experiment;
   canvas.push_back( new TCanvas( cname.c_str(), "", 920, 350 ) ); // 690 ) );
   std::string padname = "pad_" + model + "_" + beam + momentum + "_" + target + "_" + secondary + "_"
                       + experiment;
   pads.push_back( new TPad( padname.c_str(), "", 0.01, 0.01, 0.99, 0.99 ) ); // 0.95 ) );
   
   pads.back()->SetBottomMargin(0.2);

//   pads.back()->Divide( 3, 2, 0.01, 0.01 ); 
   pads.back()->Divide( 2, 1, 0.01, 0.01 ); 
      
   canvas.back()->cd();
   pads.back()->Draw();
   
   chi2_def.push_back(0.);
   chi2_fit.push_back(0.);
   chi2_sim_best_fit.push_back(0.);
   NDF.push_back(0);

   return;

}
