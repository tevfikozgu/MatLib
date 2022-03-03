project(MatriceLibrary)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.19)

include_directories(eigen-3.4.0)

include_directories(include)
add_subdirectory(src)
