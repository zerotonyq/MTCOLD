# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DPP_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DPP_autogen.dir\\ParseCache.txt"
  "DPP_autogen"
  )
endif()
