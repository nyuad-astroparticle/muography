# Variables for options
ENABLE_VIS := 1
ENABLE_UI := 1

name := exampleN02
G4TARGET := $(name)
G4EXLIB := true

# Geant4 installation directory
G4INSTALL := /opt/geant4/geant4-11.1

# ROOT installation directory
ROOTINSTALL := ~/root_install/root

# Geant4 include and library directories
G4INCLUDES := $(G4INSTALL)/include/Geant4
G4LIB := $(G4INSTALL)/lib

# ROOT include and library directories
ROOTINCLUDE := $(ROOTINSTALL)/include
ROOTLIB := $(ROOTINSTALL)/lib

# Project include and library directories
PROJECT_INCLUDE := $(CURDIR)/include
PROJECT_LIB := $(CURDIR)/lib

# Source files
SRC := exampleN02.cc $(wildcard ./src/*.cc)
# Object files
OBJ := $(SRC:.cc=.o)

CPPFLAGS += -I$(G4INCLUDES) -I$(ROOTINCLUDE) -I$(PROJECT_INCLUDE) -DKL_USE_ROOT=1 $(shell root-config --cflags)
LDFLAGS += -L$(G4LIB) -L$(ROOTLIB) $(shell root-config --libs) -Wl,-rpath,$(ROOTLIB)
LDLIBS += -lG4run -lG4physicslists -lG4vis_management -lG4intercoms -lG4event -lG4tracking -lG4clhep -lG4global -lG4processes -lG4geometry -lG4particles -lG4graphics_reps -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic $(shell geant4-config --libs)

# Conditionally define G4VIS_USE based on ENABLE_VIS
ifeq ($(ENABLE_VIS), 1)
	CPPFLAGS += -DG4VIS_USE
endif

# Conditionally define G4UI_USE based on ENABLE_UI
ifeq ($(ENABLE_UI), 1)
	CPPFLAGS += -DG4UI_USE
endif

.PHONY: all clean

all: $(name)

$(name): $(OBJ)
	@echo "Building binaries..."
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cc
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -f $(name) $(OBJ)
	# Add commands to clean up your build here
