#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"function.h"
#include"update.h"
#include"sort.h" 
#include"course.h"
#include"student.h"


Course * create_course(int n){
	Course *courlist,*tempcour,*cursor;
	courlist=(Course *)malloc(sizeof(Course));
	if(courlist==NULL){
		printf("\n分配内存失败！\n");
		exit(0);
	}
	courlist->next=NULL;
	cursor=courlist;
	
	int i,tmptype,cap;
	float credit;
	char ch;
	char name[20];
	printf("你需要输入课程的名字 类型 学分 客容量。\n\n");
	for(i=0;i<n;i++){
		tempcour=(Course *)malloc(sizeof(Course));//????
		if(tempcour==NULL){
			printf("\n分配内存失败！\n");
			exit(0);
		}
		tempcour->next=NULL;
		
		do{
			reinput:
			printf("\n");
			printf("输入第%d门课程的名字：",i+1);
			scanf("%s",name);fflush(stdin);
			printf("输入第%d门课程类型（类型是选修或者必修，分别用0和1指示）：",i+1);
			scanf("%d",&tmptype);fflush(stdin);
			printf("输入第%d门课程学分：",i+1);
			scanf("%f",&credit);fflush(stdin);
			printf("输入第%d门课程的课容量：",i+1);
			scanf("%d",&cap);fflush(stdin);
			printf("\n您输入的第%d门课程是\n课程名:\t\t%s\n课程类型：\t%d\n学分：\t\t%.2f\n课容量：\t%d\n\n修改请输入N或者n,其他任意键继续:",i+1,name,tmptype,credit,cap);
			ch=getchar();fflush(stdin);
		}while(ch=='N'||ch=='n');
		if(cap<0||tmptype>1||tmptype<0){
			printf("课容量和课程类型输入错误！请重新输入:\n");
			goto reinput;
		}else if(delete_course(courlist,name,0)!=NULL){//课程名重复检查
			printf("\n课程已经创建！\n");
			i--;
			continue;
		}
		tempcour->name=(char *)malloc(sizeof(name)+1);
		strcpy(tempcour->name,name);//
		tempcour->cap=cap;
		tempcour->credit=credit;
		tempcour->type=(CourseType)(tmptype);
		tempcour->load=0;
		
		cursor->next=tempcour;
		cursor=cursor->next;
	}
	printf("\n课程创建成功！\n");system("pause");
	return courlist;
}

Course * insert_course(Course *courlist,Course *newcour){
	Course *cursor;
	cursor=courlist;
	if(cursor->next==NULL){
		cursor->next=newcour;
	}else{
		while(cursor->next){// 
			cursor=cursor->next;
		}
		cursor->next=newcour;
	}
	return courlist;
}
Course * add_course(Course *courlist){
	Course *newcour;
	newcour=(Course *)malloc(sizeof(Course));
	if(newcour==NULL){
		printf("\n失败!\n");
		exit(0);
	}
	newcour->next=NULL;
	char name[20],ch;
	int cap,tmptype;
	float credit;
	printf("你需要输入课程的名字 类型 学分 课容量。\n\n");
	do{
		printf("\n");
		printf("输入课程的名字：");
		scanf("%s",name);fflush(stdin);
		printf("输入课程类型（类型是选修或者必修，分别用0和1指示）：");
		scanf("%d",&tmptype);fflush(stdin);
		printf("输入课程学分：");
		scanf("%f",&credit);fflush(stdin);
		printf("输入课程的课容量：");
		scanf("%d",&cap);fflush(stdin);
		printf("\n您输入的是\n课程名:\t\t%s\n课程类型：\t%d\n学分：\t\t%.2f\n课容量：\t%d\n\n修改请输入N或者n,其他任意键继续:",name,tmptype,credit,cap);
		ch=getchar();fflush(stdin);
	}while(ch=='N'||ch=='n');
	if(cap<0||tmptype>1||tmptype<0){
		printf("课容量和课程类型输入错误！\n");
		printf("无效输入不做更改，请返回菜单从新选择！\n");
		return courlist;
	}else if(delete_course(courlist,name,0)!=NULL){//课程重复检查 
		printf("\n课程已经存在，不需要创建！如果需要修改请返回菜单前往 修改课程！\n");
		return courlist;
	}else{
		newcour->name=(char *)malloc(sizeof(name)+1);
		strcpy(newcour->name,name);
		newcour->type=(CourseType)(tmptype);
		newcour->credit=credit;
		newcour->cap=cap;
		newcour->load=0;
		courlist=insert_course(courlist,newcour);
		return courlist;
	}
}
Course * delete_course(Course *courlist,char *name,int mode){
	Course *cursor,*temp;temp=NULL;
	cursor=courlist;
	while(cursor->next&&strcmp(cursor->next->name,name)!=0)
		cursor=cursor->next;
	temp=cursor->next;
	if(cursor->next){
		if(mode){
			cursor->next=cursor->next->next;
			if(temp->load){//其实也可强制删除学生，但是不人道 
				printf("\n已经有学生选课，不能删除该课程！如果需要删除，请先退课！\n"); 
			}else{
				destroy_course(temp,0);
				printf("\n删除成功!\n");
			}
		}
	}
	if(mode)
		return  courlist;
	else
		return temp;
}

Course * read_course(){
	Course *courlist,*tempcour,*cursor;
	courlist=(Course *)malloc(sizeof(Course));
	if(courlist==NULL){
		printf("\n分配内存失败！\n");
		exit(0);
	}
	courlist->next=NULL;
	cursor=courlist;
	FILE *fr;
	fr=fopen(COURSEBOOK,"r");
	if(fr==NULL){
		printf("文件打开失败!\n");
		exit(0);
	}
	
	int i,type,cap,load;
	float credit;
	char name[20];
	printf("开始读取信息……\n\n");
	while(!(feof(fr))){
		tempcour=(Course *)malloc(sizeof(Course));//????
		if(tempcour==NULL){
			printf("\n分配内存失败！\n");
			exit(0);
		}
		tempcour->next=NULL;
		fscanf(fr,"%s %d %f %d %d ",name,&type,&credit,&cap,&load);
		tempcour->name=(char *)malloc(sizeof(name)+1);
		strcpy(tempcour->name,name);//
		tempcour->cap=cap;
		tempcour->credit=credit;
		tempcour->type=(CourseType)(type);
		tempcour->load=load;

		cursor->next=tempcour;
		cursor=cursor->next;
	}
	printf("\n读取信息成功！\n");
	fclose(fr);
	return courlist;
}
void save_course(Course *courlist){
	Course *cursor;
	cursor=courlist;
	FILE *fw;
	fw=fopen(COURSEBOOK,"w");
	if(fw==NULL){
		printf("打开文件失败！请重试！\n");
		exit(0);
	}
	if(courlist!=NULL){
		cursor=cursor->next;
		do{
			fprintf(fw,"%s %d %.2f %d %d \n",cursor->name,cursor->type,cursor->credit,cursor->cap,cursor->load);
			cursor=cursor->next;
		}while(cursor!=NULL);
		fclose(fw);
	}else{
		printf("\n保存课程信息未保存！\n");exit(0);
	}
}
void modify_course(Course *courlist,char *name){
	char ch;
	int cap,type;
	float credit;
	Course *cursor,*temp;
	cursor=courlist;
	while(cursor->next&&strcmp(cursor->next->name,name)!=0)
		cursor=cursor->next;
	if(cursor->next){
		temp=cursor->next;
		do{
			print_course(temp,0);
			printf("\n请输入您要修改的内容：\n1-修改课容量\n");
			printf("2-修改课程类型\n3-修改课程学分\n0-保存退出\n");
			ch=getchar();fflush(stdin);
			switch(ch){
				case '1':
					printf("请正确输入修改后的课容量:");
					scanf("%d",&cap);fflush(stdin);
					if(cap<temp->load)printf("无效输入！课容量不能修改成比已选课人数少！\n");
					else
						temp->cap=cap;
					break;
				case '2':
					printf("请正确输入修改后的课程类型:");
					scanf("%d",&type);fflush(stdin);
					if(type>1||type<0)printf("无效输入！课程类型为0或者1！\n");
					else
						temp->type=(CourseType)(type);
					break;
				case '3':
					printf("请正确输入修改后的课程学分:");
					scanf("%f",&credit);fflush(stdin);
					if(credit<=0)printf("无效输入！课程学分不能小于0！\n");
					else
						temp->credit=credit;
					break;
				case '0':break;
				default:
					printf("无效输入，如果需要修改课程名，请直接删除该课程！\n");break;
			}
		}while(ch!='0');
		print_course(temp,0);printf("\n修改后的课程信息如上！\n");
	}else{
		printf("\n课程不存在，不需要修改！希望增加课程请前往开设新课！\n");
	}
}
void print_course(Course *courlist,int mode){
	Course *cursor;
	cursor=courlist;
	if(courlist!=NULL){
		printf("\n打印课程信息如下(课程类型0表示选修课，1表示必修课)：\n\n");
		printf("课程名\t\t类型\t学分\t课容量\t选课人数\n\n");
		if(mode){
			cursor=cursor->next;
			do{
				printf("%s\t\t%d\t%.2f\t%d\t%d\n",cursor->name,cursor->type,cursor->credit,cursor->cap,cursor->load);
				cursor=cursor->next;
			}while(cursor!=NULL);
		}else{
			printf("%s\t\t%d\t%.2f\t%d\t%d\n\n\n",cursor->name,cursor->type,cursor->credit,cursor->cap,cursor->load);
			if(cursor->load>0)
				sort_student(cursor->name,cursor->load);
		}
	}else{
		printf("\n打印课程信息失败！\n");
	}
}
void destroy_course(Course *courlist,int mode){
	Course *temp,*cursor;
	if(mode){
		cursor=courlist;
		while(cursor->next){
			temp=cursor->next;
			cursor->next=cursor->next->next;
			free(temp->name);
			free(temp);
		}
		free(courlist);
	}else{
		temp=courlist;
		free(temp->name);
		free(temp);
	}
}
