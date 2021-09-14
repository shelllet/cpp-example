# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

cmake_policy(SET CMP0091 NEW)

project(interpreter2)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

find_package(Boost REQUIRED COMPONENTS serialization log)
#find_package(Tesseract CONFIG REQUIRED)
find_package(Qt5Sql CONFIG REQUIRED)
#find_package(sqlite3 CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Websockets CONFIG REQUIRED)
find_package(Qt5SerialBus CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(libzip CONFIG REQUIRED)
find_package(OpenCV CONFIG REQUIRED)
find_package(Clang CONFIG REQUIRED)
find_package(LLVM CONFIG REQUIRED)
find_package(V8 CONFIG REQUIRED)
find_package(libzippp CONFIG REQUIRED)

# https://vcpkg.readthedocs.io/en/latest/examples/installing-and-using-packages/
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")
find_path(BOOST_BEAST_INCLUDE_DIRS "boost/beast.hpp")
#find_package(v8 CONFIG REQUIRED)
#file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/internal/*.h)


target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/third-party/v8/include/
	${Boost_INCLUDE_DIRS}
	${Tesseract_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${LLVM_SDK}/clang/include
	${LLVM_SDK}/llvm/include
	${LLVM_SDK}/build_ninja/include
	${LLVM_SDK}/build_ninja/tools/clang/include
	${V8_INCLUDE_DIR}
)


#add_definitions(-DBOOST_ALL_DYN_LINK)
add_definitions(-DV8_COMPRESS_POINTERS)
add_definitions(-DSHELL_GUI_APPLICATION)
add_definitions(-DCURRENT_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX _WIN32_WINNT=0x0601)


target_link_directories(${PROJECT_NAME} PRIVATE ${LLVM_SDK}/build_ninja/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE DXGI D3D11 ws2_32.lib
	${OpenCV_LIBS}
	${Boost_LIBRARIES}
	${YAML_CPP_LIBRARIES}
	#opencv_world
	Qt::Widgets #Qt5::WidgetsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::WebSockets #Qt5::WebsocketsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::SerialBus #Qt5::SerialBusPrivate #Qt5::PeakCanBusPlugin Qt5::TinyCanBusPlugin

	Qt::Sql
	pugixml
	#libzip::zip libzippp::libzippp
	#zip
	${V8_LIBRARIES}
	#clangAST clangLex libclang clangEdit
	#LTO LLVMMC LLVMLTO LLVMMCA
	clangTooling
	#clangBasic 
	clangFormat 
	#clangRewrite
	#clangToolingCore
	#clangToolingInclusions
	#clangLex
	#LLVMCore LLVMSupport LLVMRemarks LLVMBitstreamReader LLVMBinaryFormat
)

if(EXISTS ${V8_SNAPSHOT_BLOB})
	file(COPY ${V8_SNAPSHOT_BLOB} DESTINATION ${CMAKE_BINARY_DIR})
else()
	file(COPY ${V8_SNAPSHOT_BLOB_RELEASE} DESTINATION ${CMAKE_BINARY_DIR})
endif()