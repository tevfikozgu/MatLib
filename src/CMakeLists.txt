set(TARGET MatriceOperations)
set(TARGET_EIGEN EigenOperations)
add_executable(${TARGET} main.cpp Matrice.cpp)
add_executable(${TARGET_EIGEN} eigen_trials.cpp)
