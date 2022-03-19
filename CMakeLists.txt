cmake_minimum_required (VERSION 2.6)

project (telloc)

add_library(${PROJECT_NAME} OBJECT "")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PROJECT_NAME}
   PUBLIC
      inc/
   PRIVATE
      src/
)

# API sources
target_sources(${PROJECT_NAME}
   PUBLIC
      inc/api/telloc.h
      inc/api/telloc_config.h
   PRIVATE
      src/api/telloc.cpp
      src/api/telloc_config.cpp
      src/api/telloc_config_internal.cpp
      src/api/telloc_config_internal.h
)

# Static library
add_library(${PROJECT_NAME}StaticLib STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)