#!/bin/bash

cat tmp.txt | tr -d "," | \
    awk '{ \
            min=$3
            max=$5
            health=$7
            pension=$11
            printf "if %d <= val and val < %d:\n", min, max
            printf "  return %f + %f\n", health, pension
}'
