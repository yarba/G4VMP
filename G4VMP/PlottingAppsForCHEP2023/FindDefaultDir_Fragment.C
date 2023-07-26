   
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
   
