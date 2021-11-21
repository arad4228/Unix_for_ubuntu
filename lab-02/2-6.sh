#!/bin/bash

for DIR in $(ls ~)
do
	if [[ -d ~/$DIR ]]
	then
		ls -R ~/$DIR
	fi
done
	
exit 0
