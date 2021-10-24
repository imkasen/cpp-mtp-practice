cmake_minimum_required(VERSION 3.15)
project(Par_Code_CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed!")
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(fractal_par fractal_par.cc)
target_link_libraries(fractal_par pthread)

add_executable(pcc_par pcc_par.cc)
target_link_libraries(pcc_par pthread)
