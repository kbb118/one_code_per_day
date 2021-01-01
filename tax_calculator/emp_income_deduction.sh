#!/bin/bash

cat tmp2.txt | tr -d "," | \
    awk '{ \
            min=$1
            max=$2
            after_deduction=$3
            printf "if %d <= val and val < %d:\n", min, max
            printf "    return %f\n", after_deduction
            min=$4
            max=$5
            after_deduction=$6
            printf "if %d <= val and val < %d:\n", min, max
            printf "    return %f\n", after_deduction
            min=$7
            max=$8
            after_deduction=$9
            printf "if %d <= val and val < %d:\n", min, max
            printf "    return %f\n", after_deduction
}'
