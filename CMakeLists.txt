cmake_minimum_required (VERSION 2.6)

project (tello-c)

add_library(${PROJECT_NAME}ObjectLib OBJECT "")

target_include_directories(${PROJECT_NAME}
   PUBLIC
      inc/
   PRIVATE
      src/
)

target_sources(${PROJECT_NAME}
   INTERFACE
      inc/TelloControl.h
   PRIVATE
      src/TelloControl.cpp
)
