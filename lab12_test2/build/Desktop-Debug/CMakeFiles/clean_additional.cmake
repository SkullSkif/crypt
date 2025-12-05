# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lab12_test2_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lab12_test2_autogen.dir/ParseCache.txt"
  "lab12_test2_autogen"
  )
endif()
