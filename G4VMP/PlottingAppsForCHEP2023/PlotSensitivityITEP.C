/*
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

#include <math.h>
#include <vector>

#include "Rtypes.h"
#include "TROOT.h"
#include "TRint.h"
#include "TObject.h"
#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
// --> #include "TPad.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TLine.h"
#include "TArrow.h"

// --> LQ1 --> std::string file_dir_global = "/lustre1/g4/yarba_j/g4vmp-study";
std::string file_dir_global = "/wclustre/g4v/yarba_j/g4vmp-study";

std::string file_dir_local  = "";
std::string model           = "";
std::string beam            = "";
std::string secondary       = "";
TFile*      file            = 0;
*/

#include "general.h"

// later...
// --> proton beam only --> 
std::string momentum   = "7.5GeV";
// std::string momentum   = "5.0GeV";
std::string target     = "Pb";
std::string experiment = "ITEP";

std::vector<std::string> theta_itep771;

std::string dir_fits =
//    "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-12pars/tunes-harp-na61-fix-proc1-poly3-scan25";
//   "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-nucdestr-IAEA-ITEP-HARP/tunes-poly3-p2-4-p3-2.1-scan25";
//   "/work1/g4v/yarba_j/Prof-g4.11.0.r06-FTF-pion-nucdestr-ITEP-HARP/tunes-no-FW-protons-poly3-fix-p2-p3";
//
// this is a test Apprentice vs Professor
//
   "/work1/g4v/yarba_j/Apprentice-vs-Prof-g4.11.0-FTFP/tunes_poly3"; // Professor
//   "/work1/g4v/yarba_j/Apprentice-vs-Prof-g4.11.0-FTFP/tune_val+errs_px3qx0"; // Apprentice

// std::string dir_sim_best_fit = "bestfit-nucdestr-4pars-2022";  
// std::string dir_sim_best_fit = "bestfit-nucdestr-iaea-itep-harp-2022";
std::string dir_sim_best_fit = "tune-candidate-NucDestrProc1QEX-2022-tst3";
// std::string dir_sim_best_fit = "bestfit-pion-nucdestr-2022";

std::string dir_sim_retro = "bestfit-pion-nucdestr-2019";

std::vector<TCanvas*> canvas;
std::vector<TPad*> pads;
std::vector<double> chi2_def;
std::vector<double> chi2_fit;
std::vector<double> chi2_sim_best_fit;
std::vector<double> chi2_sim_retro;
std::vector<int> NDF;

void PrepareCanvas();

#include "PlotHisto.C"
#include "PlotGraph.C"

#include "Chi2.C"

void PlotSensitivityITEP( std::string dir_local, 
		      std::string mdl,
		      std::string bm,
		      std::string sec,
		      bool        plot_mc_spread=true,
		      bool        plot_fits=false,
		      bool        plot_sim_best_fit=false,
		      bool        plot_sim_retro=false   
		    )
{

   file_dir_local = dir_local;
   model = mdl;
   beam  = bm;
   secondary = sec;
   
/* */
//   theta_itep771.push_back("_59p1deg");
   theta_itep771.push_back("_89deg");
   theta_itep771.push_back("_119deg");
//   theta_itep771.push_back("_159p6deg");
/* */
   
/*  
   // data at these angles are available for secondary protons only
   //
   theta_itep771.push_back("_15deg");
   theta_itep771.push_back("_24p8deg");
   theta_itep771.push_back("_34p6deg");
   theta_itep771.push_back("_49p3deg");
*/
   
   file_dir_local += "/analysis_" + model + "_" + beam + "_" + experiment;
      
   std::string fname = file_dir_global + "/"
                     + file_dir_local;
   fname += "/" + model + "_" + beam + momentum 
          + "_" + target + "-ProcL_" + experiment + ".root";
   
   file = TFile::Open( fname.c_str() );
   
   std::string fitsname = dir_fits + "/" + "ipolhistos.root";
// --> Apprentice -->   std::string fitsname = dir_fits + "/" + "predictions_tnc_25_1.root";
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
   
   
   std::string fname_sim_retro = file_dir_global + "/" + dir_sim_retro;
   fname_sim_retro += "/analysis_" + model + "_" + beam + "_" + experiment;
   fname_sim_retro += "/" + model + "_" + beam + momentum 
                     + "_" + target + "-ProcL_" + experiment + ".root";
   
   TFile* file_sim_retro = 0;
   if ( plot_sim_retro )
   {
      file_sim_retro = TFile::Open( fname_sim_retro.c_str() );
   }

   PrepareCanvas();
   
   int iuniv = -1;
   std::string univ_name_pattern = "0000";
   
   TList* keys = file->GetListOfKeys();
   int nkeys   = keys->GetEntries();
   
   std::string def_dir_name = model + "Default" + experiment;

   TKey* dkey = (TKey*)(keys->FindObject( def_dir_name.c_str() ) );
   if ( !dkey ) 
   {
      std::cout << " can NOT find object " << def_dir_name << std::endl;
      return;
   }
   std::string dkey_class_name = dkey->GetClassName();
   if ( dkey_class_name.find("Directory") == std::string::npos ) 
   {
      std::cout << " object " << def_dir_name << " is NOT a directory " << std::endl;
      return;
   }
   
   std::string full_dir_name = def_dir_name + "/Data4Professor";
   
//         TIter next( file->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
   TIter itr_def( file->GetDirectory( full_dir_name.c_str() )->GetListOfKeys() );
   TKey* hkey_def = (TKey*)itr_def(); // alternative: itr_def.Next()
   
   int icount = -1;

   while ( hkey_def )
   {
      if ( !(TClass::GetClass(hkey_def->GetClassName())->InheritsFrom(TH1::Class())) )
      {
	       hkey_def = (TKey*)itr_def();
	       continue;
      }
      TH1D* hd = (TH1D*)hkey_def->ReadObj();
      std::string hdname = hd->GetName();
      
      if ( hdname.find( secondary ) == std::string::npos )
      {
	       hkey_def = (TKey*)itr_def();
	       continue;
      }
      
      bool ith_found = false;
      for ( size_t ith=0; ith<theta_itep771.size(); ++ith )
      {
	 if ( hdname.find( theta_itep771[ith]  ) != std::string::npos  )
	 {
	    std::cout << theta_itep771[ith] << " found in " << hdname << std::endl;
	    ith_found = true;
	    break;
	 }
      }
      
      if ( ! ith_found )
      {
	 hkey_def = (TKey*)itr_def();
	 continue;
      }
            
      std::cout << " processing/plotting data histo --> " << hdname << std::endl;

      double ymax = -1.;
      // find maximum
      //
      int imax = hd->GetMaximumBin();
      if ( ymax < (hd->GetBinContent(imax)+2.*hd->GetBinError(imax)) )
         ymax = hd->GetBinContent(imax)+2.*hd->GetBinError(imax);

      hd->SetMarkerColor(kBlack);
      hd->SetStats(0);
      hd->SetTitle("");
      hd->GetXaxis()->SetLabelFont(62);
      hd->GetYaxis()->SetLabelFont(62);
      hd->GetXaxis()->SetTitle("Kinetic energy of neutron [GeV]");
      hd->GetYaxis()->SetTitle("E(d^{3}#sigma/dp^{3}) [mb/GeV^{2}/SR]");
      hd->GetXaxis()->SetTitleFont(62);
      hd->GetYaxis()->SetTitleFont(62);
      hd->GetXaxis()->SetTitleOffset(1.);
      hd->GetYaxis()->SetTitleOffset(1.); // 1);
      hd->GetXaxis()->SetTitleSize(0.0475); // 45);
      hd->GetYaxis()->SetTitleSize(0.0475); // 425);
      hd->GetXaxis()->CenterTitle();
      hd->GetYaxis()->CenterTitle();
      hd->GetYaxis()->SetRangeUser( 0., ymax );
      icount++;
      
      PlotHisto( hd, icount, "p", 0 );

      // extract MC histo of the same name, from "Default"/MC4Professor
      //
      std::string hmcname = def_dir_name + "/MC4Professor/" + hdname;
      TH1D* hmc = (TH1D*)file->Get( hmcname.c_str() );
      hmc->SetLineColor(kRed);
      hmc->SetLineWidth(2);
      hmc->SetStats(0);
      imax = hmc->GetMaximumBin();
      if ( ymax < (hmc->GetBinContent(imax)+5.*hmc->GetBinError(imax)) )
	 ymax = hmc->GetBinContent(imax)+2.*hmc->GetBinError(imax);
      hd->GetYaxis()->SetRangeUser( 0., ymax );
      hmc->GetYaxis()->SetRangeUser( 0., ymax );
	    	    
      PlotHisto( hmc, icount, "histE1same", 0 );

/* plot MC sperad if requested */

      if ( plot_mc_spread )
      {
         for ( int ikd=0; ikd<nkeys; ++ikd )
         {

           TKey* key = (TKey*)(keys->At(ikd));
           std::string key_class_name = key->GetClassName();
           if ( key_class_name.find("Directory") == std::string::npos ) continue;

           TObject* obj = keys->At(ikd);
                  
           std::string dir_name = obj->GetName();
	 
	   // skip Default as we've already plotted it
	   //
	   if ( dir_name.find("Default") != std::string::npos ) continue;
	 
	   std::string huniname = dir_name + "/MC4Professor/" + hdname;
	   TH1D* huni = (TH1D*)file->Get( huniname.c_str() );
	   if ( !huni ) continue;
           huni->SetLineColor(kGreen);
           huni->SetStats(0);
           imax = huni->GetMaximumBin();
           if ( ymax < (huni->GetBinContent(imax)+5.*huni->GetBinError(imax)) )
	      ymax = huni->GetBinContent(imax)+5.*huni->GetBinError(imax);
           hd->GetYaxis()->SetRangeUser( 0., ymax );
           huni->GetYaxis()->SetRangeUser( 0., ymax );
           hmc->GetYaxis()->SetRangeUser( 0., ymax );
	   PlotHisto( huni, icount, "Lsame", 1 );
      
         }
      }
      
      // re-draw data and default MC
      //
      PlotHisto( hmc, icount, "histE1same", 0 );
      PlotHisto( hd, icount, "psame", 0 );

      // only one canvas in case of ITEP-like benchmark
      size_t icnv = 0;
      
      if ( icnv >= 0 && icnv < canvas.size() )
      {
         double thechi2 = Chi2( hd, hmc );
	 chi2_def[icnv] += thechi2; // --> Chi2( hd, hmc );
	 NDF[icnv] += hd->GetNbinsX();
	 std::cout << " thechi2 = " << thechi2 << std::endl;
	 std::cout << " chi2_def[" << icnv << "] / NDF = " 
	           << chi2_def[icnv] << "/" << NDF[icnv] << std::endl;
      }

      // plot fits, if requested
      //
      if ( plot_fits )
      {
	 TGraphAsymmErrors* gfits = (TGraphAsymmErrors*)file_fits->Get( hd->GetName() );
	 gfits->SetLineColor(kBlue);
	 gfits->SetLineWidth(2);
	 PlotGraph( gfits, icount, "same" );
	 chi2_fit[icnv] += Chi2( hd, gfits );
      }

      if ( plot_sim_best_fit )
      {
         TList* keys_sim_best_fit = file_sim_best_fit->GetListOfKeys();
         int nkeys_sim_best_fit   = keys_sim_best_fit->GetEntries();
         for ( int ibest=0; ibest<nkeys_sim_best_fit; ++ibest )
         {
           if ( ibest > 1 ) continue; // it's >1 because there might also be "Default" dir
	   TKey* key_best = (TKey*)(keys_sim_best_fit->At(ibest));
           std::string key_best_name = key_best->GetClassName();
           if ( key_best_name.find("Directory") == std::string::npos ) continue;

           TObject* obj_best = keys_sim_best_fit->At(ibest);
                  
           std::string dir_best_name = obj_best->GetName();
	 
	   // skip Default, if any, as we've already plotted it
	   //
	   if ( dir_best_name.find("Default") != std::string::npos ) continue;

	   std::string hbestname = dir_best_name + "/MC4Professor/" + hdname;
	   TH1D* hbest = (TH1D*)file_sim_best_fit->Get( hbestname.c_str() );
	   if ( !hbest ) continue;
           hbest->SetLineColor(kCyan+1); // kMagenta);
	   hbest->SetLineWidth(3);
           hbest->SetStats(0);
	   PlotHisto( hbest, icount, "histE1same", 1 );
// -->	   chi2_sim_best_fit[icnv] += Chi2( hd, hbest );
         double thebestchi2 = Chi2( hd, hbest );
	 chi2_sim_best_fit[icnv] += thebestchi2; // --> Chi2( hd, hmc );
	 std::cout << " thebestchi2 = " << thebestchi2 << std::endl;
	 std::cout << " chi2_sim_best_fit[" << icnv << "] / NDF = " 
	           << chi2_sim_best_fit[icnv] << "/" << NDF[icnv] << std::endl;
	 }
      }
      
      if ( plot_sim_retro )
      {
         TList* keys_sim_retro = file_sim_retro->GetListOfKeys();
         int nkeys_sim_retro   = keys_sim_retro->GetEntries();
         for ( int iretro=0; iretro<nkeys_sim_retro; ++iretro )
         {
           if ( iretro > 1 ) continue; // it's >1 because there might also be "Default" dir
	   TKey* key_retro = (TKey*)(keys_sim_retro->At(iretro));
           std::string key_retro_name = key_retro->GetClassName();
           if ( key_retro_name.find("Directory") == std::string::npos ) continue;

           TObject* obj_retro = keys_sim_retro->At(iretro);
                  
           std::string dir_retro_name = obj_retro->GetName();
	 
	   // skip Default, if any, as we've already plotted it
	   //
	   if ( dir_retro_name.find("Default") != std::string::npos ) continue;

	   std::string hretroname = dir_retro_name + "/MC4Professor/" + hdname;
	   TH1D* hretro = (TH1D*)file_sim_retro->Get( hretroname.c_str() );
	   if ( !hretro ) continue;
           hretro->SetLineColor(kGreen+2);
	   hretro->SetLineWidth(2);
           hretro->SetStats(0);
	   PlotHisto( hretro, icount, "histE1same", 1 );
	   chi2_sim_retro[icnv] += Chi2( hd, hretro );
	 }
      }

      // draw histo titles
      //
      std::string htitle = hmc->GetTitle();
      double x1 = hd->GetBinCenter(1) - hd->GetBinWidth(1);
      double x2 = hd->GetBinCenter(hd->GetNbinsX()) + hd->GetBinWidth(hd->GetNbinsX());
      double xpos = x1 + 0.35*(x2-x1) ;
      TLatex* hltxt = new TLatex( xpos, 0.9*ymax, htitle.c_str() );
      hltxt->SetTextSize(0.06);
      //
      // NOTE: we're already at the hd/hmc histogram, and that's where
      //       we need to be in order to draw a text over it
      // 
// -->      hltxt->Draw();

      hkey_def = (TKey*)itr_def();

   }

   for ( size_t ih=0; ih<canvas.size(); ++ih )
   {
      std::string gtitle = "G4/FTF: " + momentum + " " + beam + " on " + target
                         + " #rightarrow " + secondary + " + X; data by " + experiment;
//      gtitle += " (N. Abgrall et al. ,  Eur.Phys.J.C 76, 2016) ";
      TLatex* gltxt = new TLatex( 0.3, 0.955, gtitle.c_str() );
      gltxt->SetTextSize(0.05 ); // 0.025);
      canvas[ih]->cd();
// -->       gltxt->Draw();
      canvas[ih]->Update(); 
      std::string output = canvas[ih]->GetName();
      output += ".png";
      canvas[ih]->Print( output.c_str() );
   }
   
   for ( size_t indf=0; indf<NDF.size(); ++indf )
   {
      std::cout << " DEFAULT:      chi2/NDF = " << chi2_def[indf] <<  "/" << NDF[indf] << std::endl;
      std::cout << " FITS:         chi2/NDF = " << chi2_fit[indf] <<  "/" << NDF[indf] << std::endl;
      std::cout << " SIM BEST FIT: chi2/NDF = " << chi2_sim_best_fit[indf] <<  "/" << NDF[indf] << std::endl;
      std::cout << " SIM FIT 2019: chi2/NDF = " << chi2_sim_retro[indf] <<  "/" << NDF[indf] << std::endl;
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
   chi2_sim_retro.clear();
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
   pads.push_back( new TPad( padname.c_str(), "", 0.01, 0.01, 0.99, 0.99) ); // 0.95 ) ); //0.97 ) );
   
//    pads.back()->SetLeftMargin(0.25);
   pads.back()->SetBottomMargin(0.2);
   
   // divide by 2 in Y, num-of-theta's/2 in X
   //
   int nxpd = theta_itep771.size() ; // / 2 ;
//   pads.back()->Divide( nxpd, 2, 0.01, 0.01 ); 
   pads.back()->Divide( nxpd, 1, 0.01, 0.01 ); 
      
   canvas.back()->cd();
   pads.back()->Draw();
   
   chi2_def.push_back(0.);
   chi2_fit.push_back(0.);
   chi2_sim_best_fit.push_back(0.);
   chi2_sim_retro.push_back(0.);
   NDF.push_back(0);

   return;

}

