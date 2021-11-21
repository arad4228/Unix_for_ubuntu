#include <stdio.h>

typedef struct Student {
	char name[30];
	int ko;
	int en;
	int ma;
	int total;
} student;

int main(void)
{
	//파일에 학생의 수
	int num;
	int avg_ko = 0, avg_en = 0, avg_ma = 0; 
	char temp[BUFSIZ];
	FILE* fp = fopen("3-8.dat","r");
	FILE* ofp = fopen("3-8.out","w");
	while(fgets(temp, BUFSIZ,fp) != NULL)
		num++;
	rewind(fp);
	//첫번째 줄은 과목명이므로 삭제.
	student stlist[num-1];
	// 과목명을 명을 읽기 위한 작업
	fgets(temp, BUFSIZ, fp);	
	
	// 학생의 구조체에 데이터 저장
	for (int i = 0; i < num-1; i++)
	{
		fscanf(fp,"%s %d %d %d", stlist[i].name, &stlist[i].ko, &stlist[i].en, &stlist[i].ma);
		stlist[i].total = (stlist[i].ko + stlist[i].en + stlist[i].ma);
	}
	// 학생수 출력
	fprintf(ofp,"학생의수는  %d입니다.\n", num-1);
	// 각 학생의 점수의 합과 평균을 출력.
	for (int i = 0; i < num-1; i++)
		fprintf(ofp,"학생%s의 합은 %d이고 평균은 %d입니다.\n", stlist[i].name, stlist[i].total, stlist[i].total/3);
	// 과목 평균을 구하기 위한 작업
	for(int i = 0; i < num-1; i++)
	{	
		avg_ko = stlist[i].ko + avg_ko;
		avg_en = stlist[i].en + avg_en;
		avg_ma = stlist[i].ma + avg_ma;
	}
	//과목 평균 출력
	fprintf(ofp,"avg KO = %d, avg EN = %d, avg MA = %d\n",avg_ko/(num-1), avg_en/(num-1),avg_ma/(num-1));
	return 0;
}
