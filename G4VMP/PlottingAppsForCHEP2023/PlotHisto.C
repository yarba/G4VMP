
void PlotHisto( TH1* histo, int icount, std::string opt, int drawtype )
{
   
   if ( icount < 0 || icount >= pads[0]->GetListOfPrimitives()->GetSize() ) return;

   pads[0]->cd(icount+1);
   if ( LogX )
   {
      gPad->SetLogx();
   }
   if ( LogY )
   {
      gPad->SetLogy();
   }
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
