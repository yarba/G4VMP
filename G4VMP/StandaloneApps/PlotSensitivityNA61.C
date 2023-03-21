#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

#include <math.h>
#include <vector>

#include "Rtypes.h"
/*
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
// NA61
std::string momentum   = "31.0GeV";
std::string target     = "C";
std::string experiment = "NA61";


//std::string dir_fits = 
//   "../ProfessorInterface/convert-TFileDirectory-to-Professor/tunes-150NP-poly4-no-extra";
//std::string dir_fits = 
//   "../ProfessorInterface/Apprentice/tunes_150np_NA61_px3qx0-ncg-scan";
//std::string dir_fits = 
//   "../ProfessorInterface/convert-TFileDirectory-to-Professor/tunes-NA61-yoda-poly3";
std::string dir_fits =
//    "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-12pars/tunes-harp-na61-fix-proc1-poly3-scan25";
//     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-qex-proc0-nucdestr-p1tgt-NA61/tunes-poly3-scan25";
//     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-bestfit-nucdestr-qex-proc0-HARP-NA61/tunes-poly4-scan25";
//     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-bestfit-nucdestr-qex-proc0-HARP-NA61/tunes-poly4-scan25";
//     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-qex-proc0-HARP-NA61/tunes-poly4-scan25";
     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-qex-proc0-HARP-NA61-tst3/tunes-poly4-all-no-scan" ;  
//
//     "/work1/g4v/yarba_j/Prof-g4.11.0-FTF-qex-proc1-HARP-NA61-tst3/tunes-all-poly4-no-scan";
//
// std::string dir_sim_best_fit = "09-09-21-best-fits";
// std::string dir_sim_best_fit = "11-10-21-best-fits";  
// std::string dir_sim_best_fit = "bestfit-qex-proc0-nucdestr-p1";  
std::string dir_sim_best_fit = "tune-candidate-NucDestrProc0QEX-2022-tst3";

std::vector<TCanvas*> canvas;
std::vector<TPad*> pads;
std::vector<double> chi2_def;
std::vector<double> chi2_fit;
std::vector<double> chi2_sim_best_fit;
std::vector<int> NDF;

void PrepareCanvas();
//void PlotHisto( TH1*, int, std::string, int );
#include "PlotHisto.C"
//void PlotGraph( TGraph*, int, std::string );
#include "PlotGraph.C"

//double Chi2( TH1*, TH1* /*, int& */ );
//double Chi2( TH1*, TGraphAsymmErrors* /*, int& */ );

#include "Chi2.C"

void PlotSensitivityNA61( std::string dir_local, 
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
   
   LogX = false;
   LogY = false;
   
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
            
      std::cout << " processing/plotting data histo --> " << hdname << std::endl;
	    
      double ymax = -1.;
      // find maximum
      //
      int imax = hd->GetMaximumBin();
      if ( ymax < (hd->GetBinContent(imax)+2.*hd->GetBinError(imax)) )
         ymax = hd->GetBinContent(imax)+2.*hd->GetBinError(imax);
      //
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
	    	    
//	    PlotHisto( hd, "p" );
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
/* */      
      // re-draw data and default MC
      //
      PlotHisto( hmc, icount, "histE1same", 0 );
      PlotHisto( hd, icount, "psame", 0 );
      
      // only one canvas in case of NA61-like benchmark
      size_t icnv = 0;
      
      std::cout << " canvas.size() = " << canvas.size() << std::endl;
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
//         std::string fitsname = dir_fits + "/" + "ipolhistos.root";
//	 TFile* file_fits = TFile::Open( fitsname.c_str() );
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

           if ( ibest > 1 ) continue;
	   TKey* key_best = (TKey*)(keys_sim_best_fit->At(ibest));
           std::string key_best_name = key_best->GetClassName();
           if ( key_best_name.find("Directory") == std::string::npos ) continue;

           TObject* obj_best = keys_sim_best_fit->At(ibest);
                  
           std::string dir_best_name = obj_best->GetName();
	 
	   // skip Default as we've already plotted it
	   //
	   if ( dir_best_name.find("Default") != std::string::npos ) continue;
	   
	   std::string hbestname = dir_best_name + "/MC4Professor/" + hdname;
	   TH1D* hbest = (TH1D*)file_sim_best_fit->Get( hbestname.c_str() );
	   if ( !hbest ) continue;
           hbest->SetLineColor(kMagenta);
	   hbest->SetLineWidth(2);
           hbest->SetStats(0);
	   PlotHisto( hbest, icount, "histE1same", 1 );
	   chi2_sim_best_fit[icnv] += Chi2( hd, hbest );
         
         }
      }
      
      // draw histo titles
      //
      std::string htitle = hmc->GetTitle();
      //
      // TMP stuff, need to be fixed in the analyzer...
      //
      htitle += " [mrad]";
      //
      double x1 = hd->GetBinCenter(1) - hd->GetBinWidth(1);
      double x2 = hd->GetBinCenter(hd->GetNbinsX()) + hd->GetBinWidth(hd->GetNbinsX());
      double xpos = x1 + 0.25*(x2-x1) ;
      TLatex* hltxt = new TLatex( xpos, 0.9*ymax, htitle.c_str() );
      hltxt->SetTextSize(0.06);
      //
      // NOTE: we're already at the hd/hmc histogram, and that's where
      //       we need to be in order to draw a text over it
      // 
      hltxt->Draw();
      	    
      hkey_def = (TKey*)itr_def();

   }
      
   for ( size_t ih=0; ih<canvas.size(); ++ih )
   {
      std::string gtitle = "G4/FTF: " + momentum + " " + beam + " on " + target
                         + " #rightarrow " + secondary + " + X; data by " + experiment;
//      gtitle += " (N. Abgrall et al. ,  Eur.Phys.J.C 76, 2016) ";
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
  
// ---> do it later if needs be...   file->Close();
   
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
   pads.back()->Divide( 4, 3, 0.01, 0.01 );
      // --> canvas.back()->Divide( 4, 3, 0.01, 0.01 );
   canvas.back()->cd();
   pads.back()->Draw();
   chi2_def.push_back(0.);
   chi2_fit.push_back(0.);
   chi2_sim_best_fit.push_back(0.);
   NDF.push_back(0);

   return;

}
/*
void PlotHisto( TH1* histo, int icount, std::string opt, int drawtype )
{
   
      // ---> if ( icount < 0 || icount >= canvas[0]->GetListOfPrimitives()->GetSize() ) return;
      if ( icount < 0 || icount >= pads[0]->GetListOfPrimitives()->GetSize() ) return;
      // --> canvas[0]->cd(icount+1);
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
*/
/*
void PlotGraph( TGraph* gr, int icount, std::string opt )
{

      // ---> if ( icount < 0 || icount >= canvas[0]->GetListOfPrimitives()->GetSize() ) return;
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
*/
/*
double Chi2( TH1* hdata, TH1* hsim  )
{

   double Chi2 = 0.;
   
   int NXData = hdata->GetNbinsX();
   int NXSim = hsim->GetNbinsX();

   for ( int k=1; k<=NXSim; ++k ) 
   { 
         double xx1 = hsim->GetBinLowEdge(k);
	 double xx2 = hsim->GetBinWidth(k);
	 for (int kk=1; kk<=NXData; ++kk )
	 {
	   
	   double xd1 = hdata->GetBinLowEdge(kk);
	   double xd2 = hdata->GetBinWidth(kk);
	   
	   if ( xx1 < (xd1+xd2/2.) && xx1+xx2 > (xd1+xd2/2.) ) // in principle, this is not safe because (in general) 
                                                               // the bin width maybe different..
	    {
	       double yy1  = hsim->GetBinContent(k);
	       double eyy1 = hsim->GetBinError(k);
	       double yd1  = hdata->GetBinContent(kk); 
	       double eyd1 = hdata->GetBinError(kk);
	       if ( ( eyy1*eyy1 + eyd1*eyd1 ) > 0 )
	       {
	          Chi2 += ( yy1 - yd1 )*( yy1 - yd1 ) / ( eyy1*eyy1 + eyd1*eyd1 );
// -->	          ++NDF;
	       } 
	       break;
	    }
	    
	 }
   }
               
   return Chi2;
   
}

double Chi2( TH1* hdata, TGraphAsymmErrors* gfits )
{
   
   double Chi2=0.;
   
   int NXData = hdata->GetNbinsX();
   int NXFits = gfits->GetN();
   
   double* XFits  = gfits->GetX();
   double* YFits  = gfits->GetY();
   double* EYFits = gfits->GetEYhigh();
   
   for ( int k=1; k<=NXData; ++k ) 
   { 
      double xx1 = hdata->GetBinLowEdge(k);
      double xx2 = hdata->GetBinWidth(k);
      for (int kk=0; kk<NXFits; ++kk )
      {
	   if ( xx1 < XFits[kk] && xx1+xx2 > XFits[kk] ) 
	    {
	       double yy1  = hdata->GetBinContent(k);
	       double eyy1 = hdata->GetBinError(k);
	       if ( ( eyy1*eyy1 + EYFits[kk]*EYFits[kk] ) > 0 )
	       {
	          Chi2 += ( yy1 - YFits[kk] )*( yy1 - YFits[kk] ) / ( eyy1*eyy1 + EYFits[kk]*EYFits[kk] );
// -->	          ++NDF;
	       } 
	       break;
	    }
      }
   }

   return Chi2;

}
*/
