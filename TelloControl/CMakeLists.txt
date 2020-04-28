cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CMakeDependentOption)

project (TelloControl)

# Options
option(BUILD_STATIC_LIB "Build a static lib" ON)
option(BUILD_SHARED_LIB "Build a shared lib" OFF)
cmake_dependent_option(BUILD_UNIT_TESTS "Builds unit tests for the Tello Control project" OFF "BUILD_STATIC_LIB" ON)

find_package(Boost REQUIRED)

# Object library
add_library(${PROJECT_NAME}ObjectLib OBJECT "")

target_include_directories(${PROJECT_NAME}ObjectLib
   PUBLIC
      inc/
   PRIVATE
      src/
      ${Boost_INCLUDE_DIRS}
)

target_sources(${PROJECT_NAME}ObjectLib
   PUBLIC
      inc/TelloControl.h
   PRIVATE
      src/TelloControl.cpp
)

# Static library
if(BUILD_STATIC_LIB)
   add_library(${PROJECT_NAME}StaticLib STATIC $<TARGET_OBJECTS:${PROJECT_NAME}ObjectLib>)
endif()

# Shared library
if(BUILD_SHARED_LIB)
   add_library(${PROJECT_NAME}SharedLib SHARED $<TARGET_OBJECTS:${PROJECT_NAME}ObjectLib>)
endif()

# Unit testing
if(BUILD_UNIT_TESTS)
   add_subdirectory(test)
endif()
