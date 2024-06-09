# # 设定CMake版本
# cmake_minimum_

# # 指定工程名
# project(LcdProject)

# # 添加子目录，即确定子目录下需要执行的CMakeLists
# add_subdir

# # 导入头文件
# include_dir


# # 生成可执行的目标文件
# add_exec

# # 链接库（子目录生成的静态或动态库）
# target_link_lib

# ./src
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
cmake_minimum_required (VERSION 3.22.1) # CMake 最低版本号要求 #版本检查机制至少在 2.8 之后才被支持
# project(cmake_demo VERSION 1.0.0 LANGUAGES C CXX) #一般而言，项目需要设置一个版本号，方便进行版本的发布
project (lcdProject) # 项目信息
# aux_source_directory(. DIR_SRCS) # 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量

# 如是交叉编译要设置编译器
set(CMAKE_SYSEM_NAME linux)
set(CMAKE_C_COMPILER arm-linux-gcc)
set(CMAKE_CXX_COMILER arm-linux-g++)


set(mylib 
    lcd 
    graph 
    readpicture 
    event0 
    led
    fontset
)
# 告诉 CMake 在当前 CMakeLists.txt 文件所在的目录下查找另一个 CMakeLists.txt 文件，并将其内容包含到当前项目中。
foreach(DIR ${mylib})
    add_subdirectory(${DIR})
endforeach()
# add_subdirectory(lcd) # 告诉 cmake 去指定的目录中寻找下一个源码并执行它
# add_subdirectory(graph)
# add_subdirectory(readpicture)
# add_subdirectory(event0)

# ${PROJECT_SOURCE_DIR}，它表示项目的根目录
# 导入头文件目录后，会在这些目录下查找.h头文件，这样就不需要在代码中指定头文件
foreach(DIR ${mylib})
    include_directories(${PROJECT_SOURCE_DIR}/${DIR})
endforeach()
# include_directories(${PROJECT_SOURCE_DIR}/lcd) # 指明头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/graph)
# include_directories(${PROJECT_SOURCE_DIR}/readpicture)
# include_directories(${PROJECT_SOURCE_DIR}/event0)

## 下边生成最终目标文件
# 该命令会查找指定目录下的所有源文件，然后将结果存进指定变量名。
# 查找当前目录下的所有源文件 # 并将名称保存到 DIR_SRCS 变量
# aux_source_directory(. DIR_SRCS) #下面二选一
# add_executable(MainApp ${DIR_SRCS}) # 指定生成目标 
add_executable(exLcdPrj main.c) # 指定生成目标 

# target_link_libraries指明 *生成可执行文件 main 时需要连接* 名为 calc utils 的链接库 。
# 链接库的后缀名为 .a 或 .so ，如果是 .a 文件，则需要使用 target_link_libraries 
# target_link_libraries(LcdPro m lcd readpicture) # 指明目标文件依赖的库，并链接 calc utils 库。默认在上边include_dir下寻找？
# set(mylib lcd graph readpicture event0)
target_link_libraries(exLcdPrj m ${mylib}) # 指明目标文件依赖的库，并链接 calc utils 库。默认在上边include_dir下寻找？
