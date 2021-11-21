#! /bin/bash

echo -n "Are you OK? "
read ans

if [[ $ans == [Yy]* ]]
then
	echo "Happy"
else
	echo "Too Bad"
fi
