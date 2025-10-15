#!/bin/bash
# This example by Albert Siersema
# Used with permission (thanks!).

function doesOutput()
 # Could be an external command too, of course.
 # Here we show you can use a function as well.
{
  #ls -al *.jpg | awk '{print $5,$9}'
  ls -al | awk '{print $5,$9}'
}


nr=0          #  We want the while loop to be able to manipulate these and
totalSize=0   #+ to be able to see the changes after the 'while' finished.

while read fileSize fileName ; do
  echo "$fileName is $fileSize bytes"
  let nr++
  totalSize=$((totalSize+fileSize))   # Or: "let totalSize+=fileSize"
done<<EOF
$(doesOutput)
EOF

echo "$nr files totaling $totalSize bytes"
