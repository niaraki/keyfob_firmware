# Author: M.Niaraki
# Data: 07/17/2023

function(CheckGitInstalled)
	find_package(Git)
  if (GIT_FOUND)
        message("-- GIT found.")
	else()	
    		message("-- Git not found, please install it")
	endif()
endfunction()

