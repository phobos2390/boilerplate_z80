cmake_minimum_required(VERSION 2.6.0)

set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_ROOT_DIR ${PROJ_DIR}/src/${PROJ_NAME}/${REPO_NAME})

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_FLAGS "-g")

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

include_directories (${GTK3_INCLUDE_DIRS})

include_directories("${PROJ_DIR}/z/API")
include_directories("${PROJ_DIR}/z80/API")

set(Z80_SOURCE_DIRECTORIES ${PROJ_DIR}/z80/)

set(z80_source_files "")
foreach(source_dir ${Z80_SOURCE_DIRECTORIES})
  message("Finding everything in ${source_dir}")
  file(GLOB_RECURSE dir_src_files ${source_dir}/*.c)
  set(z80_source_files ${z80_source_files}
                       ${dir_src_files})
endforeach()

message("Building z80 source emulator files ${z80_source_files}")
add_library(z80_emu_library ${z80_source_files})

add_executable(z80_emulator src/emulator/emulator.c)
target_link_libraries(z80_emulator z80_emu_library)
target_link_libraries(z80_emulator ${GTK3_LIBRARIES})
