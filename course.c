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
		printf("\n�����ڴ�ʧ�ܣ�\n");
		exit(0);
	}
	courlist->next=NULL;
	cursor=courlist;
	
	int i,tmptype,cap;
	float credit;
	char ch;
	char name[20];
	printf("����Ҫ����γ̵����� ���� ѧ�� ��������\n\n");
	for(i=0;i<n;i++){
		tempcour=(Course *)malloc(sizeof(Course));//????
		if(tempcour==NULL){
			printf("\n�����ڴ�ʧ�ܣ�\n");
			exit(0);
		}
		tempcour->next=NULL;
		
		do{
			reinput:
			printf("\n");
			printf("�����%d�ſγ̵����֣�",i+1);
			scanf("%s",name);fflush(stdin);
			printf("�����%d�ſγ����ͣ�������ѡ�޻��߱��ޣ��ֱ���0��1ָʾ����",i+1);
			scanf("%d",&tmptype);fflush(stdin);
			printf("�����%d�ſγ�ѧ�֣�",i+1);
			scanf("%f",&credit);fflush(stdin);
			printf("�����%d�ſγ̵Ŀ�������",i+1);
			scanf("%d",&cap);fflush(stdin);
			printf("\n������ĵ�%d�ſγ���\n�γ���:\t\t%s\n�γ����ͣ�\t%d\nѧ�֣�\t\t%.2f\n��������\t%d\n\n�޸�������N����n,�������������:",i+1,name,tmptype,credit,cap);
			ch=getchar();fflush(stdin);
		}while(ch=='N'||ch=='n');
		if(cap<0||tmptype>1||tmptype<0){
			printf("�������Ϳγ����������������������:\n");
			goto reinput;
		}else if(delete_course(courlist,name,0)!=NULL){//�γ����ظ����
			printf("\n�γ��Ѿ�������\n");
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
	printf("\n�γ̴����ɹ���\n");system("pause");
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
		printf("\nʧ��!\n");
		exit(0);
	}
	newcour->next=NULL;
	char name[20],ch;
	int cap,tmptype;
	float credit;
	printf("����Ҫ����γ̵����� ���� ѧ�� ��������\n\n");
	do{
		printf("\n");
		printf("����γ̵����֣�");
		scanf("%s",name);fflush(stdin);
		printf("����γ����ͣ�������ѡ�޻��߱��ޣ��ֱ���0��1ָʾ����");
		scanf("%d",&tmptype);fflush(stdin);
		printf("����γ�ѧ�֣�");
		scanf("%f",&credit);fflush(stdin);
		printf("����γ̵Ŀ�������");
		scanf("%d",&cap);fflush(stdin);
		printf("\n���������\n�γ���:\t\t%s\n�γ����ͣ�\t%d\nѧ�֣�\t\t%.2f\n��������\t%d\n\n�޸�������N����n,�������������:",name,tmptype,credit,cap);
		ch=getchar();fflush(stdin);
	}while(ch=='N'||ch=='n');
	if(cap<0||tmptype>1||tmptype<0){
		printf("�������Ϳγ������������\n");
		printf("��Ч���벻�����ģ��뷵�ز˵�����ѡ��\n");
		return courlist;
	}else if(delete_course(courlist,name,0)!=NULL){//�γ��ظ���� 
		printf("\n�γ��Ѿ����ڣ�����Ҫ�����������Ҫ�޸��뷵�ز˵�ǰ�� �޸Ŀγ̣�\n");
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
			if(temp->load){//��ʵҲ��ǿ��ɾ��ѧ�������ǲ��˵� 
				printf("\n�Ѿ���ѧ��ѡ�Σ�����ɾ���ÿγ̣������Ҫɾ���������˿Σ�\n"); 
			}else{
				destroy_course(temp,0);
				printf("\nɾ���ɹ�!\n");
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
		printf("\n�����ڴ�ʧ�ܣ�\n");
		exit(0);
	}
	courlist->next=NULL;
	cursor=courlist;
	FILE *fr;
	fr=fopen(COURSEBOOK,"r");
	if(fr==NULL){
		printf("�ļ���ʧ��!\n");
		exit(0);
	}
	
	int i,type,cap,load;
	float credit;
	char name[20];
	printf("��ʼ��ȡ��Ϣ����\n\n");
	while(!(feof(fr))){
		tempcour=(Course *)malloc(sizeof(Course));//????
		if(tempcour==NULL){
			printf("\n�����ڴ�ʧ�ܣ�\n");
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
	printf("\n��ȡ��Ϣ�ɹ���\n");
	fclose(fr);
	return courlist;
}
void save_course(Course *courlist){
	Course *cursor;
	cursor=courlist;
	FILE *fw;
	fw=fopen(COURSEBOOK,"w");
	if(fw==NULL){
		printf("���ļ�ʧ�ܣ������ԣ�\n");
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
		printf("\n����γ���Ϣδ���棡\n");exit(0);
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
			printf("\n��������Ҫ�޸ĵ����ݣ�\n1-�޸Ŀ�����\n");
			printf("2-�޸Ŀγ�����\n3-�޸Ŀγ�ѧ��\n0-�����˳�\n");
			ch=getchar();fflush(stdin);
			switch(ch){
				case '1':
					printf("����ȷ�����޸ĺ�Ŀ�����:");
					scanf("%d",&cap);fflush(stdin);
					if(cap<temp->load)printf("��Ч���룡�����������޸ĳɱ���ѡ�������٣�\n");
					else
						temp->cap=cap;
					break;
				case '2':
					printf("����ȷ�����޸ĺ�Ŀγ�����:");
					scanf("%d",&type);fflush(stdin);
					if(type>1||type<0)printf("��Ч���룡�γ�����Ϊ0����1��\n");
					else
						temp->type=(CourseType)(type);
					break;
				case '3':
					printf("����ȷ�����޸ĺ�Ŀγ�ѧ��:");
					scanf("%f",&credit);fflush(stdin);
					if(credit<=0)printf("��Ч���룡�γ�ѧ�ֲ���С��0��\n");
					else
						temp->credit=credit;
					break;
				case '0':break;
				default:
					printf("��Ч���룬�����Ҫ�޸Ŀγ�������ֱ��ɾ���ÿγ̣�\n");break;
			}
		}while(ch!='0');
		print_course(temp,0);printf("\n�޸ĺ�Ŀγ���Ϣ���ϣ�\n");
	}else{
		printf("\n�γ̲����ڣ�����Ҫ�޸ģ�ϣ�����ӿγ���ǰ�������¿Σ�\n");
	}
}
void print_course(Course *courlist,int mode){
	Course *cursor;
	cursor=courlist;
	if(courlist!=NULL){
		printf("\n��ӡ�γ���Ϣ����(�γ�����0��ʾѡ�޿Σ�1��ʾ���޿�)��\n\n");
		printf("�γ���\t\t����\tѧ��\t������\tѡ������\n\n");
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
		printf("\n��ӡ�γ���Ϣʧ�ܣ�\n");
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
