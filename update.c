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
		printf("\n��ȡѧ����Ϣʧ�ܣ�\n");
		return;
	}else
	do{
		do{
			printf("\n����������Ҫ¼��ɼ���ѧ����ѧ�ţ�һ��ֻ��¼��һ��ѧ��:");
			scanf("%s",no);fflush(stdin);
			printf("���������  %s",no);
			printf("\n������n����N�޸ģ����������������");
			sch=getchar();fflush(stdin);
		}while(sch=='n'||sch=='N');
		stemp=delete_student(stulist,no,0);
		if(stemp==NULL){
			printf("\n�������ѧ�Ų�����!\n");
		}else if(in_student(stemp,ctemp->name,grade,0)){
			printf("����������ѧ���ĳɼ���");
			scanf("%f",grade);fflush(stdin);//
			in_student(stemp,ctemp->name,grade,1);
		}else{
			printf("\nѧ������û��ѡ���ſΣ�\n");
		}
		printf("�˳��ɼ�¼��ϵͳ������0�����������������");
		ch=getchar();fflush(stdin);
	}while(ch!='0');
	save_student(stulist);
	destroy_student(stulist,1,1);
	free(grade);
}
void update_student(Stu *stemp,char mode){
	Course *courlist,*ctemp;float *grade=(float*)malloc(sizeof(float));//���������Ҫgrade 
	char name[30],ch;
	int mycourse=0;
	FILE *fp;char cname[30];float credit;//
	courlist=read_course();
	if(mode=='1'){
		do{
			printf("������ѡ�����ƣ�");scanf("%s",name);fflush(stdin);
			printf("\n���������%s��\n������n����N�޸ģ����������������",name);
			ch=getchar();fflush(stdin);
		}while(ch=='n'||ch=='N');
		ctemp=delete_course(courlist,name,0);
		if(ctemp==NULL){
			printf("\n�γ̲����ڣ����������룡\n");
		}else if(in_student(stemp,name,grade,0)){
			for(mycourse=0;mycourse<stemp->mycourse;mycourse++){
				if(strcmp(name,(stemp->course[mycourse]).name)==0){
					printf("\n���Ѿ�ѡ�����ſΣ�\n");
					if((stemp->course[mycourse]).grade>60){
						printf("\n���ſ��Ѿ�ͨ����\n");
					}
					break;
				}	
			}
		}else{
			if(ctemp->cap<=ctemp->load){//
				printf("\n�������������޷�ѡ�Σ�\n");
			}else{
				if(ctemp->cap-ctemp->load<4)
					printf("\n��������С���뾡�����ѡ�Σ�\n");
				
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
				printf("\nѡ�γɹ���\n");
			}
		}
	}else{
		do{
			printf("�������˿����ƣ�");scanf("%s",name);fflush(stdin);
			printf("\n���������%s��\n������n����N�޸ģ����������������",name);
			ch=getchar();fflush(stdin);
		}while(ch=='n'||ch=='N');
		ctemp=delete_course(courlist,name,0);
		if(ctemp==NULL){
			printf("\n�γ̲����ڣ����������룡\n");
		}else{
			if(stemp->course==NULL){
				printf("\n��û��ѡ���ſγ̣�"); 
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
					printf("\n��û��ѡ���ſγ̣�"); 
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
					printf("\n�˿γɹ���\n");				
				}
			}
		}
	}
	print_course(courlist,1);
	printf("ѧ����Ϣ����\n");print_student(stemp,0);
	free(grade);
	save_course(courlist);//��󱣴�γ���Ϣ 
	destroy_course(courlist,1);//�ѿγ��ڴ��ͷţ�
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

