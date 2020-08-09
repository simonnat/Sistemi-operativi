#!/bin/bash

if [ $# -eq 0 ]
then
	echo "No argument"
	echo "Usage: column [Field_number] [File]"
	exit 1
fi

if [ $# -gt 1 ]
then
	echo "Too much arguments"
	echo "Usage: column [Field_number] [File]"
	exit 1
fi


if [ $# -eq 1 ]
then
	field_number=$1
	awk 'length($3)!=0 { print $'$field_number'; }'

fi
