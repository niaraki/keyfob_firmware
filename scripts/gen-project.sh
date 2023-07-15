#!/bin/bash

# Author: m.niaraki
# Date: 7/15/2023
# Desc.: I use this script to generate the folder structure for my Embedded Proejcts 
# Use: ./gen-project project-name

# folders
rootFolders=("docs" "src" "external" "scripts" "templates" "tests" "cmake" "docker")
srcFolders=("app" "bsp" "common" "drivers" "hal" "hll" "middleware")
placeholderFileName="CMakeLists.txt"

# placeholders can be used for git repo.
function createPlaceholder() {
  path="$1/$placeholderFileName" 
  echo $path
  if [[ ! -f "$path" ]]; 
  then
    touch $path
  fi
}

function createFolder() {
 path="$1/$2"
 if [[ ! -d "${path}" ]]; 
 then
  mkdir $path
  createPlaceholder $path
 fi
}

# generarte the root folders
for folder in "${rootFolders[@]}"
do
  createFolder "." ${folder}
done

# copy a one version of this script in scripts folder
cp ./gen-project.sh ./scripts/

# generate the source folder based on the layerd architecture
for folder in "${srcFolders[@]}"
do
  createFolder "./src" ${folder}
done

# create readme.md
if [[ ! -f "./readme.md" ]] && [[  ! -f "./readme.md" ]] && 
   [[  ! -f "./README.md" ]] && [[  ! -f "./Readme.md" ]];
then
  echo "## project: $1" > ./Readme.md
fi

# create license.md
if [[ ! -f "./license.md" ]] && [[  ! -f "./license.md" ]] && 
   [[  ! -f "./License.md" ]] && [[  ! -f "./LICENSE.md" ]];
then
  echo "## project  $1 license" > ./License.md
fi

# create CMakeLists.txt
if [[ ! -f "./CMakeLists.txt" ]];
then
  echo "cmake_minimum_required(VERSION 3.13)" > ./CMakeLists.txt
  echo "project($1 C CXX)" >> ./CMakeLists.txt
fi

# remove itself
rm -f ./gen-project.sh
