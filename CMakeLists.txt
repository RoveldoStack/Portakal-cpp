# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

#assimp
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "Assimp install" FORCE)
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "Assimp install PDB" FORCE)

add_subdirectory("src/Libs/Assimp")
add_subdirectory("src/Libs/Stbi")
add_subdirectory("src/Libs/ImGui")
add_subdirectory("src/Libs/ImGuizmo")
add_subdirectory("src/Libs/Yaml")

# Include sub-projects.
add_subdirectory ("src/Runtime")
add_subdirectory ("src/Editor")
add_subdirectory ("src/EditorPlayer")
add_subdirectory ("src/EditorLauncher")
add_subdirectory ("src/Player")


#target_compile_features(Runtime PUBLIC cxx_std_17)
#target_compile_features(Editor PUBLIC cxx_std_17)
#target_compile_features(EditorLauncher PUBLIC cxx_std_17)
#target_compile_features(EditorPlayer PUBLIC cxx_std_17)
#target_compile_features(Player PUBLIC cxx_std_17)