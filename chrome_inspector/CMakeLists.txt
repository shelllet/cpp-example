# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

project(let)

cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0020 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#add_definitions(-DBOOST_ALL_DYN_LINK -DV8_COMPRESS_POINTERS)
add_definitions(-DV8_COMPRESS_POINTERS)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Websockets CONFIG REQUIRED)
find_package(Qt5SerialBus CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS log)

# https://vcpkg.readthedocs.io/en/latest/examples/installing-and-using-packages/
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")
 find_path(BOOST_BEAST_INCLUDE_DIRS "boost/beast.hpp")
 #find_package(v8 CONFIG REQUIRED)
#file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/internal/*.h)
find_path(V8_INCLUDE_DIR "include/v8.h")

file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/include INC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/internal INTERNAL_SOURCES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (MSVC)
	#add_compile_options(/FC /bigobj)
	add_compile_options(/wd4309 /wd4996 /wd4244 /wd4267)
endif()

add_executable(let ${HEADERS} ${SOURCES})

#set_property(TARGET let PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_include_directories(let PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/v8/include
	${Boost_INCLUDE_DIRS}
	${BOOST_ASIO_INCLUDE_DIRS}
	${BOOST_BEAST_INCLUDE_DIRS}
	#${V8_SDK}/include
	${V8_INCLUDE_DIR}/include
)

#${CMAKE_BUILD_TYPE}
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(BUILD "debug")
else()
	set(BUILD "release")
endif()
target_link_directories(let PRIVATE "${V8_SDK}\\out\\x64.${BUILD}")

target_compile_definitions(let PRIVATE WIN32_LEAN_AND_MEAN UNICODE NOMINMAX _WIN32_WINNT=0x0601)

find_library(V8_LIBRARY v8.dll)
find_library(V8_LIBBASE_LIBRARY v8_libbase.dll)
find_library(V8_LIBPLATFORM_LIBRARY v8_libplatform.dll)
target_link_libraries(let PRIVATE ws2_32.lib
	#v8.dll.lib 
	#v8_libbase.dll.lib 
	#v8_libplatform.dll.lib
	${V8_LIBRARY}
	${V8_LIBBASE_LIBRARY}
	${V8_LIBPLATFORM_LIBRARY}
	opencv_world
	Qt::Widgets #Qt5::WidgetsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::WebSockets #Qt5::WebsocketsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::SerialBus #Qt5::SerialBusPrivate #Qt5::PeakCanBusPlugin Qt5::TinyCanBusPlugin
	${Boost_LIBRARIES}
)

find_file(V8_SNAPSHOT_BLOB_BIN snapshot_blob.bin)
message(STATUS ${V8_SNAPSHOT_BLOB_BIN})
file(COPY E:\\vcpkg\\buildtrees\\v8\\x64-windows-dbg\\snapshot_blob.bin DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY ${V8_SDK}/out/x64.${BUILD}/v8.dll DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY ${V8_SDK}/out/x64.${BUILD}/v8_libbase.dll DESTINATION ${CMAKE_BINARY_DIR})
#file(COPY ${V8_SDK}/out/x64.${BUILD}/v8_libplatform.dll DESTINATION ${CMAKE_BINARY_DIR})