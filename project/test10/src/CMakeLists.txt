# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/src)
# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/src/utils)
# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/src/calc)

# 添加子目录
add_subdirectory(calc)
add_subdirectory(utils)

# 将 main.c 添加到可执行文件中
add_executable(MainApp main.c)

# 链接 calc 和 utils 子目录中的库
target_link_libraries(MainApp calc utils)