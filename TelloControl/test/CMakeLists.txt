cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(TelloControlTests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(${PROJECT_NAME} TestMain.cpp)

target_sources(${PROJECT_NAME}
   PRIVATE
      TelloControl/CommandTests.cpp
)
