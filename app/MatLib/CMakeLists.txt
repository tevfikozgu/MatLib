project(MatLib)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
        ${PROJECT_NAME}
          PRIVATE
          libs::MatriceLibrary
)
