# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(events)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/property_browser PROPERTY_BROWSER)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/events/*.h)
#file(GLOB GLOBAL_HEADERS )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(Qt5Widgets CONFIG REQUIRED)


target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include

	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/third-party/v8/include/
	${Boost_INCLUDE_DIRS}
)

add_definitions(-DBOOST_ALL_DYN_LINK)


target_link_libraries(${PROJECT_NAME} PRIVATE DXGI D3D11 ws2_32.lib	
	${Boost_LIBRARIES}
	Qt::Widgets #Qt5::WidgetsPrivate #Qt5::QWindowsVistaStylePlugin
)

