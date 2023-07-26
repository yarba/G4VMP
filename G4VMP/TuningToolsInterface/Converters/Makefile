# In princlple, it was working even before replacing
# the commented out line with the $(shell ...) ones...

# CXX = g++ -g
ifndef CXX
  CXX := g++
endif

CXX += -g
 
# CXXFLAGS = `$(ROOTSYS)/bin/root-config --cflags --glibs`
# LDLIBS = `$(ROOTSYS)/bin/root-config --libs`
CXXFLAGS := $(shell $(ROOTSYS)/bin/root-config --cflags --glibs)
LDLIBS := $(shell $(ROOTSYS)/bin/root-config --libs)

# In principle, one can replace : with . in $MRB_QUALS
# and use it instead of e.g. e20.prof
#
qual := $(shell echo $(MRB_QUALS) | cut -d: -f1)

# --> NOT in Root6 LDLIBS += -lCintex -lReflex
# LDLIBS += $(MRB_BUILDDIR)/G4VMP/${CET_SUBDIR}.e20.prof/lib/libG4VMP_DataProducts_Analysis_dict.so
# LDLIBS += $(MRB_BUILDDIR)/G4VMP/${CET_SUBDIR}.e20.prof/lib/libG4VMP_DataProducts_Analysis.so
LDLIBS += $(MRB_BUILDDIR)/G4VMP/${CET_SUBDIR}.$(qual).prof/lib/libG4VMP_DataProducts_Analysis_dict.so
LDLIBS += $(MRB_BUILDDIR)/G4VMP/${CET_SUBDIR}.$(qual).prof/lib/libG4VMP_DataProducts_Analysis.so

BINARIES = Convert2Professor 
BINARIES += ConvertDirty2YODA
TARGETS = Convert2Professor.o
TARGETS += ConvertDirty4YODA.o

#--- if using 'make all' ---#
all : $(TARGETS)

#--- if making individual targets ---#

Convert2Professor.o : Convert2Professor.cc
	$(CXX) $(CXXFLAGS) -I$(MRB_SOURCE)/G4VMP -o $*.o -c $*.cc #compile
	$(CXX) -o $* $*.o $(LDLIBS) $(CXXFLAGS)       #link

ConvertDirty4YODA.o : ConvertDirty4YODA.cc
	$(CXX) $(CXXFLAGS) -I$(MRB_SOURCE)/G4VMP -o $*.o -c $*.cc #compile
	$(CXX) -o $* $*.o $(LDLIBS) $(CXXFLAGS)       #link

clean:
	rm -f $(BINARIES) $(TARGETS)
