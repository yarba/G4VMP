
# set_source_files_properties(ModelParamStudyProducer_module.cc 
#                             PROPERTIES 
#                             COMPILE_FLAGS -I$ENV{G4INCLUDE}/Geant4)

art_make( MODULE_LIBRARIES  
	  G4VMP_G4WrapperComponents
	  G4VMP_DataProducts_Interactions
	  G4VMP_DataProducts_ModelConfig
	  G4VMP_G4Services_ProcLevelSimSetup_service
	  G4VMP_G4Services_PhysModelConfig_service
	  ${G4_LIB_LIST}
	)
