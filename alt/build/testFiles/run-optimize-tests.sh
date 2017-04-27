#!/bin/bash
testdir=$(dirname "$0")
scanner=$testdir/../Scanner/debug/TestScanner

if [ ! -x "$scanner" ] ; then
    echo "error the scanner is not accessible at path" $scanner
    exit 1  # fail
fi

echo "Using the scanner from path" $scanner
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

echo "time $scanner $testfile /dev/null /dev/null"
time $scanner $testfile /dev/null /dev/null
echo

echo "time $scanner $testfile out-normal.log err-normal.log"
time $scanner $testfile out-normal.log err-normal.log
echo

echo "time valgrind --leak-check=full $scanner $testfile out-leak-check.log err-leak-check.log"
time valgrind --leak-check=full $scanner $testfile out-leak-check.log err-leak-check.log
echo

rm callgrind.out.*
echo "time valgrind --tool=callgrind $scanner $testfile out-callgrind.log err-callgrind.log"
time valgrind --tool=callgrind $scanner $testfile out-callgrind.log err-callgrind.log
echo
kcachegrind callgrind.out.* 2>/dev/null >/dev/null &

