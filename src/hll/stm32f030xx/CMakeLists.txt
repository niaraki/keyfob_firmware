if (CROSS_COMPILE)	
  add_library(${HLL_LIB_TARGET} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/startup/startup_stm32f030x6.s
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor_cmsis/system_stm32f0xx.c
  )
  target_include_directories(${HLL_LIB_TARGET} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor_cmsis/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/CMSIS/Core/Include
  )
endif()

	


