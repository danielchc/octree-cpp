# ---  L I B R A R I E S  --- #
# --------------------------- #

# LASlib
set(LASlib ${CMAKE_SOURCE_DIR}/lib/LAStools/LASlib/lib/libLASlib.a)
include_directories(
        ${CMAKE_SOURCE_DIR}/lib/LAStools/LASzip/src/
        ${CMAKE_SOURCE_DIR}/lib/LAStools/LASlib/inc/
)