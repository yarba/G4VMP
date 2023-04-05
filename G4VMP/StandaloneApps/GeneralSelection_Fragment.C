
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
