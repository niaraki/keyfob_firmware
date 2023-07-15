# author: M.Niraki
# Data: 07/15/2023
# Desc.: This cmake module halps to create lizard target for CCM analysis

find_program(LIZARD_BIN NAMES lizard)

if (LIZARD_BIN)
  message("-- Lizard configuration has been done.")

  add_custom_target(lizard 
  COMMAND 
    ${LIZARD_BIN}
    --CCN 10
    --length 1000
    --arguments 100
    ./src 
    > build/lizard-reports.txt
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Lizard CCM analysis"
  VERBATIM)

else(LIZARD_BIN)	
  message("-- Lizard not found, please install it [sudo] pip install lizard")
endif(LIZARD_BIN)

