# Add sources
set(HAL_SOURCES
  "./common/hal.c"
  "./common/hal_common_helper.c"
  "./config/hal_rcc_cfg.c"
  "./rcc/hal_rcc.c"
  "./dio/hal_dio.c"
  "./config/hal_dio_cfg.c"
  "./systick/hal_systick.c"
)

# Add required headers
set(HAL_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/rcc
    ${CMAKE_CURRENT_SOURCE_DIR}/dio
    ${CMAKE_CURRENT_SOURCE_DIR}/systick
)
  
add_library(${HAL_LIB_TARGET} STATIC ${HAL_SOURCES})

target_link_libraries(${HAL_LIB_TARGET} PUBLIC ${HLL_LIB_TARGET})

target_include_directories(${HAL_LIB_TARGET} PUBLIC  ${HAL_INC_DIRS})

