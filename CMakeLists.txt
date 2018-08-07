cmake_minimum_required(VERSION 2.8)
project(fakefs)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -fPIC -pie -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=28 -g")

file(GLOB ffs_src "src/fs/*.c")
file(GLOB ffs_src ${ffs_src} "src/fs/fuseops/*.c")

add_executable(fakefs ${ffs_src})
target_link_libraries(fakefs cjson fuse pthread)

add_executable(ffs_formatter src/bin/ffs_formatter.c)
target_link_libraries(ffs_formatter cjson)