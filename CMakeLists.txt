cmake_minimum_required(VERSION 3.0)
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加编译选项，如需要
add_compile_options(-Wall -Wextra -rdynamic -g3 -fPIC)

# 添加包含的头文件目录
include_directories(component)

# 添加执行文件
add_executable(MyProject ./main.cc)
target_link_libraries(MyProject pthread dl /home/melody/project/stack_trace/lib/libmyadd.so)
