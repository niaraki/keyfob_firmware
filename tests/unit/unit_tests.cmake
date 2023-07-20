# Add the first unit test #########################
add_executable( ${FIRST_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/first_unit_test.cpp
)
target_link_libraries(${FIRST_UNIT_TARGET} PUBLIC
   GTest::gtest_main
)
gtest_discover_tests(${FIRST_UNIT_TARGET})
###################################################

# Add unit tests for HAL Layer #################### 
add_executable(${HAL_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/hal/hal_common_tests.cpp
   ${TEST_FOLDER_PATH}/unit/hal/hal_rcc_tests.cpp
   ${TEST_FOLDER_PATH}/unit/hal/hal_delay_tests.cpp
)
add_definitions(-DSTM32F030x6) 
target_link_libraries(${HAL_UNIT_TARGET} PUBLIC
  ${HAL_LIB_TARGET}
   GTest::gmock_main
)
gtest_discover_tests(${HAL_UNIT_TARGET})
###################################################

# Add unit tests for APP Layer #################### 
add_executable(${APP_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/app/app_tests.cpp
)
target_link_libraries(${APP_UNIT_TARGET} PUBLIC
  ${APP_LIB_TARGET}
   GTest::gmock_main
)
gtest_discover_tests(${APP_UNIT_TARGET})
###################################################

# Add unit tests for BSP Layer #################### 
add_executable(${BSP_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/bsp/bsp_tests.cpp
)
target_link_libraries(${BSP_UNIT_TARGET} PUBLIC
  ${BSP_LIB_TARGET}
   GTest::gmock_main
)
gtest_discover_tests(${BSP_UNIT_TARGET})
###################################################

# Add unit tests for MID Layer #################### 
add_executable(${MID_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/middleware/middleware_tests.cpp
)
target_link_libraries(${MID_UNIT_TARGET} PUBLIC
  ${MID_LIB_TARGET}
   GTest::gmock_main
)
gtest_discover_tests(${MID_UNIT_TARGET})
###################################################


# Add unit tests for DRV Layer #################### 
add_executable(${DRV_UNIT_TARGET}
   ${TEST_FOLDER_PATH}/unit/drivers/driver_tests.cpp
)
target_link_libraries(${DRV_UNIT_TARGET} PUBLIC
  ${DRV_LIB_TARGET}
   GTest::gmock_main
)
gtest_discover_tests(${DRV_UNIT_TARGET})
###################################################
