cmake_minimum_required(VERSION 3.20)
project(CppPortfolio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Release by default (Debug configs from VS Code override this).
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra)
# -O2 for Release; Debug keeps -O0 -g so stepping in gdb is sane.
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Every .cpp under phase0/ becomes its own executable, named <week>_<file>,
# e.g. phase0/week1/hello.cpp -> week1_hello. Re-run CMake configure after
# adding new files.
file(GLOB_RECURSE PROGRAM_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/phase0/*.cpp)
foreach(src ${PROGRAM_SOURCES})
  get_filename_component(name ${src} NAME_WE)
  get_filename_component(dir ${src} DIRECTORY)
  get_filename_component(week ${dir} NAME)
  set(target ${week}_${name})
  add_executable(${target} ${src})
  target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/common)
  set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endforeach()
