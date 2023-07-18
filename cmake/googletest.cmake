# Author: M.Niaraki
# Date: 07/16/2023
# Desc. this cmake module helpts to fetch and use google test

include(FetchContent)

# get googletest for its github repo
message(STATUS "EXTERNAL: Clone Google Test Framework from Git repository...")
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG v1.13.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
