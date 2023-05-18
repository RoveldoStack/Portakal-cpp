
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
add_compile_definitions(PORTAKAL_SIMD_256)
#includes

#Set executable
if(WIN32)
set(RESOURCE "${CMAKE_SOURCE_DIR}/resources/Win32Icon/Portakal.rc")
add_executable (EditorPlayer ${RESOURCE} "main.cpp" "EditorPlayerApplication.h" "EditorPlayerApplication.cpp")
endif()

target_include_directories(EditorPlayer PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR})

#linker
target_link_libraries(EditorPlayer Editor)
target_link_libraries(EditorPlayer Runtime)
add_definitions(-w)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EditorPlayer PROPERTY CXX_STANDARD 20)
endif()