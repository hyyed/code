cmake_minimum_required(VERSION 3.22.1)

project(sqtable)

# # 如是交叉编译要设置编译器
# set(CMAKE_SYSEM_NAME linux)
# set(CMAKE_C_COMPILER arm-linux-gcc)
# set(CMAKE_CXX_COMILER arm-linux-g++)

set(mylib
    sqtable
)

foreach(DIR ${mylib})
    add_subdirectory(${DIR})
endforeach()

foreach(DIR ${mylib})
    # include_directories(${DIR})
    target_include_directories(${DIR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

add_executable(table main.c)

target_link_libraries(table sqtable)
