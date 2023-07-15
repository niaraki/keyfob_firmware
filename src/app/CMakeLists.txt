set(LIB_NAME app)

add_library(${LIB_NAME} STATIC
"main.c")

target_include_directories(
	${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/../../external/CMSIS/Core/Include
	${CMAKE_CURRENT_SOURCE_DIR}/../hll/stm32f030xx/vendor_cmsis/include
)
