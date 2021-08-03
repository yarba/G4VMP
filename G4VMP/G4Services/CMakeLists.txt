# services CMakeLists

#art_make( SERVICE_LIBRARIES  
#          "artg4tk_G4PhysModelParamStudy_G4Components" 
#	  "artg4tk_geantInit" 
#	  "${XERCESCLIB}" 
#	  "${G4_LIB_LIST}" )

art_make( SERVICE_LIBRARIES  
          G4VMP_G4WrapperComponents
          ${ART_FRAMEWORK_CORE}
          ${ART_PERSISTENCY_PROVENANCE} 
          ${MF_MESSAGELOGGER} )

install_headers()
