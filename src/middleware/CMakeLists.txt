add_library(${MID_LIB_TARGET} STATIC
  "./middleware.c"
)
	
target_include_directories(${MID_LIB_TARGET} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${MID_LIB_TARGET} PRIVATE
	${HAL_LIB_TARGET}
	${DRV_LIB_TARGET})

