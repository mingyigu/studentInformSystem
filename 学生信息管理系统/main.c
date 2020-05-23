#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
	char name[20];
	int English;
	int Math;
	int Programming;
}student[100]; 

void split(char *src,const char *separator,char **dest) {

     char *pNext;
     int count = 0;
     if (src == NULL || strlen(src) == 0) 
        return;
     if (separator == NULL || strlen(separator) == 0) 
        return;
     pNext = (char *)strtok(src,separator); 
     while(pNext != NULL) {
          *dest++ = pNext;
         pNext = (char *)strtok(NULL,separator);  
    }  

} 

//��ȡ�ļ��е�����ѧ������Ϣ�ŵ��ṹ��student�С� 
int getFileinfrom(){
	FILE *fp = fopen("ѧ���ɼ�.txt", "r"); 
	if(fp == NULL) {
		printf("No such file");
	}
	char str[50];
	int x = 0;
	char* res[30];
	int stindex = 0;
	while(fgets(str, 100, fp)) {
		
		
		split(str," ",res);
		strcpy(student[stindex].name,res[0]);
		student[stindex].English = atoi(res[1]);
		student[stindex].Math = atoi(res[2]);
		student[stindex].Programming = atoi(res[3]);
		
		stindex++;
	}
	fclose(fp);
	return stindex;
}

//��ʾ����ѧ������Ϣ 
void showStudentinform(int l) {
	getFileinfrom(l);
	int i = 0;
	printf("����   Ӣ��  ��ѧ �����  \n");
	for(i = 0; i < l; i++) {
		printf("%-7s",student[i].name);
		printf(" %-5d",student[i].English);
		printf(" %-5d",student[i].Math);
		printf(" %-5d \n",student[i].Programming);
	}
}


void searchStudent(int l) {
	int i = 0;
	printf("������Ҫ��ѯ��ѧ����������\n");
	char name[20];
	scanf("%s",name); 
	for(i = 0; i < l; i++) {
		if(strcmp(student[i].name,name) == 0){
			printf("������%s\nӢ�%d  ��ѧ��%d  �������%d\n",student[i].name,student[i].English,student[i].Math,student[i].Programming);
			return;
		}
		 
	}
	printf("���޴���!"); 
}

void execute(){
	printf("_________________________________________________________________\n");
	printf("|������ѧ��Ӣ���ѧ���������ſγ̵���Ϣ����ϵͳ,�ɽ������²���:|\n");
	printf("|����1�����ѧ����Ϣ                                             |\n");
	printf("|����2����ʾ����ѧ����Ϣ                                         |\n");
	printf("|����3��ɾ��ѧ����Ϣ                                             |\n");
	printf("|����4����ѯѧ����Ϣ                                             |\n");
	printf("|����5����������ɼ��ߵ�����                                     |\n"); 
	printf("|����0���˳�ϵͳ                                                 |\n");
	printf("|________________________________________________________________|\n");
	
}

//���ѧ����Ϣ 
void addStudentinform() {
	printf("������Ҫ¼���ѧ������Ϣ��");
	char name[20];
	char English[4];
	char Math[4];
	char Programming[4];
	scanf("%s %s %s %s",name,English,Math,Programming);
	FILE *fp = fopen("ѧ���ɼ�.txt", "a");
	fputs(name,fp);
	fputs(" ",fp);
	fputs(English,fp);
	fputs(" ",fp);
	fputs(Math,fp);
	fputs(" ",fp);
	fputs(Programming,fp);
	fputs("\n",fp);
	fclose(fp);
}

//ɾ��ѧ����Ϣ 
int deleteStudentinform(int l) {
	char name[10];
	printf("������Ҫɾ����ѧ��������"); 
	scanf("%s",name);
	//�Ƚ���ֻ������ȡ��ɾ��ѧ���ǵ�������Ϣ 
	FILE *fp = fopen("ѧ���ɼ�.txt", "r"); 
	if(fp == NULL) {
		printf("No such file");
	}
	char str[50];
	int x = 0;
	int i = 0;
	char* res[50];
	int stindex = 0;
	while(fgets(str, 100, fp)) {
		split(str," ",res);
		if(strcmp(res[0],name) != 0) {
			strcpy(student[stindex].name,res[0]);
			student[stindex].English = atoi(res[1]);
			student[stindex].Math = atoi(res[2]);
			student[stindex].Programming = atoi(res[3]);
			stindex++;
		}
	}
	fclose(fp);
	
	//û���ҵ���ѧ�� 
	if(l == stindex){
		return -1;
	}
	
	//�����ļ����ݸ��� 
	FILE *fq = fopen("ѧ���ɼ�.txt", "w");
	for(i = 0; i < stindex; i++) {
		char English[10];
		char Math[10];
		char Programming[10];
		itoa(student[i].English,English,10);
		itoa(student[i].Math,Math,10);
		itoa(student[i].Programming,Programming,10);
		char str[50];
		strcpy(str,student[i].name);
		strcat(str," ");
		strcat(str,English);
		strcat(str," ");
		strcat(str,Math);
		strcat(str," ");
		strcat(str,Programming);
		strcat(str,"\n");
		fputs(str,fq);
	}
	fclose(fq);
	return 1;
} 

//��ѧ����Ϣ���ݼ�����ɼ��������� 
void sortByProgramming(int  l) {
	struct Student k;
	int i,j;
	for(i = 0; i < l - 1 ; i++) {
		for(j = 1; j < l - i; j++) {
			if(student[j - 1].Programming > student[j].Programming) {
				k = student[j - 1];
				student[j - 1] = student[j];
				student[j] = k;
			}
		}
	}
	for(i = 0; i < l; i++) {
		printf("%-7s",student[i].name);
		printf(" %-5d",student[i].English);
		printf(" %-5d",student[i].Math);
		printf(" %-5d \n",student[i].Programming);
	}
}

//ִ�и��ֲ��� 
void operate(int studentNum) {
	int opt;
	execute();
	int x = 0;
	while(1) {
		printf("\n�������Ӧ�Ĳ�����:"); 
		scanf("%d",&opt);
		if(opt == 1) {
			addStudentinform();
			studentNum++;
		}
		else if(opt == 2) {
			showStudentinform(studentNum);
		}
		else if(opt == 3) {
			x = deleteStudentinform(studentNum);
			if(x != -1) {
				studentNum--;
			}
			else{
				printf("���޴��ˣ�"); 
			} 
		}
		else if(opt == 4) {
			searchStudent(studentNum);
		}
		else if(opt == 5) {
			sortByProgramming(studentNum);
		} 
		else if(opt == 0) {
			break;
		} 
	}
	printf("ϵͳ�ѹر�"); 
}

int main() {
	int studentNum  = getFileinfrom();
	operate(studentNum);
	return 0;
}














