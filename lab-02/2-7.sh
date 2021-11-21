#!/bin/bash

let dan=2
while  (( dan<=9 ))
do
	let num=1
	while (( num<=9 ))
	do
		printf "$(( $dan * $num ))\t"
	 	(( num=num+1 ))
	done
	echo " "
	(( dan=dan+1 ))
done
