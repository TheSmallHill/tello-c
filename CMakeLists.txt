cmake_minimum_required (VERSION 2.6)

project(telloc)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(${PROJECT_NAME}_BUILD_SHARED "Set to true in order to build the shared library in addition to the static library." OFF)
option(${PROJECT_NAME}_ENABLE_TESTS "Set to true to build and run tests as part of the library build" ON)

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
      ${CMAKE_CURRENT_SOURCE_DIR}/inc/api/telloc.h
      ${CMAKE_CURRENT_SOURCE_DIR}/inc/api/telloc_config.h
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config_internal.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config_internal.h
)

# Static library
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
set_property(TARGET ${PROJECT_NAME}_static PROPERTY POSITION_INDEPENDENT_CODE ON)

get_property(${PROJECT_NAME}_inc_dir TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)
set_property(TARGET ${PROJECT_NAME}_static PROPERTY INCLUDE_DIRECTORIES ${${PROJECT_NAME}_inc_dir})

# Shared library
if(${PROJECT_NAME}_BUILD_SHARED)
	add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
	set_property(TARGET ${PROJECT_NAME}_shared PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if(${PROJECT_NAME}_ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
