#!/bin/bash

current_dir=${PWD##*/}

if [ ! $current_dir == "tracker" ]; then
	echo "Must be in root directory of tracker project to make docs"
	exit 1
fi

epydoc --html src/food_utils.py -o docs/ > /dev/null
