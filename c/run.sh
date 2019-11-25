#!/usr/bin/env bash

# The program name is the first argument, minus a possibly supplied .c suffix
program=${1%".c"}

if [ -z "$program" ];
then
    echo "must supply program name"
    exit 1
fi

echo "Building and running $program..."
   
program_path="_build/bin/${program}"

make $program_path
$program_path
