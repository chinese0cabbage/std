cmake_minimum_required(VERSION 3.7)
project(std)

set(CMAKE_CXX_STANDARD 11)

add_executable(std main.cpp)

#include_directories(“G:\mysql\MySQL8.0.17\include”) # 刚刚说到的include文件夹的路径
link_directories(“/usr/local/lib”) # lib文件夹的路径
link_libraries(libmysql) # 直接写这个
target_link_libraries(std mysqlcppconn) # 项目名称 libmysql