cmake_minimum_required(VERSION 2.8)

project(Balls_simulator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE CPP ${PROJECT_SOURCE_DIR}/source/*cpp)
file(GLOB_RECURSE H ${PROJECT_SOURCE_DIR}/source/*h)
include_directories(${PROJECT_SOURCE_DIR}/source)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(balls_simulator ${CPP} ${H})
# Use the Widgets module from Qt 5.
target_link_libraries(balls_simulator Qt5::Widgets)
