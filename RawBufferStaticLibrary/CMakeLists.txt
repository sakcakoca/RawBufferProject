cmake_minimum_required (VERSION 3.14)
project(RawBufferStaticLibrary)


add_library(RawBufferStaticLibrary STATIC "RawBuffer.h" "RawBuffer.cpp")
set_target_properties(RawBufferStaticLibrary PROPERTIES LINKER_LANGUAGE CXX)