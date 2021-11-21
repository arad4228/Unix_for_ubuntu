#! /bin/bash

echo -n "Input x: "
read x

echo -n "Input y: "
read y

if (( x < y ))
then
	echo $x is less then $y
else
	echo $y is less then $x
fi
