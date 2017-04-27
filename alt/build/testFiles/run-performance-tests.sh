#!/bin/bash
testdir=$(dirname "$0")
scanner=$testdir/../Scanner/debug/TestScanner

if [ ! -x "$scanner" ] ; then
    echo "error the scanner is not accessible at path" $scanner
    exit 1  # fail
fi

echo "Using the scanner from path" $scanner

# process the scanner test files.
FILES=$testdir/performance/*.txt
for input in $FILES
do
    # take action on each file. $f store current file name
    echo "Processing performance test for" $input "..."
    
    results=${input/%txt/results} # Generated output file
    errors=${input/%txt/errors} # Generated error file
    output=${input/%txt/output} # Expected text of output file
    
    echo time $scanner $input $results $errors
    time $scanner $input $results $errors

    if [ -r "$output" ] ; then
        diff --text --side-by-side --suppress-common-lines --speed-large-files --report-identical-files --ignore-all-space $results $output
    fi
    
    echo
    
done

