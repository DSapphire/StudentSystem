#ifndef __STUDENT_H__
#define __STUDENT_H__


#define STUDENTBOOK "student.txt"


typedef struct{
	char *name;//
	float credit;
	float grade;
	int final;
}myCourse;
typedef struct student{
	char no[5];
	char *name;
	char *major;
	char sex[10];
	float gpa;
	int mycourse;
	myCourse *course;
	struct student *next;
}Stu;

void menu_sub_student(Stu *stulist);

Stu * create_student(int n);
Stu * insert_student(Stu *stulist,Stu *newstu);
Stu * add_student(Stu *stulist);
Stu * delete_student(Stu *stulist,char *no,int mode);
Stu * read_student();

void save_student(Stu *stulist);
void modify_student(Stu *stulist,char *no);
void print_student(Stu *stulist,int mode);

void destroy_student(Stu *stulist,int mode,int no);

void update_student(Stu *temp,char mode);
void read_stemp(Stu *stemp,int mode);
int in_student(Stu *temp,char *cname,float *grade,int mode);
#endif
