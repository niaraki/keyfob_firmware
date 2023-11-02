# Author: M.Niaraki
# Date: 07/16/2023
# Desc.: Unit and Integration tests for keyfob firmware
 
include(GoogleTest)

# Add include path(s)
set(TEST_FOLDER_PATH "${CMAKE_SOURCE_DIR}/tests")

include_directories(
   ${TEST_FOLDER_PATH}/fake
   ${TEST_FOLDER_PATH}/mock
)

# Set targets for unit tests
set(HAL_UNIT_TARGET keyfob_hal_unit_tests)
set(APP_UNIT_TARGET keyfob_app_unit_tests)
set(DRV_UNIT_TARGET keyfob_drv_unit_tests)
set(BSP_UNIT_TARGET keyfob_bsp_unit_tests)
set(MID_UNIT_TARGET keyfob_mid_unit_tests)

# Set targets for integration tests
set(KEYFOB_INTEGRATION_TARGET keyfob_integration_tests)

# Define targets by including them 
include(unit/unit_tests.cmake)
include(integration/integration_tests.cmake)

# CodeCoverage Configurations 
if (ENABLE_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  
  set(COVERAGE_MAIN "coverage")

  set(COVERAGE_DEPENDENCIES 
    ${HAL_UNIT_TARGET}
    ${BSP_UNIT_TARGET}
    ${DRV_UNIT_TARGET}
    ${APP_UNIT_TARGET}
    ${MID_UNIT_TARGET}
  )

  set(COVERAGE_EXCLUDES
      "${PROJECT_SOURCE_DIR}/build"
      "${PROJECT_SOURCE_DIR}/docs"
      "${PROJECT_SOURCE_DIR}/templates"
      "${PROJECT_SOURCE_DIR}/scripts"
      "${PROJECT_SOURCE_DIR}/external"
      "${PROJECT_SOURCE_DIR}/docker"
      "${PROJECT_SOURCE_DIR}/cmake"
      "${PROJECT_SOURCE_DIR}/tests/*"
      "*/gtest/*"
      "*/gmock/*"
      "*/googletest/*"
      "*/googlemock/*"
      "/usr/include/*"
   )

  setup_target_for_coverage_lcov(
    NAME ${COVERAGE_MAIN}
    EXECUTABLE ctest -j${PROCESSOR_COUNT}
    DEPENDENCIES ${COVERAGE_DEPENDENCIES}
    EXCLUDE ${COVERAGE_EXCLUDES}
  )
  
endif()
