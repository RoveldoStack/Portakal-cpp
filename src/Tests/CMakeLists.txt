# CMakeList.txt : CMake project for Portakal, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Tests "main.cpp")

target_link_libraries(Tests Portakal)