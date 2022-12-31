# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (Runtime "main.cpp" "Core/Core.h" "Window/WindowCreateDesc.h" "Window/Window.h" "Window/Window.cpp" "Containers/Array.h" "Containers/String.h" "Containers/String.cpp" "Memory/Memory.h" "Memory/Memory.cpp" "Containers/Guid.h" "Containers/Guid.cpp" "Win32/Win32Guid.h" "Win32/Win32Guid.cpp" "Compiler/Compiler.h" "Win32/Win32Log.h" "Assert/Assert.h" "Win32/Win32Assert.h" "Math/Math.h" "Math/Math.cpp" "Math/Vector2.h" "Math/Vector3.h" "Win32/Win32Window.h" "Win32/Win32Window.cpp" "Platform/PlatformMessage.h" "Platform/PlatformMessage.cpp" "Win32/Win32Message.h" "Win32/Win32Message.cpp" "Platform/PlatformMessageBoxFlags.h" "Win32/Win32MessageUtils.h" "Win32/Win32MessageUtils.cpp" "Input/Keys.h" "Window/WindowEvent.h" "Window/WindowEventType.h" "Window/WindowClosedEvent.h" "Window/WindowMovedEvent.h" "Window/WindowResizedEvent.h" "Window/MouseWheelEvent.h" "Window/MouseMovedEvent.h" "Window/MouseButtonEvent.h" "Window/MouseButtonUpEvent.h" "Window/MouseButtonDownEvent.h" "Window/KeyboardKeyEvent.h" "Window/KeyboardKeyDownEvent.h" "Window/KeyboardKeyUpEvent.h" "Window/KeyboardCharEvent.h" "Window/WindowEvents.h" "Application/Application.h" "Application/Application.cpp" "Application/ApplicationModule.h" "Message/MessageType.h" "Message/IMessage.h" "Message/IMessageListener.h" "Message/MessageAPI.h" "Message/MessageAPI.cpp" "Message/MessageModule.h" "Message/MessageModule.cpp" "Reflection/Class.h" "Reflection/Type.h" "Reflection/Function.h" "Reflection/Type.cpp" "Reflection/Attribute.h" "Reflection/Attribute.cpp" "Reflection/Field.h" "Reflection/Field.cpp" "Reflection/Assembly.h" "Reflection/Assembly.cpp" "Reflection/Reflection.h" "Window/WindowAPI.h" "Window/WindowAPI.cpp" "Window/WindowModule.h" "Window/WindowModule.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Runtime PROPERTY CXX_STANDARD 20)
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
target_link_libraries(Runtime d3d12.lib)
target_link_libraries(Runtime dxgi.lib)
target_link_libraries(Runtime d3dcompiler.lib)
target_link_libraries(Runtime Shlwapi.lib)
endif()