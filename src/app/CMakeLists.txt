add_library(${APP_LIB_NAME} STATIC
"main.c")

target_include_directories(
  ${APP_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
	${CMAKE_CURRENT_SOURCE_DIR}/../../external/CMSIS/Core/Include
	${CMAKE_CURRENT_SOURCE_DIR}/../hll/stm32f030xx/vendor_cmsis/include
  ${PROJECT_BINARY_DIR}/../configured_files/include
)

