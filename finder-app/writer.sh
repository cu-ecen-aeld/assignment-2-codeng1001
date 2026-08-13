#!/bin/sh

writefile=$1
writestr=$2

if [ -z "$writefile" ] || [ -z "$writestr" ]; then
    echo "Error: two arguments required: writefile and writestr"
    echo "Usage: $0 writefile writestr"
    exit 1
fi

writedir=$(dirname "$writefile")
mkdir -p "$writedir"

echo "$writestr" > "$writefile"
if [ $? -ne 0 ]; then
    echo "Error: could not create file $writefile"
    exit 1
fi
