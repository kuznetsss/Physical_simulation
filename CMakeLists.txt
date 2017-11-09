cmake_minimum_required(VERSION 2.8)

project(Balls_simulator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/source/*.h)
include_directories(${PROJECT_SOURCE_DIR}/source)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(EXECUTABLE balls_simulator)
add_executable(${EXECUTABLE} ${SOURCES} ${HEADERS})
target_link_libraries(${EXECUTABLE} Qt5::Widgets)

# Tests
file(GLOB_RECURSE TESTS_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp
	${PROJECT_SOURCE_DIR}/source/domain/*.cpp
	${PROJECT_SOURCE_DIR}/source/utils/*.cpp)
file(GLOB_RECURSE TESTS_HEADERS ${PROJECT_SOURCE_DIR}/source/domain/*.h
	${PROJECT_SOURCE_DIR}/source/utils/*.h)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${EXECUTABLE}_tests ${TESTS_SOURCES} ${TESTS_HEADERS})
target_link_libraries(${EXECUTABLE}_tests ${GTEST_LIBRARIES})
