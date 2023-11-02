add_library(${APP_LIB_TARGET} STATIC
"main.c"
"../hal/common/hal_interrupt_handlers.c"
)

target_include_directories(
  ${APP_LIB_TARGET} PRIVATE
  ${PROJECT_BINARY_DIR}/../configured_files/include/
  # this address should be removed when the hal layer is completed
  # because we are not allowed to use hll in the app layer
  ${CMAKE_SOURCE_DIR}/src/hll/include
)

target_link_libraries(${APP_LIB_TARGET} PUBLIC 
  ${DRV_LIB_TARGET}
  ${HAL_LIB_TARGET}
  ${MID_LIB_TARGET}
  ${BSP_LIB_TARGET}
)
