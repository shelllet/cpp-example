import sys
import os

ns = sys.argv[1]
module_name = sys.argv[2]

try:
    os.mkdir("./include/" + module_name)
except OSError as err:
    print(err)

# hpp
try:
    fhpp = open("./include/" + module_name + ".hpp", "x")

    content = f'''#pragma once
#include "common/framework.h"


using namespace {ns}::{module_name};
    '''
    fhpp.write(content)
    fhpp.close()

except OSError as err:
    print(err)


try:
    os.mkdir("./modules/" + module_name)
except OSError as err:
    print(err)

try:
    os.mkdir("./modules/" + module_name + "/src")
except OSError as err:
    print(err)


# cmake
try:
    fcmake = open("./modules/" + module_name + "/CMakeLists.txt", "x")

    content = f'''# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project({module_name})

set(CMAKE_AUTOMOC ON)

aux_source_directory(${{CMAKE_CURRENT_SOURCE_DIR}}/src SOURCES)
file(GLOB HEADERS ${{CMAKE_SOURCE_DIR}}/include/${{PROJECT_NAME}}/*.h)

add_library(${{PROJECT_NAME}} STATIC ${{SOURCES}} ${{HEADERS}})

find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(Qt5Gui CONFIG REQUIRED)

target_include_directories(${{PROJECT_NAME}} PRIVATE
	${{CMAKE_SOURCE_DIR}}/include
    ${{Boost_INCLUDE_DIRS}}
    ${{Qt5Gui_INCLUDE_DIRS}}
	${{Qt5Gui_PRIVATE_INCLUDE_DIRS}}
)
    '''

    fcmake.write(content)

    fcmake.close()
except OSError as err:
    print(err)
