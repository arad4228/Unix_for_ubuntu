#! /bin/bash
ret=0
function add {
	(( sum = $1 + $2 ))
	ret=$sum
	return
}

add $1 $2
echo "$1 + $2 = $ret"
