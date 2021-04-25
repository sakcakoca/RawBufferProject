#Creates a variable to identify and store the compiler toolset used on the platform
#It is mostly used to differentiate between Clang and Clang-cl when VisualStudio is used.

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}.  Build Type: ${CMAKE_BUILD_TYPE}. Simulate ID: ${CMAKE_CXX_SIMULATE_ID}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(COMPILER_TOOL_ON_PLATFORM "GNU")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if ("${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
        set(COMPILER_TOOL_ON_PLATFORM "CLANG-CL")
    else ()
        set(COMPILER_TOOL_ON_PLATFORM "CLANG")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(COMPILER_TOOL_ON_PLATFORM "MSVC")
else ()
    set(COMPILER_TOOL_ON_PLATFORM "UNKNOWN")
endif ()

message(STATUS "COMPILER_TOOL_ON_PLATFORM: ${COMPILER_TOOL_ON_PLATFORM}")