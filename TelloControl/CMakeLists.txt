cmake_minimum_required (VERSION 2.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (TelloControl)

find_package(Boost REQUIRED)
find_package(DBus REQUIRED)

add_library(${PROJECT_NAME}ObjectLib OBJECT "")

target_include_directories(${PROJECT_NAME}ObjectLib
   PUBLIC
      inc/
   PRIVATE
      src/
      ${Boost_INCLUDE_DIRS}
      ${DBUS_INCLUDE_DIRS}
)

target_sources(${PROJECT_NAME}ObjectLib
   INTERFACE
      inc/TelloControl.h
   PRIVATE
      src/TelloControl.cpp
)
