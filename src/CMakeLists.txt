# Version >= 3.12 required for new FindPython module
# https://cmake.org/cmake/help/v3.12/release/3.12.html
cmake_minimum_required (VERSION 3.12)

# TODO: Change this to your project name.
project (open_spiel-project-template)

set (CMAKE_CXX_STANDARD 17)

# Set C++ compilation flags for different types of builds.
if(APPLE)
  # On MacOS:
  #   -Werror causes problems with abseil on MacOS
  #   -undefined dynamic_lookup is necessary for pybind11 linking
  set (CMAKE_CXX_FLAGS "-w")
  set (CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_PROFILE} -O3 -march=native -funroll-loops -DNDEBUG -lprofiler -L/usr/local/Cellar/gperftools/2.7/lib")
else()
  set (CMAKE_CXX_FLAGS "-Werror")
endif()
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -fno-omit-frame-pointer -O1 -fno-optimize-sibling-calls -fsanitize=alignment,float-cast-overflow,float-divide-by-zero,function,object-size,pointer-overflow,return,unreachable,vptr,undefined")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -funroll-loops -DNDEBUG")

# Position-independent code is needed for Python extension modules.
# set (CMAKE_POSITION_INDEPENDENT_CODE ON)

# Needed to disable Abseil tests.
set (BUILD_TESTING OFF)

# For now, let's enable all the tests.
enable_testing()

include_directories(.)
include_directories(open_spiel/abseil-cpp)

# Turn off Python by default.
set (BUILD_WITH_PYTHON OFF CACHE BOOL "" FORCE)
mark_as_advanced(BUILD_WITH_PYTHON)
set (ENV{BUILD_WITH_PYTHON} OFF)
add_subdirectory(open_spiel)

set (OPEN_SPIEL_OBJECTS
  $<TARGET_OBJECTS:open_spiel_core>
  $<TARGET_OBJECTS:games>
  $<TARGET_OBJECTS:game_transforms>
  $<TARGET_OBJECTS:bridge_double_dummy_solver>
  $<TARGET_OBJECTS:algorithms>
)

set(ABSL
  absl::container
  absl::flags
  absl::flags_parse
  absl::flat_hash_map
  absl::optional
  absl::random_random
  absl::str_format
  absl::strings
  absl::time)

# TODO: Use `add_subdirectory(my_code_subdirectory)` here to add a code
# subdirectory to the build.
add_subdirectory(example)
