# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Portakal")
project ("Tests")

# Include sub-projects.
add_subdirectory ("src/Portakal")
add_subdirectory ("src/Tests")
