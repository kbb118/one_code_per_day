#!/bin/bash

cat tmp3.txt | tr -d "," | \
    awk '{ \
            min=$1
            max=$3
            ratio=$4
            offset=$5
            printf "if %d <= val and val < %d:\n", min, max
            printf "    return val * %d / 100.0 - %f \n", ratio, offset
}'
