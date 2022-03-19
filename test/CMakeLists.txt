cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)

add_executable(telloc_test)

get_property(ALL_INCLUDES TARGET telloc_static PROPERTY INCLUDE_DIRECTORIES)

target_link_libraries(telloc_test
	PUBLIC
		telloc_static
		${GTEST_LIBRARIES}
)

target_include_directories(telloc_test
	PUBLIC
		${ALL_INCLUDES}
		"."
		${GTEST_INCLUDE_DIRS}
)

target_sources(telloc_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/tests/ConfigTests.cpp
)
