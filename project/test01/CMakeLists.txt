# 最低要求的 CMake 版本 
cmake_minimum_required(VERSION 3.22.1) 
 
# 项目名称 
project(SimpleCalc) 
 
# 将 calc.h 头文件包含在项目中 
# 包含头文件目录
# : include_directories(${PROJECT_SOURCE_DIR}) 这行指定了要包含的头文件目录，这里使用了 ${PROJECT_SOURCE_DIR}，它表示项目的根目录。
# include_directories(${PROJECT_SOURCE_DIR}) 

# 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)


# 将 main.c 和 calc.c 源文件添加到可执行文件中,并定义了一个名为 SimpleCalc 的可执行文件
# add_executable(SimpleCalc main.c calc.c)
add_executable(SimpleCalc ${DIR_SRCS})

# aux_source_directory 命令，该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。








