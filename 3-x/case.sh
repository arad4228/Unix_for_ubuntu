#!/bin/bash

echo -n "Select Command "
read cmd

case $cmd in
	[0-9])
		date
		;;
	[a-z])
		pwd
		;;
	*)
		echo "Usage:  "
		;;
esac
