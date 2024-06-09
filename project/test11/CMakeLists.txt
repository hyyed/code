# project_directory/
# ├── CMakeLists.txt
# ├── src/
# │   ├── main.c
# │   ├── CMakeLists.txt
# │   ├── calc/
# │   │   ├── calc.c
# │   │   ├── calc.h
# │   │   └── CMakeLists.txt
# │   └── utils/
# │       ├── utils.c
# │       ├── utils.h
# │       └── CMakeLists.txt
cmake_minimum_required(VERSION 3.22.1) # 最低要求的 CMake 版本
project(MultiDirProject) # 项目名称
add_subdirectory(src)  # 添加 src 子目录


# # ./Demo3
# #     |
# #     +--- main.cc
# #     |
# #     +--- math/
# #           |
# #           +--- MathFunctions.cc
# #           |
# #           +--- MathFunctions.h
# cmake_minimum_required (VERSION 2.8) # CMake 最低版本号要求
# project (Demo3) # 项目信息
# aux_source_directory(. DIR_SRCS) # 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量


# add_subdirectory(math) # 添加 math 子目录
# add_executable(Demo main.cc) # 指定生成目标 

# # target_link_libraries指明可执行文件 main 需要连接一个名为 MathFunctions 的链接库 。
# target_link_libraries(Demo MathFunctions) # 链接 MathFunctions 库