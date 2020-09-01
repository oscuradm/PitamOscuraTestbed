
#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(B1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/DetectorConstruction
                    ${PROJECT_SOURCE_DIR}/SimActions)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
set(SOURCE
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/SensitiveDetector.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/ActionInitialization.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/EventAction.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/PrimaryGenerator.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/RunAction.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/SteppingAction.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/PhysicsList.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/BiasedRDPhysics.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/OscuraHits.cc
   ${PROJECT_SOURCE_DIR}/DetectorConstruction/OSimDetectorConstruction.cc
   ${PROJECT_SOURCE_DIR}/DetectorConstruction/OscuraBuildingBlocks.cc
   )


set(HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/SensitiveDetector.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/ActionInitialization.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/EventAction.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/PrimaryGenerator.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/RunAction.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/SteppingAction.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/PhysicsList.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/BiasedRDPhysics.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/OscuraAnalysis.hh
   ${CMAKE_CURRENT_SOURCE_DIR}/SimActions/OscuraHits.hh
   ${PROJECT_SOURCE_DIR}/DetectorConstruction/OSimDetectorConstruction.hh
   ${PROJECT_SOURCE_DIR}/DetectorConstruction/OscuraBuildingBlocks.hh
   )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(PitamDet pitam1.cc ${SOURCE} ${HEADERS})
target_link_libraries(PitamDet ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(EXAMPLEB1_SCRIPTS
  exampleB1.in
  exampleB1.out
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  )

foreach(_script ${EXAMPLEB1_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

