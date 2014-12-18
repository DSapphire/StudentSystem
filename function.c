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
		printf("1-����γ���Ϣ\t");printf("2-���´������пγ�\n");printf("0-����\n");printf("\n��ѡ��������ͣ�\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				courlist=read_course();
				printf("����ɹ���");system("pause");
				menu_sub_course(courlist);
				break;
			case '2':
				do{
					printf("����������γ�������");
					scanf("%d",&n);fflush(stdin);
					printf("���������%d��������N����n�޸ģ����������������",n);
					sch=getchar();fflush(stdin);
					if(n<3){
						printf("\n��Ч���룬�γ���������Ϊ3����Ϊ���޿�����Ϊ3��\n");
						sch='n'; 
					}
				}while(sch=='n'||sch=='N');
				courlist=create_course(n);
				menu_sub_course(courlist);
				break;
			case '0':
				return; //
			default:
				printf("\n��Ч���룡���������룡\n");break;
		}
	}while(ch!='0');
}
void menu_sub_course(Course *courlist){
	print_course(courlist,1);
	Course *temp;
	char ch,sch,name[20];
	do{
		fflush(stdin);printf("\n�������ͣ�\n");printf("1-���ҿγ���Ϣ\t\t");printf("2-�޸Ŀγ���Ϣ\n");
		printf("3-ɾ���γ�\t\t");printf("4-�����γ�\n");printf("5-��γ��ȶ�\t\t");printf("6-�ɼ�¼��\n");
		printf("7-����γ���Ϣ���ļ�\t");printf("0-����.\n");printf("\n�������������������ţ�\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				do{
					printf("��������Ҫ���ҵĿγ̵Ŀγ����֣�");
					scanf("%s",name);fflush(stdin);printf("\n��������� %s ?",name);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				temp=delete_course(courlist,name,0);
				if(temp==NULL)
					printf("\nδ�ҵ���\n");
				else
					print_course(temp,0);
				break;
			case '2':
				do{
					printf("��������Ҫ�޸ĵĿγ̵Ŀγ����֣�");
					scanf("%s",name);fflush(stdin);printf("\n��������� %s ?",name);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				modify_course(courlist,name);
				break;
			case '3':
				do{
					printf("��������Ҫɾ���Ŀγ̵Ŀγ����֣�");
					scanf("%s",name);fflush(stdin);printf("\n��������� %s ?",name);
					printf("\n������n����N�޸ģ����������������");
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
					printf("��������Ҫ¼��ɼ��Ŀγ����֣�");
					scanf("%s",name);fflush(stdin);printf("\n��������� %s ?",name);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
				}while(sch=='n'||sch=='N');
				temp=delete_course(courlist,name,0);
				if(temp==NULL)
					printf("\n�γ̲����ڣ�\n");
				else{
					print_course(temp,0);
					update_course(temp);
				}
				break;
			case '7':
				save_course(courlist);
				printf("����γ���Ϣ�ɹ���\n");
				break;
			case '0':
				break;
			default:
				printf("\n��Ч���룡���������룡\n");break;
		}
	}while(ch!='0');
	printf("�����˳�������Ϣ������\n");system("pause");
	save_course(courlist);//��󱣴�γ���Ϣ 
	destroy_course(courlist,1);//�ѿγ��ڴ��ͷţ� 

}

void menu_student(){
	char ch,sch;
	int n;
	Stu *stulist;
	do{
		fflush(stdin);
		printf("��ѡ��������ͣ�\n");printf("1-����ѧ����Ϣ\t");printf("2-���´�������ѧ����Ϣ\n");printf("0-����\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1': 
				stulist=read_student();
				menu_sub_student(stulist);
				break;
			case '2':
				printf("�����ѧ��������");
				do{
					scanf("%d",&n);fflush(stdin);
					printf("\n��������� %d ��������N����n�޸ģ����������������",n);
					sch=getchar();fflush(stdin);
					if(n<10){
						printf("\n��Ч���룬ѧ������������10��\n");
						sch='n'; 
					}
				}while(sch=='n'||sch=='N');
				stulist=create_student(n);
				menu_sub_student(stulist);
				break;
			case '0':
				break;
			default:
				printf("\n��Ч���룡���������룡\n");break;
		}
	}while(ch!='0');
}
void menu_sub_student(Stu *stulist){
	print_student(stulist,1);
	Stu *temp;
	char ch,sch,no[5];
	do{
		fflush(stdin);printf("\n�������ͣ�\n");printf("1-����ѧ����Ϣ\t\t");printf("2-�޸�ѧ����Ϣ��ѡ�κ��˿Σ�\n");
		printf("3-ɾ��ѧ����Ϣ\t\t");printf("4-����ѧ��\n");printf("5-�鿴����ѧ����Ϣ\n");printf("6-����ѧ����Ϣ���ļ�\n");
		printf("0-�˳�.\n");printf("\n�������������������ţ�\n");
		ch=getchar();fflush(stdin);
		switch(ch){
			case '1':
				do{
					printf("��������Ҫ���ҵ�ѧ����ѧ�ţ�");
					scanf("%s",no);fflush(stdin);printf("\n��������� %s ?",no);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("�������ѧ��Ϊ4λ������");sch='n';
					}
				}while(sch=='n'||sch=='N');
				temp=delete_student(stulist,no,0);
				if(temp==NULL)
					printf("\nδ�ҵ���\n");
				else
					print_student(temp,0);
				system("pause");
				break;
			case '2':
				do{
					printf("��������Ҫ�޸�ѧ����ѧ�ţ�");
					scanf("%s",no);fflush(stdin);printf("\n��������� %s ?",no);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("�������ѧ��Ϊ4λ������");sch='n';
					}
				}while(sch=='n'||sch=='N');
				if(delete_student(stulist,no,0)!=NULL)
					modify_student(stulist,no);
				else
					printf("\nѧ�Ų����ڣ�\n"); 
				break;
			case '3':
				do{
					printf("��������Ҫɾ����ѧ����ѧ�ţ�");
					scanf("%s",no);fflush(stdin);printf("\n��������� %s ?",no);
					printf("\n������n����N�޸ģ����������������");
					sch='y';sch=getchar();fflush(stdin);
					if(strlen(no)!=4){
						printf("�������ѧ��Ϊ4λ������");sch='n';
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
				printf("����ѧ����Ϣ�ɹ���\n");
				break;
			case '0':
				break;
			default:
				printf("\n��Ч���룡���������룡\n");break;
		}
		
	}while(ch!='0');
	printf("�����˳�������Ϣ������\n");system("pause");
	save_student(stulist);
	destroy_student(stulist,1,1);//��ѧ���ڴ��ͷţ� 
}
//
// 
void backup(int mode){
	int c,ch;
	FILE *fr,*fw;
	if(mode){
		do{
			system("cls");
			printf("\n�����뱸�����ݣ�\n");printf("1-ѧ����Ϣ\n");printf("2-�γ���Ϣ\n\n");printf("0-�˳�����\n\n");
			ch=getchar();fflush(stdin);
			switch(ch){
				case '1':
					if ((fr=fopen(STUDENTBOOK,"r"))==NULL||(fw=fopen(SBACKUP,"w"))==NULL){
						printf("��ʧ�ܣ�\n");
		   				exit(1);
					}	
					break;
				case '2':
					if ((fr=fopen(COURSEBOOK,"r"))==NULL||(fw=fopen(CBACKUP,"w"))==NULL){
						printf("��ʧ�ܣ�\n");
		   				exit(1);
					}			
					break;
				case '0':
					exit(0);
				default:
					printf("\n�������룡");break;
			}
			if(ch=='1'||ch=='2'){
				 while((c=fgetc(fr))!=EOF)
			       fputc(c,fw);
			    fclose(fr);fclose(fw);
			    printf("\n���ݳɹ�����Ҫʹ�ñ��ݵ�ʱ�����ֶ��޸��ļ�����\n");system("pause");
			}
		}while(ch!='1'&&ch!='2');	
	}else{
		if ((fr=fopen(STUDENTBOOK,"r"))==NULL||(fw=fopen(SBACKUP,"w"))==NULL){
			printf("��ʧ�ܣ�\n");
		   	exit(1);
		}
		while((c=fgetc(fr))!=EOF)
			fputc(c,fw);
		fclose(fr);fclose(fw);
		
		if ((fr=fopen(COURSEBOOK,"r"))==NULL||(fw=fopen(CBACKUP,"w"))==NULL){
			printf("��ʧ�ܣ�\n");
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
		printf("��ѡ��˵�ѡ�\n");printf("1-ѧ����Ϣ�˵�\n");
		printf("2-�γ���Ϣ�˵�\n");printf("3-������Ϣ\n");printf("0-�˳�����\n");
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
				printf("\n�������룡���������룡\n");
		}
	}while(ch!='0');
}
