#!/bin/bash
#echo $1

echo ""
#gawk '{gensub(".txt","",1);print ARGV[1] "\t" $3}' $1 | grep $2

#echo ""
#gawk '{gensub("dest001","",1); print }' $1

#echo ""

#awk simple example command
#awk '/src001/ {print $0} filename.txt'

awk "/$2/ {print \$3}" $1

