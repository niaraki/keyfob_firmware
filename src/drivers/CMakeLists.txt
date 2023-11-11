add_library(${DRV_LIB_TARGET} STATIC
  "./ev1527/ev1527.c"
)
	
target_include_directories(${DRV_LIB_TARGET} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/ev1527
)

target_link_libraries(${DRV_LIB_TARGET} PRIVATE ${HAL_LIB_TARGET})

