cmake_minimum_required(VERSION 3.0.0)
project(RLEV2 VERSION 0.1.0)

include(CTest)
enable_testing()


add_executable(RLEV2 src/RLE-Encode-V2.c)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
