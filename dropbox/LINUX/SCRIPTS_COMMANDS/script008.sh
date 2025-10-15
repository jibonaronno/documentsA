#!/bin/bash

echo ""

awk "/$2/ {print \$2\" \"\$3}" $1

