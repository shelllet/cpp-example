# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.17)
cmake_policy(SET CMP0091 NEW)

project(model)

set(CMAKE_AUTOMOC ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
  
find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(pugixml CONFIG REQUIRED)
#find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
	#${Qt5Core_INCLUDE_DIRS}
	#${Qt5Core_PRIVATE_INCLUDE_DIRS}
	${Qt5Gui_INCLUDE_DIRS}
	${Qt5Gui_PRIVATE_INCLUDE_DIRS}
)

