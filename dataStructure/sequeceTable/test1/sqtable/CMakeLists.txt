cmake_minimum_required(VERSION 3.22.1)
project(sqtable)

# add_subdirectory()

# include_directories()
add_library(sqtable sqtable.c)
# target_include_directories(sqtable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CMAKE_SOURCE_DIR}/sqtable)
add_executable(extestSq testsq.c)
# 注意没有链接会出错
target_link_libraries(extestSq sqtable)