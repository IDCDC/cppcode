cmake_minimum_required(VERSION 3.0)

project(WHYSC)

# 目前已经在 Ubuntu 20.04 系统中测试过该软件包

include_directories(${PROJECT_SOURCE_DIR}/include)
message(STATUS "${PROJECT_SOURCE_DIR}")


# C++ 中调要用科学计算的模块，要在系统中安装下面的 python 包
# sudo apt install python3
# sudo apt install python3-dev
# sudo apt install python3-numpy
# sudo apt install python3-scipy
# sudo apt install python3-matplotlib

find_package(PythonLibs 3)

message(STATUS "${PYTHON_INCLUDE_DIRS}")

add_subdirectory(test)
