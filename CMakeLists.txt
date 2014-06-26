cmake_minimum_required(VERSION 2.8)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -openmp-report2")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -openmp-report2")
endif()
add_definitions(-std=c++0x)

add_executable (exascel exascel.cxx reader.cxx graph.cxx)
