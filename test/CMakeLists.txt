cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_executable(telloc_test main.cpp)

find_package(Threads REQUIRED)

target_link_libraries(telloc_test
	PUBLIC
		telloc_static
		Threads::Threads
		${GTEST_LIBRARIES}
)

target_include_directories(telloc_test
	PUBLIC
		$<TARGET_PROPERTY:telloc,INCLUDE_DIRECTORIES>
		"."
		${GTEST_INCLUDE_DIRS}
)

target_sources(telloc_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/tests/ConfigurationApiTests.cpp
)

add_custom_command(TARGET telloc_test POST_BUILD COMMAND telloc_test) 
