# Variables for options
MAC_OS := 0

name := exampleN02
G4TARGET := $(name)
G4EXLIB := true

# Geant4 installation directory
G4INSTALL := /opt/geant4/geant4-11.1

# ROOT installation directory
ROOTINSTALL := /home/taskim/root_install/root

# Geant4 include and library directories
G4INCLUDES := $(G4INSTALL)/include/Geant4
G4LIB := $(G4INSTALL)/lib

# ROOT include and library directories
ROOTINCLUDE := $(ROOTINSTALL)/include
ROOTLIB := $(ROOTINSTALL)/lib

# Project include and library directories
PROJECT_INCLUDE := $(CURDIR)/include
PROJECT_LIB := $(CURDIR)/lib

# OpenGL
GLINCLUDE := /usr/include/GL
GLLIB := /usr/lib

# Source files
SRC := exampleN02.cc $(wildcard ./src/*.cc)
# Object files
OBJ := $(SRC:.cc=.o)

# CPPFLAGS += -I$(G4INCLUDES) -I$(ROOTINCLUDE) -I$(GLINCLUDE) -I$(PROJECT_INCLUDE) -DKL_USE_ROOT=1 -DG4VIS_USE -DG4UI_USE -DGEANT4_USE_OPENGL_X11=ON $(shell $(ROOTINSTALL)/bin/root-config --cflags)
CPPFLAGS += $(shell $(G4INSTALL)/bin/geant4-config --cflags) -I$(G4INCLUDES) -I$(ROOTINCLUDE) -I$(PROJECT_INCLUDE) -DKL_USE_ROOT=1 -DG4VIS_USE -DG4UI_USE -DGEANT4_USE_OPENGL_X11=ON $(shell $(ROOTINSTALL)/bin/root-config --cflags)
# LDFLAGS += -L$(G4LIB) -L$(ROOTLIB) -L$(GLLIB) -lm -ltbb $(shell $(ROOTINSTALL)/bin/root-config --libs) -Wl,-rpath,$(ROOTLIB)
LDFLAGS += -L$(G4LIB) -L$(ROOTLIB) -ltbb $(shell $(ROOTINSTALL)/bin/root-config --libs) -Wl,-rpath,$(G4LIB)  -Wl,-rpath,$(ROOTLIB)

ifeq ($(MAC_OS), 1)
	LDLIBS += $(shell geant4-config --libs) -framework OpenGL -lglfw -lGLEW 
else
	LDLIBS += $(shell geant4-config --libs) -lGL -lGLU -lGLEW -lGLX
endif

# CPPFLAGS += $(shell pkg-config --cflags Qt5Core Qt5Widgets Qt5Gui)
# LDFLAGS += `pkg-config --libs Qt5Core Qt5Widgets Qt5Gui`m

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
