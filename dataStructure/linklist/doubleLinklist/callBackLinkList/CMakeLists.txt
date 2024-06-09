cmake_minimum_required(VERSION 3.22.1)
# project(linklist)

# add_subdirectory()

include_directories(${CMAKE_SOURCE_DIR}/linklist)
add_library(callBackLinkList callBackLinkList.c)
# target_include_directories(sqtable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CMAKE_SOURCE_DIR}/sqtable)
# add_executable(exlinklist linklist.c)
# 注意没有链接会出错
# target_link_libraries(exlinklist linklist)

# message(STATUS "SRCDIR: ${SRCDIR}")
# message(STATUS "CMAKE_SOURCE_DIR        : ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# 无法为未生成的目标“fontset”指定包含目录通过这个项目。
# target_include_directories(fontset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# execute_process(
#     COMMAND ls -l
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     RESULT_VARIABLE result
#     OUTPUT_VARIABLE output
#     ERROR_VARIABLE error
# )
# message("Result: ${result}")
# message("Output: ${output}")
# message("Error: ${error}")