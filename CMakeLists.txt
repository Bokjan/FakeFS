cmake_minimum_required(VERSION 2.8)
project(fakefs)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -fPIC -pie")

file(GLOB lib_src "src/lib/*.c")
# file(GLOB bin_src "src/bin/*.c")

add_executable(libffs.so ${lib_src})
target_link_libraries(libffs.so cjson)

add_executable(ffs_formatter src/bin/ffs_formatter.c)
target_link_libraries(ffs_formatter cjson)