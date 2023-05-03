
cmake_minimum_required(VERSION 3.22) # TODO: lower
project(ocv_tidy C CXX)

find_package(Clang REQUIRED)

add_library(ocv_tidy MODULE module.cpp
    checks/dummy_check.cpp
)

# issue when building LLVM and module using GCC
target_compile_options(ocv_tidy PRIVATE "-fno-rtti")

target_include_directories(ocv_tidy PRIVATE ${CLANG_INCLUDE_DIRS})
target_link_libraries(ocv_tidy PRIVATE clang-tidy)
