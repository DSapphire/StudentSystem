#ifndef __COURSE_H__
#define __COURSE_H__

#define COURSEBOOK "course.txt"

typedef enum coursetype{
	optional,
	compulsory
}CourseType;

// 

typedef struct course{
	char *name;
	CourseType type;//compulsory
	float credit;//
	int cap;//capacity
	int load;
	
	struct course *next;
}Course;
void menu_sub_course(Course *courlist);

Course * create_course(int n);
Course * insert_course(Course *courlist,Course *newcour);
Course * add_course(Course *courlist);
Course * delete_course(Course *courlist,char *name,int mode);
Course * read_course();
void save_course(Course *courlist);
void modify_course(Course *courlist,char *name);
void print_course(Course *courlist,int mode);


void destroy_course(Course *courlist,int mode);

void sort_course(Course *courlist);
void swap_course(Course *cour1,Course *cour2);
void update_course(Course *temp);
#endif
