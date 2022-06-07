cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(octree-cpp LANGUAGES CXX)

# Configure CMake
message("Configuring CMake ...")
include(cmake/CMakeConfig.cmake)
message("CMake configured!\n")

# Handle sources
message("Handling sources ...")
include(cmake/CMakeSources.cmake)
message("Sources handled!\n")

# Load libraries
message("Loading libraries ...")
include(cmake/CMakeLibraries.cmake)
message("Libraries loaded!\n")

# Build executable
message("Building rule-based-classifier-cpp ...")
include(cmake/CMakeBuildExec.cmake)
message("Project built!\n\n")

