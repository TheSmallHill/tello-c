cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)

add_executable(telloc_test)

target_link_libraries(telloc_test
   PRIVATE
      telloc
      ${GTEST_LIBRARIES}
)

target_include_directories(telloc_test
   PRIVATE
      "."
      ${GTEST_INCLUDE_DIRS}
)

target_sources(telloc_test
   tests/ConfigTests.cpp
)
