cmake_minimum_required(VERSION 3.15)
project(Seq_Code_CPP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed!")
endif()

add_executable(fractal_seq fractal_seq.cc)

add_executable(pcc_seq pcc_seq.cc)
