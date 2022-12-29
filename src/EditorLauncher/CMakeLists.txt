# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EditorLauncher "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EditorLauncher PROPERTY CXX_STANDARD 20)
endif()

#includes
include_directories(${CMAKE_SOURCE_DIR}/src)

