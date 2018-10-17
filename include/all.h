#ifndef _STU_H
#define _STU_H
#define max 10
typedef struct student //学生信息结构体
{
    char id[max]; //学号
    char name[max]; //姓名
    int num_cource; //已选的课程数
    char selected_cource_list[50][max]; //选择的课程
    int total_credits;    //总学分　　　　　
    struct student *next; 
}stu;
typedef struct cource
{
    char num[10];         //课程编号
    char name[10];   //课程名称
    char nature[10]; //课程性质
    int time;        //课程学时
    int credit;   //课程学分
    int stu_sum;     //课程已选人数
    int stu_max;     //课程人数上限
    char students[100][max]; //本课程的学生
    struct cource *next;
}kc;
void print_kc(kc *p);
stu* stu_read();
int stu_menu();
void showall(char str[]);
int found_stu(char str[]);
void delete_cource(char str[]);
void add_cource(char str[]);
int islimit(char s[], char n[]);
void stu_write();
void search_cource();

kc* kc_read();
int manager_login(char str[]);
int manager_menu();
void add_stu();
void delete_stu();
void modify_stu();
void delete_kc();
stu *search_stu(char str[]);
kc *search_kc(char str[]);
void add_kc();
void showall_stu_kc();
void modify_kc();
void modify_password();
void kc_write();
void write(char str[]);
#endif
