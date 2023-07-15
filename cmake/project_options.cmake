#   lanugage standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# define CPU options
set(CPU_OPTIONS 
	-mthumb 
	-mcpu=cortex-m0 
	-mfloat-abi=soft
)

# define Compiler options
set(COMPILER_OPTIONS 
	#-Werror
	-Wall
	-Wextra
	-Wcast-align
	-Wconversion
	-Wsign-conversion
	-Wshadow
	-Wlogical-op
	-pedantic
	-Werror=cast-align
)

if (CMAKE_BUILD_TYPE  STREQUAL "Debug")
	message("-- Debug mode activated")
	set(DEBUG_OPTIONS -g3 -O0)
	set(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")
	set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
else()
	set(CMAKE_C_FLAGS_RELEASE "-Os ")
	set(CMAKE_CXX_FLAGS_RELEASE "-Os ")
endif()

# define linker options
set(LINKER_OPTIONS 
    ${CPU_OPTIONS}
    -specs=nano.specs
    -lc
    -lm
    -lnosys
    -Wl,--gc-sections
)

# define Language options
set(LANGUAGE_OPTIONS 
    $<$<COMPILE_LANGUAGE:C>:-std=c99>
)

add_compile_options(
    ${CPU_OPTIONS}
    ${LANGUAGE_OPTIONS}
    ${COMPILER_OPTIONS}
    ${DEBUG_OPTIONS}
)

# add defines for all targets
set(PROJECT_DEFINITIONS
	-DSTM32F030x6
) 

add_definitions(
	${PROJECT_DEFINITIONS}
)

