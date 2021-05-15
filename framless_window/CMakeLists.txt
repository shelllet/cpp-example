# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(frameless)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Svg CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
	${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
)

add_definitions(-DBOOST_ALL_DYN_LINK)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Svg Dwmapi.lib D2d1.lib
	Qt::Widgets
	pugixml
	${Boost_LIBRARIES}
)