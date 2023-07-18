add_library(${HAL_LIB_TARGET} STATIC
  "./config/hal_rcc_cfg.c"
  "./rcc/hal_rcc.c"
)

target_include_directories(${HAL_LIB_TARGET} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/common
	${CMAKE_CURRENT_SOURCE_DIR}/config
	${CMAKE_CURRENT_SOURCE_DIR}/rcc
	${CMAKE_CURRENT_SOURCE_DIR}/../hll/stm32f030xx/
	${CMAKE_CURRENT_SOURCE_DIR}/../hll/stm32f030xx/vendor_cmsis/include/
	${CMAKE_CURRENT_SOURCE_DIR}/../../external/CMSIS/Core/Include
)

if (CROSS_COMPILE)
  target_link_libraries(${HAL_LIB_TARGET} PUBLIC ${HLL_LIB_TARGET})
endif()
