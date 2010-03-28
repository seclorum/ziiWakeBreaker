#!/bin/bash
#
#   Copyright (C) 2008 Zii Labs Pte Ltd
#   All Rights Reserved.
#
#  Run this script to setup the cmake environment for the build
#  (generate the initial cache file, and generate the Makefiles)
#

# Usage:   ./prebuild.sh [build arch] [build tree] [absolute path of srcdir]

BUILDARCH=$1
BUILDDIR=$2
SRCDIR=$3

if [[ $PLASZMAHOME = "" ]]; then
   echo "PLASZMAHOME not set"
   exit
fi
if [[ $APPHOME = "" ]]; then
   echo "APPHOME not set"
   exit
fi
# set defaults
if [[ $BUILDARCH = "" ]]; then
   BUILDARCH=arm
fi

if [[ $BUILDDIR = "" ]]; then
   BUILDDIR=build.$BUILDARCH
fi

if [[ $SRCDIR = "" ]]; then
   SRCDIR=`pwd`
fi

if [[ -f $BUILDDIR ]]; then
   echo "Err: Specified [build tree] path refers to a file"
   exit
fi

if [[ ! -d $BUILDDIR ]]; then
   mkdir -p $BUILDDIR
fi

if [[ ! -d $APPHOME/bin ]]; then
   mkdir -p $APPHOME/bin
fi    

if [[ ! -d $APPHOME/lib ]]; then
   mkdir -p $APPHOME/lib
fi    

#### Run Cmake to generate the Makefiles
echo "Generate the Makefiles"

cd $BUILDDIR
cmake -DCMAKE_TOOLCHAIN_FILE=$PLASZMAHOME/toolchain-s5tools-arm.cmake $SRCDIR
echo "Makefiles generated in $BUILDDIR"


