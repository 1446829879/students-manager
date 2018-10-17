#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"all.h"
extern kc *k;
extern stu *s;
kc* kc_read()
{
    FILE *fp;
    if((fp=fopen("manager.txt","r"))==NULL)
    {
        printf("can not open manager.txt\n");
        exit(0);
    }
    kc *head = (kc*)malloc(sizeof(kc));
    kc *p = head, *q;
    while(!feof(fp))
    {
        q = (kc*)malloc(sizeof(kc));
        fread(q,sizeof(kc),1,fp);
        p->next = q;
        p = p->next;
    }
    fclose(fp);
    p->next = NULL;
    return head;
}
int manager_login(char str[])
{
    FILE *fp;
    if((fp=fopen("password.txt","r"))==NULL)
    {
        printf("can not open file\n");
        exit(0);
    }
    char s[7] = {0};
    if(fread(s,sizeof(char),6,fp)==0)
    {
        printf("read file fail\n");
        exit(0);
    }
    if(strcmp(s,str)==0) return 1;
    else 
    {
        while(strcmp(s,str)!=0)
        {
            printf("*****password error and input again: ");
            gets(str);
        }
        return 1;
    }
}
int manager_menu()
{
    int menu;
    printf("\n*****管理员菜单:");
    printf("\n*****1:添加学生\n");
    printf("*****2:删除学生信息\n");
    printf("*****3:修改学生信息\n");
    printf("*****4:添加课程\n");
    printf("*****5:删除课程\n");
    printf("*****6:修改课程信息\n");
    printf("*****7:显示课程学生信息\n");
    printf("*****8:修改密码\n");
    printf("*****0:退出管理员管理\n");
    while(1)
    {
        printf("*****请输入选择: ");
        scanf("%d",&menu);
        getchar();
        printf("\n");
        if(menu>=0&&menu<11) break;
        else printf("error input and input again\n");
    }
    return menu;
}
void add_stu()
{
    stu *p, *q;
    p = s;
    printf("*****输入要添加的学生学号(输入0000停止添加): ");
    while(1)
    {
        q = (stu*)malloc(sizeof(stu));
        gets(q->id);
        if(strcmp(q->id,"0000") == 0) break;
        if(found_stu(q->id))
        {
            printf("the id is exist\n");
            break;
        }
        printf("*****输入学生姓名，学分：\n");
        scanf("%s",q->name);
        scanf("%d",&q->total_credits);
        getchar();
        q->num_cource = 0;
        p->next = q;
        p = p->next;
        p->next = NULL;
        printf("*****输入要添加的学生学号(输入0000停止添加): ");
        char str[100] = {0};
        strcat(str," 添加学生");
        strcat(str,q->name);
        write(str);
    }
}
void delete_stu()
{
    char a[15] = {0};
    printf("*****输入要删除的学生学号: ");
    gets(a);
    stu *p = s, *q;
    p = search_stu(a);
    if(p->next)
    {
        q = p->next;
        p->next = q->next;
        for(int i = 0; i < q->num_cource; i++)
            delete_cource(q->selected_cource_list[i]);
        char str[100] = {0};
        strcat(str,"删除学生");
        strcat(str,q->name);
        write(str);
        free(q);
        printf("*****删除成功\n");
    }
    
}
void modify_stu()
{
    char num[15] = {0};
    stu *p;
    printf("*****输入要修改的学生学号: ");
    gets(num);
    p = search_stu(num);
    p = p->next;
    printf("*****当前信息: \n");
    showall(num);
    printf("*****输入修改后的信息: ");
    scanf("%s%s%d",p->id,p->name,&p->total_credits);
    getchar();
    printf("*****修改成功\n");
    char str[100] = {0};
    strcat(str,"修改学生");
    strcat(str,p->name);
    write(str);
}
stu *search_stu(char str[]) //返回指定学号学生的前驱节点
{
    stu *p = s;
    while(p->next)
    {
        if(strcmp(p->next->id,str)==0) break;
        p = p->next;
    }
    if(!p->next) printf("*****没有该学号的学生的学生\n");
    else return p;
}
void add_kc()
{
    kc *p, *q;
    p = k;
    while(p->next)
    {
        p = p->next;
    }
    while(1)
    {
        printf("*****输入要添加课程的编号(输入0000停止添加): ");
        q = (kc*)malloc(sizeof(kc));
        gets(q->num);
        if(strcmp(q->num,"0000")==0) break;
        else
        {
            printf("输入课程名称，性质，学时，学分，人数上限：\n");
            scanf("%s%s%d%d%d",q->name,q->nature,&q->time,&q->credit,&q->stu_max);
            getchar();
            q->stu_sum = 0;
            p->next = q;
            p = p->next;
            p->next = NULL;
        }
        char str[100] = {0};
        strcat(str,"添加课程");
        strcat(str,q->name);
        write(str);
    }
}
void delete_kc()
{
    char a[15] = {0};
    kc *p;
    printf("*****输入要删除的课程: ");
    gets(a);
    p = search_kc(a); 
    for(int i = 0; i < p->stu_sum; i++)
        delete_cource(p->students[i]);
    char str[100] = {0};
    strcat(str,"删除课程");
    strcat(str,p->name);
    write(str);
    printf("*****删除成功\n");
}
void modify_kc()
{
    kc *p;
    char a[15] = {0};
    printf("*****输入要修改的课程名称: ");
    gets(a);
    p = search_kc(a);
    if(p)
    {
        printf("*****当前课程信息: ");
        print_kc(p);
        printf("输入课程名称，性质，学时，学分，人数上限：\n");
        scanf("%s%s%d%d%d",p->name,p->nature,&p->time,&p->credit,&p->stu_max);
        char str[100] = {0};
        strcat(str,"修改课程");
        strcat(str,p->name);
        write(str);
    }
}
kc *search_kc(char str[])
{
    kc *p = k->next;
    while(p)
    {
        if(strcmp(p->name,str)==0) break;
        p = p->next;
    }
    if(!p) printf("*****无此课程\n");
    else return p;
}
void print_kc(kc *p)
{
    printf("*****课程编号: %s\n",p->num);
    printf("*****课程名称: %s\n",p->name);
    printf("*****课程性质: %s\n",p->nature);
    printf("*****课程学时: %d\n",p->time);
    printf("*****课程学分: %d\n",p->credit);
    printf("*****课程已选人数: %d\n",p->stu_sum);
    printf("*****课程人数上限: %d\n",p->stu_max);
}
void showall_stu_kc()
{
    kc *p = k->next;
    char s[15] = {0};
    printf("*****输入要查看课程的名称: ");
    gets(s);
    p = search_kc(s);
    if(p)
    {
        print_kc(p);
        printf("*****选课学生：\n");
        for(int i = 0; i < p->stu_sum; i++)
        {   
            printf("%s ",p->students[i]);
            if(i % 5 == 0) printf("\n");
        }
    }
}
void modify_password()
{
    char s[15] = {0};
    char str[15] = {0};
    FILE *fp;
    if((fp=fopen("password.txt","r"))==0)
    {
        printf("open fail\n");
        exit(0);
    }
    fread(str,sizeof(char),6,fp);
    fclose(fp);
    printf("*****输入当前密码: ");
    while(1)
    {
        gets(s);
        if(strcmp(s,str)==0) break;
        else printf("password error and input again\n");
    }
    printf("*****输入新的密码: ");
    gets(s);
    if((fp=fopen("password.txt","w+"))==0)
    {
        printf("open fail\n");
        exit(0);
    }
    fwrite(s,sizeof(char),6,fp);
    fclose(fp);
    write("修改管理员密码");
}
void kc_write()
{
    FILE *fp;
    if((fp=fopen("manager.txt","w+"))==NULL)
    {
        printf("can not open file\n");
        exit(0);
    }
    rewind(fp);
    kc *p = k->next;
    while(p)
    {
        fwrite(p,sizeof(kc),1,fp);
        p = p->next;
    }
    fclose(fp);
}
void write(char str[])
{
    system("date>>log.log"); 
    FILE *fp;
    if((fp=fopen("log.log","a"))==0)
    {
        printf("open fail\n");
        exit(0);
    }
    if(fputs(str,fp)==0) printf("log write fail\n");
    fclose(fp);
}
