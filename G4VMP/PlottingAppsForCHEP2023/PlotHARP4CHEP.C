#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

#include <math.h>
#include <vector>

#include "Rtypes.h"

#include "general.h"

#include "/work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0/G4ValHAD/test23/shared-root-macros/ReadHARPData.C"

#include "/work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0/G4ValHAD/test23/shared-root-macros/Chi2Calc.C"

std::string g4valhad="/work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0/G4ValHAD/";
std::string def=g4valhad+"test19-11.1.r00-build/harp-histo/";
std::string tune=g4valhad+"test19-tune2022-11.1.r00-build/harp-histo/";

std::vector<TCanvas*> canvas;
std::vector<TPad*> pads;

#include "PlotHisto.C"
#include "PlotGraph.C"
void PrepareCanvas();

void PlotHARP4CHEP()
{

   ReadHARPData( "proton", "Ta", "12.0", "piminus", "LA" );
   
   std::string fname_def  = def + "protonTa12.0GeVftfp.root";
   std::string fname_tune = tune + "protonTa12.0GeVftfp.root";
   
   TFile* file_def  = TFile::Open( fname_def.c_str()  );
   TFile* file_tune = TFile::Open( fname_tune.c_str() );
   
   PrepareCanvas();
   
   std::vector<int> id;
   id.push_back(1);
   id.push_back(6);
   
   std::string hname_base = "piminus_LA_"; // _1";
   
   for ( int i=0; i<id.size(); ++i )
   {   
      
      std::string hname = hname_base + std::to_string(id[i]);
      
      TH1D* hdef = (TH1D*)file_def->Get(hname.c_str());

      double ymax = -1.;
      int imax = hdef->GetMaximumBin();
      if ( ymax < (hdef->GetBinContent(imax)+5.*hdef->GetBinError(imax)) )
	   ymax = hdef->GetBinContent(imax)+5.*hdef->GetBinError(imax);

      hdef->SetLineColor(kRed);
      hdef->SetLineWidth(2);
      hdef->SetStats(0);
      hdef->SetTitle("");
      hdef->GetXaxis()->SetTitle("momentum of secondary pi- [GeV/c]");
      hdef->GetYaxis()->SetTitle("Cross section [mb/rad/(GeV/c)]");
      hdef->GetXaxis()->SetLabelFont(62);
      hdef->GetYaxis()->SetLabelFont(62);
      hdef->GetXaxis()->SetTitleFont(62);
      hdef->GetYaxis()->SetTitleFont(62);
      hdef->GetXaxis()->SetTitleOffset(1.);
      hdef->GetYaxis()->SetTitleOffset(1.);
      hdef->GetXaxis()->SetTitleSize(0.05);
      hdef->GetYaxis()->SetTitleSize(0.05);
      hdef->GetXaxis()->CenterTitle();
      hdef->GetYaxis()->CenterTitle();
      hdef->GetYaxis()->SetRangeUser( 0., ymax );
      PlotHisto( hdef, i, "histE1", 0 );
   
      TGraphErrors* data = getHARPAsGraph(id[i]);
      int ndata = data->GetN();
      double* ydata = data->GetY();
      double* eydata = data->GetEY();
      for ( int i=0; i<ndata; ++i )
      {
         if ( ymax < (ydata[i]+eydata[i]) )
	      ymax = ydata[i] + eydata[i]; 
      }
      hdef->GetYaxis()->SetRangeUser( 0., ymax );
      data->SetMarkerColor(kBlack);
      data->SetMarkerStyle(22);
      data->SetMarkerSize(1.5);
      PlotGraph( data, i, "psame" );
      
      TH1D* htune = (TH1D*)file_tune->Get(hname.c_str() );
      imax = htune->GetMaximumBin();
      if ( ymax < (htune->GetBinContent(imax)+5.*htune->GetBinError(imax)) )
	   ymax = htune->GetBinContent(imax)+5.*htune->GetBinError(imax);
      htune->SetLineColor(kCyan+1);
      htune->SetLineWidth(3);
      htune->SetStats(0);
      htune->SetTitle("");
      htune->GetXaxis()->SetLabelFont(62);
      htune->GetYaxis()->SetLabelFont(62);
      htune->GetXaxis()->SetTitleFont(62);
      htune->GetYaxis()->SetTitleFont(62);
      htune->GetYaxis()->SetTitleOffset(1.5);
      htune->GetXaxis()->CenterTitle();
      htune->GetYaxis()->CenterTitle();
      htune->GetYaxis()->SetRangeUser( 0., ymax );
      hdef->GetYaxis()->SetRangeUser( 0., ymax );
      PlotHisto( htune, i, "histE1same", 0 );

   }
   
   std::string output = canvas[0]->GetName();
   output += ".png";
   canvas[0]->Print( output.c_str() );
   
   return;
   
}

void PrepareCanvas()
{

   canvas.clear();
   pads.clear();
      
   std::string cname = "cnv_FTFP_proton12.0GeV_Pb_piminus_HARP";
   canvas.push_back( new TCanvas( cname.c_str(), "", 920, 350 ) );
   std::string padname = "pad_FTFP_proton12.0GeV_Pb_piminus_HARP";
   pads.push_back( new TPad( padname.c_str(), "", 0.01, 0.01, 0.99, 0.99 ) );
   pads.back()->SetBottomMargin(0.2); 
   pads.back()->Divide( 2, 1, 0.01, 0.01 );
      // --> canvas.back()->Divide( 4, 3, 0.01, 0.01 );
   canvas.back()->cd();
   pads.back()->Draw();

   return;

}
