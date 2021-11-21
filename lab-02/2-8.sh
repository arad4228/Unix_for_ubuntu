#!/bin/bash

echo -n "Is is morning?"
read answer
case $answer in
	y* | Y* ) echo Good Morning ;;
	n* | N* ) echo have a good day ;;
	*) echo Sorry your answer is not proper ;;
esac

exit 0
