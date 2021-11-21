#! /bin/bash

select cmd in pwd date quit
do
	case $cmd in
		pwd) pwd
			;;
		date) date
			;;
		quit) break
			;;
		*) echo "Invalid Selection"
			;;
	esac
done
