# Author: M.Niaraki
# Date: 07/16/2023
# Desc.: Unit and Integration tests for keyfob firmware
include(GoogleTest)

project(keyfob_tests CXX)

add_executable(${PROJECT_NAME}
  testrunner.cpp
)

target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

# add to ctest
gtest_discover_tests(${PROJECT_NAME})

# CodeCoverage Configurations 
if (ENABLE_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  
  set(COVERAGE_MAIN "coverage")

  set(COVERAGE_DEPENDENCIES 
    ${PROJECT_NAME}
  )

  set(COVERAGE_EXCLUDES
    "${PROJECT_SOURCE_DIR}/docs"
    "${PROJECT_SOURCE_DIR}/templates"
    "${PROJECT_SOURCE_DIR}/scripts"
    "${PROJECT_SOURCE_DIR}/external"
    "${PROJECT_SOURCE_DIR}/docker"
    "${PROJECT_SOURCE_DIR}/cmake"
    "${PROJECT_SOURCE_DIR}/build"
    "${PROJECT_SOURCE_DIR}/tests/*"
  )

  setup_target_for_coverage_lcov(
    NAME ${COVERAGE_MAIN}
    EXECUTABLE ${PROJECT_NAME}
    DEPENDENCIES ${COVERAGE_DEPENDENCIES}
    EXCLUDE ${COVERAGE_EXCLUDES}
  )
endif()
