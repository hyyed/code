# # project_directory/
# # ├── CMakeLists.txt
# # ├── src/
# # │   ├── main.c
# # │   ├── CMakeLists.txt
# # │   ├── calc/
# # │   │   ├── calc.c
# # │   │   ├── calc.h
# # │   │   └── CMakeLists.txt
# # │   └── utils/
# # │       ├── utils.c
# # │       ├── utils.h
# # │       └── CMakeLists.txt
# include_directories(${PROJECT_SOURCE_DIR}/src) # 包含头文件目录
# include_directories(${PROJECT_SOURCE_DIR}/src/utils) # 包含头文件目录
# include_directories(${PROJECT_SOURCE_DIR}/src/calc) # 包含头文件目录

# add_subdirectory(calc) # 添加子目录
# add_subdirectory(utils)

# add_executable(MainApp main.c) # 将 main.c 添加到可执行文件中
# target_link_libraries(MainApp calc utils) # 链接 calc 和 utils 子目录中的库

# ./Demo3
#   ├── main.c
#   ├── CMakeLists.txt
#   ├── calc/
#   │   ├── calc.c
#   │   ├── calc.h
#   │   └── CMakeLists.txt
#   └── utils/
#       ├── utils.c
#       ├── utils.h
#       └── CMakeLists.txt
cmake_minimum_required (VERSION 3.22.1) # CMake 最低版本号要求
project (Demo3) # 项目信息
# aux_source_directory(. DIR_SRCS) # 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量

include_directories(${PROJECT_SOURCE_DIR}) # 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/utils) # 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/calc) # 包含头文件目录

# 告诉 CMake 在当前 CMakeLists.txt 文件所在的目录下查找另一个 CMakeLists.txt 文件，并将其内容包含到当前项目中。
add_subdirectory(calc) # 添加子目录
add_subdirectory(utils)

add_executable(MainApp main.c) # 指定生成目标 

# target_link_libraries指明可执行文件 main 需要连接名为 calc utils 的链接库 。
# 链接库的后缀名为 .a 或 .so ，如果是 .a 文件，则需要使用 target_link_libraries 
target_link_libraries(MainApp calc utils) # 链接 calc utils 库