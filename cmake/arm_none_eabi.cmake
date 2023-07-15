set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING true)

# insert full path of the arm-gnu compiler in this env. when it's needed
set(TOOLCHAIN_PATH "")

set(TOOLCHAIN_PREFIX "arm-none-eabi-")

# inster extension of the copiler here when it's needed
#set(CMAKE_EXECUTABLE_SUFFIX ".ex")

message("-- Trying to set compiler:" ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}gcc${CMAKE_EXECUTABLE_SUFFIX})

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

#set(CMAKE_AR                        ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}ar${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_LINKER                    ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}ld${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}objcopy${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_RANLIB                    ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}ranlib${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_SIZE                      ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}size${CMAKE_EXECUTABLE_SUFFIX})
#set(CMAKE_STRIP                     ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}strip${CMAKE_EXECUTABLE_SUFFIX})

# ===== Assembly language settings ======= 
set(CMAKE_ASM_COMPILER               ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER_ID GNU)

# ===== C language settings ======= 
set(CMAKE_C_COMPILER                 ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_C_COMPILER_FORCED TRUE)


# ===== C++ language settings ======= 
set(CMAKE_CXX_COMPILER               ${TOOLCHAIN_PATH}${TOOLCHAIN_PREFIX}g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_FORCED TRUE)


#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
