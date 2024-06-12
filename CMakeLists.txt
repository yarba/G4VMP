
cmake_minimum_required (VERSION 3.18...3.22 FATAL_ERROR)

find_package(cetbuildtools REQUIRED)

project(G4VMP)

list(APPEND CMAKE_MODULE_PATH $ENV{CANVAS_ROOT_IO_DIR}/Modules $ENV{ART_DIR}/Modules)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS CAUTIOUS WERROR NO_UNDEFINED EXTRA_FLAGS -pedantic)

cet_report_compiler_flags()

# Locate some UPS areas (the versions are just minimum required) and setup include paths
# These are needed for Art/ArtIO stuff
#
find_ups_product(art)
find_ups_product(art_root_io)
find_ups_boost()
find_ups_product(canvas)
find_ups_product(canvas_root_io)
find_ups_product(cetlib_except)
find_ups_product(clhep)
find_ups_product(fhiclcpp)

# We need xerces_c for a geant library
# find_library( XERCESCLIB  NAMES xerces-c PATHS $ENV{XERCESCROOT}/lib NO_DEFAULT_PATH )
#
# OK, now there's a better way to find xerces_c libraries...
find_ups_product(xerces_c)

# This is the tricky spot !!!
#
set( G4INSTALL $ENV{G4INSTALL} )
#
IF (NOT G4INSTALL) 
# FIXME: this will need to be updated !!!
MESSAGE ( STATUS "Looking for UPS product geant4" )
find_ups_geant4()
ELSE()
#
MESSAGE ( STATUS "Building vs local geant4 (non-ups)" )
#
include_directories ( $ENV{G4INCLUDE} )
include_directories ( $ENV{G4INCLUDE}/Geant4 )

find_library( G4FR NAMES G4FR PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GMOCREN NAMES G4GMocren PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4OPENGL NAMES G4OpenGL PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4RAYTRACER  NAMES G4RayTracer PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4TREE  NAMES G4Tree PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4VRML  NAMES G4VRML PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4ANALYSIS  NAMES G4analysis PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4DIGITS_HITS  NAMES G4digits_hits PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4ERROR_PROPAGATION  NAMES G4error_propagation PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4EVENT  NAMES G4event PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GEOMETRY  NAMES G4geometry PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GL2PS  NAMES G4gl2ps PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GLOBAL  NAMES G4global PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GRAPHICS_REPS  NAMES G4graphics_reps PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4INTERCOMS  NAMES G4intercoms PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4INTERFACES  NAMES G4interfaces PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4MATERIALS NAMES G4materials PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4MODELING  NAMES G4modeling PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4PARMODELS  NAMES G4parmodels PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4PARTICLES  NAMES G4particles PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
# NOTE: Since 11.1.r06 (11.2.b01) G4persistency splits into
#       G4mctruth, G4geomtext and (optional) G4gdml 
# --> NO MORE --> find_library( G4PERSISTENCY  NAMES G4persistency PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4MCTRUTH  NAMES G4mctruth PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GEOMTEXT  NAMES G4geomtext PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4GDML  NAMES G4gdml PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
#
find_library( G4PHYSICSLISTS  NAMES G4physicslists PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4PROCESSES  NAMES G4processes PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4READOUT  NAMES G4readout PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4RUN  NAMES G4run PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4TRACK  NAMES G4track PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4TRACKING  NAMES G4tracking PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4VISHEPREP  NAMES G4visHepRep PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4VIS_MANAGEMENT  NAMES G4vis_management PATHS $ENV{G4LIB} NO_DEFAULT_PATH )
find_library( G4ZLIB  NAMES G4zlib PATHS $ENV{G4LIB} NO_DEFAULT_PATH )

set( G4_LIB_LIST ${XERCESC}
                 ${G4FR}
                 ${G4GMOCREN}
                 ${G4RAYTRACER}
                 ${G4TREE}
                 ${G4VRML}
                 ${G4ANALYSIS}
                 ${G4DIGITS_HITS}
                 ${G4ERROR_PROPAGATION}
                 ${G4EVENT}
                 ${G4GEOMETRY}
                 ${G4GLOBAL}
                 ${G4GRAPHICS_REPS}
                 ${G4INTERCOMS}
                 ${G4INTERFACES}
                 ${G4MATERIALS}
                 ${G4MODELING}
                 ${G4PARMODELS}
                 ${G4PARTICLES}
		 ${G4MCTRUTH}
		 ${G4GEOMTEXT}
		 ${G4GDML}
                 ${G4PHYSICSLISTS}
                 ${G4PROCESSES}
                 ${G4READOUT}
                 ${G4RUN}
                 ${G4TRACK}
                 ${G4TRACKING}
                 ${G4VISHEPREP}
                 ${G4VIS_MANAGEMENT}
                 ${G4ZLIB}
)

IF ( G4OPENGL AND G4GL2PS )
MESSAGE ( STATUS "Adding OpenGL librarirs: ${G4OPENGL} ${G4GL2PS}" )
set( G4_LIB_LIST ${G4_LIB_LIST} ${G4OPENGL} ${G4GL2PS} )
# Enable visualization using OpenGL in x windows
#
MESSAGE (STATUS "Adding OpenGL definitions" )
add_definitions(-DG4_STORE_TRAJECTORY -DG4VERBOSE -DG4UI_USE -DG4VIS_USE -DG4UI_USE_TCSH -DG4INTY_USE_XT -DG4VIS_USE_OPENGLX -DG4VIS_USE_OPENGL)
ELSE()
MESSAGE ( STATUS "OpenGL option disabled" )
ENDIF()

ENDIF()

find_ups_product(messagefacility)

# macros for dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

# Build these directories
add_subdirectory( G4VMP )
# add_subdirectory( fcl )
# add_subdirectory( gdml )
	
# ups - table and config files
#
add_subdirectory(ups)


# packaging utility
#
include(UseCPack)
