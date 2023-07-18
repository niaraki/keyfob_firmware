add_library(${HAL_LIB_NAME} STATIC
  "./config/hal_rcc_cfg.c"
  "./rcc/hal_rcc.c"
)
	
target_include_directories(${HAL_LIB_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/common
	${CMAKE_CURRENT_SOURCE_DIR}/config
	${CMAKE_CURRENT_SOURCE_DIR}/rcc
)

target_link_libraries(${HAL_LIB_NAME} PUBLIC ${HLL_LIB_NAME})

