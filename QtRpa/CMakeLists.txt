# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

project(Velkhana)

add_definitions(-DPROJECT_NAME="${PROJECT_NAME}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(Boost_USE_STATIC_LIBS ON)

add_subdirectory(modules/common)
add_subdirectory(modules/model)
add_subdirectory(modules/interpreter)
add_subdirectory(modules/frameless)
#add_subdirectory(modules/scintilla)
add_subdirectory(modules/creator)
add_subdirectory(modules/wizard)
add_subdirectory(modules/property)
#add_subdirectory(modules/property_browser)
#add_subdirectory(modules/graphics)
add_subdirectory(modules/events)


