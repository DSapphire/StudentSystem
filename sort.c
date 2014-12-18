#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"function.h"
#include"update.h"
#include"sort.h" 
#include"course.h"
#include"student.h"

void sort_course(Course *courlist){
	Course *cursor;
	int n=0,i,flag=0;
	cursor=courlist;
	while(cursor->next){
		n++;
		cursor=cursor->next;
	}
	for(i=0;i<n;i++){
		cursor=courlist->next;
		for(cursor=courlist->next;cursor->next!=NULL;cursor=cursor->next){
			if(cursor->load<cursor->next->load){
				swap_course(cursor,cursor->next);
			}
		}
	}
	printf("\n课程按照热度排序后如下：\n\n"); 
	print_course(courlist,1);
	system("pause");
}
void swap_course(Course *cour1,Course *cour2){
	char *name;
	CourseType type;//compulsory
	float credit;int cap;int load;
	name=(char*)malloc(sizeof(cour1->name)+1);strcpy(name,cour1->name);free(cour1->name);
	cour1->name=(char*)malloc(sizeof(cour2->name)+1);strcpy(cour1->name,cour2->name);free(cour2->name);
	cour2->name=(char*)malloc(sizeof(name)+1);strcpy(cour2->name,name);free(name);
	type=cour1->type;cour1->type=cour2->type;cour2->type=type;
	credit=cour1->credit;cour1->credit=cour2->credit;cour2->credit=credit;
	cap=cour1->credit;cour1->cap=cour2->cap;cour2->cap=cap;
	load=cour1->load;cour1->load=cour2->load;cour2->load=load;
}
void sort_student(char *cname,int cload){
	Stu *stulist,*cursor;
	int i=0;
	float *grade;
	char **sname, **sex, **no;
	grade=(float*)malloc(sizeof(float)*cload);
	sname=(char**)malloc(sizeof(char*)*cload);
	sex=(char**)malloc(sizeof(char*)*cload);
	no=(char**)malloc(sizeof(char*)*cload);
	
	stulist=read_student();
	cursor=stulist->next; 
	i=0;
	while(cursor!=NULL&&i<cload){
		if(in_student(cursor,cname,&grade[i],0)){
			sname[i]=(char*)malloc(sizeof(char)*30);strcpy(sname[i],cursor->name);
			sex[i]=(char*)malloc(sizeof(char)*10);strcpy(sex[i],cursor->sex);
			no[i]=(char*)malloc(sizeof(char)*5);strcpy(no[i],cursor->no);
			i++;	
		}
		cursor=cursor->next;
	}
	sort_bygrade(no,sname,sex,grade,cload);
	printf("选课学生信息(按成绩排名)：\n\n");
	printf("学号\t姓名\t性别\t成绩\n");
	for(i=0;i<cload;i++){
		printf("%s\t%s\t%s\t%.2f\n",no[i],sname[i],sex[i],grade[i]);
		free(no[i]);free(sname[i]);free(sex[i]);
	}
	free(sname);free(sex);free(no);free(grade);
	destroy_student(stulist,1,1);//把学生内存释放！
}
void sort_bygrade(char *sno[],char *sname[],char *ssex[],float *sgrade,int n){
	int i,j,flag;
	char name[30],sex[10],no[5];
	float grade;
	for(i=1;i<n;i++){
		flag=0;
		for(j=0;j<n-i;j++){
			if(sgrade[j]<sgrade[j+1]){
				strcpy(no,sno[j]);strcpy(sno[j],sno[j+1]);strcpy(sno[j+1],no);
				strcpy(sex,ssex[j]);strcpy(ssex[j],ssex[j+1]);strcpy(ssex[j+1],sex);
				strcpy(name,sname[j]);strcpy(sname[j],sname[j+1]);strcpy(sname[j+1],name);
				grade=sgrade[j];sgrade[j]=sgrade[j+1];sgrade[j+1]=grade; 
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}
int in_student(Stu *temp,char *cname,float *grade,int mode){
	int flag=0,i;
	if(temp->mycourse){
		for(i=0;i<temp->mycourse;i++){
			if(strcmp((temp->course[i]).name,cname)==0){
				flag=1;
				if(mode==0)
					grade[0]=(temp->course[i]).grade;
				else{
					(temp->course[i]).grade=grade[0];
					(temp->course[i]).final=1;
				}
				break;
			}
		} 
	}
	return flag;
}
