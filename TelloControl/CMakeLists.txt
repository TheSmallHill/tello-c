cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CMakeDependentOption)

project (TelloControl)

# Options
option(BUILD_SHARED_LIB "Build a shared lib" OFF)
option(BUILD_UNIT_TESTS "Builds unit tests for the Tello Control project" ON)

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

# Static library (always made)
add_library(${PROJECT_NAME}StaticLib STATIC $<TARGET_OBJECTS:${PROJECT_NAME}ObjectLib>)

# Shared library
if(BUILD_SHARED_LIB)
   add_library(${PROJECT_NAME}SharedLib SHARED $<TARGET_OBJECTS:${PROJECT_NAME}ObjectLib>)
endif()

# Unit testing
if(BUILD_UNIT_TESTS)
   add_subdirectory(test)
endif()
