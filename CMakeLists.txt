cmake_minimum_required(VERSION 3.10)
project(exampleN02)
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Geant4 installation directory
set(G4INSTALL /opt/geant4/geant4-11.1)
# ROOT installation directory
set(ROOTINSTALL ~/root_install/root)
# Find Geant4 package, specifying the path if necessary
find_package(Geant4 REQUIRED PATHS ${G4INSTALL} NO_DEFAULT_PATH)
# Include Geant4 directories
include(${Geant4_USE_FILE})
# Find ROOT package
find_package(ROOT REQUIRED)
# Include ROOT directories
include_directories(${ROOT_INCLUDE_DIRS})
# Find Qt5 package
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
# Include Qt5 directories
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
# Project include and library directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Source files
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc exampleN02.cc)
# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
# Link libraries
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} Qt5::Widgets Qt5::Core Qt5::Gui)
# Add compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE KL_USE_ROOT=1 G4VIS_USE G4UI_USE)
# Add compile options
target_compile_options(${PROJECT_NAME})
# Set RPATH
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH ${ROOTINSTALL}/lib)
# Conditionally define G4VIS_USE and G4UI_USE
if(ENABLE_VIS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE G4VIS_USE)
endif()
if(ENABLE_UI)
    target_compile_definitions(${PROJECT_NAME} PRIVATE G4UI_USE)
endif()

