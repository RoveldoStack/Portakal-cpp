# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (Portakal "main.cpp" "Core/Core.h" "Window/WindowCreateDesc.h" "Window/Window.h" "Window/Window.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Portakal PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

#compiler flags
if(WIN32)
add_compile_definitions(PORTAKAL_OS_WINDOWS)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_definitions(PORTAKAL_COMPILER_MSVC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_definitions(PORTAKAL_COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_definitions(PORTAKAL_COMPILER_GNU)
else()
  add_compile_definitions(PORTAKAL_COMPILER_INVALID)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_definitions(QUAX_DEBUG)
endif()

add_compile_definitions(PORTAKAL_SAFE)

include_directories(${CMAKE_SOURCE_DIR}/src)

if(WIN32)
target_link_libraries(Portakal d3d12.lib)
target_link_libraries(Portakal dxgi.lib)
target_link_libraries(Portakal d3dcompiler.lib)
target_link_libraries(Portakal Shlwapi.lib)
endif()