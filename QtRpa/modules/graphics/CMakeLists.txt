# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(graphics)

set(CMAKE_AUTOMOC ON)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/property_browser PROPERTY_BROWSER)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
#aux_source_directory(${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME} HEADERS)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Svg CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
	${Qt5Svg_INCLUDE_DIRS}
)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	find_library(QSCINTILLA_LIBRARY NAMES qscintilla2_qt5d)
	message(STATUS CMAKE_BUILD_TYPE2: ${CMAKE_BUILD_TYPE})
else()
	find_library(QSCINTILLA_LIBRARY NAMES qscintilla2_qt5)
	message(STATUS CMAKE_BUILD_TYPE1: ${CMAKE_BUILD_TYPE})
endif()

#get_filename_component(SCINTILLA_ROOT ${SCINTILLA_LIBRARY} DIRECTORY)
#get_filename_component(SCINTILLA_ROOT ${SCINTILLA_ROOT} DIRECTORY)

message(STATUS QSCINTILLA_LIBRARY: ${QSCINTILLA_LIBRARY})


target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${QSCINTILLA_LIBRARY}
    )
