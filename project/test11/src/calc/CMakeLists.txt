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
# # 添加库文件
# add_library(calc calc.c)



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
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
# include_directories(${PROJECT_SOURCE_DIR}/src/calc) # 包含头文件目录
aux_source_directory(. DIR_LIB_SRCS)

# add_library 将 当前 目录下的源文件编译为静态链接库。
add_library (calc calc.c) # 生成链接库