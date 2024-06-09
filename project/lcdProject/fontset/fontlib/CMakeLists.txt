

add_library(fontlib font.c truetype.c)
# target_include_directories(fontlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 如果包含字体文件，可以在此复制到生成库的目录
# file(COPY simfang.ttf DESTINATION ${CMAKE_BINARY_DIR}/fontlib)