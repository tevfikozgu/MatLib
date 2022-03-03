#cmake_minimum_required(VERSION 3.19)
#project(MatriceLibrary)
#include_directories(src include)
##add_library(LIB src/Matrice.cpp)
#
#set(CMAKE_CXX_STANDARD 14)
#
#add_executable(MatriceLibrary src/main.cpp)
##target_link_libraries(MatriceLibrary LIB)
##file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")
##add_executable(MatriceLibrary ${SOURCES})
#
##file(GLOB LIB_SOURCES src/*.cpp )
##file(GLOB LIB_HEADERS include/*.h )
##add_library( YourLib ${LIB_SOURCES} ${LIB_HEADERS} )
#
##add_executable(MatriceLibrary ${LIB_SOURCES} ${LIB_HEADERS})
#
#include_directories(eigen-3.4.0)
##add_executable(Eigen eigen_trials.cpp)

project(MatriceLibrary)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 2.8)
include_directories(include)
add_subdirectory(src)