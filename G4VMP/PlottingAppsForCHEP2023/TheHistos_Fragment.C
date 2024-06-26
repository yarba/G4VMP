
      double ymax = -1.;
      double ymin = 1000000.;
      
      // find maximum & minimum
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
      hd->GetXaxis()->SetTitleOffset(1.);
      hd->GetYaxis()->SetTitleOffset(1.);
      hd->GetXaxis()->SetTitleSize(0.05);
      hd->GetYaxis()->SetTitleSize(0.05);
      hd->GetXaxis()->CenterTitle();
      hd->GetYaxis()->CenterTitle();
      if ( LogY )
      {
         int imin = hd->GetMinimumBin();
         if ( ymin > (hd->GetBinContent(imin)-2.*hd->GetBinError(imin)) )
            ymin = hd->GetBinContent(imin)-2.*hd->GetBinError(imin);
         ymin = std::min(ymin,0.01);
	 hd->GetYaxis()->SetRangeUser( ymin, ymax );
      }
      else
      {
         hd->GetYaxis()->SetRangeUser( 0., ymax );
      }
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
      if ( ymax < (hmc->GetBinContent(imax)-2.*hmc->GetBinError(imax)) )
	 ymax = hmc->GetBinContent(imax)-2.*hmc->GetBinError(imax);
      if ( LogY )
      {
         int imin = hmc->GetMinimumBin();
         if ( ymin < (hmc->GetBinContent(imin)-2.*hmc->GetBinError(imin)) )
	    ymin = hmc->GetBinContent(imin)-2.*hmc->GetBinError(imin);
         ymin = std::min(ymin,0.01);
         hd->GetYaxis()->SetRangeUser( ymin, ymax );
         hmc->GetYaxis()->SetRangeUser( ymin, ymax );
      }
      else
      {
         hd->GetYaxis()->SetRangeUser( 0., ymax );
         hmc->GetYaxis()->SetRangeUser( 0., ymax );
      }
	    	    
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
           if ( LogY )
	   {
              int imin = huni->GetMinimumBin();
              if ( ymin < (hmc->GetBinContent(imin)-2.*huni->GetBinError(imin)) )
	         ymin = huni->GetBinContent(imin)-2.*huni->GetBinError(imin);
              ymin = std::min(ymin,0.01);
	      hd->GetYaxis()->SetRangeUser( 0., ymax );
              huni->GetYaxis()->SetRangeUser( 0., ymax );
              hmc->GetYaxis()->SetRangeUser( 0., ymax );
	   }
	   else
	   {
	      hd->GetYaxis()->SetRangeUser( 0., ymax );
              huni->GetYaxis()->SetRangeUser( 0., ymax );
              hmc->GetYaxis()->SetRangeUser( 0., ymax );
	   }
	   
	   PlotHisto( huni, icount, "Lsame", 1 );
      
         }
      }
      
      // re-draw data and default MC
      //
      PlotHisto( hmc, icount, "histE1same", 0 );
      PlotHisto( hd, icount, "psame", 0 );

      size_t pos = 0;
      std::string txt = hmc->GetTitle();
      pos = txt.find("theta");
      txt = txt.substr(pos);
      txt = "#" + txt;
      std::cout << "txt = " << txt << std::endl;
      TLatex* ltxt = new TLatex( 2., 0.3, txt.c_str() );
      ltxt->Draw();

      TLegend* lg = new TLegend( 0.125, 0.125, 0.725, 0.275 );
      lg->SetFillColor(0);
      lg->SetBorderSize(0);
      TLegendEntry* dentry = lg->AddEntry( hd, "Data", "p");
      dentry->SetTextFont(62);
      dentry->SetTextSize(0.04);

      // only one canvas in case of ITEP-like benchmark
      size_t icnv = 0;
      
      if ( icnv >= 0 && icnv < canvas.size() )
      {
         double thechi2 = Chi2( hd, hmc );

	 std::string schi2 = std::to_string( (thechi2/hd->GetNbinsX()) );
	 pos = schi2.find(".");
	 if ( pos != std::string::npos )
	 {
	    schi2 = schi2.substr(0,pos+2);
	 } 
	 schi2 = "Geant4.11.1/FTF Default :   #chi^{2}/NDF=" + schi2;
	 std::cout << "schi2 = " << schi2 << std::endl;
	 TLegendEntry* entry = lg->AddEntry( hmc, schi2.c_str(), "L");
	 entry->SetTextColor(hmc->GetLineColor());
	 entry->SetTextFont(62);
	 entry->SetTextSize(0.04);

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

      TH1D* hbest = 0;
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
	   /* TH1D* */ hbest = (TH1D*)file_sim_best_fit->Get( hbestname.c_str() );
	   if ( !hbest ) continue;
           hbest->SetLineColor(kCyan+1); // 7); // kMagenta);
	   hbest->SetLineWidth(3);
           hbest->SetStats(0);
	   if ( LogY )
	   {
	      hbest->GetYaxis()->SetRangeUser( ymin, ymax );
	   }
	   PlotHisto( hbest, icount, "histE1same", 1 );
// -->	   chi2_sim_best_fit[icnv] += Chi2( hd, hbest );
         double thebestchi2 = Chi2( hd, hbest );

	 std::string sbchi2 = std::to_string( (thebestchi2/hd->GetNbinsX()) );
	 pos = sbchi2.find(".");
	 if ( pos != std::string::npos )
	 {
	    if (sbchi2.find("0") == 0)
	    {
	       sbchi2 = sbchi2.substr(0,pos+3);
	    }
	    else
	    {
	       sbchi2 = sbchi2.substr(0,pos+2);
	    }
	 } 
	 sbchi2 = "Geant4.11.1/FTF Best Fit :   #chi^{2}/NDF=" + sbchi2;
	 std::cout << "NDF = " << hd->GetNbinsX() << std::endl;
	 std::cout << "sbchi2 = " << sbchi2 << std::endl;
	 TLegendEntry* bentry = lg->AddEntry( hbest, sbchi2.c_str(), "L");
	 bentry->SetTextFont(62);
	 bentry->SetTextColor(hbest->GetLineColor());
	 bentry->SetTextSize(0.04);

	 chi2_sim_best_fit[icnv] += thebestchi2; // --> Chi2( hd, hmc );
	 std::cout << " thebestchi2 = " << thebestchi2 << std::endl;
	 std::cout << " chi2_sim_best_fit[" << icnv << "] / NDF = " 
	           << chi2_sim_best_fit[icnv] << "/" << NDF[icnv] << std::endl;
	 }
      }
      
      lg->Draw();
      
