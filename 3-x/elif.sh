#! /bin/bash

echo -n "Input Score: "
read score

if (( $score >= 90 ))
then
	echo "Your Score is great"
elif (( $score >= 80 ))
then
	ehco "Your Score is good"
else
	echo "Your Score is not good"
fi
