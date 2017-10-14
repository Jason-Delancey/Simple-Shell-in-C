#!/bin/bash

## Bash file used to install git basic tools on Debian-based or Fedora Linux systems
## Also installs valgrind tool
## Uses default package-management tool

## Must run following command to make it executable: chmod a+x install_git.sh
## Then run the executable: ./install_git.sh
## Use valgrind using the syntax: valgrind --tool=memcheck --leak-check=yes executable_name

echo "Installing git...."
sudo apt-get update
sudo apt-get install git-all
sudo apt-get install valgrind
