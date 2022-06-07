# ---  S O U R C E S  --- #
# ----------------------- #

# Gather all source files
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
set(test_sources
        src/main_options.cpp
        src/models/Lpoint.cpp
        src/models/point.cpp
        src/readers/handlers.cpp
        src/readers/FileReaderFactory.cpp
        src/readers/LasFileReader.cpp
        src/readers/TxtFileReader.cpp
        src/octree/octree.cpp
        src/octree/octant.cpp
        src/octree/Kernel.cpp
        src/octree/helper.cpp)

# Include directories
include_directories(
        "inc/"
        "src/readers"
        "src/octree"
        "src/models"
        )
