#!/bin/bash

## This job must be executed on VM2 machines
## See ./README.md

## Nightly launched

echo "Job 5"
set -e

casejob=5
# change default  compiler
change_compiler=etc/jenkins/change_compiler-`uname -s`-`uname -r`-$casejob.sh
echo try to source file  "$change_compiler"
test -f "$change_compiler" && echo  source file "$change_compiler"
test -f "$change_compiler" && cat  "$change_compiler"
test -f "$change_compiler" && source "$change_compiler"


# configuration & build
autoreconf -i \
  && ./configure  --enable-download --enable-debug --prefix=/builds/workspace/freefem \
  && ./3rdparty/getall -a \
  && ./etc/jenkins/blob/build_PETSc.sh \
  && ./etc/jenkins/blob/build.sh

if [ $? -eq 0 ]
then
  echo "Build process complete"
else
  echo "Build process failed"
  exit 1
fi

# check
./etc/jenkins/blob/check.sh

if [ $? -eq 0 ]
then
  echo "Check process complete"
else
  echo "Check process failed"
  exit 1
fi

# install
./etc/jenkins/blob/install.sh

if [ $? -eq 0 ]
then
  echo "Install process complete"
else
  echo "Install process failed"
fi
