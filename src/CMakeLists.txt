# Author: M.Niaraki
# Project: Keyfob firmware

if (CROSS_COMPILE)
  message(STATUS "Cross Compile: Enabled")
  cmake_minimum_required(VERSION 3.20)
  # Add cmake module path
  set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../cmake)
  # Add required modules
  include(arm_none_eabi) 
  include(project_options)
  # Define project for cross compile
  project(keyfob_firmware)
  enable_language(C ASM)
else()
  message(STATUS "Cross Compile: Disabled")
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/srcc)
  set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
  set(CMAKE_C_COMPILER_ID GNU)
  set(CMAKE_CXX_COMPILER_ID GNU)
  set(CMAKE_ASM_COMPILER_ID GNU)
endif()

# Sets name of the final artifact
set(EXE_NAME ${PROJECT_NAME}.elf)
 
# Specifies the address of the linker script(based on selected MCU) 
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/hll/stm32f030xx/linker/STM32F030F4Px_FLASH.ld)

include(libs)

add_definitions(
    -DSTM32F030x6
) 

# Add each layer as subdirectory
add_subdirectory(hll) 
add_subdirectory(hal) 
add_subdirectory(drivers) 
add_subdirectory(middleware) 
add_subdirectory(bsp) 
add_subdirectory(app)


if(CROSS_COMPILE)
  # create executable based on the app_lib 
  add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:${APP_LIB_TARGET}>)

  # Change the target name
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} SUFFIX ".elf")

  # Link other static library for each layer of the architecture
  target_link_libraries(${PROJECT_NAME} PUBLIC
    ${APP_LIB_TARGET}  
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
    COMMAND ${CMAKE_NM} -C -l -n -S     ${EXE_NAME} > ${PROJECT_NAME}.sym     
    COMMAND ${CMAKE_OBJDUMP} -S         ${EXE_NAME} > ${PROJECT_NAME}.lst
  )
else()
  set_target_properties(${HAL_LIB_TARGET} PROPERTIES LINKER_LANGUAGE C)
  set_target_properties(${DRV_LIB_TARGET} PROPERTIES LINKER_LANGUAGE C)
  set_target_properties(${MID_LIB_TARGET} PROPERTIES LINKER_LANGUAGE C)
  set_target_properties(${BSP_LIB_TARGET} PROPERTIES LINKER_LANGUAGE C)
  set_target_properties(${APP_LIB_TARGET} PROPERTIES LINKER_LANGUAGE C)
  add_custom_target(${PROJECT_TARGET} All DEPENDS ${APP_LIB_TARGET})
endif()

