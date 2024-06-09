# 最低要求的 CMake 版本 
cmake_minimum_required(VERSION 3.22.1) 
 
# 项目名称 
project(HELLO) 

# 生成静态库 
add_library(libcalc SHARED calc.c)    
# 设置输出名称
set_target_properties(libcalc PROPERTIES OUTPUT_NAME "calc")

# 生成可执行文件
add_executable(hello main.c)

# 链接库
target_link_libraries(hello libcalc)
