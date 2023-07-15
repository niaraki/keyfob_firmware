set(LIB_NAME hll)

add_library(${LIB_NAME} STATIC
  "./startup/startup_stm32f030x6.s"
	"./vendor_cmsis/system_stm32f0xx.c"
)
	
target_include_directories(${LIB_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/vendor_cmsis/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/CMSIS/Core/Include
)
	


