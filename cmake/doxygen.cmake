
# Data: 07/15/2023

if (BUILD_DOC)

	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		# set input and output files
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/docs/Doxyfile)

		# request to configure the file
		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("-- Doxygen configuration has been done.")

		# note the option ALL which allows to build the docs together with the application
		add_custom_target(docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Generation doxygen documents"
		VERBATIM)

	else(DOXYGEN_FOUND)	
    		message("-- Doxygen not found, please install it")
	endif(DOXYGEN_FOUND)
	
endif(BUILD_DOC)
