# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(common)

set(CMAKE_AUTOMOC ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

find_package(Boost REQUIRED COMPONENTS serialization log)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Clang CONFIG REQUIRED)
find_package(LLVM CONFIG REQUIRED)
find_package(g3logger CONFIG REQUIRED)
find_package(ICU REQUIRED COMPONENTS uc dt in io)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Widgets_PRIVATE_INCLUDE_DIRS}
)

#message(STATUS ${ICU_LIBRARY})

#add_definitions(-DBOOST_ALL_DYN_LINK)
add_definitions(-DBOOST_LOG_USE_WCHAR_T -DBOOST_LOG_WITHOUT_CHAR)

add_definitions(-DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}" -DCMAKE_OUT_DIR="${CMAKE_OUT_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE
	clangTooling
	clangFormat
	g3logger
	${ICU_LIBRARY}
)