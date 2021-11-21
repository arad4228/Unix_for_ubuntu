#bash shall을 가지고 한다. 
#! /bin/bash
#세 변수 i,j,k를 사용한다고 선언
i, j, k 
#i = 0, j =1이라는 값을 넣어준다.
i=0
j=1

#반복문 i가 100보다 작은 동안 작동한다.
while (( i < 100))
do
	#변수 i의값을 출력하고 k에는i+j를 넣고, i에는 j의 값을, j에는 k의값을 넣는다.
	echo ${i}
	(( k = i+j ))
	(( i = j ))
	(( j = k ))
done

