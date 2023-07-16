# Author: M.Niarki
# Data: 07/15/2023
# Desc.: Cmake module for cppcheck

message("-- Cppcheck included" )
if (ENABLE_CPPCHECK)
    find_program(CPPCHECK_BIN NAMES cppcheck)
    
    if (CPPCHECK_BIN)
        execute_process(COMMAND ${CPPCHECK_BIN} --version
        OUTPUT_VARIABLE CPPCHECK_VERSION
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
        message ("-- Cppcheck version is : ${CPPCHECK_VERSION}")

        set(CPPCHECK_BUILD_DIR ${PROJECT_BINARY_DIR}/analysis/cppcheck) 
        # create cppcheck build folder  
        if(NOT EXISTS ${CPPCHECK_BUILD_DIR})
            file(MAKE_DIRECTORY ${CPPCHECK_BUILD_DIR})
        endif()
        set(CPPCHECK_BUILD_DIR_ARG "--cppcheck-build-dir=${CPPCHECK_BUILD_DIR}" CACHE STRING "cppcheck build directory")		
        set(CPPCHECK_ERROR_EXITCODE_ARG "--error-exitcode=1" CACHE STRING "The exit code to use when an error detected by cmake")
        set(CPPCHECK_CHECKS_ARG 
            "--enable=all" 
            "--platform=native"
            "--quiet"
            "--inline-suppr"
            #"--xml-version=2"
            "--suppress=missingIncludeSystem"
            "--suppress=unmatchedSuppression"
            "--suppress=unusedFunction"
            #--output-file=cppcheck-report.txt
            CAHCE STRING "Arguments for the checks to run"
        )
        set(_CPPCHECK_EXCLUDES)
        
        # set exclude files and folders
        foreach(ex ${CPPCHECK_EXCLUDES})
            list(APPEND _CPPCHECK_EXCLUDES "-i${ex}")
        endforeach()
        
        set(CPPCHECK_ALL_ARGS
            ${CPPCHECK_PROJECT_DIR_ARG}
            ${CPPCHECK_BUILD_DIR_ARG}
            ${CPPCHECK_ERROR_EXITCODE_ARG}
            ${CPPCHECK_CHECKS_ARG}
            ${_CPPCHECK_EXCLUDES}
            ${PROJECT_DEFINITIONS}
        )
        
        set(CPPCHECK_COMMAND
            ${CPPCHECK_BIN}
            ${CPPCHECK_ALL_ARGS})
        
        add_custom_target(cppcheck_analysis
            COMMAND ${CPPCHECK_COMMAND})
        
        message("-- Cppcheck configuration finshed.")
    
    else(CPPCHECK_BIN)
        message(FATAL_ERROR "-- Cppcheck not fount, please install it")
    endif(CPPCHECK_BIN)
endif(ENABLE_CPPCHECK)
