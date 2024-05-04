cmake_minimum_required(VERSION 3.26)
project(Project2)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(Source_Code)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(Test
        Source_Code/Graph.h
        Source_Code/NodeInfo.cpp
        Source_Code/TSP.cpp
        Source_Code/TSP.h
)

target_link_libraries(Test gtest gtest_main)

# List your source files for the executable
set(SOURCE_FILES
        Source_Code/parse.cpp
        Source_Code/Graph.h
        Source_Code/DataSelection.h
        Source_Code/NodeInfo.h
        Source_Code/NodeInfo.cpp
        Source_Code/main.cpp
        Source_Code/parse.h
        Source_Code/TSP.cpp
        Source_Code/TSP.h

)

# Define the executable target
add_executable(Main ${SOURCE_FILES})