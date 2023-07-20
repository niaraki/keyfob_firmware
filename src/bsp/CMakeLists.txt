add_library(${BSP_LIB_TARGET} STATIC
  "./bsp.c"
)
	
target_include_directories(${BSP_LIB_TARGET} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${BSP_LIB_TARGET} PRIVATE ${HAL_LIB_TARGET})

