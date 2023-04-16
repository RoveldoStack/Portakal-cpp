add_library(ImGuizmo "ImGuizmo.h" "ImGuizmo.cpp")

include_directories(${CMAKE_SOURCE_DIR}/src)


target_link_libraries(ImGuizmo ImGui)
