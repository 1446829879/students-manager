#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"all.h"
extern stu *s;
extern kc *k;
stu* stu_read()
{
    FILE *fp;
    if((fp=fopen("stu.txt","r"))==NULL)
    {
        printf("can not open stu.txt\n");
        exit(0);
    }
    stu *head = (stu*)malloc(sizeof(stu));
    stu *p = head, *q;
    while(!feof(fp))
    {
        q = (stu*)malloc(sizeof(stu));
        fread(q,sizeof(stu),1,fp);
        p->next = q;
        p = p->next;
    }
    fclose(fp);
    p->next = NULL;
    return head;
}
int stu_menu()
{
    int menu;
    printf("\n******学生菜单\n");
    printf("*****1:查看所有课程信息\n");
    printf("*****2:查看某一课程信息\n");
    printf("*****3:删除课程\n");
    printf("*****4:添加课程\n");
    printf("*****0:退出\n");
    while(1)
    {
        printf("*****请输入选择: ");
        scanf("%d",&menu);
        getchar();
        printf("\n");
        if(menu>=0&&menu<6) break;
        else printf("*****error input, please input again\n");
    }
    return menu;
}
int found_stu(char str[])
{
    stu *p = s->next;
    while(p)
    {
        if(strcmp(p->id,str)==0) break;
        else p = p->next;
    }
    if(!p) return 0;
    else return 1;
}
void showall(char str[])
{
    stu *p = s->next;
    while(p)
    {
        if(strcmp(p->id,str)==0) break;
        else p = p->next;
    }
    printf("\n学号%s\n",p->id);
    printf("姓名%s\n",p->name);
    printf("已选%d门课程",p->num_cource);
    for(int i = 0; i < p->num_cource; i++)
    {
        printf("%s ",p->selected_cource_list[i]);
    }
    printf("\n总学分：%d\n",p->total_credits);
}
void search_cource()
{
    kc *p;
    char s[15] = {0};
    printf("*****输入要查看课程的名称: ");
    gets(s);
    p = search_kc(s);
    if(p) print_kc(p);
}
void delete_cource(char str[])
{
    stu *p = s->next;
    kc *q = k->next;
    char s[15] = {0};
    while(p)
    {
        if(strcmp(p->id,str)==0 || strcmp(p->name,str)==0) break;
        p = p->next;
    }
    if(strcmp(p->id,str)==0)
    {
        printf("*****输入要删除的课程: ");
        gets(s);
    }
    q = search_kc(s);
    if(q)
    {
        int i;
        for(i = 0; i < p->num_cource; i++)
            if(strcmp(s,p->selected_cource_list[i])==0) break;
        char t[15] = {0};
        strcpy(t,s);
        strcpy(s,p->selected_cource_list[i]);
        strcpy(p->selected_cource_list[i],t);
        p->num_cource--;
        for(i = 0; i < q->stu_sum; i++)
            if(strcmp(q->students[i],p->name)==0) break;
        int x = q->stu_sum - 1;
        strcpy(t,q->students[i]);
        strcpy(q->students[i],q->students[x]);
        strcpy(q->students[x],t);
        q->stu_sum--;
    }
}
void add_cource(char str[])
{
    stu *p = s;
    char s[10] = {0};
    int n;
    while(p)
    {
        if(strcmp(p->id,str) == 0) break;
        else p = p->next;
    }
    if(!p) printf("not fount %s\n",str);
    else
    {
        while(1)
        {
            printf("*****输入添加课程名称(输入0000停止添加): ");
            gets(s);
            if(strcmp(s,"0000")==0) break;
            if(islimit(s,p->name))
            {
                int x = p->num_cource;
                strcpy(p->selected_cource_list[x],s);
                p->num_cource ++;
                printf("*****添加成功！\n");
            }
        }
    }
}
int islimit(char s[], char n[])
{
    kc *p;
    p = k->next;
    while(p)
    {
        if(strcmp(s,p->name)==0) break;
        p = p->next;
    }
    if(!p) 
    {
        printf("*****无此课程\n");
        return 0;
    }
    else
    {
        if(p->stu_sum == p->stu_max) 
        {
            printf("*****人数已满\n");
            return 0;
        }
        else 
        {
            strcpy(p->students[p->stu_sum],n);
            p->stu_sum++;
            return 1;
        }
    }
}
void stu_write()
{

    FILE *fp;
    if((fp=fopen("stu.txt","w+"))==NULL)
    {
        printf("can not open stu.txt\n");
        exit(0);
    }
    stu *p = s->next;
    while(p)
    {
        fwrite(p,sizeof(stu),1,fp);
        p = p->next;
    }
    fclose(fp);
}
