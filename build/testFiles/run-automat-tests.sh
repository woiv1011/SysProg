#!/bin/bash

testdir=$(dirname "$0")

automatdir=$testdir/../Automat
if [ ! -d "$automatdir" ] ; then
    echo "error the automat directory is not accessible at path" $automatdir
    exit 1  # fail
fi

make -C $automatdir clean
echo

make -C $automatdir -j all
echo

automat=$automatdir/debug/TestAutomat
if [ ! -x "$automat" ] ; then
    echo "error the automat is not accessible at path" $automat
    exit 1  # fail
fi

echo "Using the automat from path" $automat
echo

testfile=$testdir/"performance/The_King_James_Version_of_the_Bible.txt"
if [ -r "$1" ] ; then
    testfile=$1
fi

if [ ! -r "$testfile" ] ; then
    echo "error the testfile is not accessible at path" $testfile
    exit 1  # fail
fi

echo "Using the testfile from path" $testfile "with size" $(du -h $testfile | cut -f1)
echo

echo "time $automat $testfile > /dev/null"
time $automat $testfile > /dev/null
echo

echo "time $automat $testfile > out-normal.log"
time $automat $testfile > out-normal.log
echo

echo "time valgrind --leak-check=full $automat $testfile > out-leak-check.log"
time valgrind --leak-check=full $automat $testfile > out-leak-check.log
echo

rm callgrind.out.*
echo "time valgrind --tool=callgrind $automat $testfile > out-callgrind.log"
time valgrind --tool=callgrind $automat $testfile > out-callgrind.log
echo
kcachegrind callgrind.out.* 2>/dev/null >/dev/null &

