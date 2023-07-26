
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
