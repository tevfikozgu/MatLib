cmake_minimum_required(VERSION 3.19)
project(MatriceLibrary)

set(CMAKE_CXX_STANDARD 17)
include_directories(eigen-3.4.0)
add_executable(MatriceLibrary main.cpp)
#add_executable(Eigen eigen_trials.cpp)
