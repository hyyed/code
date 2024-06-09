#设置版本号
cmake_minimum_required(VERSION 3.10)

#项目名称
project(SLink)
set(Obj SLink)

#设置编译参数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")


#设置工具链（默认是gcc)
#set(CMAKE_C_COMPLIER gcc )

#添加子项目

#添加头文件

#添加可执行文件
add_executable(${Obj} main.c slink.c)

#在make后自动执行命令
add_custom_command(
    TARGET ${Obj}
    POST_BUILD
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${Obj}
    COMMENT "run project"
)

#添加库

