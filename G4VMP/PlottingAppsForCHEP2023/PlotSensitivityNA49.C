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

// later...
// NA49
std::string momentum   = "158.0GeV";
std::string target     = "C";
std::string experiment = "NA49";

std::vector<std::string> label_na49;

std::string dir_fits =
   "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-qex-proc0-HARP-NA61-tst3/tunes-poly4-all-no-scan" ;  
// std::string dir_sim_best_fit = "bestfit-qex-proc1-nucdestr-p1";  
std::string dir_sim_best_fit = "tune-candidate-NucDestrProc1QEX-2022-tst3";

std::vector<TCanvas*> canvas;
std::vector<TPad*> pads;
std::vector<double> chi2_def;
std::vector<double> chi2_fit;
std::vector<double> chi2_sim_best_fit;
std::vector<int> NDF;

void PrepareCanvas();
void PlotHisto( TH1*, int, std::string, int );
void PlotGraph( TGraph*, int, std::string );

#include "Chi2.C"

void PlotSensitivityNA49( std::string dir_local, 
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
   
   // alternative labels can be e.g. "_pT_DDIFF_10", etc. 
   //
   label_na49.push_back("_dNdxF");
   label_na49.push_back("_pT");
//   label_na49.push_back("_pT_DDIFF_10");
//   label_na49.push_back("_pT_DDIFF_15");
//   label_na49.push_back("_pT_DDIFF_20");
//   label_na49.push_back("_pT_DDIFF_25");
   
   std::vector<std::string> skip;
   skip.push_back("DDIFF");
   
   file_dir_local += "/analysis_" + model + "_" + beam + "_" + experiment;
      
   std::string fname = file_dir_global + "/"
                     + file_dir_local;
   fname += "/" + model + "_" + beam + momentum 
          + "_" + target + "-ProcL_" + experiment + ".root";

   file = TFile::Open( fname.c_str() );
   
   std::string fitsname = dir_fits + "/" + "ipolhistos.root";
// --> Apprentice -->   std::string fitsname = dir_fits + "/" + "predictions_ncg_25_1.root";
   TFile* file_fits = 0 ;
   if ( plot_fits )
   {
      file_fits = TFile::Open( fitsname.c_str() );
   }
      
   std::string fname_sim_best_fit = file_dir_global + "/" + dir_sim_best_fit;
   fname_sim_best_fit += "/analysis_" + model + "_" + beam + "_" + experiment;
   fname_sim_best_fit += "/" + model + "_" + beam + momentum 
                        + "_" + target + "-ProcL_" + experiment + ".root";

                        + "_" + target + "-ProcL_" + experiment + ".root";
   
   TFile* file_sim_best_fit = 0;
   if ( plot_sim_best_fit ) 
   {
      file_sim_best_fit = TFile::Open( fname_sim_best_fit.c_str() );
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
      
      bool label_found = false;
      for ( size_t il=0; il<label_na49.size(); ++il )
      {
	 if ( hdname.find( label_na49[il]  ) != std::string::npos  )
	 {
	    label_found = true;
	    break;
	 }
      }
            
      if ( ! label_found )
      {
	 hkey_def = (TKey*)itr_def();
	 continue;
      }

      bool skip_found = false;
      for ( size_t isk=0; isk<skip.size(); ++isk )
      {
         if ( hdname.find(skip[isk]) != std::string::npos )
	 {
	    skip_found = true;
	    break;
	 }
      }
      if ( skip_found )
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
      hd->GetXaxis()->SetTitleFont(62);
      hd->GetYaxis()->SetTitleFont(62);
      hd->GetYaxis()->SetTitleOffset(1.5);
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
      
      // plot MC spread if requested
      //
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

      int icnv = 0;
      
      double thechi2 = Chi2( hd, hmc );
      std::cout << hd->GetName()  << " --> " << thechi2 << "/" << hd->GetNbinsX() << std::endl;
      chi2_def[icnv] += thechi2; // --> Chi2( hd, hmc );
      NDF[icnv] += hd->GetNbinsX();
            
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
           hbest->SetLineColor(kMagenta);
	   hbest->SetLineWidth(2);
           hbest->SetStats(0);
	   PlotHisto( hbest, icount, "histE1same", 1 );
           std::cout << hd->GetName() << " --> " << Chi2(hd,hbest) << "/" << hd->GetNbinsX() << std::endl;
	   chi2_sim_best_fit[icnv] += Chi2( hd, hbest );
	 }
      }

      // draw histo titles
      //
      // std::string htitle = hmc->GetTitle();
      // std::string htitle = momentum + " GeV/c " + beam + "+" + target + " -> " + secondary;
      std::string htitle = "secondary " + secondary;
      double x1 = hd->GetBinCenter(1) - hd->GetBinWidth(1);
      double x2 = hd->GetBinCenter(hd->GetNbinsX()) + hd->GetBinWidth(hd->GetNbinsX());
      double xpos = x1 + 0.2*(x2-x1) ;
      TLatex* hltxt = new TLatex( xpos, 0.95*ymax, htitle.c_str() );
      hltxt->SetTextSize(0.04);
      //
      // NOTE: we're already at the hd/hmc histogram, and that's where
      //       we need to be in order to draw a text over it
      // 
      hltxt->Draw();

      // move the counter before going the loop again
      //
      hkey_def = (TKey*)itr_def();

   }

   for ( size_t ih=0; ih<canvas.size(); ++ih )
   {
      std::string gtitle = "G4/FTF: " + momentum + " " + beam + " on " + target
                         + " #rightarrow " + secondary + " + X; data by " + experiment;
      TLatex* gltxt = new TLatex( 0.1, 0.975, gtitle.c_str() );
      gltxt->SetTextSize(0.025);
      canvas[ih]->cd();
      gltxt->Draw();
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
   canvas.push_back( new TCanvas( cname.c_str(), "", 920, 690 ) );
   std::string padname = "pad_" + model + "_" + beam + momentum + "_" + target + "_" + secondary + "_"
                       + experiment;
   pads.push_back( new TPad( padname.c_str(), "", 0.01, 0.01, 0.99, 0.97 ) );
   
   // divide by 2 in Y, num-of-theta's/2 in X
   //
   int nxpd = label_na49.size();
   if ( nxpd <= 0 ) return; 
   if ( nxpd > 2 )
   {
      nxpd /= 2;
      pads.back()->Divide( nxpd, 2, 0.01, 0.01 );
   }
   else
   {
      pads.back()->Divide( nxpd, 1, 0.01, 0.01 ); 
   }
      
   canvas.back()->cd();
   pads.back()->Draw();
   chi2_def.push_back(0.);
   chi2_fit.push_back(0.);
   chi2_sim_best_fit.push_back(0.);
   NDF.push_back(0);

   return;

}

void PlotHisto( TH1* histo, int icount, std::string opt, int drawtype )
{
   
   if ( icount < 0 || icount >= pads[0]->GetListOfPrimitives()->GetSize() ) return;

   pads[0]->cd(icount+1);
   gPad->Update();
   pads[0]->Update();
   canvas[0]->Update();
   if ( drawtype == 0 )
   {
         histo->Draw( opt.c_str() );
   }
   else if ( drawtype == 1 )
   {
         histo->DrawCopy( opt.c_str() );
   }
   gPad->Update();
   pads[0]->Update();
   canvas[0]->Update();
      
   return;

}

void PlotGraph( TGraph* gr, int icount, std::string opt )
{

   if ( icount < 0 || icount >= pads[0]->GetListOfPrimitives()->GetSize() ) return;
      pads[0]->cd(icount+1);
      gPad->Update();
      pads[0]->Update();
      canvas[0]->Update();
      gr->Draw( opt.c_str() );
      gPad->Update();
      pads[0]->Update();
      canvas[0]->Update();
      
   return;

}
