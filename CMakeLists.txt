# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Runtime")
project ("Editor")
project ("EditorPlayer")
project ("EditorLauncher")
project ("Player")

project ("Stbi")
project ("ImGui")
project ("ImGuizmo")
project ("Yaml-cpp")

# Include sub-projects.
add_subdirectory ("src/Runtime")
add_subdirectory("src/Editor")
add_subdirectory("src/EditorPlayer")
add_subdirectory ("src/EditorLauncher")
add_subdirectory ("src/Player")

add_subdirectory("src/Libs/Stbi")
add_subdirectory("src/Libs/ImGui")
add_subdirectory("src/Libs/ImGuizmo")
add_subdirectory("src/Libs/Yaml")

target_compile_features(Runtime PUBLIC cxx_std_17)
target_compile_features(Editor PUBLIC cxx_std_17)
target_compile_features(EditorLauncher PUBLIC cxx_std_17)
target_compile_features(EditorPlayer PUBLIC cxx_std_17)
target_compile_features(Player PUBLIC cxx_std_17)
