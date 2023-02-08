# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (Editor "main.cpp" "Domain/DomainFileExtensions.h" "Domain/DomainFolder.h" "Renderer/ImGuiAPI.h"  "Renderer/ImGuiAPI.cpp" "Renderer/ImGuiRenderer.h" "Renderer/ImGuiRenderer.cpp" "Renderer/DX12ImGuiRenderer.h" "Renderer/DX12ImGuiRenderer.cpp" "Renderer/ImGuiRendererModule.h" "Renderer/ImGuiRendererModule.cpp" "Renderer/ImGuiExecutorModule.h" "Renderer/ImGuiExecutorModule.cpp" "GUI/Window/GUIWindowModule.h" "GUI/Window/GUIWindowModule.cpp" "GUI/MenuItem/GUIMenuItemBehaviour.h" "GUI/MenuItem/GUICustomMenuItem.h" "GUI/Window/EditorWindowDockState.h" "GUI/Window/EditorWindow.h" "GUI/MenuItem/MenuItemTemplates.h" "Project/Project.h" "Project/ProjectYamlSerializer.h" "Project/ProjectYamlSerializer.cpp" "Project/ProjectGenerator.h" "Project/ProjectGenerator.cpp" "Project/ProjectYaml.h" "GUI/Window/EditorWindowSettings.h"  "GUI/Window/EditorWindowSettingsYamlSerializer.h" "GUI/Window/EditorWindowSettingsYamlSerializer.cpp" "GUI/MenuItem/GUIMainMenuItemModule.h" "GUI/MenuItem/GUIMainMenuItemModule.cpp" "GUI/MenuItem/MenuItemTree.h" "GUI/MenuItem/MenuItemTree.cpp" "GUI/Window/EditorWindowAPI.h" "GUI/Window/EditorWindowAPI.cpp" "GUI/Window/EditorWindow.cpp" "GUI/Window/TestWindow.h" "GUI/Window/TestWindow.cpp" "Project/ProjectModule.h" "Project/ProjectModule.cpp" "Project/ProjectAPI.h" "Project/ProjectAPI.cpp" "Project/ProjectPaths.h" "Project/ProjectPaths.cpp" "GUI/Window/DomainObserverWindow.h" "GUI/Window/DomainObserverWindow.cpp" "GUI/Window/WorldObserverWindow.h" "GUI/Window/WorldObserverWindow.cpp" "GUI/Window/ObjectObserverWindow.h" "GUI/Window/ObjectObserverWindow.cpp" "GUI/Window/GameObserverWindow.h" "GUI/Window/GameObserverWindow.cpp" "Domain/DomainFolder.cpp" "Domain/DomainModule.h" "Domain/DomainModule.cpp" "Domain/DomainAPI.h" "Domain/DomainAPI.cpp"  "Domain/DomainFileDescriptor.h" "Domain/DomainFileDescriptorYamlSerialize.h" "Domain/DomainFileDescriptorYamlSerialize.cpp" "Resource/EditorResource.h" "Resource/EditorResourceType.h" "Resource/EditorImageResource.h" "Resource/EditorImageResource.cpp" "Resource/EditorResourceModule.h" "Resource/EditorResourceRequest.h" "Resource/EditorResourceModule.cpp" "Resource/EditorResourceAPI.h" "Resource/EditorResourceAPI.cpp" "Asset/CustomAssetSerializerAttribute.h" "Asset/IAssetSerializer.h" "Asset/TextAssetSerializer.h" "Asset/TextAssetSerializer.cpp" "Domain/DomainFile.h" "Domain/DomainFile.cpp" "Asset/IAssetImporter.h" "Asset/CustomAssetImporterAttribute.h" "Asset/SimpleTextAssetImporter.h" "Asset/SimpleTextAssetImporter.cpp" "Asset/IAssetVisualizer.h" "Asset/CustomAssetVisualizerAttribute.h" "Asset/SimpleTextAssetVisualizer.h" "Asset/SimpleTextAssetVisualizer.cpp")

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