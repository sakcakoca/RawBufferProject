option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    message(STATUS "cppcheck found")
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK}
        --suppress=missingInclude
        --enable=all
        --inline-suppr
        --inconclusive
        -i
        ${CMAKE_SOURCE_DIR}/imgui/lib)
  else()
    message(STATUS "cppcheck requested but executable not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    message(STATUS "clang-tidy found")
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
  else()
    message(STATUS "clang-tidy requested but executable not found")
  endif()
endif()

if(ENABLE_INCLUDE_WHAT_YOU_USE)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  if(INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  else()
    message(STATUS "include-what-you-use requested but executable not found")
  endif()
endif()
