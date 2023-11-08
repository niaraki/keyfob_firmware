# Add sources
set(HAL_SOURCES
  "./common/hal.c"
  "./common/hal_common_helper.c"
  "./rcc/hal_rcc.c"
  "./config/hal_rcc_cfg.c"
  "./dio/hal_dio.c"
  "./config/hal_dio_cfg.c"
  "./exti/hal_exti.c"
  "./config/hal_exti_cfg.c"
  "./systick/hal_systick.c"
  "./timer/hal_timer.c"
  "./config/hal_timer_cfg.c"
)

# Add required headers
set(HAL_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/rcc
    ${CMAKE_CURRENT_SOURCE_DIR}/dio
    ${CMAKE_CURRENT_SOURCE_DIR}/exti
    ${CMAKE_CURRENT_SOURCE_DIR}/systick
    ${CMAKE_CURRENT_SOURCE_DIR}/timer
)
  
add_library(${HAL_LIB_TARGET} STATIC ${HAL_SOURCES})

target_link_libraries(${HAL_LIB_TARGET} PUBLIC ${HLL_LIB_TARGET})

target_include_directories(${HAL_LIB_TARGET} PUBLIC  ${HAL_INC_DIRS})

