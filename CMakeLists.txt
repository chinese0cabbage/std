cmake_minimum_required(VERSION 3.7)
project(std)

set(CMAKE_CXX_STANDARD 11)

add_executable(std main.cpp stl_allocation_test.h)

#include_directories(“G:\mysql\MySQL8.0.17\include”) # 刚刚说到的include文件夹的路径
link_directories(“/usr/local/lib”) # lib文件夹的路径
link_libraries(libmysql) # 直接写这个
target_link_libraries(std mysqlcppconn) # 项目名称 libmysql

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/install/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/install/lib")
link_libraries(librttr_core)
target_link_libraries(std ${CMAKE_CURRENT_SOURCE_DIR}/install/lib/librttr_core.so)

set(BOOST_ROOT "~/puppy/install/x64-install/oss/include/boost")
include_directories(~/puppy/install/x64-install/oss/include)
link_directories(~/puppy/install/x64-install/oss/lib)
target_link_libraries(std boost_thread boost_system boost_program_options)