cmake_minimum_required(VERSION 3.22.1)

project(exllist)

# 设置编译参数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGES} -g")
# # 如是交叉编译要设置编译器
# set(CMAKE_SYSEM_NAME linux)
# set(CMAKE_C_COMPILER arm-linux-gcc)
# set(CMAKE_CXX_COMILER arm-linux-g++)

set(mylib
    linklist
    callBackLinkList
)

foreach(DIR ${mylib})
    add_subdirectory(${DIR})
endforeach()

foreach(DIR ${mylib})
    include_directories(${DIR})
    # target_include_directories(${DIR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_executable(exllist main.c)

target_link_libraries(exllist ${mylib})


message(STATUS "SRCDIR: ${SRCDIR}")
message(STATUS "CMAKE_SOURCE_DIR        : ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# 无法为未生成的目标“fontset”指定包含目录通过这个项目。
# target_include_directories(fontset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# execute_process(
#     COMMAND make
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     RESULT_VARIABLE result
#     OUTPUT_VARIABLE output
#     ERROR_VARIABLE error
# )
# message("Result: ${result}")
# message("Output: ${output}")
# message("Error: ${error}")