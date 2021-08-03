
find_program(ROOT_CONFIG_EXECUTABLE root-config PATHS ${ROOTSYS}/bin $ENV{ROOTSYS}/bin)

execute_process(
    COMMAND ${ROOT_CONFIG_EXECUTABLE} --libs 
    OUTPUT_VARIABLE ROOT_LIBRARIES 
    OUTPUT_STRIP_TRAILING_WHITESPACE)

art_make( LIB_LIBRARIES  
	  art_root_io::TFileService_service
	  G4VMP_ExpDataAccess
	  G4VMP_DataProducts_Analysis 
	  G4VMP_DataProducts_Analysis_dict 
	  ${G4_LIB_LIST}
	  ${ROOT_LIBRARIES} )

