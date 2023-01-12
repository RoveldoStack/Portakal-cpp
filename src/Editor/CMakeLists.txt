# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (Editor "main.cpp" "Domain/DomainFileExtensions.h" "Domain/DomainFolder.h" "Renderer/ImGuiAPI.h"  "Renderer/ImGuiAPI.cpp" "Renderer/ImGuiRenderer.h" "Renderer/ImGuiRenderer.cpp" "Renderer/DX12ImGuiRenderer.h" "Renderer/DX12ImGuiRenderer.cpp" "Renderer/ImGuiRendererModule.h" "Renderer/ImGuiRendererModule.cpp" "Renderer/ImGuiExecutorModule.h" "Renderer/ImGuiExecutorModule.cpp" "GUI/GUIWindowModule.h" "GUI/GUIWindowModule.cpp" "GUI/GUIMenuItemBehaviour.h" "GUI/GUICustomMenuItem.h" "GUI/EditorWindowDockState.h" "GUI/EditorWindow.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Editor PROPERTY CXX_STANDARD 20)
endif()

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

#includes
include_directories(${CMAKE_SOURCE_DIR}/src)

#linker
target_link_libraries(Editor Runtime)
target_link_libraries(Editor ImGui)