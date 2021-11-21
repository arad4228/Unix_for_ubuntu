#! /bin/bash
function add {
	(( sum = $1 + $2 ))
	return $sum
}

add $1 $2
echo "$1 + $2 = $?"
