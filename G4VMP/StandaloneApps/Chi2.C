


double Chi2( TH1* hdata, TH1* hsim /*, int& NDF */ )
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

