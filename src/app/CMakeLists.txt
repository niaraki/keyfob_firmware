add_library(${APP_LIB_NAME} STATIC
"main.c")

target_include_directories(
  ${APP_LIB_NAME} PRIVATE
  ${PROJECT_BINARY_DIR}/../configured_files/include/
)
target_link_libraries(${APP_LIB_NAME} PUBLIC 
  ${DRV_LIB_NAME}
  ${HAL_LIB_NAME}
)
