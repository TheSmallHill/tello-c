cmake_minimum_required (VERSION 2.6)

project(telloc)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(${PROJECT_NAME}_ENABLE_TESTS "Set to true to build and run tests as part of the library build" ON)

# Just always building with PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME} OBJECT "")

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
      ${CMAKE_CURRENT_SOURCE_DIR}/src/telloc_instance_internal.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/telloc_instance_internal.h
)

# Static library
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)

# Shared library
add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)

if(${PROJECT_NAME}_ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
