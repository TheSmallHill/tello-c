cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (TelloControl)

find_package(Boost REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(DBUS dbus-1)

add_library(${PROJECT_NAME}ObjectLib OBJECT "")

target_include_directories(${PROJECT_NAME}ObjectLib
   PUBLIC
      inc/
      ${DBUS_INCLUDE_DIRS}
   PRIVATE
      src/
      ${Boost_INCLUDE_DIRS}
)

target_sources(${PROJECT_NAME}ObjectLib
   PUBLIC
      inc/TelloControl.h
      inc/NetworkConnect.h
   PRIVATE
      src/TelloControl.cpp
      src/NetworkConnect.cpp
)
