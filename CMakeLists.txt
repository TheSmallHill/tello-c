cmake_minimum_required (VERSION 2.6)

project (tello-c)

add_library(${PROJECT_NAME} OBJECT "")

target_include_directories(${PROJECT_NAME}
   PUBLIC
      inc/
   PRIVATE
      src/
)

# API sources
target_sources(${PROJECT_NAME}
   INTERFACE
      inc/api/telloc.h
   PRIVATE
      src/api/telloc.c
)
