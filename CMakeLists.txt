# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)
project ("RawBufferProject")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set standard project settings
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)


# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
# sanitizer and code coverage options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)


#Add Header Only Libraries and Directories
add_library(RawBufferHeaderOnly INTERFACE)
target_include_directories(RawBufferHeaderOnly INTERFACE .)

# Include sub-projects.
add_subdirectory("RawBufferHeaderOnly")
add_subdirectory("RawBufferStaticLibrary")
add_subdirectory("RawBufferTests")
add_subdirectory ("RawBufferUser")