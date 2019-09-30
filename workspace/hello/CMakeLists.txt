
project(hello)

set(CMAKE_CXX_FLAGS_RELEASE  "-O2")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

add_executable(hello main.cpp)