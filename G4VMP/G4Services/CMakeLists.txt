# services CMakeLists

#art_make( SERVICE_LIBRARIES  
#          "artg4tk_G4PhysModelParamStudy_G4Components" 
#	  "artg4tk_geantInit" 
#	  "${XERCESCLIB}" 
#	  "${G4_LIB_LIST}" )

#art_make( SERVICE_LIBRARIES  
#          G4VMP_G4WrapperComponents
#          ${ART_FRAMEWORK_CORE}
#          ${ART_PERSISTENCY_PROVENANCE} 
#          ${MF_MESSAGELOGGER} )

art_make( SERVICE_LIBRARIES  
          G4VMP_G4WrapperComponents
          art::Framework_Core
          art::Persistency_Provenance 
          messagefacility::MF_MessageLogger )

install_headers()
