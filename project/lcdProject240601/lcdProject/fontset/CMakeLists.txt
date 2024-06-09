cmake_minimum_required (VERSION 3.22.1) # CMake 最低版本号要求 #版本检查机制至少在 2.8 之后才被支持
# project(aafontset) # 项目名称

# set(CMAKE_SYSEM_NAME linux)
# set(CMAKE_C_COMPILER arm-linux-gcc)
# set(CMAKE_CXX_COMILER arm-linux-g++)

# 导入头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/fontlib)
# 添加 font 子目录
add_subdirectory(fontlib)


#生成静态库
add_library(fontset fontset.c)
target_link_libraries(fontset m fontlib)

# 生成局部可执行文件 注意：需要链接头文件所所使用的所有库
link_directories(${CMAKE_SOURCE_DIR}/lcd) # 添加需要链接 lcd 库
add_executable(exfontset tsfontset.c)
target_link_libraries(exfontset m fontlib lcd)

message(STATUS "SRCDIR: ${SRCDIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# 无法为未生成的目标“fontset”指定包含目录通过这个项目。(不能放在生成静态库的上边)
# target_include_directories(fontset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

execute_process(
    COMMAND ls -l
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    ERROR_VARIABLE error
)

message("Result: ${result}")
message("Output: ${output}")
message("Error: ${error}")




