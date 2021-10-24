cmake_minimum_required(VERSION 3.15)
project(Par_Code_CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed!")
endif()

add_executable(fractal_par fractal_par.cc)
target_link_libraries(fractal_par pthread)

add_executable(pcc_par pcc_par.cc)
target_link_libraries(pcc_par pthread)
