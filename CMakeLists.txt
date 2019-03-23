cmake_minimum_required(VERSION 3.8)

project(Balls_simulator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/source/*.h)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)

set(EXECUTABLE balls_simulator)
add_executable(${EXECUTABLE} ${SOURCES} ${HEADERS})
target_link_libraries(${EXECUTABLE} Qt5::Widgets pthread)
target_include_directories(${EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/source)

# Tests
set(COMPILE_TESTS TRUE CACHE BOOL "Wether tests should be compiled")
if (COMPILE_TESTS)
  set(MEMORYCHECK_COMMAND_OPTIONS "-q --tool=memcheck --show-reachable=yes
    --num-callers=50 --trace-children=yes --leak-check=full")
  include(CTest)
  file(GLOB_RECURSE TESTS_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp
		${PROJECT_SOURCE_DIR}/source/domain/*.cpp
		${PROJECT_SOURCE_DIR}/source/utils/*.cpp)
	file(GLOB_RECURSE TESTS_HEADERS ${PROJECT_SOURCE_DIR}/source/domain/*.h
		${PROJECT_SOURCE_DIR}/source/utils/*.h
		${PROJECT_SOURCE_DIR}/test/*.h)

	find_package(GTest REQUIRED)

	add_executable(${EXECUTABLE}_tests ${TESTS_SOURCES} ${TESTS_HEADERS})
  target_include_directories(${EXECUTABLE}_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/test
    ${PROJECT_SOURCE_DIR}/source/
    )
  target_link_libraries(${EXECUTABLE}_tests GTest::GTest pthread)
  add_test(NAME Unit_tests COMMAND ${EXECUTABLE}_tests)
endif(COMPILE_TESTS)

