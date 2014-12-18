#include <stdio.h>
#include <stdlib.h>
#include<string.h> 

#include"function.h"
#include"update.h"
#include"sort.h" 
#include"course.h"
#include"student.h"

Stu * create_student(int n){
	Stu *stulist,*tempstu,*cursor;
	stulist=(Stu*)malloc(sizeof(Stu));
	if(stulist==NULL){
		printf("内存分配失败！");
		exit(0);
	}
	stulist->gpa=0;
	stulist->next=NULL;
	stulist->mycourse=0;
	stulist->course=NULL;
	cursor=stulist;
	
	char no[5],name[80],major[80],sex[10],ch;
	int i;
	printf("\n您需要输入学生的学号 姓名 性别 专业\n");
	for(i=0;i<n;i++){
		tempstu=(Stu*)malloc(sizeof(Stu));
		if(tempstu==NULL){
			printf("\n内存分配失败！\n");
			exit(0);
		}
		tempstu->next=NULL;
		tempstu->mycourse=0;
		tempstu->course=NULL;
		tempstu->gpa=0;
		do{
			printf("\n");
			printf("输入第%d个同学的学号(四位整数)：",i+1);
			scanf("%s",no);fflush(stdin);
			printf("输入第%d个同学的名字：",i+1);
			scanf("%s",name);fflush(stdin);
			printf("输入第%d个同学的性别：",i+1);
			scanf("%s",sex);fflush(stdin);
			printf("输入第%d个同学的专业：",i+1);
			scanf("%s",major);fflush(stdin);
			printf("您输入的学生信息是\n学号:\t%s\n名字:\t%s\n性别:\t%s\n专业:\t%s\n",no,name,sex,major);
			printf("\n修改请输入N或者n,其他任意键继续:");
			ch=getchar();fflush(stdin);
			if(strlen(no)!=4){
				printf("学号输入错误！"); 
				ch='n'; 
			}
		}while(ch=='n'||ch=='N');
		if(delete_student(stulist,no,0)!=NULL){//学号重复检查 
			printf("\n学号重复！请重新输入！\n");
			i--;
			continue;
		}
		strcpy(tempstu->no,no);
		tempstu->name=(char*)malloc(sizeof(name)+1);
		strcpy(tempstu->name,name);
		strcpy(tempstu->sex,sex);
		tempstu->major=(char*)malloc(sizeof(major)+1);
		strcpy(tempstu->major,major);
		
		cursor->next=tempstu;
		cursor=cursor->next;
	}
	
	printf("\n学生信息创建成功！\n");
	return stulist;
}
Stu * insert_student(Stu *stulist,Stu *newstu){
	Stu *cursor;
	cursor=stulist;
	if(cursor->next==NULL){
		cursor->next=newstu;
	}else{
		while(cursor->next&&strcmp(cursor->next->no,newstu->no)>0){// 
			cursor=cursor->next;
		}
		newstu->next=cursor->next;
		cursor->next=newstu;
	}
	return stulist;
}
Stu * add_student(Stu *stulist){
	Stu *newstu;
	newstu=(Stu*)malloc(sizeof(Stu));
	if(newstu==NULL){
		printf("\n内存分配失败！\n");
		exit(0);
	}
	newstu->next=NULL;
	newstu->mycourse=0;
	newstu->course=NULL;
	
	char no[5],name[80],major[80],sex[10],ch;
	printf("\n您需要输入学生的学号 姓名 性别 专业\n");
	do{
		printf("\n");
		printf("输入学号(四位整数)：");
		scanf("%s",no);fflush(stdin);
		printf("输入名字：");
		scanf("%s",name);fflush(stdin);
		printf("输入性别：");
		scanf("%s",sex);fflush(stdin);
		printf("输入专业：");
		scanf("%s",major);fflush(stdin);
		printf("您输入的学生信息是\n学号:\t%s\n名字:\t%s\n性别:\t%s\n专业:\t%s\n",no,name,sex,major);
		printf("\n修改请输入N或者n,其他任意键继续:");
		ch=getchar();fflush(stdin);
		if(strlen(no)!=4){
			printf("学号输入错误！"); 
			ch='n'; 
		}
	}while(ch=='n'||ch=='N');
	if(delete_student(stulist,no,0)!=NULL){//学号重复检查 
			printf("\n学号重复！请重新输入！\n");
			return stulist; 
	}
	newstu->gpa=0;
	strcpy(newstu->no,no);
	newstu->name=(char*)malloc(sizeof(name)+1);
	strcpy(newstu->name,name);
	strcpy(newstu->sex,sex);
	newstu->major=(char*)malloc(sizeof(major)+1);
	strcpy(newstu->major,major);
	
	stulist=insert_student(stulist,newstu);
	return stulist;
}
Stu * delete_student(Stu *stulist,char *no,int mode){
	Stu *cursor,*temp;temp=NULL;
	cursor=stulist;
	while(cursor->next&&strcmp(cursor->next->no,no)!=0)
		cursor=cursor->next;
	temp=cursor->next;
	if(cursor->next){
		if(mode){
			if(temp->mycourse){//也可以后台强制删除，但是不人性 
				printf("\n学生有选课信息，如需删除，请先退课！\n");
			}else{
				cursor->next=cursor->next->next;
				destroy_student(temp,0,0);
				printf("\n删除成功!\n");
			}
		}
	}
	if(mode)
		return  stulist;
	else
		return temp;
}
Stu * read_student(){
	Stu *stulist,*tempstu,*cursor;
	stulist=(Stu*)malloc(sizeof(Stu));
	if(stulist==NULL){
		printf("内存分配失败！");
		return;
	}
	stulist->gpa=0;
	stulist->next=NULL;
	stulist->course=NULL;
	cursor=stulist;
	FILE *fr;
	fr=fopen(STUDENTBOOK,"r");
	if(fr==NULL){
		printf("文件打开失败!\n");
		exit(0);
	}
	char no[5],sname[80],cname[80],major[80],sex[10];float gpa,credit,grade,calcredit,calgrade;int mycourse,final;
	while(!(feof(fr))){
		tempstu=(Stu*)malloc(sizeof(Stu));
		if(tempstu==NULL){
			printf("\n内存分配失败！\n");
			return;
		}
		tempstu->next=NULL;
		fscanf(fr,"%s %s %s %s %f %d ",no,sname,sex,major,&gpa,&mycourse);
		strcpy(tempstu->no,no);
		tempstu->name=(char*)malloc(sizeof(sname)+1);
		strcpy(tempstu->name,sname);
		strcpy(tempstu->sex,sex);
		tempstu->major=(char*)malloc(sizeof(major)+1);
		strcpy(tempstu->major,major);
		tempstu->mycourse=mycourse;
		
		calcredit=0;calgrade=0;
		tempstu->course=(myCourse*)malloc(sizeof(myCourse)*mycourse);
		if(tempstu->course!=NULL)
			for(mycourse=0;mycourse<tempstu->mycourse;mycourse++){
				fscanf(fr,"%s %f %f %d ",cname,&credit,&grade,&final);//
				(tempstu->course[mycourse]).name=(char*)malloc(sizeof(cname));
				strcpy((tempstu->course[mycourse]).name,cname);
				(tempstu->course[mycourse]).credit=credit;
				(tempstu->course[mycourse]).grade=grade;
				(tempstu->course[mycourse]).final=final;
				if(final)
					calcredit+=credit;calgrade+=credit*grade;
			}
		if(calcredit>0)
			tempstu->gpa=calgrade/calcredit;
		else
			tempstu->gpa=0;
		
		cursor->next=tempstu;
		cursor=cursor->next;
	}
	fclose(fr);
	printf("\n学生信息读取成功！\n");
	return stulist;
} 

void save_student(Stu *stulist){
	Stu *cursor;
	cursor=stulist;
	int mycourse;
	FILE *fw;
	fw=fopen(STUDENTBOOK,"w");
	if(fw==NULL){
		printf("打开文件失败！请重试！\n");
		return;
	}
	if(stulist!=NULL){
		cursor=cursor->next;
		do{
			fprintf(fw,"\n%s %s %s %s %.2f %d \n",cursor->no,cursor->name,cursor->sex,cursor->major,cursor->gpa,cursor->mycourse);
			for(mycourse=0;mycourse<cursor->mycourse;mycourse++){
				fprintf(fw,"%s %.2f %.2f %d \n",(cursor->course[mycourse]).name,(cursor->course[mycourse]).credit,(cursor->course[mycourse]).grade,(cursor->course[mycourse]).final);
			}
			cursor=cursor->next;
		}while(cursor!=NULL);
		fclose(fw);
	}else{
		printf("\n保存学生信息失败！\n");
	}
}
void modify_student(Stu *stulist,char *no){
	Stu* temp;
	temp=delete_student(stulist,no,0);
	char ch;
	
	do{
		printf("\n请选择操作类型：\n");printf("1-选课\t2-退课\t0-退出\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				update_student(temp,ch);
				break;
			case '2':
				update_student(temp,ch);
				break;
			case '0':
				break; 
			 default:
			 	printf("错误输入！请重新选择！\n");break; 
		}
	}while(ch!='0');
}
void print_student(Stu *stulist,int mode){
	Stu * cursor;
	cursor=stulist;
	if(stulist!=NULL){
		printf("\n打印学生信息如下：\n");
		printf("\n学号\t姓名\t性别\t专业\tGPA\t已选课程数量\t\n\n");
		if(mode){
			cursor=cursor->next;
			do{
				printf("%s\t%s\t%s\t%s\t%.2f\t%d\n",cursor->no,cursor->name,cursor->sex,cursor->major,cursor->gpa,cursor->mycourse);
				cursor=cursor->next;
			}while(cursor!=NULL);
		}else{
			int i;
			printf("%s\t%s\t%s\t%s\t%.2f\t%d\n",cursor->no,cursor->name,cursor->sex,cursor->major,cursor->gpa,cursor->mycourse);
			printf("\n所选课程信息如下(结课为0表示未考试，成绩未录入)：\n");
			printf("\n课程名\t学分\t结课\t成绩\n\n");
			for(i=0;i<cursor->mycourse;i++)
				printf("%s\t%.2f\t%d\t%.2f\n",(cursor->course[i]).name,(cursor->course[i]).credit,(cursor->course[i]).final,(cursor->course[i]).grade);
			printf("\n");
		}	
	}else{
		printf("\n打印课程信息失败！\n");
	}
}
void destroy_student(Stu *stulist,int mode,int no){
	Stu *cursor,*temp;
	int mycourse;
	if(mode){
		cursor=stulist;
		while(cursor->next){
			temp=cursor->next;
			cursor->next=cursor->next->next;
			for(mycourse=0;mycourse<temp->mycourse;mycourse++){
				free((temp->course[mycourse]).name);
			}
			free(temp->course);free(temp->name);free(temp->major);
			free(temp);
		}
		free(stulist);
	}else{
		temp=stulist;
		for(mycourse=0;mycourse<temp->mycourse;mycourse++){
			free((temp->course[mycourse]).name);
		}
		free(temp->course);
		if(!no){
			free(temp->name);free(temp->major);
			free(temp);
		}	
	}
}

