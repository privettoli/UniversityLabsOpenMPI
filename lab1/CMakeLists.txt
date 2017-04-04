cmake_minimum_required(VERSION 3.7)
project(lab1)

SET(CMAKE_C_COMPILER /usr/local/bin/mpicc)
SET(CMAKE_CXX_COMPILER /usr/local/bin/mpicxx)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp AbstractTask.h MasterTask.cpp MasterTask.h TaskRunner.cpp TaskRunner.h WorkerTask.cpp WorkerTask.h Constants.h StringUtils.cpp StringUtils.h)
add_executable(lab1 ${SOURCE_FILES})

find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(lab1 ${MPI_LIBRARIES})
