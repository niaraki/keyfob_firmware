add_library(${DRV_LIB_NAME} STATIC
  "./spi_flash.c"
)
	
target_include_directories(${DRV_LIB_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${DRV_LIB_NAME} PUBLIC ${HAL_LIB_NAME})

