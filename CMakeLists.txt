cmake_minimum_required(VERSION 3.20)
project(Project_1)

set(CMAKE_CXX_STANDARD 20)

set(GMP_INCLUDE_DIR "C:/msys64/mingw64/include")
set(GMP_LIB_DIR "C:/msys64/mingw64/lib")

include_directories(${GMP_INCLUDE_DIR})

find_library(GMP_LIB gmp PATHS ${GMP_LIB_DIR})

add_executable(Project_1 main.cpp)
target_link_libraries(Project_1 ${GMP_LIB})
