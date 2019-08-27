project(Quantum)

cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

include_directories(src/Gestionnaires)
include_directories(src/Interfaces)
include_directories(src/Modules)
include_directories(src/Utils)

add_executable(testQuantum ${SOURCES})
target_link_libraries(testQuantum pthread)

install (TARGETS testQuantum DESTINATION bin)
