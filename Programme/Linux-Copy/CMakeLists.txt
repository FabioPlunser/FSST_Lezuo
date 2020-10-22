cmake_minimum_required(VERSION 3.0.0)
project(Copy_with_POSIX VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Copy_with_POSIX src/copy_with_POSIX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
