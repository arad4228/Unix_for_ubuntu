#! /bin/bash
echo -n "Enter number: "
read x

sum=0
num=1

until ((num > $x))
do
	((sum = sum + num ))
	((num = num + 1 ))
done
	echo "sum is $sum"

