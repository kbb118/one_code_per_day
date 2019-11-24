#!/bin/bash
if [ -z $1 ];then
    echo "Create contest directory."
    echo "example: $0 abcXXX"
    exit 1
fi

mkdir ./$1 && cp ../template/* $1
