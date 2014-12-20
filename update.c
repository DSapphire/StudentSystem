#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"function.h"
#include"update.h"
#include"sort.h" 
#include"course.h"
#include"student.h"
void update_course(Course *ctemp){
	Stu* stulist,*stemp;
	char no[5],ch,sch;
	float *grade;grade=(float*)malloc(sizeof(float)*2);
	stulist=read_student();
	
	if(stulist==NULL){
		printf("\n读取学生信息失败！\n");
		return;
	}else
	do{
		do{
			printf("\n请输入您需要录入成绩的学生的学号，一次只能录入一个学生:");
			scanf("%s",no);fflush(stdin);
			printf("您输入的是  %s",no);
			printf("\n请输入n或者N修改，其他任意键继续：");
			sch=getchar();fflush(stdin);
		}while(sch=='n'||sch=='N');
		stemp=delete_student(stulist,no,0);
		if(stemp==NULL){
			printf("\n输入错误！学号不存在!\n");
		}else if(in_student(stemp,ctemp->name,grade,0)){
			printf("请输入您给学生的成绩：");
			scanf("%f",grade);fflush(stdin);//
			in_student(stemp,ctemp->name,grade,1);
		}else{
			printf("\n学生可能没有选这门课！\n");
		}
		printf("退出成绩录入系统请输入0，其他任意键继续：");
		ch=getchar();fflush(stdin);
	}while(ch!='0');
	save_student(stulist);
	destroy_student(stulist,1,1);
	free(grade);
}
void update_student(Stu *stemp,char mode){
	Course *courlist,*ctemp;float *grade=(float*)malloc(sizeof(float));//纯粹参数需要grade 
	char name[30],ch;
	int mycourse=0;
	FILE *fp;char cname[30];float credit;//
	courlist=read_course();
	if(mode=='1'){
		do{
			printf("请输入选课名称：");scanf("%s",name);fflush(stdin);
			printf("\n您输入的是%s？\n请输入n或者N修改，其他任意键继续：",name);
			ch=getchar();fflush(stdin);
		}while(ch=='n'||ch=='N');
		ctemp=delete_course(courlist,name,0);
		if(ctemp==NULL){
			printf("\n课程不存在！请重新输入！\n");
		}else if(in_student(stemp,name,grade,0)){
			for(mycourse=0;mycourse<stemp->mycourse;mycourse++){
				if(strcmp(name,(stemp->course[mycourse]).name)==0){
					printf("\n您已经选过这门课！\n");
					if((stemp->course[mycourse]).grade>60){
						printf("\n这门课已经通过！\n");
					}
					break;
				}	
			}
		}else{
			if(ctemp->cap<=ctemp->load){//
				printf("\n课容量已满，无法选课！\n");
			}else{
				if(ctemp->cap-ctemp->load<4)
					printf("\n课余量较小，请尽快完成选课！\n");
				
				if(stemp->course==NULL){
					stemp->course=(myCourse*)malloc(sizeof(myCourse));
					stemp->course->name=(char*)malloc(sizeof(name)+1);
					strcpy(stemp->course->name,name);
					stemp->course->credit=ctemp->credit;
					stemp->course->final=0;
					stemp->course->grade=0;
				}else{
					fp=fopen(TEMP,"w");
					for(mycourse=0;mycourse<stemp->mycourse;mycourse++)
						fprintf(fp,"%s %.2f %.2f %d \n",(stemp->course[mycourse]).name,(stemp->course[mycourse]).credit,(stemp->course[mycourse]).grade,(stemp->course[mycourse]).final);
					fclose(fp);
					destroy_student(stemp,0,1);
					read_stemp(stemp,1);
					stemp->mycourse++;
					(stemp->course[mycourse]).name=(char*)malloc(sizeof(name)+1);
					strcpy((stemp->course[mycourse]).name,name);
					(stemp->course[mycourse]).credit=ctemp->credit;
					(stemp->course[mycourse]).final=0;
					(stemp->course[mycourse]).grade=0;
				}
				ctemp->load++;// 
				printf("\n选课成功！\n");
			}
		}
	}else{
		do{
			printf("请输入退课名称：");scanf("%s",name);fflush(stdin);
			printf("\n您输入的是%s？\n请输入n或者N修改，其他任意键继续：",name);
			ch=getchar();fflush(stdin);
		}while(ch=='n'||ch=='N');
		ctemp=delete_course(courlist,name,0);
		if(ctemp==NULL){
			printf("\n课程不存在！请重新输入！\n");
		}else{
			if(stemp->course==NULL){
				printf("\n您没有选这门课程！"); 
			}else{
				char flag='n';int i;
				for(mycourse=0;mycourse<stemp->mycourse;mycourse++){
					if(strcmp(name,(stemp->course[mycourse]).name)==0){
						flag='y';
						i=mycourse;
						break;
					}	
				}
				if(flag=='n'){
					printf("\n您没有选这门课程！"); 
				}else{
					fp=fopen(TEMP,"w");
					for(mycourse=0;mycourse<stemp->mycourse;mycourse++){
						if(mycourse!=i)
						fprintf(fp,"%s %.2f %.2f %d \n",(stemp->course[mycourse]).name,(stemp->course[mycourse]).credit,(stemp->course[mycourse]).grade,(stemp->course[mycourse]).final);
					}
					fclose(fp);
					destroy_student(stemp,0,1);
					stemp->mycourse--;
					read_stemp(stemp,0);
					ctemp->load--;
					printf("\n退课成功！\n");				
				}
			}
		}
	}
	print_course(courlist,1);
	printf("学生信息如下\n");print_student(stemp,0);
	free(grade);
	save_course(courlist);//最后保存课程信息 
	destroy_course(courlist,1);//把课程内存释放！
}
void read_stemp(Stu *stemp,int mode){
	int mycourse;char cname[30];int final;float credit,grade;
	stemp->course=(myCourse*)malloc(sizeof(myCourse)*(stemp->mycourse+mode));
	FILE *fp=fopen(TEMP,"r");
	if(fp!=NULL)
	for(mycourse=0;mycourse<stemp->mycourse;mycourse++){
		fscanf(fp,"%s %f %f %d ",cname,&credit,&grade,&final);//
		(stemp->course[mycourse]).name=(char*)malloc(sizeof(cname));
		strcpy((stemp->course[mycourse]).name,cname);
		(stemp->course[mycourse]).credit=credit;
		(stemp->course[mycourse]).grade=grade;
		(stemp->course[mycourse]).final=final;
	}
	fclose(fp);
}

