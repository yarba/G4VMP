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

#include "Chi2.C"

int FindGoodUniv()
{

   std::string flocation = 
   "/wclustre/g4v/yarba_j/g4vmp-study/ana-g4.11.1.r07-pion-Diff-NP200/analysis_FTFP_piplus_NA61/";
   std::string fname = flocation + "FTFP_piplus60.0GeV_C-ProcL_NA61.root";
   
   std::string secondary = "piplus";
   std::string thehname = "NA61_beam211_momentum60GeV_target6_piplus_0_10";
   
   TFile* file = TFile::Open( fname.c_str() );
   
   std::string ddname = "FTFPDefaultNA61/Data4Professor/";
   std::string hdname = ddname + thehname; 
   TH1D* hd = (TH1D*)file->Get( hdname.c_str() ); 
   
   std::string univ_name_pattern = "0000";
   
   int nuniv = 200;
   
   double chi2min = FLT_MAX;
   
   int iusave = -1;
   
   for ( int iu=1; iu<=200; ++iu )
   {
      std::string count = std::to_string(iu); 
      std::string univ_name = univ_name_pattern;
      univ_name.replace( univ_name.size()-count.size(), count.size(), count ); 
      univ_name = "FTFPUniv" + univ_name + "NA61/MC4Professor/";
      std::string huname = univ_name + thehname;
      TH1D* hu = (TH1D*)file->Get( huname.c_str() );
      double thechi2 = Chi2( hd, hu );
      if ( thechi2 < chi2min )
      {
         chi2min = thechi2;
	 iusave = iu;
      }
   }
   
   std::cout << " iusave = " << iusave << " chi2min = " << chi2min << std::endl;
/* for iusave=120 :
 TObjString = FTFP: MESON_EXCI_E_PER_WNDNUCLN=58.1
 TObjString = FTFP: MESON_NUCDESTR_P1_TGT=0.001026
 TObjString = FTFP: PION_AVRG_PT2=0.395471
 TObjString = FTFP: PION_DIFF_M_TGT=2.82167
 TObjString = FTFP: PION_NONDIFF_M_TGT=2.8675
 TObjString = FTFP: PION_PROC1_A1=4.90664
 TObjString = FTFP: PION_PROC1_A2=-6.61704
 TObjString = FTFP: PION_PROC1_B1=0.323679
 TObjString = FTFP: PION_PROC1_B2=0.899831
 TObjString = FTFP: USE_MESON_NUCDESTR_P1_ADEP_TGT=1
*/
   
   std::string cnvname = "cnv_piplus60.0GeV_" + secondary + "_NA61"; 
   TCanvas* canvas = new TCanvas( cnvname.c_str(), "", 920, 690 );
   TPad*    pad = new TPad( "pad", "", 0.01, 0.01, 0.99, 0.97 );
   pad->Divide( 4, 3, 0.01, 0.01 );
   canvas->cd();
   pad->Draw();      

//    TKey* dkey = (TKey*)(keys->FindObject( "FTFPDefaultNA61/MC4Professor" ) );
   TIter itr_mc( file->GetDirectory( "FTFPDefaultNA61/MC4Professor" )->GetListOfKeys() );
   TKey* hkey_mc = (TKey*)itr_mc(); // alternative: itr_mc.Next()

   int icount = 1;

   while ( hkey_mc )
   {
      if ( !(TClass::GetClass(hkey_mc->GetClassName())->InheritsFrom(TH1::Class())) )
      {
	       hkey_mc = (TKey*)itr_mc();
	       continue;
      }
      TH1D* hmc = (TH1D*)hkey_mc->ReadObj();
      std::string hmcname = hmc->GetName();
      if ( hmcname.find( secondary ) == std::string::npos )
      {
	       hkey_mc = (TKey*)itr_mc();
	       continue;
      }
            
      std::cout << " processing/plotting data histo --> " << hmcname << std::endl;

      hmc->SetLineColor(kRed);
      hmc->SetLineWidth(2);
      hmc->SetStats(0);
      hmc->SetTitle("");
      
      pad->cd(icount);
      hmc->DrawCopy("histE1");
      
      hdname = ddname + hmcname ;
      hd = (TH1D*)file->Get( hdname.c_str() );
      hd->SetMarkerColor(kBlack);
      hd->DrawCopy("psame");
      
      std::string iusavename = std::to_string(iusave);
      std::string uname = univ_name_pattern;
      uname.replace( uname.size()-iusavename.size(), iusavename.size(), iusavename );
      uname = "FTFPUniv" + uname + "NA61/MC4Professor/";

      std::string huname = uname + hmcname;
      TH1D* hu = (TH1D*)file->Get( huname.c_str() );
      hu->SetLineColor(kMagenta+2); // kGreen);
      hu->SetLineWidth(2);
      hu->DrawCopy("histE1same");
      
      icount++;

      // draw histo titles
      //
      std::string htitle = hu->GetTitle();
      //
      // TMP stuff, need to be fixed in the analyzer...
      //
      htitle += " [mrad]";
      //
      double x1 = hd->GetBinCenter(1) - hd->GetBinWidth(1);
      double x2 = hd->GetBinCenter(hmc->GetNbinsX()) + hd->GetBinWidth(hd->GetNbinsX());
      double xpos = x1 + 0.25*(x2-x1) ;
      int imax = hmc->GetMaximumBin();
      double ymax = hmc->GetBinContent(imax) + 2.*hmc->GetBinError(imax);
      TLatex* hltxt = new TLatex( xpos, 0.9*ymax, htitle.c_str() );
      hltxt->SetTextSize(0.06);
      //
      // NOTE: we're already at the hd/hmc histogram, and that's where
      //       we need to be in order to draw a text over it
      // 
      hltxt->Draw();

      hkey_mc = (TKey*)itr_mc();
   }

      std::string gtitle = "G4/FTF: 60 GeV piplus on C #rightarrow piplus + X; data by NA61";
//      gtitle += " (N. Abgrall et al. ,  Eur.Phys.J.C 76, 2016) ";
      TLatex* gltxt = new TLatex( 0.1, 0.975, gtitle.c_str() );
      gltxt->SetTextSize(0.025);
      canvas->cd();
      gltxt->Draw();


/*
   std::string dmcname = "FTFPDefaultNA61/MC4Professor/";
   std::string hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_0_10";
   TH1D* hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_0_10";
   hd = (TH1D*)file->Get( hdname.c_str() );
      
   std::string iusavename = std::to_string(iusave);
   std::string uname = univ_name_pattern;
   uname.replace( uname.size()-iusavename.size(), iusavename.size(), iusavename );
   uname = "FTFPUniv" + uname + "NA61/MC4Professor/";

   std::string huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_0_10";
   TH1D* hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);

   pad->cd(1);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_10_20";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_10_20";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_10_20";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(2);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_20_40";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_20_40";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_20_40";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(3);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_40_60";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_40_60";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_40_60";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(4);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_60_100";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_60_100";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_60_100";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(5);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_100_140";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_100_140";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_100_140";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(6);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");

   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_140_180";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_140_180";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_140_180";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(7);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
   
   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_180_240";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_180_240";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_180_240";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(8);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");

   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_240_300";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_240_300";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_240_300";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(9);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");

   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_300_360";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_300_360";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_300_360";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(10);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");

   hmcname = dmcname + "NA61_beam211_momentum60GeV_target6_piplus_360_420";
   hmc = (TH1D*)file->Get( hmcname.c_str() );
   hmc->SetLineColor(kRed);
   hmc->SetLineWidth(2);
   hmc->SetStats(0);
   hdname = ddname + "NA61_beam211_momentum60GeV_target6_piplus_360_420";
   hd = (TH1D*)file->Get( hdname.c_str() );
   huname = uname + "NA61_beam211_momentum60GeV_target6_piplus_360_420";
   hu = (TH1D*)file->Get( huname.c_str() );
   hu->SetLineColor(kGreen);
   hu->SetLineWidth(2);
   
   pad->cd(11);
   hmc->DrawCopy("histE1");
   hd->DrawCopy("psame");
   hu->DrawCopy("histE1same");
*/   
   
   std::string output = canvas->GetName();
   output += "_FindGoodUniv.png";
   canvas->Print( output.c_str() );
   
   return 0;

}
