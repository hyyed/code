cmake_minimum_required(VERSION 3.10)

add_library(lcddevice lcddevice.c)

add_executable(test_lcd test.c)

target_link_libraries(test_lcd lcddevice)
