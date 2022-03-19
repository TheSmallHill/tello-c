cmake_minimum_required (VERSION 2.6)

project (telloc)

option(${PROJECT_NAME}_BUILD_SHARED "Set to true in order to build the shared library in addition to the static library." OFF)

add_library(${PROJECT_NAME} OBJECT "")

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

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
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
set_property(TARGET ${PROJECT_NAME}_static PROPERTY POSITION_INDEPENDENT_CODE ON)

# Shared library
if(${PROJECT_NAME}_BUILD_SHARED)
	add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
	set_property(TARGET ${PROJECT_NAME}_shared PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
