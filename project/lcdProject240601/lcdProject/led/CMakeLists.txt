

# # 添加 font 子目录
# add_subdirectory(led)  

# #添加头文件路径
# include_directories(${CMAKE_SOURCE_DIR}/fontlib)

#生成静态库
add_library(led led.c)

# 链接 font 子目录中的库
# target_link_libraries(fontset fontlib)

