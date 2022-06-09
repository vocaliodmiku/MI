cmake_minimum_required(VERSION 3.14.0)
project(viterbi VERSION 0.1.0)

include(FetchContent)
include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fPIC")
add_subdirectory(pybind11)

# third_party: libtorch use FetchContent_Declare to download, and
# use find_package to find since libtorch is not a standard cmake project

pybind11_add_module(MI BaseMI.cpp BaseMI.h LM.cpp LM.h MI.h MIDemo1.cpp )