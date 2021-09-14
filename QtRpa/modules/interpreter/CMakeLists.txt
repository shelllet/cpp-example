# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(interpreter)
set(CMAKE_AUTOMOC ON)
set(Python3_USE_STATIC_LIBS TRUE)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)

set(PYTHON_VER python3.9)
set(PYBIND11_FINDPYTHON ON)

find_path(PYTHON_INCLUDE_DIRS "${PYTHON_VER}/Python.h")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    find_library(PYTHON_LIBRARY python39_d)
    find_library(QSCINTILLA_LIBRARY NAMES qscintilla2_qt5d)
else ()
    find_library(PYTHON_LIBRARY python39)
    find_library(QSCINTILLA_LIBRARY NAMES qscintilla2_qt5)
endif ()



message(STATUS BUILD: ${CMAKE_BUILD_TYPE})
message(STATUS PYTHON: ${PYTHON_INCLUDE_DIRS})
message(STATUS PYTHON: ${PYTHON_LIBRARY})

find_package(Qt5Gui CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(pybind11 CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Svg CONFIG REQUIRED)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}/${PYTHON_VER}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Svg_INCLUDE_DIRS}
    ${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
)


target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${Boost_LIBRARIES}
    Qt::Gui Qt5::GuiPrivate
    ${PYTHON_LIBRARIES}
    ${QSCINTILLA_LIBRARY}
	pybind11::lto pybind11::embed pybind11::module
    Pathcch
    )
