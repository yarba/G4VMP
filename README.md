# G4VMP
A collection of applications and scripts to study the effect of Geant4 model parameters variations.

It is based on Geant4 simulation toolkit (https://geant4.web.cern.ch) and is interfaced to art and art_root_io frameworks developed at Fermilab (www.fnal.gov).

The software is an open source but no support is provided.

Get it as follows:

git clone git@github.com:yarba/G4VMP.git (SSH)

git clone https://github.com/yarba/G4VMP.git (HTTPS)

This revision is compatible with geant4-11-01-ref-07 as well as art v3_13_02 
and art_root_io v1_12_04 (via setup of critic v2_12_04 portmanteau).
Compiler gcc/g++ and CLHEP 2.4.6.4a will be set up as part of art.
Root will be set up as part of art_root_io.
Also required are cmake v3_25_2 and mrb v6_08_01 (both are required by art v3_13_02).
To build Geant4 one also needs xerces_c v3_2_3e.
Specifically, starting this revision the software transitions to buld with gcc12.1.0 (e26).
Transition to 11.1.r07 (i.e. post-11.2.b01) required changes in G4VMP/CMakeLists.txt
since library G4persistency has split into G4mctruth, G4geomtext and (optional) G4gdml libraries. 

==========================================

Example procedure:

source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup critic v2_12_04 -q e26:prof

setup xerces_c v3_2_3e -q e206 (NOTE: No more "prof", etc.)

setup cmake v3_25_2 

cd \<path-to-your-g4-area\>


==========================================

Geant4 collaborators can obtain the source code from the repo (authentination required):

git clone ssh://git@gitlab.cern.ch:7999/geant4/geant4-dev.git geant4-11-01-ref-07

cd geant4-11-01-ref-07

git checkout geant4-11-01-ref-07


export G4INSTALL=$PWD

cd ..

mkdir geant4-11-01-ref-07-build

cd geant4-11-01-ref-07-build

NOTE: make sure to include -DGEANT4_USE_GDML=ON 
      in case geometry input is envisioned
NOTE: if one wants to build static libs instead of shared ones,
      one should all to cmake the following options:
      -DBUILD_SHARED_LIBS=OFF -DBUILD_STATIC_LIBS=ON
NOTE: since mid-10.7.ref-XX cycle, c++17 is STANDARD, 
      so there's no need to explicitly specify -DGEANT4_BUILD_CXXSTD=17 
      also, since ref-05, CMAKE_CXX_STANDARD replaces GEANT4_BUILD_CXXSTD
NOTE: starting release 11.0 the default build is MT, thus to build "serial"
      one needs to specify it explicitly
NOTE: use of system libexpat or internal one, it's a user's choice

cmake -DCMAKE_INSTALL_PREFIX=$G4INSTALL \
-DGEANT4_USE_GDML=ON -DXERCESC_ROOT_DIR=$XERCESCROOT \
-DGEANT4_USE_SYSTEM_CLHEP=ON \
-DGEANT4_BUILD_MULTITHREADED=OFF \
-DGEANT4_USE_SYSTEM_EXPAT=OFF \
-DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc \
$G4INSTALL

make -j8

make install

cd \<your-G4VMP-area\>

setup mrb v6_08_01

export MRB_PROJECT=G4VMP

mrb newDev [ -v vX_YY_ZZ -q eXY:prof ]

source localProducts*/setup

=========================================================

JUST an EXAMPLE: 

mrb newDev -v dev -q e26:prof

source localProducts_G4VMP_dev_e26_prof/setup
  
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

source ./geant4make-no-ups.sh geant4-11-01-ref-07 \<path-to-your-g4-area\>

cd $MRB_BUILDDIR

mrb b

=========================================================

ADDITIONAL INFORMATION

One can also install everything in a form of "local products".
However, with the way G4VMP is setup right now, it will require to permit all
absolute paths in transitive dependencies in targets exported by project G4VMP.
As of right now, this is turned OFF in art/mrb.
And it is not clear how to properly set it to ON via mrb tools.
Thus it will require a "hack", i.e. after building MANUALLY changing
in the CMakeCache.txt file:
G4VMP_IGNORE_ABSOLUTE_TRANSITIVE_DEPENDENCIES:BOOL=
to the following:
G4VMP_IGNORE_ABSOLUTE_TRANSITIVE_DEPENDENCIES:BOOL=ON

This will allow to use mrbslp in the batch jobs instead of mrbsetenv as 
the later can cause issues when used in production scripts.


=========================================================

In some cases custom modifications are needed in core tools, e.g. art, etc.
Then the whole critic portmanteau can be built from scratch, together with G4VMP toolkit.

Example instructions below illustrate how it was done with the development version 
of critic as of Aug.2021 and reference release geant4-10-07-ref-06.

=========================================================

source /cvmfs/geant4-ib.opensciencegrid.org/products/setup

setup xerces_c v3_2_3 -q e20:prof

setup cmake v3_20_0

setup mrb v5_12_02

export MRB_PROJECT=critic

mkdir \<dir-of-your-choice\>  # e.g. mrb-art-develop

cd \<dir-of-your-choice\>

mrb newDev -v develop -T e20-prof -q e20:prof # e.g.

. e20-debug/local*/setup

mrb g -r critic_suite

cd srcs

git clone git@github.com:yarba/G4VMP.git 

cd ..

mrb uv clhep v2_4_4_2

mrbsetenv

mrb uc

cd srcs/G4VMP

source ./geant4make-no-ups.sh  geant4-10-07-ref-06 /work1/g4v/yarba_j/geant4-local-builds/gcc-9.3.0

cd $MRB_BUILD

mrb b


For building Geant4 (before anything else)

=========================================================

In addition to setting up xerces_c and cmake:

setup clhep v2_4_4_2 -q e20:prof

cd \<you-g4-install-area\> # e.g. /project/Geant4/yarba_j/geant4-local-builds/gcc-9.3.0

git clone ssh://git@gitlab.cern.ch:7999/geant4/geant4-dev.git geant4-10-07-ref-06

cd geant4-10-07-ref-06

git checkout geant4-10-07-ref-06

export G4INSTALL=$PWD

cd ..

mkdir geant4-10-07-ref-06-build

cd geant4-10-07-ref-06-build

NOTE: Starting release 11.0 the Default build is MT \
       thus it may make sense to use flag -DGEANT4_BUILD_MULTITHREADED=OFF \
       Also one may want to consider -DGEANT4_USE_SYSTEM_EXPAT=OFF 

cmake -DCMAKE_INSTALL_PREFIX=$G4INSTALL \
-DGEANT4_USE_GDML=ON -DXERCESC_ROOT_DIR=$XERCESCROOT \
-DGEANT4_USE_SYSTEM_CLHEP=ON \
-DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc \
$G4INSTALL

make -j20

make install

=========================================================




