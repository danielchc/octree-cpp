# ---  B U I L D I N G  --- #
# ------------------------- #

# Executable
add_executable(octree-cpp ${sources})

# Linking libraries
target_link_libraries(octree-cpp ${LASlib})
