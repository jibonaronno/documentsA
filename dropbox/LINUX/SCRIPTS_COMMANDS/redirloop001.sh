#!/bin/bash
# redirloop001.sh

if [ -z "$1" ]
then
  Filename=names.data       # Default, if no filename specified.
else
  Filename=$1
fi  
#+ Filename=${1:-names.data}
#  can replace the above test (parameter substitution).

count=0

echo

while [ "$name" != Smith ]  # Why is variable $name in quotes?
do
  read name                 # Reads from $Filename, rather than stdin.
  echo $name
  let "count += 1"
  if [ $count -gt 15 ]
  	then
  	break
  fi
done <"$Filename"           # Redirects stdin to file $Filename. 
#    ^^^^^^^^^^^^

echo; echo "$count names read"; echo

exit 0
