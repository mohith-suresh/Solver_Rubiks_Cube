cmake_minimum_required(VERSION 3.10)
project(rubiks_cube_solver LANGUAGES CXX)

# Use C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell the compiler to search headers in Model/
include_directories(${CMAKE_SOURCE_DIR}/Model)

# List all .cpp source files for the final executable:
set(SOURCE_FILES
    main.cpp
    Model/RubiksCube.cpp
)

# Create the executable target "rubiks_cube_solver"
add_executable(rubiks_cube_solver ${SOURCE_FILES})

# If you ever see "cannot find header XYZ", you can add more include directories:
# include_directories(${CMAKE_SOURCE_DIR}/Solver)
# include_directories(${CMAKE_SOURCE_DIR}/PatternDatabases)