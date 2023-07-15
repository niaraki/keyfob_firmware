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

# Project modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(doxygen)


