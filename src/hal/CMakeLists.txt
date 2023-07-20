# Add sources
set(HAL_SOURCES
  "./common/hal_common_helper.c"
  "./config/hal_rcc_cfg.c"
  "./rcc/hal_rcc.c"
)

# Add required headers
set(HAL_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/rcc
)
  
if (CROSS_COMPILE)
  add_library(${HAL_LIB_TARGET} STATIC
    ${HAL_SOURCES}
  )
  target_link_libraries(${HAL_LIB_TARGET} PUBLIC ${HLL_LIB_TARGET})
else()
  list(APPEND HAL_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../hll/stm32f030xx/vendor_cmsis/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/CMSIS/Core/Include
    # Add fake hll layer to test low layer
    ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/fake/hll/include/
  )
  add_library(${HAL_LIB_TARGET} STATIC
    ${HAL_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/fake/hll/fake_hll.c
  )
endif()

target_include_directories(${HAL_LIB_TARGET} PUBLIC ${HAL_INC_DIRS})

