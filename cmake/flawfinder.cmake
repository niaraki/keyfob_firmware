# author: M.Niraki
# Data: 07/15/2023
# Desc.: This cmake module halps to create flawfinder target for static CVE analysis

find_program(FLAWFINDER_BIN NAMES flawfinder)

if (FLAWFINDER_BIN)
  message("-- flawfinder configuration has been done.")

  add_custom_target(flawfinder 
  COMMAND 
    ${FLAWFINDER_BIN}
    --html 
    --context 
    --minlevel=1 
    ./src 
    > build/flawfinder-report.html
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "flawfinder CVE analysis"
  VERBATIM)

else(FLAWFINDER_BIN)	
  message("-- flawfinder not found, please install it [sudo] pip install flawfinder")
endif(FLAWFINDER_BIN)

