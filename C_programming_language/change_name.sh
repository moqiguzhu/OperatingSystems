#!/bin/bash

names=$`ls`
p_path=`pwd`
echo $p_path

for name in $names
do
    if [[ $name == *.cpp ]]
    then
        name_pre=$p_path"/"$name
        name_no_suffix=`echo $name | cut -d'.' -f 1`
        name_after=$p_path"/"$name_no_suffix".c"
        `mv $name_pre $name_after`
    fi
done
