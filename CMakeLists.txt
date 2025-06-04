cmake_minimum_required(VERSION 3.10)
project(rubiks_cube_solver LANGUAGES CXX)

# Use C++14 standard
set(CMAKE_C_COMPILER   "/opt/homebrew/bin/gcc-15")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")

include_directories("/opt/homebrew/Cellar/gcc/15.1.0/include/c++/15/aarch64-apple-darwin24")

# Tell the compiler to search headers in Model/
include_directories(${CMAKE_SOURCE_DIR}/Model)

# List all .cpp source files for the final executable:
set(SOURCE_FILES
    main.cpp
    Model/RubiksCube.cpp
    Model/RubiksCube3dArray.cpp
    Model/RubiksCube1dArray.cpp
    Model/RubiksCubeBitboard.cpp
)

# Create the executable target "rubiks_cube_solver"
add_executable(rubiks_cube_solver ${SOURCE_FILES})

# If you ever see "cannot find header XYZ", you can add more include directories:
# include_directories(${CMAKE_SOURCE_DIR}/Solver)
# include_directories(${CMAKE_SOURCE_DIR}/PatternDatabases)