cmake_minimum_required (VERSION 3.8)
project(RawBufferStaticLibrary)


add_library(RawBufferStaticLibrary STATIC "RawBuffer.h")
set_target_properties(RawBufferStaticLibrary PROPERTIES LINKER_LANGUAGE CXX)