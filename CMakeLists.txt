cmake_minimum_required (VERSION 2.6)

project(telloc)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(${PROJECT_NAME}_ENABLE_TESTS "Set to true to build and run tests as part of the library build" ON)

# Just always building with PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME} OBJECT "")

set(PRIVATE_LINK_LIBS)
set(PUBLIC_LINK_LIBS)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		inc/
	PRIVATE
		src/
)

if(UNIX)
	find_package(Threads REQUIRED)
	
	list(APPEND PRIVATE_LINK_LIBS Threads::Threads)
endif()

# Sources
target_sources(${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/inc/api/telloc.h
		${CMAKE_CURRENT_SOURCE_DIR}/inc/api/telloc_config.h
		${CMAKE_CURRENT_SOURCE_DIR}/inc/api/telloc_types.h
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config_internal.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/api/telloc_config_internal.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/telloc_instance_internal.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/telloc_instance_internal.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/udp/client.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/udp/client.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/udp/client.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/udp/client.h
)

# Static library
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME}_static
	PUBLIC
		${PUBLIC_LINK_LIBS}
	PRIVATE
		${PRIVATE_LINK_LIBS}
)

# Shared library
add_library(${PROJECT_NAME}_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME}_shared
	PUBLIC
		${PUBLIC_LINK_LIBS}
	PRIVATE
		${PRIVATE_LINK_LIBS}
)

if(${PROJECT_NAME}_ENABLE_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
