#!/bin/bash
testdir=$(dirname "$0")
scanner=$testdir/../Scanner/debug/TestScanner

if [ ! -x "$scanner" ] ; then
    echo "error the scanner is not accessible at path" $scanner
    exit 1  # fail
fi

echo "Using the scanner from path" $scanner

# process the scanner test files.
FILES=$testdir/scanner/*.input.txt
if [ -r "$1" ] ; then
    FILES=$@
fi

for input in $FILES
do
    # take action on each file. $f store current file name
    echo "Scanning "$input" file..."
    
    results=${input/%input.txt/results.txt} # Generated output file
    output=${input/%input.txt/output.txt} # Expected text of output file
    
    echo time $scanner $input $results
    time $scanner $input $results
    
    diff --text --report-identical-files --ignore-all-space --brief $results $output
    echo diff --text --side-by-side --suppress-common-lines --speed-large-files --report-identical-files --ignore-all-space --width 150 $results $output
    
    echo 
    echo 
done

