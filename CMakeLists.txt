# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Runtime")
project ("Editor")
project ("EditorPlayer")
project ("EditorLauncher")
project ("Player")

# Include sub-projects.
add_subdirectory ("src/Runtime")
add_subdirectory("src/Editor")
add_subdirectory("src/EditorPlayer")
add_subdirectory ("src/EditorLauncher")
add_subdirectory ("src/Player")
