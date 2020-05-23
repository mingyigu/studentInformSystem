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

//读取文件中的所有学生的信息放到结构体student中。 
int getFileinfrom(){
	FILE *fp = fopen("学生成绩.txt", "r"); 
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

//显示所有学生的信息 
void showStudentinform(int l) {
	getFileinfrom(l);
	int i = 0;
	printf("姓名   英语  数学 计算机  \n");
	for(i = 0; i < l; i++) {
		printf("%-7s",student[i].name);
		printf(" %-5d",student[i].English);
		printf(" %-5d",student[i].Math);
		printf(" %-5d \n",student[i].Programming);
	}
}


void searchStudent(int l) {
	int i = 0;
	printf("请输入要查询的学生的姓名：\n");
	char name[20];
	scanf("%s",name); 
	for(i = 0; i < l; i++) {
		if(strcmp(student[i].name,name) == 0){
			printf("姓名：%s\n英语：%d  数学：%d  计算机：%d\n",student[i].name,student[i].English,student[i].Math,student[i].Programming);
			return;
		}
		 
	}
	printf("查无此人!"); 
}

void execute(){
	printf("_________________________________________________________________\n");
	printf("|以下是学生英语、数学、程序三门课程的信息管理系统,可进行如下操作:|\n");
	printf("|输入1：添加学生信息                                             |\n");
	printf("|输入2：显示所有学生信息                                         |\n");
	printf("|输入3：删除学生信息                                             |\n");
	printf("|输入4：查询学生信息                                             |\n");
	printf("|输入5：按计算机成绩高低排序                                     |\n"); 
	printf("|输入0：退出系统                                                 |\n");
	printf("|________________________________________________________________|\n");
	
}

//添加学生信息 
void addStudentinform() {
	printf("请输入要录入的学生的信息：");
	char name[20];
	char English[4];
	char Math[4];
	char Programming[4];
	scanf("%s %s %s %s",name,English,Math,Programming);
	FILE *fp = fopen("学生成绩.txt", "a");
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

//删除学生信息 
int deleteStudentinform(int l) {
	char name[10];
	printf("请输入要删除的学生的姓名"); 
	scanf("%s",name);
	//先进行只读，获取非删除学生们的所有信息 
	FILE *fp = fopen("学生成绩.txt", "r"); 
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
	
	//没有找到该学生 
	if(l == stindex){
		return -1;
	}
	
	//进行文件内容覆盖 
	FILE *fq = fopen("学生成绩.txt", "w");
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

//对学生信息根据计算机成绩进行排序 
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

//执行各种操作 
void operate(int studentNum) {
	int opt;
	execute();
	int x = 0;
	while(1) {
		printf("\n请输入对应的操作数:"); 
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
				printf("查无此人！"); 
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
	printf("系统已关闭"); 
}

int main() {
	int studentNum  = getFileinfrom();
	operate(studentNum);
	return 0;
}














