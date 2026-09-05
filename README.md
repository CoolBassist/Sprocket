# Sprocket
> A toolkit to aid and simplify the annoying parts of game development with SFML

## What is Sprocket?
Sprocket is meant to be remove most of the boilerplate that comes with starting a new game project. Sprocket takes care of the gamestate, audio, and window management for you, you just need to tell it what to do!

The template should show and explain Sprocket in action.

## Quick Start (for new projects)
1. ```bash
   git clone https://github.com/SFML/cmake-sfml-project.git <project-title>
   ```
2. 
   ```bash
   cd <project-title>/src
   git submodule add https://github.com/CoolBassist/Sprocket.git
   ```

3. Copy and paste the following into the CMakeLists.txt
   ```cmake
   set(SPROCKET_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Sprocket")
   if(NOT TARGET Sprocket::Sprocket)
       file(GLOB_RECURSE SPROCKET_SOURCES CONFIGURE_DEPENDS "${SPROCKET_SOURCE_DIR}/*.cpp")
       if(NOT SPROCKET_SOURCES)
           message(FATAL_ERROR
               "No Sprocket sources found in '${SPROCKET_SOURCE_DIR}'. "
               "Check SPROCKET_SOURCE_DIR and run: git submodule update --init --recursive")
       endif()
   
       if(NOT TARGET spdlog::spdlog)
           include(FetchContent)
           FetchContent_Declare(spdlog
               GIT_REPOSITORY https://github.com/gabime/spdlog.git
               GIT_TAG v1.15.3
               GIT_SHALLOW ON
               EXCLUDE_FROM_ALL
               SYSTEM)
           FetchContent_MakeAvailable(spdlog)
       endif()
   
       add_library(sprocket STATIC ${SPROCKET_SOURCES})
       add_library(Sprocket::Sprocket ALIAS sprocket)
       target_include_directories(sprocket PUBLIC "${SPROCKET_SOURCE_DIR}")
       target_compile_features(sprocket PUBLIC cxx_std_17)
       target_link_libraries(sprocket PUBLIC SFML::Graphics SFML::Audio spdlog::spdlog)
   endif()
   target_link_libraries(main PRIVATE Sprocket::Sprocket)

4. Create `src/utils/gameState.hpp`. This is going to store the different states for your game, such as gamestate, music and sound effects. Look at the template for an example of how to structure this.
5. All done!

## Installation
To start using Sprocket, add it as a submodule to your project, or download the files and add directly to your project. Use the CMake code in the quickstart to get it to compile.
