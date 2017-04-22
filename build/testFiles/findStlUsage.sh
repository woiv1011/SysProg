#!/bin/bash

testdir=$(dirname "$0")

maindir=$testdir/..
if [ ! -d $maindir ] ; then
    echo "error the main directory is not accessible at path" $maindir
    exit 1  # fail
fi

grep -w -e "<string>" -e "<string.h>" -e "<list>" -e "<vector>" -e "<map>" -r --include="*.h" --include="*.cpp" --color=always $maindir
