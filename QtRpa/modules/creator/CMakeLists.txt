# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

cmake_policy(SET CMP0091 NEW)
project(creator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(LLVM_SDK $ENV{LLVM_SDK})
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/property_browser PROPERTY_BROWSER)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
aux_source_directory(${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME} HEADERS)
# graphics
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/graphics SRC_GRAPHICS)

#file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)


file(GLOB ROOT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/resource_file.rc)

file(GLOB WIZARD_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/wizard/*.cpp)
file(GLOB CREATOR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/creator/*.cpp)
file(GLOB EVENTS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/events/*.cpp)
file(GLOB COMMON_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp)
file(GLOB PROPERTY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/properties/*.cpp)
file(GLOB ACTIVITIES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/activities/*.cpp)
file(GLOB EXTENSION_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/extension/*.cpp)
file(GLOB DATABASE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/database/*.cpp)
file(GLOB MODEL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/model/*.cpp)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/engine ENGINE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(/FC)
add_compile_options(/wd4309 /wd4996 /wd4244 /wd4267 /wd4251 /wd4624)

#qt5_add_resources(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/resource_file.rc)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS}
	${INC_GRAPHICS} ${SRC_GRAPHICS}
	${ROOT_FILES}
	#${PROPERTY_BROWSER}
	${WIZARD_FILES}
	${CREATOR_FILES} 
	${PROPERTY_FILES}
	${PROPERTIES_FILES}
	${EVENTS_FILES}
	${COMMON_FILES}
	${ACTIVITIES_FILES}
	${EXTENSION_FILES}
	${DATABASE_FILES}
	${MODEL_FILES}
	${PROPERTY_BROWSER_FILES}
	${SCINTILLA_FILES}
	${ENGINE}
)

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
find_package(unofficial-breakpad CONFIG REQUIRED)
find_package(Clang CONFIG REQUIRED)
find_package(LLVM CONFIG REQUIRED)
find_package(V8 CONFIG REQUIRED)
find_package(BZip2 REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(Qt5Svg CONFIG REQUIRED)

if(PORT MATCHES "Boost")
    set(VCPKG_LIBRARY_LINKAGE static)
endif()

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
	${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
	${LLVM_SDK}/clang/include
	${LLVM_SDK}/llvm/include
	${LLVM_SDK}/build_ninja/include
	${LLVM_SDK}/build_ninja/tools/clang/include
)




#add_definitions(-DBOOST_ALL_DYN_LINK)


target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX _WIN32_WINNT=0x0601)


target_link_directories(${PROJECT_NAME} PRIVATE ${LLVM_SDK}/build_ninja/lib)


target_link_libraries(${PROJECT_NAME} PRIVATE DXGI D3D11 ws2_32.lib
	${OpenCV_LIBS}
	${Boost_LIBRARIES}
	${YAML_CPP_LIBRARIES}
	unofficial::breakpad::libbreakpad unofficial::breakpad::libbreakpad_client
	#opencv_world
	Qt::Widgets Qt5::WidgetsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::WebSockets #Qt5::WebsocketsPrivate #Qt5::QWindowsVistaStylePlugin
	Qt::SerialBus #Qt5::SerialBusPrivate #Qt5::PeakCanBusPlugin Qt5::TinyCanBusPlugin
	Qt::Sql
	pugixml
	#libzip::zip
	libzip::zip libzippp::libzippp
	common
	model
	#properties
	#graphics
	events
	frameless
	wizard
    property

	#Qt5::QSvgPlugin Qt5::QSvgIconPlugin
	Qt::Svg #Qt5::Svg Qt::SvgPrivate Qt5::SvgPrivate
	#V8::V8
	#clangBasic 
	#clangFormat 
	#clangRewrite
	#clangToolingCore
	#clangToolingInclusions
	#clangLex
	#LLVMCore LLVMSupport LLVMRemarks LLVMBitstreamReader LLVMBinaryFormat
	interpreter
	#scintilla

	clangAST clangLex libclang clangEdit
	LTO LLVMMC LLVMLTO LLVMMCA
)





#file(COPY ${SCINTILLA_ROOT}/bin/SciLexer.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})


