# G4VMP
A collection of applications and scripts to study the effect of Geant4 model parameters variations.

It is based on Geant4 simulation toolkit (https://geant4.web.cern.ch) and is interfaced to art and art_root_io frameworks developed at Fermilab (www.fnal.gov).

The software is an open source but no support is provided.

Get it as follows:

git clone git@github.com:yarba/G4VMP.git (SSH)

git clone https://github.com/yarba/G4VMP.git (HTTPS)

This revision is compatible with geant4-10-07-ref-05 as well as art v3_09_02 and art_root_io v1_08_02 (via setup of critic v2_08_02 portmanteau).
Compiler gcc/g++ and CLHEP 2.4.4.1 will be set up as part of art.
Root will be set up as part of art_root_io.
Also required are cmake v3_20_0 and mrb v5_10_00 (both are required by art v3_09_02).
To build Geant4 one also needs xerces_c v3_2_3.

=====================================================================

Example procedure:

source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup critic v2_08_02 -q e20:prof

setup xerces_c v3_2_3 -q e20:prof

setup cmake v3_20_0

cd <path-to-your-g4-area>

git clone ssh://git@gitlab.cern.ch:7999/geant4/geant4-dev.git geant4-10-07-ref-05

cd geant4-10-07-ref-05

git checkout geant4-10-07-ref-05

export G4INSTALL=$PWD

cd ..

mkdir geant4-10-07-ref-05-build

cd geant4-10-07-ref-05-build

NOTE: make sure to include -DGEANT4_USE_GDML=ON 
      in case geometry input is envisioned
NOTE: if one wants to build static libs instead of shared ones,
      one should all to cmake the following options:
      -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
NOTE: since mid-10.7.ref-XX cycle, c++17 is STANDARD, 
      so there's no need to explicitly specify -DGEANT4_BUILD_CXXSTD=17 
      also, since ref-05, CMAKE_CXX_STANDARD replaces GEANT4_BUILD_CXXSTD

cmake -DCMAKE_INSTALL_PREFIX=$G4INSTALL \
-DGEANT4_USE_GDML=ON -DXERCESC_ROOT_DIR=$XERCESCROOT \
-DGEANT4_USE_SYSTEM_CLHEP=ON \
-DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc \
$G4INSTALL

make -j8

make install

cd <your-G4VMP-area>

setup mrb v5_10_00

export MRB_PROJECT=G4VMP

mrb newDev [ -v vX_YY_ZZ -q eXY:prof ]

source localProducts*/setup

=========================================================

JUST an EXAMPLE: 

mrb newDev -v dev -q e20:prof
source localProducts_G4VMP_dev_e20_prof/setup
  
NOTE: Add NEW PACKAGE to $MRB_SOURCE/srcs (e.g. G4VMP), THEN run "mrb uc" so that 
      srcs/CMakeLists.txt is updated accordingly, and files .cmake_add_subdirs and
      .cmake_include_dirs are also updated properly
      This was NOT the case with (much) earlier versions of the tools...

=========================================================

cd $MRB_SOURCE}/srcs

git clone git@github.com:yarba/G4VMP.git 

mrb uc

mrbsetenv

cd $MRB_SOURCE}/srcs/G4VMP

source ./geant4make-no-ups.sh geant4-10-07-ref-05 <path-to-your-g4-area>

cd $MRB_BUILDDIR

mrb b




