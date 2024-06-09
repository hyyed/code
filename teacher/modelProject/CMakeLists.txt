cmake_minimum_required(VERSION 3.10)

project(Project)
#模块头文件路径
include_directories(${CMAKE_SOURCE_DIR}/lcddevice)
#添加子目录
add_subdirectory(lcddevice)

add_executable(project main.c)

target_link_libraries(project lcddevice)