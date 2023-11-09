# Author: M.Niaraki
# Date: 07/15/2023
# Desc.: CMakeLists.txt for keyfob firmware

cmake_minimum_required(VERSION 3.23)

# Versionin should be like semver
project(keyfob 
      DESCRIPTION  "keyfob access control firmware" 
      HOMEPAGE_URL "keyfob.ir"
      VERSION      1.0.0
)

enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)

# Disable in-source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Project option
option(BUILD_DOC       "Generate docs with doxygen" ON)
option(ENABLE_CPPCHECK "Static code analysis by cppcheck" ON)
option(ENABLE_TESTS    "Build project tests" ON)
option(ENABLE_COVERAGE "Enable code-coverage report" ON)

# Project modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(doxygen)
include(libs)

if (ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

# Read last hash in the code-base
include(checkgit)
CheckGitInstalled()

# Read last hash from code-base
execute_process(
    COMMAND  git rev-parse --short HEAD
    OUTPUT_VARIABLE GIT_HASH
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Config the project
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
  "${CMAKE_BINARY_DIR}/configured_files/include/config.h"
)

include_directories("${CMAKE_BINARY_DIR}/configured_files/include/")

# Static Analyzer Settings
set(CPPCHECK_PROJECT_DIR_ARG
	"${CMAKE_SOURCE_DIR}/src"
	CACHE STRING "source path for cppcheck")

set(CPPCHECK_EXCLUDES
	"${CMAKE_SOURCE_DIR}/src/hll"
	"${CMAKE_SOURCE_DIR}/scripts"
	"${CMAKE_SOURCE_DIR}/templates"
	"${CMAKE_SOURCE_DIR}/docs"
	"${CMAKE_SOURCE_DIR}/docker"
	"${CMAKE_SOURCE_DIR}/cmake"
	"${CMAKE_SOURCE_DIR}/external")

if(ENABLE_CPPCHECK)
  include(cppcheck)
endif()

# Clangformat checks
include(ClangFormat)
file(GLOB_RECURSE list_of_src_header_files 
  "${CMAKE_SOURCE_DIR}/src/app/*.[c|h]"
  "${CMAKE_SOURCE_DIR}/src/bsp/*.[c|h]"
  "${CMAKE_SOURCE_DIR}/src/middleware/*.[c|h]"
  "${CMAKE_SOURCE_DIR}/src/common/*.[c|h]"
  "${CMAKE_SOURCE_DIR}/src/hal/*.[c|h]"
  )
clangformat_setup(${list_of_src_header_files})

# Lizard for CCM analysis
include(lizard)

# Flawfinder for CVE analysis
include(flawfinder)

# GoogleTests
if (ENABLE_TESTS)
  include(googletest)
  # Enable ctest before adding tests subdirectory
  enable_testing()
  # Add sources 
	set(CROSS_COMPILE OFF)
	add_subdirectory(src src_test)
  # Add tests
  add_subdirectory(tests)
endif(ENABLE_TESTS)


