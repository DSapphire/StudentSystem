#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include"function.h"
#include"update.h"
#include"sort.h" 
#include"course.h"
#include"student.h"

void menu_course(){
	char ch,sch;
	int n;
	Course *courlist;
	do{
		fflush(stdin);
		printf("1-载入课程信息\t");printf("2-重新创建所有课程\n");printf("0-返回\n");printf("\n请选择操作类型：\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				courlist=read_course();
				printf("载入成功！");system("pause");
				menu_sub_course(courlist);
				break;
			case '2':
				do{
					printf("请输出创建课程数量：");
					scanf("%d",&n);fflush(stdin);
					printf("您输入的是%d？请输入N或者n修改，其他任意键继续：",n);
					sch=getchar();fflush(stdin);
					if(n<3){
						printf("\n无效输入，课程数量至少为3！因为必修课至少为3！\n");
						sch='n'; 
					}
				}while(sch=='n'||sch=='N');
				courlist=create_course(n);
				menu_sub_course(courlist);
				break;
			case '0':
				return; //
			default:
				printf("\n无效输入！请重新输入！\n");break;
		}
	}while(ch!='0');
}
void menu_sub_course(Course *courlist){
	print_course(courlist,1);
	Course *temp;
	char ch,sch,name[20];
	do{
		fflush(stdin);printf("\n操作类型：\n");printf("1-查找课程信息\t\t");printf("2-修改课程信息\n");
		printf("3-删除课程\t\t");printf("4-新增课程\n");printf("5-查课程热度\t\t");printf("6-成绩录入\n");
		printf("7-保存课程信息到文件\t");printf("0-返回.\n");printf("\n请输入操作类型数字序号：\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				do{
					printf("请输入需要查找的课程的课程名字：");
					scanf("%s",name);fflush(stdin);printf("\n您输入的是 %s ?",name);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				temp=delete_course(courlist,name,0);
				if(temp==NULL)
					printf("\n未找到！\n");
				else
					print_course(temp,0);
				break;
			case '2':
				do{
					printf("请输入需要修改的课程的课程名字：");
					scanf("%s",name);fflush(stdin);printf("\n您输入的是 %s ?",name);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				modify_course(courlist,name);
				break;
			case '3':
				do{
					printf("请输入需要删除的课程的课程名字：");
					scanf("%s",name);fflush(stdin);printf("\n您输入的是 %s ?",name);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				courlist=delete_course(courlist,name,1);
				break;
			case '4':
				courlist=add_course(courlist);
				break;
			case '5':
				sort_course(courlist);
				break;
			case '6':
				do{
					printf("请输入需要录入成绩的课程名字：");
					scanf("%s",name);fflush(stdin);printf("\n您输入的是 %s ?",name);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				temp=delete_course(courlist,name,0);
				if(temp==NULL)
					printf("\n课程不存在！\n");
				else{
					print_course(temp,0);
					update_course(temp);
				}
				break;
			case '7':
				save_course(courlist);
				printf("保存课程信息成功！\n");
				break;
			case '0':
				break;
			default:
				printf("\n无效输入！请重新输入！\n");break;
		}
	}while(ch!='0');
	printf("正在退出……信息保存中\n");system("pause");
	save_course(courlist);//最后保存课程信息 
	destroy_course(courlist,1);//把课程内存释放！ 

}

void menu_student(){
	char ch,sch;
	int n;
	Stu *stulist;
	do{
		fflush(stdin);
		printf("请选择操作类型：\n");printf("1-载入学生信息\t");printf("2-重新创建所有学生信息\n");printf("0-返回\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1': 
				stulist=read_student();
				menu_sub_student(stulist);
				break;
			case '2':
				printf("请输出学生人数：");
				do{
					scanf("%d",&n);fflush(stdin);
					printf("\n您输入的是 %d ？请输入N或者n修改，其他任意键继续：",n);
					sch=getchar();fflush(stdin);
					if(n<10){
						printf("\n无效输入，学生人数不少于10！\n");
						sch='n'; 
					}
				}while(sch=='n'||sch=='N');
				stulist=create_student(n);
				menu_sub_student(stulist);
				break;
			case '0':
				break;
			default:
				printf("\n无效输入！请重新输入！\n");break;
		}
	}while(ch!='0');
}
void menu_sub_student(Stu *stulist){
	print_student(stulist,1);
	Stu *temp;
	char ch,sch,no[5];
	do{
		fflush(stdin);printf("\n操作类型：\n");printf("1-查找学生信息\t\t");printf("2-修改学生信息（选课和退课）\n");
		printf("3-删除学生信息\t\t");printf("4-增加学生\n");printf("5-查看所有学生信息\n");printf("6-保存学生信息到文件\n");
		printf("0-退出.\n");printf("\n请输入操作类型数字序号：\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				do{
					printf("请输入需要查找的学生的学号：");
					scanf("%s",no);fflush(stdin);printf("\n您输入的是 %s ?",no);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("输入错误，学号为4位整数！");sch='n';
					}
				}while(sch=='n'||sch=='N');
				temp=delete_student(stulist,no,0);
				if(temp==NULL)
					printf("\n未找到！\n");
				else
					print_student(temp,0);
				system("pause");
				break;
			case '2':
				do{
					printf("请输入需要修改学生的学号：");
					scanf("%s",no);fflush(stdin);printf("\n您输入的是 %s ?",no);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("输入错误，学号为4位整数！");sch='n';
					}
				}while(sch=='n'||sch=='N');
				if(delete_student(stulist,no,0)!=NULL)
					modify_student(stulist,no);
				else
					printf("\n学号不存在！\n"); 
				break;
			case '3':
				do{
					printf("请输入需要删除的学生的学号：");
					scanf("%s",no);fflush(stdin);printf("\n您输入的是 %s ?",no);
					printf("\n请输入n或者N修改，其他任意键继续：");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("输入错误，学号为4位整数！");sch='n';
					}
				}while(sch=='n'||sch=='N');
				stulist=delete_student(stulist,no,1);
				break;
			case '4':
				stulist=add_student(stulist);
				break;
			case '5':
				print_student(stulist,1);
				break;
			case '6':
				save_student(stulist);system("pause");
				printf("保存学生信息成功！\n");
				break;
			case '0':
				break;
			default:
				printf("\n无效输入！请重新输入！\n");break;
		}
		
	}while(ch!='0');
	printf("正在退出……信息保存中\n");system("pause");
	save_student(stulist);
	destroy_student(stulist,1,1);//把学生内存释放！ 
}
//
// 
void backup(int mode){
	int c,ch;
	FILE *fr,*fw;
	if(mode){
		do{
			system("cls");
			printf("\n请输入备份内容：\n");printf("1-学生信息\n");printf("2-课程信息\n\n");printf("0-退出程序\n\n");
			ch=getchar();fflush(stdin);
			switch(ch){
				case '1':
					if ((fr=fopen(STUDENTBOOK,"r"))==NULL||(fw=fopen(SBACKUP,"w"))==NULL){
						printf("打开失败！\n");
		   				exit(1);
					}	
					break;
				case '2':
					if ((fr=fopen(COURSEBOOK,"r"))==NULL||(fw=fopen(CBACKUP,"w"))==NULL){
						printf("打开失败！\n");
		   				exit(1);
					}			
					break;
				case '0':
					exit(0);
				default:
					printf("\n错误输入！");break;
			}
			if(ch=='1'||ch=='2'){
				 while((c=fgetc(fr))!=EOF)
			       fputc(c,fw);
			    fclose(fr);fclose(fw);
			    printf("\n备份成功！需要使用备份的时候请手动修改文件名！\n");system("pause");
			}
		}while(ch!='1'&&ch!='2');	
	}else{
		if ((fr=fopen(STUDENTBOOK,"r"))==NULL||(fw=fopen(SBACKUP,"w"))==NULL){
			printf("打开失败！\n");
		   	exit(1);
		}
		while((c=fgetc(fr))!=EOF)
			fputc(c,fw);
		fclose(fr);fclose(fw);
		
		if ((fr=fopen(COURSEBOOK,"r"))==NULL||(fw=fopen(CBACKUP,"w"))==NULL){
			printf("打开失败！\n");
		   	exit(1);
		}
		while((c=fgetc(fr))!=EOF)
			fputc(c,fw);
	}
}
void menu(){
	char ch;
	do{
		system("cls");
		printf("请选择菜单选项：\n");printf("1-学生信息菜单\n");
		printf("2-课程信息菜单\n");printf("3-备份信息\n");printf("0-退出程序\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case'1':
				menu_student();
				break;
			case '2':
				menu_course();
				break;
			case '3':
				backup(1);
			case '0':
				break;
			default:
				printf("\n错误输入！请重新输入！\n");
		}
	}while(ch!='0');
}
