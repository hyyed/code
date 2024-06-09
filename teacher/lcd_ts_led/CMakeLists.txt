cmake_minimum_required(VERSION 3.10)

project(lcd_ts_led)

set(CMAKE_C_COMPILER arm-linux-gcc)

#模块头文件路径
include_directories(${CMAKE_SOURCE_DIR}/lcd)
include_directories(${CMAKE_SOURCE_DIR}/ts)
include_directories(${CMAKE_SOURCE_DIR}/led)

#添加子目录
add_subdirectory(lcd)
add_subdirectory(ts)
add_subdirectory(led)


add_executable(lcd_ts_led main.c)

#添加连接库
target_link_libraries(lcd_ts_led lcd ts led)