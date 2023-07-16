# Author: M.Niaraki
# Date: 07/16/2023
# Desc.: Unit and Integration tests for keyfob firmware
project(keyfob_tests CXX)

add_executable(${PROJECT_NAME}
  testrunner.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

# add to ctest
add_test(keyfob_all_tests ${PROJECT_NAME})

