#!/bin/sh

echo "Checking the building environment sanity ..."

check() {
  if which $1 > /dev/null; 
  then 
    if [ -z "$2" ];  then
     echo "$1 found: `$1 --version`"; 
    else
     echo "$1 found"; 
    fi
  else 
    echo "$1 does not exist. please insatll it"; 
    exit 1;
  fi
} 

check cppcheck 
check lizard 
check flawfinder 
check clang-format 
check arm-none-eabi-gcc 
check doxygen 
check lcov 
check make 0
check cmake 0
check gcc 0

echo "Done!"
exit 0

