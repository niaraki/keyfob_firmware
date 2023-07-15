# Author: M.Niaraki
# Project: Keyfob firmware

cmake_minimum_required(VERSION 3.13)

# Add cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)

# Add required modules 
include(arm_none_eabi) 
include(project_options)

project(keyfob_firmware 
		VERSION      1.0.0
	  DESCRIPTION  "keyfob access control firmware" 
		HOMEPAGE_URL "keyfob.ir")

enable_language(C ASM)

# Sets name of the final artifact
set(EXE_NAME ${PROJECT_NAME}.elf)
 
# Specifies the address of the linker script(based on selected MCU) 
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/hll/stm32f030xx/linker/STM32F030F4Px_FLASH.ld)

# Add each layer subdirectory
add_subdirectory(hll) 
add_subdirectory(app)

# Create executable based on the app_lib 
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:app>)

# Change the target name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} SUFFIX ".elf")

# Link other static library for each layer of the architecture
target_link_libraries(${PROJECT_NAME} PUBLIC
	hll
	app
)

target_link_options(${PROJECT_NAME} PRIVATE -T${LINKER_SCRIPT} -Wl,-Map=${PROJECT_NAME}.map,--cref ${LINKER_OPTIONS})
set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS ${LINKER_SCRIPT})

# Print executable size informations
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXE_NAME})

# Generate final artifacts (elf, hex and bin files) 
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O srec    ${EXE_NAME} ${PROJECT_NAME}.srec
        COMMAND ${CMAKE_OBJCOPY} -O ihex    ${EXE_NAME} ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O binary  ${EXE_NAME} ${PROJECT_NAME}.bin
        COMMAND ${CMAKE_OBJDUMP} -S         ${EXE_NAME} > ${PROJECT_NAME}.lst
        COMMAND ${CMAKE_NM} -C -l -n -S     ${EXE_NAME} > ${PROJECT_NAME}.sym     
)
