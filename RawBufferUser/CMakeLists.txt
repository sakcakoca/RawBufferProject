# CMakeList.txt : CMake project for RawBufferProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(RawBufferUser)

# Add source to this project's executable.
add_executable (RawBufferUser "RawBufferUser.cpp" "RawBufferUser.h")

# TODO: Add tests and install targets if needed.
target_link_libraries(RawBufferUser PRIVATE project_warnings project_options)