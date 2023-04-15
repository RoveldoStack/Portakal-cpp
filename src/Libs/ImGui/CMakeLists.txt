add_library(ImGui
"imgui.h" "imgui.cpp"
"imgui_demo.cpp"
"imgui_draw.cpp"
"imgui_internal.h"
"imgui_tables.cpp"
"imgui_widgets.cpp"
"backends/imgui_impl_dx12.h"
"backends/imgui_impl_dx12.cpp"
"backends/imgui_impl_dx11.h"
"backends/imgui_impl_dx11.cpp"
"backends/imgui_impl_win32.h"
"backends/imgui_impl_win32.cpp"
"misc/cpp/imgui_stdlib.cpp")

include_directories(${CMAKE_SOURCE_DIR}/src/Libs/ImGui)
include_directories(${CMAKE_SOURCE_DIR}/src/Libs/ImGui/backends)
