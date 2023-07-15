# Author: M.Niaraki
# Date: 07/15/2023
# Desc.: CMakeLists.txt for keyfob firmware

cmake_minimum_required(VERSION 3.13)
project(keyfob VERSION 1.0.0)

# Disable in-source build
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Project option
option(BUILD_DOC "Generate docs with doxygen" ON)
option(ENABLE_CPPCHECK "Static code analysis by cppcheck" ON)

# Project modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(doxygen)

# Static Analyzer Settings
set(CPPCHECK_PROJECT_DIR_ARG
	"${CMAKE_SOURCE_DIR}/src"
	#"${CMAKE_SOURCE_DIR}/tests"
	CACHE STRING "source path for cppcheck")

set(CPPCHECK_EXCLUDES
	"${CMAKE_SOURCE_DIR}/src/hll"
	"${CMAKE_SOURCE_DIR}/scripts"
	"${CMAKE_SOURCE_DIR}/templates"
	"${CMAKE_SOURCE_DIR}/docs"
	"${CMAKE_SOURCE_DIR}/external")

# Clangformat checks
include(ClangFormat)
file(GLOB_RECURSE list_of_src_header_files "${CMAKE_SOURCE_DIR}/src/*.[c|h]")
clangformat_setup(${list_of_src_header_files})

# Lizard for CCM analysis
include(lizard)


