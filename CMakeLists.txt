cmake_minimum_required (VERSION 2.6)

project (TelloControl)

add_library(TelloControl SHARED "")

target_include_directories(${PROJECT_NAME}
   PUBLIC
      inc/
   PRIVATE
      src/
)
